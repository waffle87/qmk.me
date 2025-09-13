LTO_ENABLE = yes
TOP_SYMBOLS = yes
MAGIC_ENABLE = yes
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
OS_DETECTION_ENABLE = yes
DEBOUNCE_TYPE = asym_eager_defer_pk
AVR_CFLAGS += -mrelax
INTROSPECTION_KEYMAP_C = introspection.c

SRC += $(USER_PATH)/jack.c $(USER_PATH)/tapping.c

ifeq ($(strip $(OLED_ENABLE)), yes)
  SRC += $(USER_PATH)/oled.c
  WPM_ENABLE = yes
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += $(USER_PATH)/colour.c
endif

ifeq ($(strip $(UNICODE_COMMON)), yes)
	UNICODE_ENABLE = no
	SRC += $(USER_PATH)/unicode.c
endif

ifeq ($(PLATFORM), CHIBIOS)
	ifeq ($(MCU_SERIES), RP2040)
		RP2040_MATH_IN_ROM = no
		PROGRAM_CMD = doas picotool load $(BUILD_DIR)/$(TARGET).uf2
	endif
	EXTRAFLAGS += -O3
endif
