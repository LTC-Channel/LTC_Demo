/**
 * @file lv_demo_priner.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_printer_theme.h"
#include "lv_clock.h"


/*********************
 *      DEFINES
 *********************/
/*Bg positions*/
#define LV_DEMO_PRINTER_BG_NONE (-LV_VER_RES)
#define LV_DEMO_PRINTER_BG_FULL 0
#define LV_DEMO_PRINTER_BG_NORMAL (-2 * (LV_VER_RES / 3))
#define LV_DEMO_PRINTER_BG_SMALL (-5 * (LV_VER_RES / 6))

/*Sizes*/
#define LV_DEMO_PRINTER_BTN_H   (50)
#define LV_DEMO_PRINTER_BTN_W   (200)

/*Animations*/
#define LV_DEMO_PRINTER_ANIM_Y (LV_VER_RES / 20)
#define LV_DEMO_PRINTER_ANIM_DELAY (40)
#define LV_DEMO_PRINTER_ANIM_TIME  (150)
#define LV_DEMO_PRINTER_ANIM_TIME_BG  (300)

/*Padding*/
#define LV_DEMO_PRINTER_TITLE_PAD 35

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void home_clock(uint32_t delay);

LV_EVENT_CB_DECLARE(print_open_event_cb);
LV_EVENT_CB_DECLARE(back_to_home_event_cb);


LV_EVENT_CB_DECLARE(scan_open_icon_event_cb);
LV_EVENT_CB_DECLARE(scan_ready_event_cb);

LV_EVENT_CB_DECLARE(copy_open_icon_event_cb);
LV_EVENT_CB_DECLARE(scan_next_event_cb);
LV_EVENT_CB_DECLARE(scan_save_event_cb);
LV_EVENT_CB_DECLARE(hue_slider_event_cb);
LV_EVENT_CB_DECLARE(lightness_slider_event_cb);
LV_EVENT_CB_DECLARE(usb_icon_event_cb);
LV_EVENT_CB_DECLARE(print_cnt_bnt_event_cb);
LV_EVENT_CB_DECLARE(print_start_event_cb);
LV_EVENT_CB_DECLARE(back_to_print_event_cb);
LV_EVENT_CB_DECLARE(mobile_icon_event_cb);
LV_EVENT_CB_DECLARE(internet_icon_event_cb);
LV_EVENT_CB_DECLARE(setup_icon_event_cb);


LV_EVENT_CB_DECLARE(icon_generic_event_cb);

static void lv_demo_printer_anim_out_all(lv_obj_t * obj, uint32_t delay);
static void lv_demo_printer_anim_in(lv_obj_t * obj, uint32_t delay);

LV_IMG_DECLARE(digital_7_200);
/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * bg_top;
static lv_obj_t * bg_bottom;
static lv_obj_t * scan_img;
static lv_obj_t * print_cnt_label;
static lv_color_t bg_color_prev;
static lv_color_t bg_color_act;
static uint16_t print_cnt;
static uint16_t hue_act;
static int16_t lightness_act;
static const char * scan_btn_txt;

static lv_style_t clock_style;

