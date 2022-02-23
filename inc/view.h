#if !defined(_VIEW_H)
#define _VIEW_H

#define EDJ_FILE "edje/main.edj"

void view_set_module_day_layout(Evas_Object *layout);
void view_set_module_second_layout(Evas_Object *layout);
void view_set_module_minute_layout(Evas_Object *layout);
Evas_Object *view_get_bg(void);
Evas_Object *view_get_bg_plate(void);
Evas_Object *view_get_module_day_layout(void);
Evas_Object *view_get_module_second_layout(void);
Evas_Object *view_get_module_minute_layout(void);

/*
 * Create a view
 */
void view_set_text(Evas_Object *parent, const char *part_name, const char *text);
void view_rotate_hand(Evas_Object *hand, double degree, Evas_Coord cx, Evas_Coord cy);
//void view_rotate_moonphase(float degree);
Evas_Object *view_create_layout(Evas_Object *parent, const char *file_path, const char *group_name, void *user_data);
Evas_Object *view_create_bg(Evas_Object *win, const char *image_path, int width, int height);
Evas_Object *view_create_bg_plate(Evas_Object *bg, const char *image_path, int width, int height);
void view_set_module_property(Evas_Object *layout, int x, int y, int w, int h);
Evas_Object *view_create_module_layout(Evas_Object *parent, const char *file_path, const char *group_name);
void view_set_opacity_to_parts(Evas_Object *parts);
Evas_Object *view_create_parts(Evas_Object *parent, const char *image_path, int x, int y, int w, int h);

void view_create_base_gui(int width, int height);
void view_destroy_base_gui(void);

#endif
