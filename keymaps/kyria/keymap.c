#include "waffle.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_stack_of_waffles(
    KC_NO, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,
    KC_NO, HRML(KC_A, KC_S, KC_D, KC_F), KC_G,
    KC_NO, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, LINKS, KC_NO,
                  KC_NO, UPDIR, ESCLWR,   KC_SPC,   KC_NO,

                    KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_NO,
                    KC_H, HRMR(KC_J, KC_K, KC_L, KC_SCLN), KC_NO,
    KC_NO, KC_MPLY, KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_NO,
    KC_NO, KC_BSPC, PSTRSE, PNP, KC_NO
  ),

  [_LOWER] = LAYOUT_stack_of_waffles(
    KC_TRNS, KC_1,    KC_2 ,  KC_3,     KC_4,     KC_5,
    KC_TRNS, HRML(KC_EXLM, KC_AT, KC_HASH, KC_DLR),  KC_PERC,
    KC_TRNS, KC_TRNS, KC_TAB, KC_CAPS,  KC_TILD,  KC_GRV,  KC_TRNS, KC_TRNS,
                              KC_TRNS,  KC_TRNS,  KC_TRNS, H_S,     KC_TRNS,

                      KC_6,    KC_7,     KC_8,     KC_9,     DEG0,     KC_TRNS,
                      KC_CIRC, HRMR(KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN), KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN,  KC_UP,    KC_RGHT,  KC_TRNS,  KC_TRNS,
    KC_TRNS, STAR,    KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_RAISE] = LAYOUT_stack_of_waffles(
    KC_TRNS, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,
    KC_TRNS, KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
    KC_TRNS, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,  RWORD,   KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                      KC_NOMODE, KC_SCRIPT, KC_BLOCKS, KC_REGIONAL, QK_MAKE, KC_TRNS,
                      KC_WIDE,   KC_AUSSIE, KC_ZALGO,  KC_SUPER,    QK_BOOT, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_F6,     KC_F7,     KC_F8,     KC_F9,       KC_F10,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
  [_BASE]  = { { KC_VOLU, KC_VOLD }, { KC_MNXT, KC_MPRV } },
  [_LOWER] = { { RGB_SAI, RGB_SAD }, { RGB_HUI, RGB_HUD } },
  [_RAISE] = { { KC_LEFT, C(KC_RGHT) }, { C(S(KC_TAB)), C(KC_TAB) } }
};
#endif

#ifdef OLED_ENABLE
bool oled_task_keymap(void) {
  if (is_keyboard_left()) {
    wpm_graph();
    render_wpm();
  }
  return false;
}
#endif