lv_style_list_t * list;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_clock_demo(void)
{

    bg_color_prev = LV_DEMO_PRINTER_BLUE;
    bg_color_act = LV_DEMO_PRINTER_BLUE;

    lv_theme_t * th = lv_demo_printer_theme_init(LV_COLOR_BLACK, LV_COLOR_BLACK,
            0, &lv_font_montserrat_14, &lv_font_montserrat_22,
            &lv_font_montserrat_28, &lv_font_montserrat_32);
    lv_theme_set_act(th);

    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

    bg_top = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(bg_top, LV_OBJ_PART_MAIN);
    lv_obj_set_style_local_bg_opa(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_obj_set_style_local_bg_color(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_DEMO_PRINTER_BLUE);
    lv_obj_set_size(bg_top, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_y(bg_top, LV_DEMO_PRINTER_BG_NORMAL);

    home_clock(0);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void home_clock(uint32_t delay) {

    lv_obj_t * title = lv_label_create(lv_scr_act(), NULL);
    lv_theme_apply(title, (lv_theme_style_t)LV_DEMO_PRINTER_THEME_TITLE);
    lv_label_set_text(title, "2020/09/29");
    lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0,
        LV_DEMO_PRINTER_TITLE_PAD);
        lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_RIGHT, -60, LV_DEMO_PRINTER_TITLE_PAD);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(title, delay);

    lv_coord_t box_w = 760;
    lv_obj_t * box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(box, box_w, 260);
    //lv_obj_set_style_local_bg_color(box, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_DEMO_PRINTER_GREEN);
    lv_obj_align(box, NULL, LV_ALIGN_IN_TOP_MID, 0, 100);
    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(box, delay);

    

    lv_style_init(&clock_style);
    lv_style_set_text_font(&clock_style, LV_STATE_DEFAULT, &digital_7_200);

    //LV_IMG_DECLARE(lv_demo_printer_img_btn_bg_1);
    //LV_IMG_DECLARE(lv_demo_printer_img_btn_bg_2);
    //LV_IMG_DECLARE(lv_demo_printer_img_btn_bg_3);
    LV_IMG_DECLARE(lv_demo_printer_img_btn_bg);

    //lv_obj_set_style_local_bg_color(box, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_NAVY); // clock background 

    lv_obj_t * bg_1 = lv_img_create(box, NULL);
    lv_obj_set_click(bg_1, true);
    lv_obj_align_origo(bg_1, NULL, LV_ALIGN_IN_LEFT_MID, 60, -85);
    lv_theme_apply(bg_1, (lv_theme_style_t)LV_DEMO_PRINTER_THEME_ICON);
    lv_img_set_src(bg_1, &lv_demo_printer_img_btn_bg);
    lv_img_set_antialias(bg_1, false);

    lv_obj_t * txt_1 = lv_label_create(bg_1, NULL);
    lv_label_set_text(txt_1, "0");
    lv_theme_apply(txt_1, LV_DEMO_PRINTER_THEME_LABEL_WHITE);
    lv_obj_align(txt_1, bg_1, LV_ALIGN_CENTER, -38, -75);
    lv_obj_add_style(txt_1, LV_CONT_PART_MAIN, &clock_style);

    lv_obj_t * bg_2 = lv_img_create(box, NULL);
    lv_obj_set_click(bg_2, true);
    lv_obj_align_origo(bg_2, NULL, LV_ALIGN_IN_LEFT_MID, 225, -85);
    lv_theme_apply(bg_2, (lv_theme_style_t)LV_DEMO_PRINTER_THEME_ICON);
    lv_img_set_src(bg_2, &lv_demo_printer_img_btn_bg);
    lv_img_set_antialias(bg_2, false);

    lv_obj_t * txt_2 = lv_label_create(bg_2, NULL);
    lv_label_set_text(txt_2, "1");
    lv_theme_apply(txt_2, LV_DEMO_PRINTER_THEME_LABEL_WHITE);
    lv_obj_align(txt_2, bg_2, LV_ALIGN_CENTER, -38, -75);
    lv_obj_add_style(txt_2, LV_CONT_PART_MAIN, &clock_style);

    lv_obj_t * bg_3 = lv_img_create(box, NULL);
    lv_obj_set_click(bg_3, true);
    lv_obj_align_origo(bg_3, NULL, LV_ALIGN_IN_RIGHT_MID, -320, -85);
    lv_theme_apply(bg_3, (lv_theme_style_t)LV_DEMO_PRINTER_THEME_ICON);
    lv_img_set_src(bg_3, &lv_demo_printer_img_btn_bg);
    lv_img_set_antialias(bg_3, false);

    lv_obj_t * txt_3 = lv_label_create(bg_3, NULL);
    lv_label_set_text(txt_3, "0");
    lv_theme_apply(txt_3, LV_DEMO_PRINTER_THEME_LABEL_WHITE);
    lv_obj_align(txt_3, bg_3, LV_ALIGN_CENTER, -38, -75);
    lv_obj_add_style(txt_3, LV_CONT_PART_MAIN, &clock_style);

    lv_obj_t * bg_4 = lv_img_create(box, NULL);
    lv_obj_set_click(bg_4, true);
    lv_obj_align_origo(bg_4, NULL, LV_ALIGN_IN_RIGHT_MID, -155, -85);
    lv_theme_apply(bg_4, (lv_theme_style_t)LV_DEMO_PRINTER_THEME_ICON);
    lv_img_set_src(bg_4, &lv_demo_printer_img_btn_bg);
    lv_img_set_antialias(bg_4, false);

    lv_obj_t * txt_4 = lv_label_create(bg_4, NULL);
    lv_label_set_text(txt_4, "0");
    lv_theme_apply(txt_4, LV_DEMO_PRINTER_THEME_LABEL_WHITE);
    lv_obj_align(txt_4, bg_4, LV_ALIGN_CENTER, -38, -75);
    lv_obj_add_style(txt_4, LV_CONT_PART_MAIN, &clock_style);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(box, delay);
}


static void lv_demo_printer_anim_out_all(lv_obj_t * obj, uint32_t delay) {
    lv_obj_t * child = lv_obj_get_child_back(obj, NULL);
    while(child) {
        if(child != scan_img && child != bg_top && child != bg_bottom && child != lv_scr_act()) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, child);
            lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME);
            lv_anim_set_delay(&a, delay);
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
            if(lv_obj_get_y(child) < 80) {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                        lv_obj_get_y(child) - LV_DEMO_PRINTER_ANIM_Y);
            } else {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                        lv_obj_get_y(child) + LV_DEMO_PRINTER_ANIM_Y);

                delay += LV_DEMO_PRINTER_ANIM_DELAY;
            }
            lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
            lv_anim_start(&a);
        }
        child = lv_obj_get_child_back(obj, child);
    }
}

static void lv_demo_printer_anim_in(lv_obj_t * obj, uint32_t delay)
{
    if (obj != bg_top && obj != bg_bottom && obj != lv_scr_act()) {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME);
        lv_anim_set_delay(&a, delay);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
        lv_anim_set_values(&a, lv_obj_get_y(obj) - LV_DEMO_PRINTER_ANIM_Y,
                lv_obj_get_y(obj));
        lv_anim_start(&a);

        lv_obj_fade_in(obj, LV_DEMO_PRINTER_ANIM_TIME - 50, delay);
    }
}




