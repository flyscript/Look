#include <tizen.h>
#include <app.h>
#include <watch_app.h>
#include <watch_app_efl.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <device/battery.h>

#include "look.h"
#include "view.h"
#include "data.h"

static struct main_info {
	int sec_min_restart;
	int cur_day;
	bool heartrate_supported;
	int cur_heartrate;
	int cur_steps;
	int cur_month;
	int cur_weekday;
	bool ambient;
	bool low_battery;
	bool smooth_tick;
	int cur_min;
} s_info = {
	.sec_min_restart = 0,
	.cur_day = 0,
	.heartrate_supported = false,
	.cur_heartrate = 70,
	.cur_steps = 70,
	.cur_month = 0,
	.cur_weekday = 0,
	.ambient = false,
	.low_battery = false,
	.smooth_tick = false,
	.cur_min = 0
};

static void _set_time(int hour, int min, int sec);
static void _set_date(int day, int month, int day_of_week);
static void _set_heartrate(int rate);
static void _set_steps(int steps);
static void _set_battery(int bat);
static Evas_Object *_create_parts(parts_type_e type);
static void _create_base_gui(int width, int height);

/**
 * @brief The system language changed event callback function.
 * @param[in] event_info The system event information
 * @param[in] user_data The user data passed from the add event handler function
 */
void lang_changed(app_event_info_h event_info, void* user_data)
{
	/*
	 * Takes necessary actions when language setting is changed
	 */
	char *locale = NULL;

	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	if (locale == NULL)
		return;

	elm_language_set(locale);
	free(locale);

	return;
}

/**
 * @brief The region format changed event callback function.
 * @param[in] event_info The system event information
 * @param[in] user_data The user data passed from the add event handler function
 */
void region_changed(app_event_info_h event_info, void* user_data)
{
	/*
	 * Takes necessary actions when region setting is changed
	 */
}

/**
 * @brief The low battery event callback function.
 * @param[in] event_info The system event information
 * @param[in] user_data The user data passed from the add event handler function
 */
void low_battery(app_event_info_h event_info, void* user_data)
{
	/*
	 * Takes necessary actions when system is running on low battery
	 */
}

/**
 * @brief The low memory event callback function.
 * @param[in] event_info The system event information
 * @param[in] user_data The user data passed from the add event handler function
 */
void low_memory(app_event_info_h event_info, void* user_data)
{
	/*
	 * Takes necessary actions when system is running on low memory
	 */
	watch_app_exit();
}

/**
 * @brief The device orientation changed event callback function.
 * @param[in] event_info The system event information
 * @param[in] user_data The user data passed from the add event handler function
 */
void device_orientation(app_event_info_h event_info, void* user_data)
{
	/*
	 * Takes necessary actions when device orientation is changed
	 */
}

/**
 * @brief Called when the application starts.
 * @param[in] width The width of the window of idle screen that will show the watch UI
 * @param[in] height The height of the window of idle screen that will show the watch UI
 * @param[in] user_data The user data passed from the callback registration function
 */
static bool app_create(int width, int height, void* user_data)
{
	/*
	 * Hook to take necessary actions before main event loop starts
	 * Initialize UI resources and application's data
	 */

	app_event_handler_h handlers[5] = { NULL, };

	/*
	 * Register callbacks for each system event
	 */
	if (watch_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, lang_changed, NULL) != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_add_event_handler () is failed");

	if (watch_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, region_changed, NULL) != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_add_event_handler () is failed");

	if (watch_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, low_battery, NULL) != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_add_event_handler () is failed");

	if (watch_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, low_memory, NULL) != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_add_event_handler () is failed");

	if (watch_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, device_orientation, NULL) != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_add_event_handler () is failed");

	dlog_print(DLOG_DEBUG, LOG_TAG, "%s", __func__);

	/*
	 * Create base GUI
	 */
	_create_base_gui(width, height);

	// Check features
	/*sensor_type_e type = SENSOR_HRM;
	sensor_h sensor;

	bool heartrateSupported;
	int error = sensor_is_supported(type, &heartrateSupported);
	if (error != SENSOR_ERROR_NONE)
	{
	    dlog_print(DLOG_ERROR, LOG_TAG, "sensor_is_supported error: %d", error);
	}

    dlog_print(DLOG_DEBUG, LOG_TAG, "HRM is%s supported", supported ? "" : " not");
*/
    s_info.heartrate_supported = true;//heartrateSupported;

	return true;
}

