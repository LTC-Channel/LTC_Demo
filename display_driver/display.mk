CSRCS += fbdev.c
CSRCS += monitor.c
CSRCS += R61581.c
CSRCS += SSD1963.c
CSRCS += ST7565.c
CSRCS += UC1610.c
CSRCS += SHARP_MIP.c

DEPPATH += --dep-path $(LVGL_DIR)/../display_driver
VPATH += :$(LVGL_DIR)/../display_driver

CFLAGS += "-I$(LVGL_DIR)/../display_driver"
