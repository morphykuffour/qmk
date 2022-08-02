#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

// custom TODO micmic precondition dactyl layout
#define ADV MT(MOD_LCTL, KC_ESC)
#define NAV MT(RAISE, KC_TAB) // TODO fix
#define SYM MT(LOWER, KC_ENT) // TODO fix

#define HO_S MT(MOD_LALT,KC_S)
#define HO_T MT(MOD_LGUI,KC_T)
#define HO_N MT(MOD_RGUI,KC_N)
#define HO_E MT(MOD_RALT,KC_E)

// interact with keyd with KC_LEAD

// repeat last key
enum custom_keycodes {
    // it can be called REP if you want but "REPEAT" is clearer and still fits under the 8 char "limit"
    REPEAT = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_DEL,
        KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  , KC_SCLN,KC_MINS,
        ADV,     KC_A  , KC_R  , HO_S  , HO_T  , KC_G  ,                         KC_M  , HO_N  , HO_E  , KC_I  ,KC_O,KC_QUOT,
        KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,                         KC_K  , KC_H  , KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                         KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                         RAISE,KC_SPC,                             KC_BSPC, LOWER,
                                         REPEAT,KC_LEAD,                         KC_END,  KC_DEL,
                                         KC_BSPC, KC_GRV,                        KC_LGUI, KC_LALT
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                         _______,KC_PSCR,                                                       _______, KC_P0,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______

    ),

    [_RAISE] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
          _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
          _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
                          QK_BOOT,_______,                                                      KC_EQL ,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______
    )
};

// https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131 
// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;

// Initialize variables holding the bitfield
// representation of active modifiers.
uint8_t mod_state;
uint8_t oneshot_mod_state;

void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != REPEAT) {
        // Early return when holding down a pure layer key
        // to retain modifiers
        switch (keycode) {
            case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                return;
        }
        last_modifier = oneshot_mod_state > mod_state ? oneshot_mod_state : mod_state;
        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->event.pressed) {
                    last_keycode = GET_TAP_KC(keycode);
                }
                break;
            default:
                if (record->event.pressed) {
                    last_keycode = keycode;
                }
                break;
        }
    } else { // keycode == REPEAT
        if (record->event.pressed) {
            register_mods(last_modifier);
            register_code16(last_keycode);
        } else {
            unregister_code16(last_keycode);
            unregister_mods(last_modifier);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_repeat_key(keycode, record);
    // It's important to update the mod variables *after* calling process_repeat_key, or else
    // only a single modifier from the previous key is repeated (e.g. Ctrl+Shift+T then Repeat produces Shift+T)
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    return true;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // // Replace the sequences below with your own sequences.
    // SEQ_ONE_KEY(KC_T) {
    //   // When I press KC_LEAD and then T, this sends CTRL + SHIFT + T
    //   SEND_STRING(SS_LCTRL(SS_LSFT("t")));
    // }
    // // Note: This is not an array, you don't need to put any commas
    // // or semicolons between sequences.
    // SEQ_TWO_KEYS(KC_N, KC_T) {
    //   // When I press KC_LEAD and then N followed by T, this sends CTRL + T
    //   SEND_STRING(SS_LCTRL("t"));
    // }
    
    // open flameshot
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_LALT("s"));
    }
  }
}