/**
 * @brief Called when another application sends a launch request to the application.
 * @param[in] width The width of the window of idle screen that will show the watch UI
 * @param[in] height The height of the window of idle screen that will show the watch UI
 * @param[in] user_data The user data passed from the callback registration function
 */
static void app_control(app_control_h app_control, void *user_data)
{
	/*
	 * Handle the launch request.
	 */
}

/**
 * @brief Called when the application is completely obscured by another application and becomes invisible.
 * @param[in] user_data The user data passed from the callback registration function
 */
static void app_pause(void *user_data)
{
	/*
	 * Take necessary actions when application becomes invisible.
	 */

	s_info.smooth_tick = false;

	/* //TODO: Commented out because this might trigger a hangup

	edje_object_signal_emit(view_get_module_second_layout(),"second_stop_tick","");
	edje_object_signal_emit(view_get_module_minute_layout(),"minute_stop_tick","");
	*/

}

/**
 * @brief Called when the application becomes visible.
 * @param[in] user_data The user data passed from the callback registration function
 */
static void app_resume(void *user_data)
{
	/*
	 * Take necessary actions when application becomes visible.
	 */

	//	Flag smooth tick for restart
	s_info.smooth_tick = false;

}

/**
 * @brief Called when the application's main loop exits.
 * @param[in] user_data The user data passed from the callback registration function
 */
static void app_terminate(void *user_data)
{
	view_destroy_base_gui();
}

/**
 * @brief Called at each second. This callback is not called while the app is paused or the device is in ambient mode.
 * @param[in] watch_time The watch time handle. watch_time will not be available after returning this callback. It will be freed by the framework.
 * @param[in] user_data The user data to be passed to the callback functions
 */
void app_time_tick(watch_time_h watch_time, void* user_data)
{
	int hour = 0;
	int min = 0;
	int sec = 0;
	int year = 0;
	int month = 0;
	int day = 0;
	int day_of_week = 0;
	int battery_level = 0;
	int heart_rate = 69;
	int step_count = 420;

	watch_time_get_hour(watch_time, &hour);
	watch_time_get_minute(watch_time, &min);
	watch_time_get_second(watch_time, &sec);
	watch_time_get_day(watch_time, &day);
	watch_time_get_month(watch_time, &month);
	watch_time_get_year(watch_time, &year);
	watch_time_get_day_of_week(watch_time, &day_of_week);

	int ret = device_battery_get_percent(&battery_level);
	if (ret != 0)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get battery level");
		return;
	}

	// Time
	_set_time(hour, min, sec);

	// Date
	_set_date(day, month, day_of_week);

	// Battery
	_set_battery(battery_level);

	// Heart rate
	if (s_info.heartrate_supported)
	{
		_set_heartrate(heart_rate);
	}

	// Steps
	_set_steps(step_count);
}

/**
 * @brief Called at each minute when the device in the ambient mode.
 * @param[in] watch_time The watch time handle. watch_time will not be available after returning this callback. It will be freed by the framework
 * @param[in] user_data The user data to be passed to the callback functions
 */
void app_ambient_tick(watch_time_h watch_time, void* user_data)
{
	int hour = 0;
	int min = 0;
	int battery_level = 0;

	watch_time_get_hour(watch_time, &hour);
	watch_time_get_minute(watch_time, &min);

	_set_time(hour, min, 0);

	int ret = device_battery_get_percent(&battery_level);
	if (ret != 0)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get battery level");
		return;
	}

	_set_battery(battery_level);
}

