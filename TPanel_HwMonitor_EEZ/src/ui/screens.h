#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *cpu;
    lv_obj_t *cpu_1;
    lv_obj_t *gpu;
    lv_obj_t *gpu_1;
    lv_obj_t *ip_text;
    lv_obj_t *l1_cpu_frequency;
    lv_obj_t *l1_cpu_frequency_1;
    lv_obj_t *l1_cpu_power;
    lv_obj_t *l1_cpu_power_1;
    lv_obj_t *l1_cpu_temp;
    lv_obj_t *l1_cpu_temp_1;
    lv_obj_t *l1_cpu_usage;
    lv_obj_t *l1_cpu_usage_1;
    lv_obj_t *l1_gpu_core_frequency;
    lv_obj_t *l1_gpu_core_frequency_1;
    lv_obj_t *l1_gpu_memory_freq;
    lv_obj_t *l1_gpu_memory_freq_1;
    lv_obj_t *l1_gpu_temp;
    lv_obj_t *l1_gpu_temp_1;
    lv_obj_t *l1_gpu_usage;
    lv_obj_t *l1_gpu_usage_1;
    lv_obj_t *l1_hdd_usage0;
    lv_obj_t *l1_hdd_usage0_1;
    lv_obj_t *l1_hdd_usage1;
    lv_obj_t *l1_hdd_usage1_1;
    lv_obj_t *l1_hdd_usage3;
    lv_obj_t *l1_hdd_usage3_1;
    lv_obj_t *l1_ram_usage;
    lv_obj_t *l1_ram_usage_1;
    lv_obj_t *l2_cpu_temp;
    lv_obj_t *l3_gpu_temp;
    lv_obj_t *label_container_cpu;
    lv_obj_t *label_container_cpu_1;
    lv_obj_t *label_container_gpu;
    lv_obj_t *label_container_gpu_1;
    lv_obj_t *label_container_mem_hdd;
    lv_obj_t *led_comm_can;
    lv_obj_t *led_comm_uart;
    lv_obj_t *led_comm_udp;
    lv_obj_t *m1_cpu;
    lv_obj_t *m1_cpu_1;
    lv_obj_t *m1_hdd;
    lv_obj_t *m1_ram;
    lv_obj_t *mem_hdd;
    lv_obj_t *sys_ticks;
    lv_obj_t *t1_cpu_frequency;
    lv_obj_t *t1_cpu_frequency_1;
    lv_obj_t *t1_cpu_power;
    lv_obj_t *t1_cpu_power_1;
    lv_obj_t *t1_cpu_temp;
    lv_obj_t *t1_cpu_temp_1;
    lv_obj_t *t1_cpu_usage;
    lv_obj_t *t1_cpu_usage_1;
    lv_obj_t *t1_gpu_core_frequency;
    lv_obj_t *t1_gpu_core_frequency_1;
    lv_obj_t *t1_gpu_memory_freq;
    lv_obj_t *t1_gpu_memory_freq_1;
    lv_obj_t *t1_gpu_temp;
    lv_obj_t *t1_gpu_temp_1;
    lv_obj_t *t1_gpu_usage;
    lv_obj_t *t1_gpu_usage_1;
    lv_obj_t *t1_hdd_usage0;
    lv_obj_t *t1_hdd_usage1;
    lv_obj_t *t1_hdd_usage2;
    lv_obj_t *t1_ram_usage;
    lv_obj_t *t2_clock_bar;
    lv_obj_t *t2_clock_label;
    lv_obj_t *t2_temp_bar;
    lv_obj_t *t2_temp_label;
    lv_obj_t *t3_clock_bar;
    lv_obj_t *t3_clock_label;
    lv_obj_t *t3_temp_bar;
    lv_obj_t *t3_temp_label;
    lv_obj_t *t4_hdd_usage0;
    lv_obj_t *t4_hdd_usage1;
    lv_obj_t *t4_hdd_usage2;
    lv_obj_t *t4_ram_usage;
    lv_obj_t *tab1;
    lv_obj_t *tab2;
    lv_obj_t *tab3;
    lv_obj_t *tab4;
    lv_obj_t *tab5;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/