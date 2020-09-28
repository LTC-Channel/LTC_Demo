CSRCS += lv_demo_printer.c

CSRCS += lv_demo_printer_icon_bright.c
CSRCS += lv_demo_printer_icon_eco.c
CSRCS += lv_demo_printer_icon_hue.c
CSRCS += lv_demo_printer_icon_pc.c
CSRCS += lv_demo_printer_icon_tel.c
CSRCS += lv_demo_printer_icon_wifi.c
CSRCS += lv_demo_printer_img_btn_bg.c
CSRCS += lv_demo_printer_img_cloud.c
CSRCS += lv_demo_printer_img_copy.c
CSRCS += lv_demo_printer_img_internet.c
CSRCS += lv_demo_printer_img_phone.c
CSRCS += lv_demo_printer_img_print.c
CSRCS += lv_demo_printer_img_printer2.c
CSRCS += lv_demo_printer_img_ready.c
CSRCS += lv_demo_printer_img_scan_example.c
CSRCS += lv_demo_printer_img_scan.c
CSRCS += lv_demo_printer_img_setup.c
CSRCS += lv_demo_printer_img_usb.c
CSRCS += lv_demo_printer_img_wave.c
CSRCS += lv_demo_printer_theme.c
CSRCS += lv_demo_printer_img_mobile.c
CSRCS += lv_demo_printer_img_no_internet.c


DEPPATH += --dep-path $(LVGL_DIR)/lv_examples/src/lv_demo_printer
VPATH += :$(LVGL_DIR)/lv_examples/src/lv_demo_printer
CFLAGS += "-I$(LVGL_DIR)/lv_examples/src/lv_demo_printer"

