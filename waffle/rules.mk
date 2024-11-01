LTO_ENABLE = yes
TOP_SYMBOLS = yes
NRKO_ENABLE = yes
COMBO_ENABLE = yes
MAGIC_ENABLE = no
UNICODE_COMMON = yes
EXTRAKEY_ENABLE = yes
BOOTMAGIC_ENABLE = yes
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
AUTOCORRECT_ENABLE = yes
MOUSE_JIGGLE_ENABLE = yes
DEBOUNCE_TYPE = asym_eager_defer_pk
AVR_CFLAGS += -mrelax
INTROSPECTION_KEYMAP_C = waffle.c

SRC += tapping.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
	WPM_ENABLE = yes
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += color.c
endif

ifeq ($(strip $(UNICODE_COMMON)), yes)
	UNICODE_ENABLE = no
	SRC += unicode.c
endif

ifeq ($(PLATFORM), CHIBIOS)
	RANDWORD = yes
	EXTRAFLAGS += -Os
endif

ifneq ($(findstring Gentoo, $(shell arm-none-eabi-gcc --version)),)
	EXTRAFLAGS += -U_FORTIFY_SOURCE
endif

ifeq ($(strip $(RANDWORD)), yes)
	OPT_DEFS += -DRANDWORD
endif

ifeq ($(strip $(MOUSE_JIGGLE_ENABLE)), yes)
	OPT_DEFS += -DMOUSE_JIGGLE_ENABLE
	MOUSEKEY_ENABLE = yes
	DEFERRED_EXEC_ENABLE = yes
endif
