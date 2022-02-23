#if !defined(_DATA_H)
#define _DATA_H

#define IMAGE_BG "images/watch_bg.png"
#define IMAGE_BG_AMBIENT "images/watch_bg_ambient.png"
#define IMAGE_BG_AMBIENT_LOWBAT "images/watch_bg_ambient_low_battery.png"
#define IMAGE_BG_PLATE "images/watch_bg_plate.png"
#define IMAGE_HANDS_BAT "images/watch_hand_battery.png"
#define IMAGE_HANDS_BAT_LOWBAT "images/watch_hand_battery_low_battery.png"
#define IMAGE_HANDS_BAT_SHADOW "images/watch_hand_battery_shadow.png"
#define IMAGE_HANDS_SEC "images/watch_hand_sec.png"
#define IMAGE_HANDS_SEC_SHADOW "images/watch_hand_sec_shadow.png"
#define IMAGE_HANDS_SEC_AMBIENT "images/watch_hand_sec_ambient.png"
#define IMAGE_HANDS_MIN "images/watch_hand_min.png"
#define IMAGE_HANDS_MIN_SHADOW "images/watch_hand_min_shadow.png"
#define IMAGE_HANDS_MIN_AMBIENT "images/watch_hand_min_ambient.png"
#define IMAGE_HANDS_MIN_AMBIENT_LOWBAT "images/watch_hand_min_ambient_low_battery.png"
#define IMAGE_HANDS_HOUR "images/watch_hand_hr.png"
#define IMAGE_HANDS_HOUR_SHADOW "images/watch_hand_hr_shadow.png"
#define IMAGE_HANDS_HOUR_AMBIENT "images/watch_hand_hr_ambient.png"
#define IMAGE_HANDS_HOUR_AMBIENT_LOWBAT "images/watch_hand_hr_ambient_low_battery.png"
#define IMAGE_HANDS_MODULE_CALENDAR "images/watch_hand_module_calendar.png"
#define IMAGE_HANDS_MODULE_CALENDAR_SHADOW "images/watch_hand_module_calendar_shadow.png"

#define LOW_BATTERY_LEVEL 25

typedef enum {
	PARTS_TYPE_HANDS_SEC = 0,
	PARTS_TYPE_HANDS_MIN = 1,
	PARTS_TYPE_HANDS_HOUR = 2,
	PARTS_TYPE_HANDS_MODULE_MONTH = 3,
	PARTS_TYPE_HANDS_MODULE_WEEKDAY = 4,
	PARTS_TYPE_HANDS_SEC_SHADOW = 5,
	PARTS_TYPE_HANDS_MIN_SHADOW = 6,
	PARTS_TYPE_HANDS_HOUR_SHADOW = 7,
	PARTS_TYPE_HANDS_MODULE_MONTH_SHADOW = 8,
	PARTS_TYPE_HANDS_MODULE_WEEKDAY_SHADOW = 9,
	PARTS_TYPE_HANDS_BAT = 10,
	PARTS_TYPE_HANDS_BAT_SHADOW = 11,
	PARTS_TYPE_BG_PLATE= 12,
	PARTS_TYPE_MAX,
} parts_type_e;

/*
 * Initialize the data component
 */
void data_initialize(void);

/*
 * Finalize the data component
 */
void data_finalize(void);

void data_get_resource_path(const char *file_in, char *file_path_out, int file_path_max);
int data_get_hour_plus_angle(int minute, int second);
char *data_get_parts_image_path(parts_type_e type);
void data_get_parts_position(parts_type_e type, int *x, int *y);
int data_get_parts_width_size(parts_type_e type);
int data_get_parts_height_size(parts_type_e type);

int data_get_juliandate(int day, int month, int year);
float data_get_moonphase(int day, int month, int year);

/**
 * @brief Get the TopLeft position of object A as it would be if centered on object B
 * @param[in] sizeA The A size
 * @param[in] sizeB The B size
 */
static int get_a_centered_on_b(int sizeA, int sizeB)
{
	return (sizeB / 2) - (sizeA / 2);
}

bool set_object_background_image(Evas_Object* obj, const char* image);

char* get_day_of_week(int day);

#endif
