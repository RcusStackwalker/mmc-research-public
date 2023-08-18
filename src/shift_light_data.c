#include <stdint.h>
#include <maps_desc.h>
#include "shift_light.h"

#include <engine_rpm_hires.h>

const uint16_t flash_shift_light_rpm_thresholds[SHIFT_LIGHT_STAGE_COUNT] = {
	RPM_TO_HIRESTICKS(5500),
	RPM_TO_HIRESTICKS(6000),
	RPM_TO_HIRESTICKS(6250),
};

DECLARE_ARRAY_DESC(flash_shift_light_rpm_thresholds,
	"Shift Light",
	"Engine RPM Thresholds",
	"RPMhires",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"3\">"
	"<data>Low</data>"
	"<data>Mid</data>"
	"<data>High</data>"
	"</table>");

extern uint8_t flash_shift_light_flash_patterns[SHIFT_LIGHT_STAGE_COUNT][SHIFT_LIGHT_MAX_SLICE_COUNT] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1,  0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0, 0, 0,  1, 1, 1, 1, 0, 0, 0, 0 },
};

DECLARE_3DARRAY_DESC(flash_shift_light_flash_patterns,
	"Shift Light",
	"Flash Patterns",
	"uint8",
	"<table name=\"X\" type=\"Static X Axis\" elements=\"16\">"
	"<data>0</data>"
	"<data>1</data>"
	"<data>2</data>"
	"<data>3</data>"
	"<data>4</data>"
	"<data>5</data>"
	"<data>6</data>"
	"<data>7</data>"
	"<data>8</data>"
	"<data>9</data>"
	"<data>10</data>"
	"<data>11</data>"
	"<data>12</data>"
	"<data>13</data>"
	"<data>14</data>"
	"<data>15</data>"
	"</table>",
	"<table name=\"Y\" type=\"Static Y Axis\" elements=\"3\">"
	"<data>Low</data>"
	"<data>Mid</data>"
	"<data>High</data>"
	"</table>");

const uint8_t flash_shift_light_control_mode = 1;
DECLARE_VALUE_DESC(flash_shift_light_control_mode, "Shift Light", "Shift Light Control Mode", "uint8");
