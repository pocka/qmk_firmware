#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _SYMBOLS,
  _VIM
};

enum custom_keycodes {
  SYMBOLS = SAFE_RANGE,
  VIM,
  VIM_B,
  VIM_D,
  VIM_G,
  VIM_R,
  VIM_U,
  VIM_W
};

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | `    |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  | Enter| Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      |      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      |Symbol| VIM  | Alt  |Space |Space |Space |Space | Alt  |      |      |      | Ctrl |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC, \
      KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSLASH, \
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_ENTER, KC_ENTER, \
      KC_LSHIFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,   KC_NO,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSHIFT, \
      KC_LCTRL,  KC_NO,   SYMBOLS, VIM,     KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_NO,   KC_NO,   KC_NO,    KC_RCTRL \
      ),

  /* Symbols
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |      |      |      |      |      |             |      |      |      |   -  |   =  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | `    |      |      |      |      |      |             |      |      |      |   [  |   ]  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |      |      |      |      |      |             |      |      |  ;   |   '  | Enter| Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|      |      |      |      |      |      |      |      |      |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      |Symbol| VIM  | Alt  |Space |Space |Space |Space | Alt  |      |      |      | Ctrl |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_SYMBOLS] = LAYOUT( \
      KC_ESC,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_MINUS, KC_EQUAL, KC_BSPC, \
      KC_GRV,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_LBRC,  KC_RBRC,  KC_BSLASH, \
      KC_TAB,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_SCLN, KC_QUOT,  KC_ENTER, KC_ENTER, \
      KC_LSHIFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_COMM, KC_DOT,   KC_SLSH,  KC_RSHIFT, \
      KC_LCTRL,  KC_NO,   SYMBOLS, VIM,     KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_NO,   KC_NO,    KC_NO,    KC_RCTRL \
      ),

  /* VIM
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |      |      |      |      |      |             |      |      |      |      |      | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | `    |      | VIM_W|      | VIM_R|      |             | Copy | VIM_U|      |      | Paste|   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |      |      | VIM_D|      | VIM_G|             |LArrow|DArrow|TArrow|RArrow| Enter| Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|      | Cut  |      |      | VIM_B|      |      |      |      |      |      |      | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      |Symbol| VIM  | Alt  |Space |Space |Space |Space | Alt  |      |      |      | Ctrl |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_VIM] = LAYOUT( \
      KC_ESC,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_BSPC, \
      KC_GRV,    KC_NO,   VIM_W,   KC_NO,   VIM_R,   KC_NO,                     KC_COPY, VIM_U,   KC_NO,  KC_NO,    KC_PASTE, KC_BSLASH, \
      KC_TAB,    KC_NO,   KC_NO,   VIM_D,   KC_NO,   VIM_G,                     KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, KC_ENTER, KC_ENTER, \
      KC_LSHIFT, KC_NO,   KC_CUT,  KC_NO,   KC_NO,   VIM_B,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_RSHIFT, \
      KC_LCTRL,  KC_NO,   SYMBOLS, VIM,     KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_NO,  KC_NO,    KC_NO,    KC_RCTRL \
      ),
};

#else
#error "undefined keymaps"
#endif


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#define LAYER_HSV_SYMBOLS HSV_GOLD
#define LAYER_HSV_VIM     HSV_CYAN
#define LAYER_HSV_QWERTY  HSV_WHITE

uint16_t oled_timer;
bool oled_disabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t ctrl_key = get_mods() & MOD_MASK_CTRL;
  uint8_t shift_key = get_mods() & MOD_MASK_SHIFT;

  if (record->event.pressed) {
    oled_timer = timer_read();
    oled_disabled = false;
  }


  switch (keycode) {
    // ----- ----- ----- ----- ----- -----
    // Layer keys
    case SYMBOLS:
      if (record->event.pressed) {
        layer_on(_SYMBOLS);
        rgblight_sethsv_noeeprom(LAYER_HSV_SYMBOLS);
      } else {
        layer_off(_SYMBOLS);
        rgblight_sethsv_noeeprom(LAYER_HSV_QWERTY);
      }
      return false;
    case VIM:
      if (record->event.pressed) {
        layer_on(_VIM);
        rgblight_sethsv_noeeprom(LAYER_HSV_VIM);
      } else {
        layer_off(_VIM);
        rgblight_sethsv_noeeprom(LAYER_HSV_QWERTY);
      }
      return false;

    // ----- ----- ----- ----- ----- -----
    // VIM emulation keys
    case VIM_B:
      if (record->event.pressed && !get_mods()) {
        SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_LEFT) SS_UP(X_LCTRL));
        return false;
      }
      return true;
    case VIM_D:
      if (!record->event.pressed) {
        return true;
      }

      if (ctrl_key) {
        del_mods(MOD_MASK_CTRL);
        SEND_STRING(SS_TAP(X_PGDOWN));
        register_mods(ctrl_key);
        return false;
      }

      if (!get_mods()) {
        SEND_STRING(SS_TAP(X_DEL));
        return false;
      }

      return true;
    case VIM_G:
      if (!record->event.pressed) {
        return true;
      }

      if (shift_key) {
        del_mods(MOD_MASK_SHIFT);
        SEND_STRING(SS_TAP(X_END));
        set_mods(shift_key);
        return false;
      }

      if (!get_mods()) {
        SEND_STRING(SS_TAP(X_HOME));
        return false;
      }

      return true;
    case VIM_R:
      if (!record->event.pressed) {
        return true;
      }

      if (ctrl_key) {
        del_mods(MOD_MASK_CTRL);
        SEND_STRING(SS_TAP(X_AGAIN));
        set_mods(ctrl_key);
        return false;
      }

      return true;
    case VIM_U:
      if (!record->event.pressed) {
        return true;
      }

      if (ctrl_key) {
        del_mods(MOD_MASK_CTRL);
        SEND_STRING(SS_TAP(X_PGUP));
        set_mods(ctrl_key);
        return false;
      }

      if (!get_mods()) {
        SEND_STRING(SS_TAP(X_UNDO));
        return false;
      }

      return true;
    case VIM_W:
      if (!record->event.pressed) {
        return true;
      }

      if (!get_mods()) {
        SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_RIGHT) SS_UP(X_LCTRL));
        return false;
      }

      return true;
  }
  return true;
}

void matrix_init_user(void) {
  #ifdef SSD1306OLED
    // Turn on the display
    iota_gfx_init(!has_usb());
  #endif

  rgblight_enable();
  rgblight_sethsv(LAYER_HSV_QWERTY);
}



#ifdef SSD1306OLED

// Enable update loop
void matrix_scan_user(void) {
     iota_gfx_task();
}

void matrix_update(
  struct CharacterMatrix *dest,
  const struct CharacterMatrix *source
) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

#define L_BASE 0
#define L_SYMBOLS (1<<_SYMBOLS)
#define L_VIM (1<<_VIM)

#define OLED_ICON_PADDING PSTR("        ")

static void render_status_icon(struct CharacterMatrix *matrix, uint8_t width, uint8_t height, const char icon[height][width]) {
  for (uint8_t row = 0; row < height; row++) {
    matrix_write_P(matrix, OLED_ICON_PADDING);
    matrix_write_P(matrix, icon[row]);

    if (row < height - 1) {
      matrix_write_P(matrix, PSTR("\n"));
    }
  }
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  static const char default_layer[][5] PROGMEM = {
    {0x85, 0x86, 0x87, 0x88, 0},
    {0xa5, 0xa6, 0xa7, 0xa8, 0},
    {0xc5, 0xc6, 0xc7, 0xc8, 0}
  };

  static const char symbol_layer[][6] PROGMEM = {
    {0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0},
    {0xa9, 0xaa, 0xab, 0xac, 0xad, 0},
    {0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0}
  };

  static const char vim_layer[][6] PROGMEM = {
    {0x80, 0x81, 0x82, 0x83, 0x84, 0},
    {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0},
    {0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0}
  };

  matrix_write_P(matrix, PSTR("\n"));

  switch (layer_state) {
    case L_BASE:
      render_status_icon(matrix, 5, 3, default_layer);
      break;
    case L_SYMBOLS:
      render_status_icon(matrix, 6, 3, symbol_layer);
      break;
    case L_VIM:
      render_status_icon(matrix, 6, 3, vim_layer);
      break;
  }
}

static void render_gopher(struct CharacterMatrix *matrix, uint16_t frame) {
  static const char gopher_foot[5] PROGMEM = {0xce, 0xcf, 0xd0, 0xd1, 0};

  static const char gopher_body_anim[][5] PROGMEM = {
    {0xae, 0xaf, 0xb0, 0xb1, 0},
    {0xb4, 0xaf, 0xb0, 0xb5, 0},
  };

  static const char gopher_head_anim[][5] PROGMEM = {
    {0x8e, 0x8f, 0x90, 0x91, 0},
    {0x8e, 0x96, 0x97, 0x91, 0},
    {0x8e, 0xb6, 0xb7, 0x91, 0},
    {0x8e, 0xd6, 0xd7, 0x91, 0},
  };

  matrix_write_P(matrix, PSTR("\n"));

  // Head
  uint8_t head_frame_index = 0;
  switch (frame) {
    case 5:
    case 9:
      head_frame_index = 1;
      break;
    case 6:
    case 8:
      head_frame_index = 2;
      break;
    case 7:
      head_frame_index = 3;
      break;
  }
  matrix_write_P(matrix, OLED_ICON_PADDING);
  matrix_write_P(matrix, gopher_head_anim[head_frame_index]);
  matrix_write_P(matrix, PSTR("\n"));

  // Body
  matrix_write_P(matrix, OLED_ICON_PADDING);
  matrix_write_P(matrix, gopher_body_anim[frame % 50 > 25 ? 1 : 0]);
  matrix_write_P(matrix, PSTR("\n"));

  // Foot
  matrix_write_P(matrix, OLED_ICON_PADDING);
  matrix_write_P(matrix, gopher_foot);
}

#define ANIM_FRAME_INTERVAL 10
#define ANIM_FRAME_MAX ANIM_FRAME_INTERVAL * 300

// Display timeout in seconds
#define OLED_TIMEOUT 60000

uint16_t anim_frame = 0;

void iota_gfx_task_user(void) {
  if (oled_disabled) {
    return;
  }

  if (timer_elapsed(oled_timer) > OLED_TIMEOUT) {
    iota_gfx_off();
    oled_disabled = true;
    return;
  }

  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_layer_status(&matrix);
  }else{
    render_gopher(&matrix, anim_frame / ANIM_FRAME_INTERVAL);

    anim_frame++;

    if (anim_frame >= ANIM_FRAME_MAX) {
      anim_frame = 0;
    }
  }
  matrix_update(&display, &matrix);
}

#endif
