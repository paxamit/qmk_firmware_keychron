/* Copyright 2023 ~ 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

#ifdef LK_WIRELESS_ENABLE
#    include "transport.h"
#    include "keychron_wireless_common.h"
#endif

#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl

/* Transport-based RGB colors (hue, saturation — brightness is preserved) */
#define TP_24G_HUE  152   /* Blue */
#define TP_24G_SAT  255
#define TP_BT_HUE   190   /* Purple-ish for BT, just in case */
#define TP_BT_SAT   255

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

/* Custom keycode for toggling transport: USB ↔ 2.4G */
enum custom_keycodes_user {
    KC_TP_TOG = NEW_SAFE_RANGE,
};

#ifdef LK_WIRELESS_ENABLE
void matrix_scan_user(void) {
    static transport_t last_tp = TRANSPORT_USB;
    transport_t current_tp = get_transport();
    
    if (current_tp != last_tp) {
        if (current_tp == TRANSPORT_USB) {
            /* Restore user's preferred saved color for USB mode */
            rgb_matrix_reload_from_eeprom();
        }
        last_tp = current_tp;
    }

    /* Enforce custom colors for wireless modes. 
     * Keychron's indicator.c reloads EEPROM after blinking, which can wipe our custom color 
     * and leave the backlight black. This ensures it stays the correct color. */
    if (rgb_matrix_is_enabled()) {
        if (current_tp == TRANSPORT_P2P4) {
            if (rgb_matrix_get_hue() != TP_24G_HUE || rgb_matrix_get_sat() != TP_24G_SAT) {
                rgb_matrix_sethsv_noeeprom(TP_24G_HUE, TP_24G_SAT, rgb_matrix_get_val());
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            }
        } else if (current_tp == TRANSPORT_BLUETOOTH) {
            if (rgb_matrix_get_hue() != TP_BT_HUE || rgb_matrix_get_sat() != TP_BT_SAT) {
                rgb_matrix_sethsv_noeeprom(TP_BT_HUE, TP_BT_SAT, rgb_matrix_get_val());
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            }
        }
    }
}
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_TP_TOG,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        CTL_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_HYPR,  KC_LGUI,  KC_LALT,                        LT(WIN_FN,KC_SPC),                              KC_RALT,  KC_INS,   KC_DEL,   KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_82(
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            RGB_TOG,
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  KC_PGUP,  KC_HOME,  KC_PGDN,  KC_PSCR,  _______,  _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, KC_INS,   KC_DELETE,          _______,            KC_END,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  KC_END,   _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

void keyboard_post_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

#ifdef LK_WIRELESS_ENABLE
    switch (keycode) {
        case KC_TP_TOG:
            if (record->event.pressed) {
                /* Toggle transport: USB ↔ 2.4G */
                transport_t current = get_transport();
                transport_t next;
                if (current == TRANSPORT_P2P4) {
                    next = TRANSPORT_USB;
                } else {
                    next = TRANSPORT_P2P4;
                }
                set_transport_soft_override(next);
            }
            return false;
    }
#endif

    return true;
}
