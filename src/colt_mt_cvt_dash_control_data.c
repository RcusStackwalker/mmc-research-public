#include "colt_mt_cvt_dash_control_data.h"

#include <maps_desc.h>
#include <conversions.h>
#include <engine_rpm_hires.h>

#define S1IND 0x08
#define S2IND 0x18
#define S3IND 0x38
#define S4IND 0x78
#define S5IND 0xf8

const uint8_t flash_shift_light_flash_patterns[SHIFT_LIGHT_STAGE_COUNT][DASH_FLASH_MAX_SLICE_COUNT] = {
	{ [0 ... DASH_FLASH_MAX_SLICE_COUNT - 1] = S1IND },
	{ [0 ... DASH_FLASH_MAX_SLICE_COUNT - 1] = S2IND },
	{ [0 ... DASH_FLASH_MAX_SLICE_COUNT - 1] = S3IND },
	{ [0 ... DASH_FLASH_MAX_SLICE_COUNT - 1] = S4IND },
	{ [0 ... DASH_FLASH_MAX_SLICE_COUNT - 1] = S5IND },
	{ 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00 },
};

DECLARE_3DARRAY_DESC(flash_shift_light_flash_patterns,
	"CVT Dash Control",
	"Shift Light Flash Patterns (100ms per slice)",
	"uint8",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"16\">\n"
	"<data>0</data>\n"
	"<data>1</data>\n"
	"<data>2</data>\n"
	"<data>3</data>\n"
	"<data>4</data>\n"
	"<data>5</data>\n"
	"<data>6</data>\n"
	"<data>7</data>\n"
	"<data>8</data>\n"
	"<data>9</data>\n"
	"<data>10</data>\n"
	"<data>11</data>\n"
	"<data>12</data>\n"
	"<data>13</data>\n"
	"<data>14</data>\n"
	"<data>15</data>\n"
	"</table>",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"6\">\n"
	"<data>0</data>\n"
	"<data>1</data>\n"
	"<data>2</data>\n"
	"<data>3</data>\n"
	"<data>4</data>\n"
	"<data>5</data>\n"
	"</table>");

const uint16_t flash_shift_light_rpm_thresholds[SHIFT_LIGHT_STAGE_COUNT] = {
	RPM_TO_HIRESTICKS(4000),
	RPM_TO_HIRESTICKS(4500),
	RPM_TO_HIRESTICKS(5000),
	RPM_TO_HIRESTICKS(5500),
	RPM_TO_HIRESTICKS(6000),
	RPM_TO_HIRESTICKS(6250),
};
DECLARE_ARRAY_DESC(flash_shift_light_rpm_thresholds,
	"CVT Dash Control",
	"Shift Light Engine RPM Thresholds",
	"RPMhires",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"6\">\n"
	"<data>0</data>\n"
	"<data>1</data>\n"
	"<data>2</data>\n"
	"<data>3</data>\n"
	"<data>4</data>\n"
	"<data>5</data>\n"
	"</table>");


const uint8_t flash_asc_flash_pattern[DASH_FLASH_MAX_SLICE_COUNT] =
	{ 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00 };
DECLARE_ARRAY_DESC(flash_asc_flash_pattern,
	"CVT Dash Control",
	"Gear Indicator Flash Pattern on ASC",
	"uint8",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"16\">\n"
	"<data>0</data>\n"
	"<data>1</data>\n"
	"<data>2</data>\n"
	"<data>3</data>\n"
	"<data>4</data>\n"
	"<data>5</data>\n"
	"<data>6</data>\n"
	"<data>7</data>\n"
	"<data>8</data>\n"
	"<data>9</data>\n"
	"<data>10</data>\n"
	"<data>11</data>\n"
	"<data>12</data>\n"
	"<data>13</data>\n"
	"<data>14</data>\n"
	"<data>15</data>\n"
	"</table>");

const uint16_t flash_asc_lamp_startup_time = MS_TO_40HZTICKS(1000);
DECLARE_VALUE_DESC(flash_asc_lamp_startup_time,
	"CVT Dash Control",
	"ASC Lamp Indication on Ignition",
	"Time");
