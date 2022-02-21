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

#if !defined(_CLASSIC_WATCH_H)
#define _CLASSIC_WATCH_H

#if !defined(PACKAGE)
#define PACKAGE "org.example.look"
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "look"

/* Angle */
#define HOUR_ANGLE 30
#define MIN_ANGLE 6
#define SEC_ANGLE 6
#define MONTH_ANGLE 30
#define WEEKDAY_ANGLE 51

/* Layout */
#define BASE_WIDTH 360
#define BASE_HEIGHT 360

#define MODULE_MOONPHASE_SIZE 240
#define MODULE_DAY_NUM_SIZE 100
#define MODULE_DAY_NUM_RIGHT_PADDING 22
#define MODULE_MONTH_SIZE 128
#define MODULE_WEEKDAY_SIZE MODULE_MONTH_SIZE

#define HANDS_SEC_WIDTH 30
#define HANDS_SEC_HEIGHT 360
#define HANDS_MIN_WIDTH 30
#define HANDS_MIN_HEIGHT 360
#define HANDS_HOUR_WIDTH 30
#define HANDS_HOUR_HEIGHT 360
#define HANDS_MODULE_CALENDAR_WIDTH 20
#define HANDS_MODULE_CALENDAR_HEIGHT 128

#define HANDS_SEC_SHADOW_PADDING 5
#define HANDS_MIN_SHADOW_PADDING 9
#define HANDS_HOUR_SHADOW_PADDING 9

#endif