/**
 * @brief Called when the device enters or exits the ambient mode.
 * @param[in] ambient_mode If @c true the device enters the ambient mode, otherwise @c false
 * @param[in] user_data The user data to be passed to the callback functions
 */
void app_ambient_changed(bool ambient_mode, void* user_data)
{
	s_info.ambient = ambient_mode;

	Evas_Object *bg = NULL;
	Evas_Object *object = NULL;
	Evas_Object *hands = NULL;

	bg = view_get_bg();
	if (bg == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get bg");
		return;
	}

	if (ambient_mode) // Ambient
	{
		// Set Watchface
		set_object_background_image(bg, (s_info.low_battery ? IMAGE_BG_AMBIENT_LOWBAT : IMAGE_BG_AMBIENT));

		object = view_get_bg_plate();
		evas_object_hide(object);

		// Set Left & Right Modules
		object = view_get_module_left_layout();
		edje_object_signal_emit(object,"set_ambient","");
		if (s_info.low_battery)
		{
			evas_object_hide(object);
		}

		object = view_get_module_right_layout();
		edje_object_signal_emit(object,"set_ambient","");

		if (s_info.low_battery)
		{
			evas_object_hide(object);
		}

		// Set Step Module
		object = view_get_module_steps_layout();
		evas_object_hide(object);

		//Set Battery Hand
		hands = evas_object_data_get(bg, "__HANDS_BAT__");
		evas_object_hide(hands);
		hands = evas_object_data_get(bg, "__HANDS_BAT_SHADOW__");
		evas_object_hide(hands);

		//Set Minute Hand
		set_object_background_image(evas_object_data_get(bg, "__HANDS_MIN__"), (s_info.low_battery ? IMAGE_HANDS_MIN_AMBIENT_LOWBAT : IMAGE_HANDS_MIN_AMBIENT));

		hands = evas_object_data_get(bg, "__HANDS_MIN_SHADOW__");
		evas_object_hide(hands);

		//Set Hour Hand
		set_object_background_image(evas_object_data_get(bg, "__HANDS_HOUR__"), (s_info.low_battery ? IMAGE_HANDS_HOUR_AMBIENT_LOWBAT : IMAGE_HANDS_HOUR_AMBIENT));

		hands = evas_object_data_get(bg, "__HANDS_HOUR_SHADOW__");
		evas_object_hide(hands);

		//Set Second Hand
		object = view_get_module_second_layout();
		edje_object_signal_emit(object,"second_set_ambient","");
		evas_object_hide(object);

		/*TODO: Commented out as smooth tick is re-implemented
		//Set Minute Hand
		object = view_get_module_minute_layout();
		edje_object_signal_emit(object,"minute_set_ambient","");
		*/

		s_info.smooth_tick = false;

	}
	else // Non-ambient
	{
		// Set Watchface
		set_object_background_image(bg, IMAGE_BG);
		object = view_get_bg_plate();
		evas_object_show(object);

		// Set Left & Right Modules
		object = view_get_module_left_layout();
		evas_object_show(object);
		edje_object_signal_emit(object,"set_default","");
		object = view_get_module_right_layout();
		evas_object_show(object);
		edje_object_signal_emit(object,"set_default","");

		// Set Step Module
		object = view_get_module_steps_layout();
		evas_object_show(object);

		//Set Battery Hand
		hands = evas_object_data_get(bg, "__HANDS_BAT__");
		evas_object_show(hands);
		hands = evas_object_data_get(bg, "__HANDS_BAT_SHADOW__");
		evas_object_show(hands);

		//Set Second Hand
		hands = view_get_module_second_layout();
		evas_object_show(hands);

		//Set Minute Hand
		set_object_background_image(evas_object_data_get(bg, "__HANDS_MIN__"), IMAGE_HANDS_MIN);
		hands = evas_object_data_get(bg, "__HANDS_MIN_SHADOW__");
		evas_object_show(hands);

		//Set Hour Hand
		set_object_background_image(evas_object_data_get(bg, "__HANDS_HOUR__"), IMAGE_HANDS_HOUR);
		hands = evas_object_data_get(bg, "__HANDS_HOUR_SHADOW__");
		evas_object_show(hands);
	}
}

