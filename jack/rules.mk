LTO_ENABLE = yes
TOP_SYMBOLS = yes
MAGIC_ENABLE = no
COMBO_ENABLE = yes
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
UNICODE_COMMON = yes
GRAVE_ESC_ENABLE = no
EXTRAKEY_ENABLE = yes
BOOTMAGIC_ENABLE = yes
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
SPACE_CADET_ENABLE = no
AUTOCORRECT_ENABLE = yes
MOUSE_JIGGLE_ENABLE = yes
CUSTOM_TAP_CODE_ENABLE = no
DEBOUNCE_TYPE = asym_eager_defer_pk
AVR_CFLAGS += -mrelax
INTROSPECTION_KEYMAP_C = jack.c

SRC += tapping.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
	WPM_ENABLE = yes
endif

ifeq ($(strip $(UNICODE_COMMON)), yes)
	UNICODE_ENABLE = no
	SRC += unicode.c
endif

ifeq ($(strip $(CUSTOM_TAP_CODE_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_TAP_CODE_ENABLE
	SRC += tap_code.c
endif

ifeq ($(PLATFORM), CHIBIOS)
	EXTRAFLAGS += -Os
endif

ifneq ($(findstring Gentoo, $(shell arm-none-eabi-gcc --version)),)
	EXTRAFLAGS += -U_FORTIFY_SOURCE
endif

ifeq ($(strip $(MOUSE_JIGGLE_ENABLE)), yes)
	OPT_DEFS += -DMOUSE_JIGGLE_ENABLE
	MOUSEKEY_ENABLE = yes
	DEFERRED_EXEC_ENABLE = yes
endif
