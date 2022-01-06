/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd
 *
 * Licensed under the Flora License, Version 1.1 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://floralicense.org/license/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <app_common.h>
#include <Elementary.h>
#include <efl_extension.h>
#include <dlog.h>

#include "look.h"
#include "data.h"

#define MINIMUM_DAY_DIFFERENCE 32

typedef struct _date_info {
	int year;
	int month;
	int day;
} date_info_s;

/**
 * @brief Get path of resource.
 * @param[in] file_in File name
 * @param[out] file_path_out The point to which save full path of the resource
 * @param[in] file_path_max Size of file name include path
 */
void data_get_resource_path(const char *file_in, char *file_path_out, int file_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(file_path_out, file_path_max, "%s%s", res_path, file_in);
		free(res_path);
	}
}

/**
 * @brief Initialization function for data module.
 */
void data_initialize(void)
{
	/*
	 * If you need to initialize managing data,
	 * please use this function.
	 */
}

/**
 * @brief Finalization function for data module.
 */
void data_finalize(void)
{
	/*
	 * If you need to finalize managing data,
	 * please use this function.
	 */
}

/**
 * @brief Get plus angle for the hour hand.
 * @param[in] minute Current minute
 * @param[in] second Current second
 */
int data_get_hour_plus_angle(int minute, int second)
{
	double minutes = minute + ((second/60) * 0.5);
	double angle = minute * 0.5;

	return angle;
}

/**
 * @brief Get a image path of the part.
 * @param[in] type The part type
 */
char *data_get_parts_image_path(parts_type_e type)
{
	char image_path[PATH_MAX] = { 0, };
	char *resource_image = NULL;

	switch (type) {
	case PARTS_TYPE_HANDS_SEC:
		resource_image = IMAGE_HANDS_SEC;
		break;
	case PARTS_TYPE_HANDS_MIN:
		resource_image = IMAGE_HANDS_MIN;
		break;
	case PARTS_TYPE_HANDS_HOUR:
		resource_image = IMAGE_HANDS_HOUR;
		break;
	case PARTS_TYPE_HANDS_MODULE_MONTH:
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY:
		resource_image = IMAGE_HANDS_MODULE_CALENDAR;
		break;
	case PARTS_TYPE_HANDS_SEC_SHADOW:
		resource_image = IMAGE_HANDS_SEC_SHADOW;
		break;
	case PARTS_TYPE_HANDS_MIN_SHADOW:
		resource_image = IMAGE_HANDS_MIN_SHADOW;
		break;
	case PARTS_TYPE_HANDS_HOUR_SHADOW:
		resource_image = IMAGE_HANDS_HOUR_SHADOW;
		break;
	case PARTS_TYPE_HANDS_MODULE_MONTH_SHADOW:
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY_SHADOW:
		resource_image = IMAGE_HANDS_MODULE_CALENDAR_SHADOW;
		break;
	default:
		dlog_print(DLOG_ERROR, LOG_TAG, "type error : %d", type);
		return NULL;
	}

	data_get_resource_path(resource_image, image_path, sizeof(image_path));

	return strdup(image_path);
}

/**
 * @brief Get a position of the part.
 * @param[in] type The part type
 * @param[out] x The pointer to an integer in which to store the X coordinate of the part
 * @param[out] y The pointer to an integer in which to store the Y coordinate of the part
 */
void data_get_parts_position(parts_type_e type, int *x, int *y)
{
	switch (type) {
	case PARTS_TYPE_HANDS_SEC:
		*x = (BASE_WIDTH / 2) - (HANDS_SEC_WIDTH / 2);
		*y = 0;
		break;
	case PARTS_TYPE_HANDS_MIN:
		*x = (BASE_WIDTH / 2) - (HANDS_MIN_WIDTH / 2);
		*y = 0;
		break;
	case PARTS_TYPE_HANDS_HOUR:
		*x = (BASE_WIDTH / 2) - (HANDS_HOUR_WIDTH / 2);
		*y = 0;
		break;
	case PARTS_TYPE_HANDS_MODULE_MONTH:
		*x = (BASE_WIDTH / 2) - HANDS_MODULE_CALENDAR_WIDTH - 54;
		*y = 175;
		break;
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY:
		*x = (BASE_WIDTH / 2) + 54;
		*y = 175;
		break;
	case PARTS_TYPE_HANDS_SEC_SHADOW:
		*x =  (BASE_WIDTH / 2) - (HANDS_SEC_WIDTH / 2);
		*y = HANDS_SEC_SHADOW_PADDING;
		break;
	case PARTS_TYPE_HANDS_MIN_SHADOW:
		*x = (BASE_WIDTH / 2) - (HANDS_MIN_WIDTH / 2);
		*y = HANDS_MIN_SHADOW_PADDING;
		break;
	case PARTS_TYPE_HANDS_HOUR_SHADOW:
		*x = (BASE_WIDTH / 2) - (HANDS_HOUR_WIDTH / 2);
		*y = HANDS_HOUR_SHADOW_PADDING;
		break;
	case PARTS_TYPE_HANDS_MODULE_MONTH_SHADOW:
		*x = (BASE_WIDTH / 2) - HANDS_MODULE_CALENDAR_WIDTH - 54;
		*y = 175 + HANDS_MODULE_CALENDAR_PADDING;
		break;
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY_SHADOW:
		*x = (BASE_WIDTH / 2) + 54;
		*y = 175 + HANDS_MODULE_CALENDAR_PADDING;
		break;
	default:
		dlog_print(DLOG_ERROR, LOG_TAG, "type error : %d", type);
		break;
	}

}