/**
 * @brief Main function of the application.
 */
int main(int argc, char *argv[])
{
	int ret = 0;

	watch_app_lifecycle_callback_s event_callback = { 0, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;
	event_callback.time_tick = app_time_tick;
	event_callback.ambient_tick = app_ambient_tick;
	event_callback.ambient_changed = app_ambient_changed;

	ret = watch_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_main() is failed. err = %d", ret);
	}

	return ret;
}

/**
 * @brief Set time at the watch.
 * @pram[in] hour The hour number
 * @pram[in] min The min number
 * @pram[in] sec The sec number
 */
static void _set_time(int hour, int min, int sec)
{
	Evas_Object *bg = NULL;
	Evas_Object *hands = NULL;
	Evas_Object *hands_shadow = NULL;
	double degree = 0.0f;

	bg = view_get_bg();
	if (bg == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get bg");
		return;
	}

	/*
	 * Rotate hands at the watch
	 */
	if (!s_info.ambient && !s_info.smooth_tick)
	{
		s_info.smooth_tick = true;
		degree = sec * SEC_ANGLE;
		hands = view_get_module_second_layout();
		view_rotate_hand(hands, degree, (BASE_WIDTH / 2), (BASE_HEIGHT / 2));
		edje_object_signal_emit(hands,"second_start_tick","");
	}

	degree = (min * MIN_ANGLE) + data_get_minute_plus_angle(sec);
	hands = evas_object_data_get(bg, "__HANDS_MIN__");
	view_rotate_hand(hands, degree, (BASE_WIDTH / 2), (BASE_HEIGHT / 2));
	hands_shadow = evas_object_data_get(bg, "__HANDS_MIN_SHADOW__");
	view_rotate_hand(hands_shadow, degree, (BASE_WIDTH / 2), (BASE_HEIGHT / 2) + HANDS_MIN_SHADOW_PADDING);

	if (s_info.cur_min != min)
	{
		s_info.cur_min = min;

		degree = (hour * HOUR_ANGLE) + data_get_hour_plus_angle(min, sec);
		hands = evas_object_data_get(bg, "__HANDS_HOUR__");
		view_rotate_hand(hands, degree, (BASE_WIDTH / 2), (BASE_HEIGHT / 2));
		hands_shadow = evas_object_data_get(bg, "__HANDS_HOUR_SHADOW__");
		view_rotate_hand(hands_shadow, degree, (BASE_WIDTH / 2), (BASE_HEIGHT / 2) + HANDS_HOUR_SHADOW_PADDING);
	}
}

/**
 * @brief Set battery level of the watch.
 * @pram[in] bat The battery level
 */
