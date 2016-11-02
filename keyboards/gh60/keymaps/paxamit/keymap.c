#include "gh60.h"
#include "action_layer.h"
 

#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl

#define KEYMAP_ANSI_60( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
    K40, K41, K42,           K45,                     K4A, K4B, K4C, K4D  \
) { \
    { K00, K01,   K02, K03,   K04,   K05, K06,   K07,   K08,   K09,   K0A, K0B, K0C,   K0D }, \
    { K10, K11,   K12, K13,   K14,   K15, K16,   K17,   K18,   K19,   K1A, K1B, K1C,   K1D }, \
    { K20, K21,   K22, K23,   K24,   K25, K26,   K27,   K28,   K29,   K2A, K2B, KC_NO, K2D }, \
    { K30, KC_NO, K32, K33,   K34,   K35, K36,   K37,   K38,   K39,   K3A, K3B, KC_NO, K3D }, \
    { K40, K41,   K42, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, KC_NO, K4A, K4B, K4C,   K4D }  \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP_ANSI_60(
	    KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,   KC_5,   KC_6,   KC_7,   KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,   KC_Y,   KC_U,   KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
        CTL_ESC, KC_A,    KC_S,    KC_D,  KC_F,   KC_G,   KC_H,   KC_J,   KC_K, KC_L,    KC_SCLN, KC_QUOT,          KC_ENT, \
        KC_LSFT,          KC_Z,    KC_X,  KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, \
        KC_FN0,  KC_LGUI, KC_LALT,                KC_FN2,                                KC_RALT, KC_FN0,  KC_FN3,  KC_FN4),
    /* 1: fn */
	KEYMAP(
        TRNS,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11,   F12,DELETE, \
        TRNS,MPRV,MPLY,MNXT,TRNS,TRNS,TRNS,PGUP,HOME,PGDN,PSCR,TRNS,  TRNS,  TRNS, \
        TRNS,TRNS,MUTE,PGDN,TRNS,TRNS,LEFT,DOWN,  UP,RGHT, INS,DELETE,TRNS,  TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, END,TRNS,TRNS,  TRNS,  TRNS, \
        TRNS,TRNS,TRNS,          TRNS,               TRNS,TRNS,TRNS,  TRNS,  TRNS),
    
	KEYMAP(
        TRNS,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,               TRNS,TRNS,TRNS,TRNS,TRNS),

	KEYMAP(
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          SPACE,              TRNS,TRNS,TRNS,TRNS,TRNS),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [1] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [2] = ACTION_LAYER_TAP_KEY(1, KC_SPACE),
    [3] = ACTION_LAYER_TOGGLE(2),
    [4] = ACTION_LAYER_TOGGLE(3),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
//// MACRODOWN only works in this function
//      switch(id) {
//        case 0:
//          if (record->event.pressed) {
//            register_code(KC_RSFT);
//          } else {
//            unregister_code(KC_RSFT);
//          }
//        break;
//      }
    return MACRO_NONE;
};

void matrix_scan_user(void) {

//Layer LED indicators
    uint32_t layer = layer_state;

	
   if (layer & (1<<2)) 
   {
        gh60_esc_led_on();
   }
   else
   {
        gh60_esc_led_off();
   }

   if (layer & (1<<3)) 
   {
       gh60_wasd_leds_on();
   } 
   else 
   {
       gh60_wasd_leds_off();
   }
};
