#include QMK_KEYBOARD_H
#include "features/select_word.h"
#include "raw_hid.h"
#include "action_layer.h"

#define _BASE 0
#define _SYMBOL 1
#define _EXTEND 2
#define _QWERTY 3

// custom keycodes
#define ADV_VIM LT(_EXTEND, KC_ESC)
#define NAV_TAB LT(_EXTEND, KC_TAB)
#define SYM_ENT LT(_SYMBOL, KC_ENT)
#define SPC_ALT MT(MOD_LALT, KC_SPACE)
#define CTL_BSP MT(MOD_LCTL, KC_BSPC)
#define EXTEND TG(_EXTEND)
#define QWERTY TG(_QWERTY)

// TODO better home row mods https://www.reddit.com/r/ErgoMechKeyboards/comments/weipet/my_homerow_mods_alternative/
// #define HO_S MT(MOD_LALT,KC_S)
// #define HO_T MT(MOD_LGUI,KC_T)
// #define HO_N MT(MOD_RGUI,KC_N)
// #define HO_E MT(MOD_RALT,KC_E)

#define CC_UNDO LCTL(KC_Z)
#define CC_REDO LCTL(KC_Y)
#define CC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)

// macros
bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
enum custom_keycodes {
    UPDIR = SAFE_RANGE,
    PWDIR,
    GITST,
    GITGP,
    REPEAT,
    TMUXESC,
    SRCHSEL,
    JOINLN,
    COPY_PASTA,
    SELWORD,
    ALT_TAB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_5x6(
        KC_GRV , KC_7  , KC_8  , KC_9  , KC_0  , KC_5  ,                         KC_6  , KC_1  , KC_2  , KC_3  , KC_4   ,KC_DEL,
        KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  , KC_SCLN,KC_MINS,
        ADV_VIM, KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_M  , KC_N  , KC_E  , KC_I  , KC_O,   KC_QUOT,
        KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,                         KC_K  , KC_H  , KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                         KC_LBRC,KC_RBRC,                                                        KC_PLUS, KC_EQL,
                                         NAV_TAB,SPC_ALT,                        CTL_BSP, SYM_ENT,
                                         REPEAT, KC_LEAD,                        KC_END,  KC_DEL,
                                         KC_BSPC,KC_GRV,                         EXTEND, QWERTY
    ),

    [_SYMBOL] = LAYOUT_5x6(
        _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F5  ,                       KC_F6  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F11 ,    
        _______, KC_QUOT, KC_LABK, KC_RABK, KC_DQUO, KC_DOT ,                       KC_AMPR, _______  , KC_LBRC, KC_RBRC, KC_PERC, KC_F12 ,    
        _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL , KC_HASH,                       KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES, TO(_EXTEND), 
        _______, KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, UPDIR,                         KC_TILD, KC_DLR , KC_LCBR, KC_RCBR, KC_AT  , _______,    
                        C(KC_END), C(KC_HOME),                                                      KC_HOME, KC_END , 
                                         _______,SRCHSEL,                        _______,_______,
                                         _______,_______,                        _______,_______,
                                         _______,_______,                        _______,_______

    ),

    [_EXTEND] = LAYOUT_5x6(
          _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______, 
          KC_WH_U,SELWORD,KC_WBAK,KC_MS_U,KC_WFWD,_______,                        JOINLN,_______,KC_UP,_______,_______,ALT_TAB,                          
          _______,_______,KC_MS_L,KC_MS_D,KC_MS_R,_______,                        _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,                        
          KC_WH_D,CC_UNDO,CC_REDO,CC_CUT,_______,COPY_PASTA,                      _______,_______,_______,_______,_______,TMUXESC,
                           UPDIR,PWDIR,                                                     GITST,GITGP,
                                        KC_BTN1,KC_BTN2,                        _______,_______,                        
                                        KC_BTN3,_______,                        _______,_______,                        
                                        _______,_______,                        _______,_______
    ),
  /*https://type-fu.com/app */
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                         KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                         KC_NO,KC_SPC,                           KC_BSPC, KC_ENT,
                                         KC_TAB,KC_HOME,                         KC_END,  KC_DEL,
                                         KC_BSPC, KC_GRV,                        KC_LGUI, QWERTY
    )
};

// https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131
// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode  = KC_NO;
uint8_t  last_modifier = 0;

// Initialize variables holding the bitfield
// representation of active modifiers.
uint8_t mod_state;
uint8_t oneshot_mod_state;

void process_repeat_key(uint16_t keycode, const keyrecord_t* record) {
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

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // if (!process_achordion(keycode, record)) { return false; }
    // if (!process_autocorrection(keycode, record)) { return false; }
    // if (!process_custom_shift_keys(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) {
        return false;
    }
    process_repeat_key(keycode, record);
    mod_state         = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    switch (keycode) {
        case COPY_PASTA:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));
            } else {
                SEND_STRING(SS_LCTL("v"));
            }
            break;
        case UPDIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;

        case PWDIR: // pwd
            if (record->event.pressed) {
                SEND_STRING("pwd\r\n");
            }
            return false;

        case GITST: // git status
            if (record->event.pressed) {
                SEND_STRING("gs\r\n");
            }
            return false;

        case GITGP: // git status
            if (record->event.pressed) {
                SEND_STRING("gp\r\n");
            }
            return false;

        case TMUXESC: // Enter copy mode in Tmux.
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("a") SS_TAP(X_ESC));
            }
            return false;

        case SRCHSEL: // Searches the current selection in a new tab.
            if (record->event.pressed) {
                // Mac users, change LCTL to LGUI.
                SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER));
            }
            return false;

        case JOINLN: // Join lines like Vim's `J` command.
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_END) SS_TAP(X_DEL) SS_TAP(X_SPC) SS_LCTL(SS_TAP(X_RGHT) SS_TAP(X_LEFT) SS_LSFT(SS_TAP(X_LEFT) SS_TAP(X_RGHT))) SS_TAP(X_SPC));
            }
            return false;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

// use leader key with i3 window manager
LEADER_EXTERNS();

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        // TODO move to sxhkd with MOD_MEH

        // i3 new terminal
        SEQ_TWO_KEYS(KC_N, KC_E) {
            SEND_STRING(SS_LALT(SS_TAP(X_ENTER)));
        }
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

// allow neovim lua api to toggle into _BASE when entering insert mode 
// and toggle to _QWERTY in command mode
// luahidapi
void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    switch (*command_id) {
        case 0:
          // TG(_BASE);
          layer_state_set(0);
          break;
        case 1:
          // TG(_QWERTY);
          layer_state_set(3);
          break;
    }
}
