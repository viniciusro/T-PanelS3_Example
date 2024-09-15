#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_cpu(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSING) {
        action_drag_event_handler(e);
    }
}

static void event_handler_cb_main_gpu(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSING) {
        action_drag_event_handler(e);
    }
}

static void event_handler_cb_main_mem_hdd(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSING) {
        action_drag_event_handler(e);
    }
}

static void event_handler_cb_main_cpu_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSING) {
        action_drag_event_handler(e);
    }
}

static void event_handler_cb_main_gpu_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSING) {
        action_drag_event_handler(e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff424242), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_tabview_create(parent_obj, LV_DIR_LEFT, 80);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 465);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_tabview_get_tab_btns(parent_obj);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff424242), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffe9e9e9), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 250, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_ITEMS | LV_STATE_CHECKED);
                }
                {
                    lv_obj_t *obj = lv_tabview_get_content(parent_obj);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // tab1
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "Monitor");
                            objects.tab1 = obj;
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_img_src(obj, &img_dark_wavy, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // CPU
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.cpu = obj;
                                    lv_obj_set_pos(obj, -11, -10);
                                    lv_obj_set_size(obj, 220, 146);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_cpu, LV_EVENT_ALL, flowState);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff4c4c4c), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_clip_corner(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // label_container_cpu
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_container_cpu = obj;
                                            lv_obj_set_pos(obj, 93, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "CPU");
                                            lv_obj_set_style_text_letter_space(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuTemp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_temp = obj;
                                            lv_obj_set_pos(obj, 5, 29);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature:");
                                        }
                                        {
                                            // t1_cpuTemp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_temp = obj;
                                            lv_obj_set_pos(obj, 155, 22);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00C");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuUsage
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_usage = obj;
                                            lv_obj_set_pos(obj, 5, 58);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Usage:");
                                        }
                                        {
                                            // t1_cpuUsage
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_usage = obj;
                                            lv_obj_set_pos(obj, 173, 51);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "0%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuPower
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_power = obj;
                                            lv_obj_set_pos(obj, 5, 87);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Power:");
                                        }
                                        {
                                            // t1_cpuPower
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_power = obj;
                                            lv_obj_set_pos(obj, 149, 80);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00W");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuFrequency
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_frequency = obj;
                                            lv_obj_set_pos(obj, 5, 116);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Freq:");
                                        }
                                        {
                                            // t1_cpuFrequency
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_frequency = obj;
                                            lv_obj_set_pos(obj, 84, 109);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "0000MHz");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    // GPU
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.gpu = obj;
                                    lv_obj_set_pos(obj, 151, 147);
                                    lv_obj_set_size(obj, 220, 146);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_gpu, LV_EVENT_ALL, flowState);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff4c4c4c), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_clip_corner(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // label_container_gpu
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_container_gpu = obj;
                                            lv_obj_set_pos(obj, 93, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "GPU");
                                            lv_obj_set_style_text_letter_space(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuTemp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_temp = obj;
                                            lv_obj_set_pos(obj, 6, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature:");
                                        }
                                        {
                                            // t1_gpuTemp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_temp = obj;
                                            lv_obj_set_pos(obj, 157, 8);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00C");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuUsage
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_usage = obj;
                                            lv_obj_set_pos(obj, 5, 50);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Usage:");
                                        }
                                        {
                                            // t1_gpuUsage
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_usage = obj;
                                            lv_obj_set_pos(obj, 154, 42);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuCoreFrequency
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_core_frequency = obj;
                                            lv_obj_set_pos(obj, 6, 86);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Freq:");
                                        }
                                        {
                                            // t1_gpuCoreFrequency
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_core_frequency = obj;
                                            lv_obj_set_pos(obj, 103, 77);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "000MHz");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuMemoryFreq
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_memory_freq = obj;
                                            lv_obj_set_pos(obj, 6, 118);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "MEM:");
                                        }
                                        {
                                            // t1_gpuMemoryFreq
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_memory_freq = obj;
                                            lv_obj_set_pos(obj, 86, 111);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "0000MHz");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    // MEM_HDD
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.mem_hdd = obj;
                                    lv_obj_set_pos(obj, -11, 303);
                                    lv_obj_set_size(obj, 220, 137);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_mem_hdd, LV_EVENT_ALL, flowState);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff4c4c4c), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_clip_corner(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // label_container_mem_hdd
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_container_mem_hdd = obj;
                                            lv_obj_set_pos(obj, 44, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "MEM & HDD");
                                            lv_obj_set_style_text_letter_space(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_ramUsage
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_ram_usage = obj;
                                            lv_obj_set_pos(obj, 5, 24);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "RAM Usage:");
                                        }
                                        {
                                            // t1_ramUsage
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_ram_usage = obj;
                                            lv_obj_set_pos(obj, 157, 17);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_hddUsage0
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_hdd_usage0 = obj;
                                            lv_obj_set_pos(obj, 5, 53);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "HDD 1:");
                                        }
                                        {
                                            // t1_hddUsage0
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_hdd_usage0 = obj;
                                            lv_obj_set_pos(obj, 157, 46);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_hddUsage1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_hdd_usage1 = obj;
                                            lv_obj_set_pos(obj, 5, 82);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "HDD 2:");
                                        }
                                        {
                                            // t1_hddUsage1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_hdd_usage1 = obj;
                                            lv_obj_set_pos(obj, 157, 75);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_hddUsage3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_hdd_usage3 = obj;
                                            lv_obj_set_pos(obj, 5, 111);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "HDD 3:");
                                        }
                                        {
                                            // t1_hddUsage2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_hdd_usage2 = obj;
                                            lv_obj_set_pos(obj, 157, 104);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // tab2
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "CPU");
                            objects.tab2 = obj;
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_img_src(obj, &img_dark_wavy, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // CPU_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.cpu_1 = obj;
                                    lv_obj_set_pos(obj, 74, 256);
                                    lv_obj_set_size(obj, 220, 146);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_cpu_1, LV_EVENT_ALL, flowState);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff4c4c4c), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_clip_corner(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // label_container_cpu_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_container_cpu_1 = obj;
                                            lv_obj_set_pos(obj, 93, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "CPU");
                                            lv_obj_set_style_text_letter_space(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuTemp_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_temp_1 = obj;
                                            lv_obj_set_pos(obj, 5, 29);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature:");
                                        }
                                        {
                                            // t1_cpuTemp_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_temp_1 = obj;
                                            lv_obj_set_pos(obj, 155, 22);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00C");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuUsage_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_usage_1 = obj;
                                            lv_obj_set_pos(obj, 5, 58);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Usage:");
                                        }
                                        {
                                            // t1_cpuUsage_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_usage_1 = obj;
                                            lv_obj_set_pos(obj, 173, 51);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "0%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuPower_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_power_1 = obj;
                                            lv_obj_set_pos(obj, 5, 87);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Power:");
                                        }
                                        {
                                            // t1_cpuPower_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_power_1 = obj;
                                            lv_obj_set_pos(obj, 149, 80);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00W");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_cpuFrequency_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_cpu_frequency_1 = obj;
                                            lv_obj_set_pos(obj, 5, 116);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Freq:");
                                        }
                                        {
                                            // t1_cpuFrequency_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_cpu_frequency_1 = obj;
                                            lv_obj_set_pos(obj, 84, 109);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "0000MHz");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    // l2_cpuTemp
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.l2_cpu_temp = obj;
                                    lv_obj_set_pos(obj, -1, 7);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Temperature:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t2_temp_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t2_temp_label = obj;
                                    lv_obj_set_pos(obj, 262, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00 °C");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t2_temp_bar
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.t2_temp_bar = obj;
                                    lv_obj_set_pos(obj, 0, 39);
                                    lv_obj_set_size(obj, 285, 20);
                                    lv_bar_set_value(obj, 50, LV_ANIM_ON);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff748493), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000bff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffff0035), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 180, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_main_stop(obj, 70, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 91);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Clock:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t2_clock_bar
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.t2_clock_bar = obj;
                                    lv_obj_set_pos(obj, 0, 133);
                                    lv_obj_set_size(obj, 285, 20);
                                    lv_bar_set_range(obj, 0, 4800);
                                    lv_bar_set_value(obj, 2400, LV_ANIM_ON);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff748493), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000bff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffff0035), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 180, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_main_stop(obj, 70, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                }
                                {
                                    // t2_clock_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t2_clock_label = obj;
                                    lv_obj_set_pos(obj, 232, 93);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00 MHz");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // m1_cpu
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    objects.m1_cpu = obj;
                                    lv_obj_set_pos(obj, 323, 123);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_cpu);
                                }
                                {
                                    // m1_cpu_1
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    objects.m1_cpu_1 = obj;
                                    lv_obj_set_pos(obj, 323, 29);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_temperature);
                                }
                            }
                        }
                        {
                            // tab3
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "GPU");
                            objects.tab3 = obj;
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC);
                            lv_obj_set_style_bg_img_src(obj, &img_dark_wavy, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // GPU_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.gpu_1 = obj;
                                    lv_obj_set_pos(obj, 74, 262);
                                    lv_obj_set_size(obj, 220, 146);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_gpu_1, LV_EVENT_ALL, flowState);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_rounded(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff4c4c4c), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_opa(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_clip_corner(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // label_container_gpu_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_container_gpu_1 = obj;
                                            lv_obj_set_pos(obj, 93, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "GPU");
                                            lv_obj_set_style_text_letter_space(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuTemp_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_temp_1 = obj;
                                            lv_obj_set_pos(obj, 6, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature:");
                                        }
                                        {
                                            // t1_gpuTemp_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_temp_1 = obj;
                                            lv_obj_set_pos(obj, 157, 8);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00C");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuUsage_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_usage_1 = obj;
                                            lv_obj_set_pos(obj, 5, 50);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Usage:");
                                        }
                                        {
                                            // t1_gpuUsage_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_usage_1 = obj;
                                            lv_obj_set_pos(obj, 154, 42);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "00%");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuCoreFrequency_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_core_frequency_1 = obj;
                                            lv_obj_set_pos(obj, 6, 86);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Freq:");
                                        }
                                        {
                                            // t1_gpuCoreFrequency_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_core_frequency_1 = obj;
                                            lv_obj_set_pos(obj, 103, 77);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "000MHz");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            // l1_gpuMemoryFreq_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.l1_gpu_memory_freq_1 = obj;
                                            lv_obj_set_pos(obj, 6, 118);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "MEM:");
                                        }
                                        {
                                            // t1_gpuMemoryFreq_1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.t1_gpu_memory_freq_1 = obj;
                                            lv_obj_set_pos(obj, 86, 111);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "0000MHz");
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    // l3_gpuTemp
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.l3_gpu_temp = obj;
                                    lv_obj_set_pos(obj, -1, 7);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Temperature:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t3_temp_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t3_temp_label = obj;
                                    lv_obj_set_pos(obj, 262, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00 °C");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t3_temp_bar
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.t3_temp_bar = obj;
                                    lv_obj_set_pos(obj, 0, 39);
                                    lv_obj_set_size(obj, 285, 20);
                                    lv_bar_set_value(obj, 50, LV_ANIM_ON);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff748493), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000bff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffff0035), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 180, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_main_stop(obj, 70, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 91);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Clock:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t3_clock_bar
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.t3_clock_bar = obj;
                                    lv_obj_set_pos(obj, 0, 133);
                                    lv_obj_set_size(obj, 285, 20);
                                    lv_bar_set_range(obj, 0, 4800);
                                    lv_bar_set_value(obj, 2400, LV_ANIM_ON);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff748493), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000bff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffff0035), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 180, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_main_stop(obj, 70, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                }
                                {
                                    // t3_clock_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t3_clock_label = obj;
                                    lv_obj_set_pos(obj, 232, 93);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00 MHz");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // tab4
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "MEM & HDD");
                            objects.tab4 = obj;
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_img_src(obj, &img_dark_wavy, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // m1_hdd
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    objects.m1_hdd = obj;
                                    lv_obj_set_pos(obj, 309, 93);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_hdd);
                                }
                                {
                                    // l1_ramUsage_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.l1_ram_usage_1 = obj;
                                    lv_obj_set_pos(obj, 15, 14);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "RAM Usage:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t4_ramUsage
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t4_ram_usage = obj;
                                    lv_obj_set_pos(obj, 228, 8);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00%");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // l1_hddUsage0_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.l1_hdd_usage0_1 = obj;
                                    lv_obj_set_pos(obj, 15, 60);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "HDD 1:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t4_hddUsage0
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t4_hdd_usage0 = obj;
                                    lv_obj_set_pos(obj, 228, 54);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00%");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // l1_hddUsage1_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.l1_hdd_usage1_1 = obj;
                                    lv_obj_set_pos(obj, 15, 107);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "HDD 2:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t4_hddUsage1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t4_hdd_usage1 = obj;
                                    lv_obj_set_pos(obj, 228, 100);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00%");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // l1_hddUsage3_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.l1_hdd_usage3_1 = obj;
                                    lv_obj_set_pos(obj, 15, 153);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "HDD 3:");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // t4_hddUsage2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.t4_hdd_usage2 = obj;
                                    lv_obj_set_pos(obj, 228, 146);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "00%");
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // m1_ram
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    objects.m1_ram = obj;
                                    lv_obj_set_pos(obj, 311, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_ram);
                                }
                            }
                        }
                        {
                            // tab5
                            lv_obj_t *obj = lv_tabview_add_tab(lv_obj_get_parent(parent_obj), "DECK");
                            objects.tab5 = obj;
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_img_src(obj, &img_grainy_gradients, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "TODO");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // led_comm_udp
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_comm_udp = obj;
            lv_obj_set_pos(obj, 393, 469);
            lv_obj_set_size(obj, 6, 6);
            lv_led_set_color(obj, lv_color_hex(4283197133));
            lv_led_set_brightness(obj, 255);
        }
        {
            // sys_ticks
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sys_ticks = obj;
            lv_obj_set_pos(obj, 5, 464);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 168, 464);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "WIFI IP:");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ip_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ip_text = obj;
            lv_obj_set_pos(obj, 226, 464);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "000.000.000.000");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // led_comm_can
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_comm_can = obj;
            lv_obj_set_pos(obj, 358, 469);
            lv_obj_set_size(obj, 6, 6);
            lv_led_set_color(obj, lv_color_hex(4293094669));
            lv_led_set_brightness(obj, 255);
        }
        {
            // led_comm_uart
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_comm_uart = obj;
            lv_obj_set_pos(obj, 376, 469);
            lv_obj_set_size(obj, 6, 6);
            lv_led_set_color(obj, lv_color_hex(4279091171));
            lv_led_set_brightness(obj, 255);
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalTextProperty(flowState, 85, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.sys_ticks);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.sys_ticks;
            lv_label_set_text(objects.sys_ticks, new_val);
            tick_value_change_obj = NULL;
        }
    }
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