static void _set_battery(int bat)
{
	Evas_Object *bg = NULL;
	Evas_Object *hands = NULL;
	Evas_Object *hands_shadow = NULL;
	double degree = 0.0f;

	bg = view_get_bg();
	if (bg == NULL)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get bg");
		return;
	}

	/*
	 *
	 *  Adjust battery indicator status
	 */

	// Low Battery
	if (bat <= LOW_BATTERY_LEVEL && !s_info.low_battery)
	{
		s_info.low_battery = true;

		set_object_background_image(evas_object_data_get(bg, "__HANDS_BAT__"), IMAGE_HANDS_BAT_LOWBAT);

		if (s_info.ambient)
		{
			set_object_background_image(bg, IMAGE_BG_AMBIENT_LOWBAT);
			evas_object_hide(view_get_module_left_layout());
			evas_object_hide(view_get_module_right_layout());
			set_object_background_image(evas_object_data_get(bg, "__HANDS_MIN__"), IMAGE_HANDS_MIN_AMBIENT_LOWBAT);
			set_object_background_image(evas_object_data_get(bg, "__HANDS_HOUR__"), IMAGE_HANDS_HOUR_AMBIENT_LOWBAT);
		}
	}
	// Regular Battery
	else if (bat > LOW_BATTERY_LEVEL && s_info.low_battery)
	{
		s_info.low_battery = false;

		set_object_background_image(evas_object_data_get(bg, "__HANDS_BAT__"), IMAGE_HANDS_BAT);

		if (s_info.ambient)
		{
			set_object_background_image(bg, IMAGE_BG_AMBIENT);
			evas_object_show(view_get_module_left_layout());
			evas_object_show(view_get_module_right_layout());
			set_object_background_image(evas_object_data_get(bg, "__HANDS_MIN__"), IMAGE_HANDS_MIN_AMBIENT);
			set_object_background_image(evas_object_data_get(bg, "__HANDS_HOUR__"), IMAGE_HANDS_HOUR_AMBIENT);
		}
	}

	// Rotate battery hand
	if (!s_info.ambient)
	{
		degree = BATTERY_START_ANGLE + (bat * BATTERY_ANGLE);
		hands = evas_object_data_get(bg, "__HANDS_BAT__");
		view_rotate_hand(hands, degree, (BASE_WIDTH / 2), (BASE_HEIGHT / 2));
		hands_shadow = evas_object_data_get(bg, "__HANDS_BAT_SHADOW__");
		view_rotate_hand(hands_shadow, degree, (BASE_WIDTH / 2), (BASE_HEIGHT / 2) + HANDS_BAT_SHADOW_PADDING);
	}
}

/**
 * @brief Set date on the watch.
 * @pram[in] day The day number
 * @pram[in] month The month number
 * @pram[in] day_of_week The day of week number
 */
static void _set_date(int day, int month, int day_of_week)
{
	Evas_Object *module_layout = NULL;
	char txt_day_num[32] = { 0, };
	char txt_day_txt[4] = { 0, };

	/*
	 * Set day on the watch
	 */
	if (s_info.cur_day != day) {
		module_layout = view_get_module_left_layout();

		snprintf(txt_day_num, sizeof(txt_day_num), "%d", day);
		view_set_text(module_layout, "txt.day.num", txt_day_num);

		snprintf(txt_day_txt, sizeof(txt_day_txt), "%s", get_day_of_week(day_of_week));
		view_set_text(module_layout, "txt.day.txt", txt_day_txt);

		s_info.cur_day = day;
	}
}

/**
 * @brief Set heart rate on the watch.
 * @pram[in] rate The BPM
 */
static void _set_heartrate(int rate)
{
	Evas_Object *module_layout = NULL;
	char txt_rate_num[32] = { 0, };

	/*
	 * Set heart rate on the watch
	 */
	if (s_info.cur_heartrate != rate) {
		module_layout = view_get_module_right_layout();

		snprintf(txt_rate_num, sizeof(txt_rate_num), "%d", rate);
		view_set_text(module_layout, "txt.heartrate.num", txt_rate_num);

		s_info.cur_heartrate = rate;
	}
}

/**
 * @brief Set steps on the watch.
 * @pram[in] rate The BPM
 */
