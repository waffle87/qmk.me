CONVERT_TO = blok
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
ENCODER_MAP_ENABLE = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
PROGRAM_CMD = doas picotool load $(BUILD_DIR)/$(TARGET).uf2
