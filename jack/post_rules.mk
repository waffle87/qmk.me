ifeq ($(MCU_SERIES), RP2040)
	include picosdk_math.mk
endif

ifeq ($(strip $(RP2040_MATH_IN_ROM)), yes)
	OPT_DEFS += -DRP2040_MATH_IN_ROM
	MCU_LDSCRIPT = RP2040_FLASH_TIMECRIT_ROM_MATH
endif

ifeq ($(strip $(MOUSE_JIGGLE_ENABLE)), yes)
	OPT_DEFS += -DMOUSE_JIGGLE_ENABLE
	MOUSEKEY_ENABLE = yes
	DEFERRED_EXEC_ENABLE = yes
endif