/**
 * @brief Get a width size of the part.
 * @param[in] type The part type
 */
int data_get_parts_width_size(parts_type_e type)
{
	int parts_width = 0;

	switch (type) {
	case PARTS_TYPE_HANDS_SEC:
	case PARTS_TYPE_HANDS_SEC_SHADOW:
		parts_width = HANDS_SEC_WIDTH;
		break;
	case PARTS_TYPE_HANDS_MIN:
	case PARTS_TYPE_HANDS_MIN_SHADOW:
		parts_width = HANDS_MIN_WIDTH;
		break;
	case PARTS_TYPE_HANDS_HOUR:
	case PARTS_TYPE_HANDS_HOUR_SHADOW:
		parts_width = HANDS_HOUR_WIDTH;
		break;
	case PARTS_TYPE_HANDS_MODULE_MONTH:
	case PARTS_TYPE_HANDS_MODULE_MONTH_SHADOW:
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY:
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY_SHADOW:
		parts_width = HANDS_MODULE_CALENDAR_WIDTH;
		break;
	default:
		dlog_print(DLOG_ERROR, LOG_TAG, "type error : %d", type);
		break;
	}

	return parts_width;
}

/**
 * @brief Get a height size of the part.
 * @param[in] type The part type
 */
int data_get_parts_height_size(parts_type_e type)
{
	int parts_height = 0;

	switch (type) {
	case PARTS_TYPE_HANDS_SEC:
	case PARTS_TYPE_HANDS_SEC_SHADOW:
		parts_height = HANDS_SEC_HEIGHT;
		break;
	case PARTS_TYPE_HANDS_MIN:
	case PARTS_TYPE_HANDS_MIN_SHADOW:
		parts_height = HANDS_MIN_HEIGHT;
		break;
	case PARTS_TYPE_HANDS_HOUR:
	case PARTS_TYPE_HANDS_HOUR_SHADOW:
		parts_height = HANDS_HOUR_HEIGHT;
		break;
	case PARTS_TYPE_HANDS_MODULE_MONTH:
	case PARTS_TYPE_HANDS_MODULE_MONTH_SHADOW:
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY:
	case PARTS_TYPE_HANDS_MODULE_WEEKDAY_SHADOW:
		parts_height = HANDS_MODULE_CALENDAR_HEIGHT;
		break;
	default:
		dlog_print(DLOG_ERROR, LOG_TAG, "type error : %d", type);
		break;
	}

	return parts_height;
}

/**
 * @brief Check whether a leap year.
 * @pram[in] year The year number
 */
static Eina_Bool _check_leap_year(int year)
{
	Eina_Bool ret = EINA_FALSE;

	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
		ret = EINA_TRUE;
	} else {
		ret = EINA_FALSE;
	}

	return ret;
}

/**
 * @brief Calculates total days.
 * @pram[in] day The day number
 * @pram[in] month The month number
 * @pram[in] year The year number
 */
/*
static int _get_total_days(int day, int month, int year)
{
	Eina_Bool is_leap_year = EINA_FALSE;
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int i = 0;
	long total = 0L;

	total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

	is_leap_year = _check_leap_year(year);
	if (is_leap_year) {
		months[1]++;
	}

	for (i = 0; i < month - 1; i++) {
		total += months[i];
	}

	total += day;

	return total;
}*/

char* get_day_of_week(int day)
{
	char months[8][3] = {"SAT", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
	char weekday[4] = { 0, };

	snprintf(weekday, sizeof(weekday), "%s", months + day);

	return strdup(weekday);
}

