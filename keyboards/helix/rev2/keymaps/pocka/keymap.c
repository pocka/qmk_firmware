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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t ctrl_key = get_mods() & MOD_MASK_CTRL;
  uint8_t shift_key = get_mods() & MOD_MASK_SHIFT;


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
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif

    rgblight_enable();
    rgblight_sethsv(LAYER_HSV_QWERTY);
}



//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_SYMBOLS (1<<_SYMBOLS)
#define L_VIM (1<<_VIM)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_SYMBOLS:
           matrix_write_P(matrix, PSTR("Symbols"));
           break;
        case L_VIM:
           matrix_write_P(matrix, PSTR("VIM"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[0][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
