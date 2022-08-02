#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _EXTEND 3

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

// custom keycodes
#define VIM MT(MOD_LCTL, KC_ESC)
#define NAV_TAB LT(_RAISE, KC_TAB)
#define SYM_ENT LT(_LOWER, KC_ENT)
#define EXTEND TG(_EXTEND) 

// #define HO_S MT(MOD_LALT,KC_S)
// #define HO_T MT(MOD_LGUI,KC_T)
// #define HO_N MT(MOD_RGUI,KC_N)
// #define HO_E MT(MOD_RALT,KC_E)

enum custom_keycodes {
    // repeat last key
    REPEAT = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  , KC_DEL,
        KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  , KC_SCLN,KC_MINS,
        VIM,     KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_M  , KC_N  , KC_E  , KC_I  , KC_O,   KC_QUOT,
        KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,                         KC_K  , KC_H  , KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                         KC_LBRC,KC_RBRC,                                                        KC_PLUS, KC_EQL,
                                         NAV_TAB,KC_SPC,                         KC_BSPC, SYM_ENT,
                                         REPEAT,KC_LEAD,                         KC_END,  KC_DEL,
                                         KC_BSPC, KC_GRV,                        EXTEND, KC_LGUI
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
                          QK_BOOT,_______,                                                      KC_EQL , QK_BOOT,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______
    ),

    [_EXTEND] = LAYOUT_5x6(
        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        _______,_______,_______,_______,_______,_______,                        _______,KC_WBAK,KC_MS_U,KC_WFWD,_______,_______,
        _______,_______,_______,_______,_______,_______,                        _______,KC_MS_L,KC_MS_D,KC_MS_R,_______,_______,
        _______,_______,KC_CUT,KC_COPY,KC_PSTE,_______,                        _______,KC_BTN3,KC_WH_D,KC_WH_U,_______,_______,
                       _______,_______,                                                        _______,_______,
                                        _______,_______,                        KC_BTN1,KC_BTN2,
                                        _______,_______,                        KC_BTN3,_______,
                                        _______,_______,                        _______,_______
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
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    return true;
};

// use leader key with i3 window manager
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    // TODO move to sxhkd with MOD_MEH
    // i3 focus left
    SEQ_ONE_KEY(KC_N) {
      SEND_STRING(SS_LALT("h"));
    }
    // i3 move left
    SEQ_TWO_KEYS(KC_N, KC_N) {
      SEND_STRING(SS_LALT(SS_LSFT("h")));
    }
    
    // i3 focus right
    SEQ_ONE_KEY(KC_I) {
      SEND_STRING(SS_LALT("l"));
    }
    // i3 move right
    SEQ_TWO_KEYS(KC_I, KC_I) {
      SEND_STRING(SS_LALT(SS_LSFT("l")));
    }

    // i3 focus up
    SEQ_ONE_KEY(KC_U) {
      SEND_STRING(SS_LALT("k"));
    }
    // i3 move up
    SEQ_TWO_KEYS(KC_U, KC_U) {
      SEND_STRING(SS_LALT(SS_LSFT("k")));
    }

    // i3 focus down
    SEQ_ONE_KEY(KC_E) {
      SEND_STRING(SS_LALT("j"));
    }
    // i3 move down
    SEQ_TWO_KEYS(KC_E, KC_E) {
      SEND_STRING(SS_LALT(SS_LSFT("j")));
    }

    // i3 open flameshot
    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_LALT("s"));
    }
  }
}