static void _set_steps(int steps)
{
	Evas_Object *module_layout = NULL;
	char txt_steps_num[32] = { 0, };

	if (s_info.cur_steps != steps) {
		module_layout = view_get_module_steps_layout();

		snprintf(txt_steps_num, sizeof(txt_steps_num), "%s", getCounterDigit(steps));
/*
		char steps_0[2] = { 0, };
		snprintf(steps_0, sizeof(steps_0), "%s", txt_steps_num[0]);
		view_set_text(module_layout, "txt.0.num", steps_0);

		char steps_1[2] = { 0, };
		snprintf(steps_1, sizeof(steps_1), "%s", txt_steps_num[1]);
		view_set_text(module_layout, "txt.1.num", steps_1);

		char steps_2[2] = { 0, };
		snprintf(steps_2, sizeof(steps_2), "%s", txt_steps_num[2]);
		view_set_text(module_layout, "txt.2.num", steps_2);

		char steps_3[2] = { 0, };
		snprintf(steps_3, sizeof(steps_3), "%s", txt_steps_num[3]);
		view_set_text(module_layout, "txt.3.num", steps_3);

		char steps_4[2] = { 0, };
		snprintf(steps_4, sizeof(steps_4), "%s", txt_steps_num[4]);
		view_set_text(module_layout, "txt.4.num", steps_4);
*/
		s_info.cur_steps = steps;
	}
}

/**
 * @brief Create parts of watch.
 * @param[in] type Parts type
 */
static Evas_Object *_create_parts(parts_type_e type)
{
	Evas_Object *parts = NULL;
	Evas_Object *bg = NULL;
	char *parts_image_path = NULL;
	int x = 0, y = 0, w = 0, h = 0;

	/*
	 * Get the BG
	 */
	bg = view_get_bg();

	/*
	 * Get the information about the part
	 */
	parts_image_path = data_get_parts_image_path(type);
	data_get_parts_position(type, &x, &y);
	w = data_get_parts_width_size(type);
	h = data_get_parts_height_size(type);

	/*
	 * Create the part object
	 */
	parts = view_create_parts(bg, parts_image_path, x, y, w, h);
	if (parts == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create parts : %d", type);
	}

	free(parts_image_path);

	/*
	 * Set opacity to shadow hands
	 */
	if (type == PARTS_TYPE_HANDS_HOUR_SHADOW ||
			type == PARTS_TYPE_HANDS_MIN_SHADOW ||
			type == PARTS_TYPE_HANDS_SEC_SHADOW) {
		view_set_opacity_to_parts(parts);
	}

	return parts;
}

/**
 * @brief Create base GUI for the watch.
 * @param[in] width The width size of the watch
 * @param[in] height The height size of the watch
 */
