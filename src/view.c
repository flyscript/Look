#include <Elementary.h>
#include <efl_extension.h>
#include <app.h>
#include <dlog.h>

#include "look.h"
#include "view.h"

static struct view_info {
	Evas_Object *bg;
	Evas_Object *plate;
	Evas_Object *module_left_layout;
	Evas_Object *module_right_layout;
	Evas_Object *module_second_layout;
	Evas_Object *module_minute_layout;
} s_info = {
	.bg = NULL,
	.plate = NULL,
	.module_left_layout = NULL,
	.module_right_layout = NULL,
	.module_second_layout = NULL,
	.module_minute_layout = NULL,
};

/**
 * @brief Set the module left layout.
 */
void view_set_module_left_layout(Evas_Object *layout)
{
	if (layout == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "layout is NULL");
		return;
	}

	s_info.module_left_layout = layout;
}

/**
 * @brief Set the module right layout.
 */
void view_set_module_right_layout(Evas_Object *layout)
{
	if (layout == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "layout is NULL");
		return;
	}

	s_info.module_right_layout = layout;
}

/**
 * @brief Set the module second layout.
 */
void view_set_module_second_layout(Evas_Object *layout)
{
	if (layout == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "layout is NULL");
		return;
	}

	s_info.module_second_layout = layout;
}

/**
 * @brief Set the module minute layout.
 */
void view_set_module_minute_layout(Evas_Object *layout)
{
	if (layout == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "layout is NULL");
		return;
	}

	s_info.module_minute_layout = layout;
}

/**
 * @brief Get the bg object.
 */
Evas_Object *view_get_bg(void)
{
	return s_info.bg;
}

/**
 * @brief Get the bg plate object.
 */
Evas_Object *view_get_bg_plate(void)
{
	return s_info.plate;
}

/**
 * @brief Get the module left layout.
 */
Evas_Object *view_get_module_left_layout(void)
{
	return s_info.module_left_layout;
}

/**
 * @brief Get the module right layout.
 */
Evas_Object *view_get_module_right_layout(void)
{
	return s_info.module_right_layout;
}

/**
 * @brief Get the module second layout.
 */
Evas_Object *view_get_module_second_layout(void)
{
	return s_info.module_second_layout;
}

/**
 * @brief Get the module minute layout.
 */
Evas_Object *view_get_module_minute_layout(void)
{
	return s_info.module_minute_layout;
}

/**
 * @brief Set text to the part.
 * @param[in] parent Object has part to which you want to set text
 * @param[in] part_name Part name to which you want to set the text
 * @param[in] text Text you want to set to the part
 */
void view_set_text(Evas_Object *parent, const char *part_name, const char *text)
{
	if (parent == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return;
	}

	/* Set text of target part object */
	elm_object_part_text_set(parent, part_name, text);
}

/**
 * @brief Rotate hands of the watch.
 * @param[in] hand The hand you want to rotate
 * @param[in] degree The degree you want to rotate
 * @param[in] cx The rotation's center horizontal position
 * @param[in] cy The rotation's center vertical position
 */
void view_rotate_hand(Evas_Object *hand, double degree, Evas_Coord cx, Evas_Coord cy)
{
	Evas_Map *m = NULL;

	if (hand == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "hand is NULL");
		return;
	}

	m = evas_map_new(4);
	evas_map_util_points_populate_from_object(m, hand);
	evas_map_util_rotate(m, degree, cx, cy);
	evas_object_map_set(hand, m);
	evas_object_map_enable_set(hand, EINA_TRUE);
	evas_map_free(m);
}

/**
 * @breif Create a bg object for the watch
 * @param[in] win The window object
 * @param[in] image_path The image path for bg
 * @param[in] width The width size of bg
 * @param[in] height The height size of bg
 */
Evas_Object *view_create_bg(Evas_Object *win, const char *image_path, int width, int height)
{
	Evas_Object *bg = NULL;
	Eina_Bool ret = EINA_FALSE;

	if (win == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "window is NULL");
		return NULL;
	}

	bg = elm_bg_add(win);
	if (bg == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to add bg");
		return NULL;
	}

	ret = elm_bg_file_set(bg, image_path, NULL);
	if (ret != EINA_TRUE)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set the background image");
		evas_object_del(bg);
		return NULL;
	}

	elm_bg_option_set(bg, ELM_BG_OPTION_CENTER);

	evas_object_move(bg, 0, 0);
	evas_object_resize(bg, width, height);
	evas_object_show(bg);

	s_info.bg = bg;

	return bg;
}

/**
 * @breif Create a bg plate object for the watch
 * @param[in] win The window object
 * @param[in] image_path The image path for bg
 * @param[in] width The width size of bg
 * @param[in] height The height size of bg
 */
Evas_Object *view_create_bg_plate(Evas_Object *bg, const char *image_path, int width, int height)
{
	Evas_Object *plate = NULL;
	Eina_Bool ret = EINA_FALSE;

	if (bg == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "bg is NULL");
		return NULL;
	}

	plate = elm_image_add(bg);
	if (plate == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to add plate");
		return NULL;
	}

	ret = elm_bg_file_set(plate, image_path, NULL);
	if (ret != EINA_TRUE)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set the background image");
		evas_object_del(plate);
		return NULL;
	}

	elm_bg_option_set(plate, ELM_BG_OPTION_CENTER);

	evas_object_move(plate, (BASE_WIDTH / 2) - (width / 2), (BASE_HEIGHT / 2) - (width / 2));
	evas_object_resize(plate, width, height);
	evas_object_show(plate);

	s_info.plate = plate;

	return plate;
}

