BOOTMAGIC_ENABLE = yes
EXTRAKEY_ENABLE = yes
NRKO_ENABLE = yes
COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes
AUTOCORRECT_ENABLE = yes
TOP_SYMBOLS = yes
LTO_ENABLE = yes
TAP_DANCE_ENABLE = yes
UNICODE_COMMON = yes
MOUSEKEY_ENABLE = yes
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
DEBOUNCE_TYPE = asym_eager_defer_pk

SRC += waffle.c tapping.c

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
	EXTRAFLAGS += -O3
endif

ifneq ($(findstring Gentoo, $(shell arm-none-eabi-gcc --version)),)
	EXTRAFLAGS += -U_FORTIFY_SOURCE
endif

ifeq ($(strip $(RANDWORD)), yes)
	OPT_DEFS += -DRANDWORD
endif