static void _create_base_gui(int width, int height)
{
	Evas_Object *win = NULL;
	Evas_Object *bg = NULL;
	Evas_Object *bg_plate = NULL;
	Evas_Object *module_left_layout = NULL;
	Evas_Object *module_right_layout = NULL;
	Evas_Object *module_steps_layout = NULL;
	Evas_Object *module_sec_layout = NULL;
	Evas_Object *hands_min = NULL;
	Evas_Object *hands_min_shadow = NULL;
	Evas_Object *hands_hour = NULL;
	Evas_Object *hands_hour_shadow = NULL;
	Evas_Object *hands_bat = NULL;
	Evas_Object *hands_bat_shadow = NULL;
	char bg_path[PATH_MAX] = { 0, };
	char bg_plate_path[PATH_MAX] = { 0, };
	char edj_path[PATH_MAX] = { 0, };
	int ret = 0;

	/*
	 * Get window object
	 */
	ret = watch_app_get_elm_win(&win);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed to get window. err = %d", ret);
		return;
	}
	evas_object_resize(win, width, height);
	evas_object_show(win);

	/*
	 * Get background image file path
	 */
	data_get_resource_path(IMAGE_BG, bg_path, sizeof(bg_path));

	/*
	 * Create BG
	 */
	bg = view_create_bg(win, bg_path, width, height);
	if (bg == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create a bg");
		return;
	}

	/*
	 * Create hands & shadow hands to display the battery level
	 */

	hands_bat_shadow = _create_parts(PARTS_TYPE_HANDS_BAT_SHADOW);
	evas_object_data_set(bg, "__HANDS_BAT_SHADOW__", hands_bat_shadow);
	hands_bat = _create_parts(PARTS_TYPE_HANDS_BAT);
	evas_object_data_set(bg, "__HANDS_BAT__", hands_bat);

	/*
	 * Get background plate image file path
	 */
	data_get_resource_path(IMAGE_BG_PLATE, bg_plate_path, sizeof(bg_plate_path));

	/*
	 * Create BG Plate
	 */
	bg_plate = view_create_bg_plate(bg, bg_plate_path, BG_PLATE_WIDTH, BG_PLATE_HEIGHT);
	if (bg_plate == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create bg plate");
		return;
	}

	/*
	 * Get edje file path
	 */
	data_get_resource_path(EDJ_FILE, edj_path, sizeof(edj_path));

	/*
	 * Create layout to display left module on watch
	 */
	module_left_layout = view_create_module_layout(bg, edj_path, "layout_module_left");
	if (module_left_layout)
	{
		view_set_module_property(module_left_layout, WATCH_LEFT_MODULE_RIGHT_PADDING, (BASE_HEIGHT / 2) - (WATCH_LEFT_MODULE_SIZE / 2), WATCH_LEFT_MODULE_SIZE, WATCH_LEFT_MODULE_SIZE);
		view_set_module_left_layout(module_left_layout);
	}

	/*
	 * Create layout to display right module on watch
	 */
	module_right_layout = view_create_module_layout(bg, edj_path, "layout_module_right");
	if (module_right_layout)
	{
		view_set_module_property(module_right_layout, BASE_WIDTH - WATCH_RIGHT_MODULE_SIZE - WATCH_RIGHT_MODULE_LEFT_PADDING, (BASE_HEIGHT / 2) - (WATCH_RIGHT_MODULE_SIZE / 2), WATCH_RIGHT_MODULE_SIZE, WATCH_RIGHT_MODULE_SIZE);
		view_set_module_right_layout(module_right_layout);
	}

	/*
	 * Create layout to display steps module on watch
	 */
	module_steps_layout = view_create_module_layout(bg, edj_path, "layout_module_steps");
	if (module_right_layout)
	{
		view_set_module_property(module_steps_layout, (BASE_WIDTH / 2) - (WATCH_STEPS_MODULE_SIZE_X/2) + WATCH_STEPS_MODULE_PADDING_X, (BASE_HEIGHT / 2) - (WATCH_STEPS_MODULE_SIZE_Y / 2) + WATCH_STEPS_MODULE_PADDING_Y, WATCH_STEPS_MODULE_SIZE_X, WATCH_STEPS_MODULE_SIZE_Y);
		view_set_module_steps_layout(module_steps_layout);
	}

	/*
	 * Create hands & shadow hands to display at the watch
	 */
	hands_min_shadow = _create_parts(PARTS_TYPE_HANDS_MIN_SHADOW);
	evas_object_data_set(bg, "__HANDS_MIN_SHADOW__", hands_min_shadow);
	hands_min = _create_parts(PARTS_TYPE_HANDS_MIN);
	evas_object_data_set(bg, "__HANDS_MIN__", hands_min);

	hands_hour_shadow = _create_parts(PARTS_TYPE_HANDS_HOUR_SHADOW);
	evas_object_data_set(bg, "__HANDS_HOUR_SHADOW__", hands_hour_shadow);
	hands_hour = _create_parts(PARTS_TYPE_HANDS_HOUR);
	evas_object_data_set(bg, "__HANDS_HOUR__", hands_hour);

	/*
	 * Create layout to display second hand on the watch
	 */
	module_sec_layout = view_create_module_layout(bg, edj_path, "layout_module_second");
	if (module_sec_layout)
	{
		view_set_module_property(module_sec_layout, 0, 0, 360, 360);
		view_set_module_second_layout(module_sec_layout);
	}
}
