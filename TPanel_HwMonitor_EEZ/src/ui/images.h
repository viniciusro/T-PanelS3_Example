#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_blue_purple_swirls;
extern const lv_img_dsc_t img_grainy_gradients;
extern const lv_img_dsc_t img_abstract_waves;
extern const lv_img_dsc_t img_dark_wavy;
extern const lv_img_dsc_t img_cpu;
extern const lv_img_dsc_t img_temperature;
extern const lv_img_dsc_t img_hdd;
extern const lv_img_dsc_t img_ram;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[8];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/