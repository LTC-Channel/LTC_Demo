#include "../lv_conf.h"
#include "../display_driver/fbdev.h"
#include "../input_driver/evdev.h"
#include <unistd.h>
#include "lv_clock.h"

static lv_disp_buf_t disp_buf;
static lv_color_t lvbuf1[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10]; /*Declare a buffer for 1/10 screen size*/
static lv_color_t lvbuf2[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10];

void main(){
    
    lv_init();
    
    //Linux frame buffer device init
    fbdev_init();

    // Touch pointer device init
    evdev_init();

    lv_disp_buf_init(&disp_buf, lvbuf1, lvbuf2, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10);    /*Initialize the display buffer*/
    
    // Initialize and register a display driver
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = fbdev_flush;    // flushes the internal graphical buffer to the frame buffer
    disp_drv.buffer = &disp_buf;        // set teh display buffere reference in the driver
    lv_disp_drv_register(&disp_drv);

    // Initialize and register a pointer device driver
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;    // defined in lv_drivers/indev/evdev.h
    lv_indev_drv_register(&indev_drv);

    lv_clock_demo();

    // Handle LitlevGL tasks (tickless mode)
    while(1) {
        lv_tick_inc(5);
        lv_task_handler();
        usleep(5000);
    }
    return 0;

}