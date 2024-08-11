POINTING_DEVICE_DRIVER = cirque_pinnacle_spi

# depends on 21844 & 23699
QUANTUM_PAINTER_DRIVERS += ls0xx_spi

ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
	SRC += lib/jetbrainsmono11.qff.c
endif
