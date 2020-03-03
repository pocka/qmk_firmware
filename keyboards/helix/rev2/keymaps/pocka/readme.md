# Helix Layout (pocka's edition)

## Customize

see `qmk_firmware/keyboards/helix/rev2/keymaps/pocka/rules.mk`

```
# Helix Spacific Build Options
# you can uncomment and edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集し、コメントアウトをはずします。
# HELIX_ROWS = 5              # Helix Rows is 4 or 5
# OLED_ENABLE = no            # OLED_ENABLE
# LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
# LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
# LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
# LED_ANIMATIONS = yes        # LED animations
# IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```
## Compile

go to qmk top directory.
```
$ cd qmk_firmware
```

build
```
$ make helix:pocka
$ make helix/rev2/back:pocka               # with backlight
$ make HELIX=no_ani helix/rev2/back:pocka  # with backlight without animation
$ make helix/rev2/under:pocka              # with underglow
$ make helix/rev2/oled:pocka               # with oled
$ make helix/rev2/oled/back:pocka          # with oled and backlight
$ make helix/rev2/oled/under:pocka         # with oled and underglow
```

flash to keyboard

```
$ make helix:pocka:flash
$ make helix/rev2/back:pocka:flash               # with backlight
$ make HELIX=no_ani helix/rev2/back:pocka:flash  # with backlight without animation
$ make helix/rev2/under:pocka:flash              # with underglow
$ make helix/rev2/oled:pocka:flash               # with oled
$ make helix/rev2/oled/back:pocka:flash          # with oled and backlight
$ make helix/rev2/oled/under:pocka:flash         # with oled and underglow

```

## Link
* more detail wrote in Japanese [helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)
* [Helix top](https://github.com/MakotoKurauchi/helix)