/**
 * @brief Make a layout to target parent object with edje file.
 * @param[in] parent The object to which you want to add this layout
 * @param[in] file_path File path of EDJ file will be used
 * @param[in] group_name Name of group in EDJ you want to set to
 * @param[in] user_data The user data to be passed to the callback functions
 */
Evas_Object *view_create_layout(Evas_Object *parent, const char *file_path, const char *group_name, void *user_data)
{
	Evas_Object *layout = NULL;

	if (parent == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL.");
		return NULL;
	}

	/*
	 * Create layout by EDC(edje file)
	 */
	layout = elm_layout_add(parent);
	elm_layout_file_set(layout, file_path, group_name);

	/*
	 * Layout size setting
	 */
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	evas_object_show(layout);

	return layout;
}

/**
 * @brief Set property for module layout.
 * @param[in] layout The object to which you want to set
 * @param[in] x The X coordinate of the module layout
 * @param[in] y The Y coordinate of the module layout
 * @param[in] w The width size of the module layout
 * @param[in] h The height size of the module layout
 */
void view_set_module_property(Evas_Object *layout, int x, int y, int w, int h)
{
	if (layout == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "layout is NULL");
		return;
	}

	evas_object_move(layout, x, y);
	evas_object_resize(layout, w, h);
}

/**
 * @brief Create a layout for the watch.
 * @param[in] parent The object to which you want to add this layout
 * @param[in] file_path File path of EDJ file will be used
 * @param[in] group_name Group name of EDJ group will be used
 */
Evas_Object *view_create_module_layout(Evas_Object *parent, const char *file_path, const char *group_name)
{
	Evas_Object *layout = NULL;

	if (parent == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "parent is NULL");
		return NULL;
	}

	if (file_path == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "file path is NULL");
		return NULL;
	}

	if (group_name == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "group name is NULL");
		return NULL;
	}

	layout = view_create_layout(parent, file_path, group_name, NULL);
	if (layout == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create module layout");
		return NULL;
	}

	evas_object_show(layout);

	return layout;
}

/**
 * @brief Set opacity to parts of watch.
 * @param[in] parts The parts of watch
 */
void view_set_opacity_to_parts(Evas_Object *parts)
{
	if (parts == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set opacity to parts");
		return;
	}

	evas_object_color_set(parts, 255, 255, 255, 255 * 0.5);
}

/**
 * @brief Create a part for the watch.
 * @param[in] parent The object to which you want to add this object
 * @param[in] image_path The path of the image file you want to set
 * @param[in] x The X coordinate of the part
 * @param[in] y The Y coordinate of the part
 * @param[in] w The width size of the part
 * @param[in] h The height size of the part
 */
Evas_Object *view_create_parts(Evas_Object *parent, const char *image_path, int x, int y, int w, int h)
{
	Evas_Object *parts = NULL;
	Eina_Bool ret = EINA_FALSE;

	if (parent == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "bg is NULL");
		return NULL;
	}

	parts = elm_image_add(parent);
	if (parts == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to add image");
		return NULL;
	}

	ret = elm_image_file_set(parts, image_path, NULL);
	if (ret != EINA_TRUE)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set image");
		evas_object_del(parts);
		return NULL;
	}

	evas_object_move(parts, x, y);
	evas_object_resize(parts, w, h);
	evas_object_show(parts);

	return parts;
}

/**
 * @brief Destroy base GUI.
 */
void view_destroy_base_gui(void)
{
	if (s_info.module_left_layout)
	{
		evas_object_del(s_info.module_left_layout);
		s_info.module_left_layout = NULL;
	}
	if (s_info.module_right_layout)
	{
		evas_object_del(s_info.module_right_layout);
		s_info.module_right_layout = NULL;
	}

	if (s_info.module_second_layout)
	{
		evas_object_del(s_info.module_second_layout);
		s_info.module_second_layout = NULL;
	}

	if (s_info.plate)
	{
		evas_object_del(s_info.plate);
		s_info.plate = NULL;
	}

	if (s_info.bg)
	{
		evas_object_data_del(s_info.bg, "__HANDS_SEC__");
		evas_object_data_del(s_info.bg, "__HANDS_SEC_SHADOW__");
		evas_object_data_del(s_info.bg, "__HANDS_MIN__");
		evas_object_data_del(s_info.bg, "__HANDS_MIN_SHADOW__");
		evas_object_data_del(s_info.bg, "__HANDS_HOUR__");
		evas_object_data_del(s_info.bg, "__HANDS_HOUR_SHADOW__");
		evas_object_data_del(s_info.bg, "__HANDS_BAT__");
		evas_object_data_del(s_info.bg, "__HANDS_BAT_SHADOW__");
		evas_object_del(s_info.bg);
		s_info.bg = NULL;
	}
}
