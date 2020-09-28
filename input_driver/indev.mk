CSRCS += FT5406EE8.c
CSRCS += keyboard.c
CSRCS += mouse.c
CSRCS += mousewheel.c
CSRCS += evdev.c
CSRCS += libinput.c
CSRCS += XPT2046.c

DEPPATH += --dep-path $(LVGL_DIR)/../input_driver
VPATH += :$(LVGL_DIR)/../input_driver

CFLAGS += "-I$(LVGL_DIR)/../input_driver"
