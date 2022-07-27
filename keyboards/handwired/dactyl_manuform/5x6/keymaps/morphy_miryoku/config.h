// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define XXX KC_NO
#define ADV MT(MOD_LCTL,KC_ESC)

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                         K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                         K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                         K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                         K35, K36, K37, N38, N39 \
) \
LAYOUT_5x6( \
KC_F1,    KC_F2, KC_F3, KC_F4, KC_F5,KC_F6,                           KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
KC_PGUP,  K00,   K01,   K02,   K03,  K04,                             K05,   K06,   K07,   K08,  K09,  KC_MINS, \
ADV,      K10,   K11,   K12,   K13,  K14,                             K15,   K16,   K17,   K18,  K19,  KC_QUOT, \
KC_PGDN,  K20,   K21,   K22,   K23,  K24,                             K25,   K26,   K27,   K28,  K29,  KC_BSLASH, \
                 XXX, K32,                                                  K37, XXX, \
                                K34, K33,                          K36, K35, \
                                          KC_LEAD, XXX,         XXX, XXX, \
                                          XXX, XXX,         XXX, XXX \
)

