#ifndef MAPS_DECL_H
#define MAPS_DECL_H

#if 0
#define SDA_POINTER(x) (const int16_t)((uint16_t* const)SMALL_DATA_AREA_BASE - &x)

#define TEMP_3DMAP_SRC	.type = 3, .xsrc = SDA_POINTER(temp_axis_target_x), .ysrc = SDA_POINTER(temp_axis_target_y)
#define TEMP_2DMAP_SRC	.type = 2, .xsrc = SDA_POINTER(temp_axis_target_x)

#define TEMP_AXIS_SRC_XDST .dst = SDA_POINTER(temp_axis_target_x), .src = SDA_POINTER(temp_axis_src)
#define TEMP_AXIS_SRC_YDST .dst = SDA_POINTER(temp_axis_target_y), .src = SDA_POINTER(temp_axis_src)

#endif

#define TEMP_2DMAP_SRC	.type = 2, .xsrc = TEMP_AXIS_TARGET_X_SDA
#define TEMP_2DMAPY_SRC	.type = 2, .xsrc = TEMP_AXIS_TARGET_Y_SDA
#define TEMP_3DMAP_SRC	.type = 3, .xsrc = TEMP_AXIS_TARGET_X_SDA, .ysrc = TEMP_AXIS_TARGET_Y_SDA

#define TEMP_AXIS_SRC_XDST .dst = TEMP_AXIS_TARGET_X_SDA, .src = TEMP_AXIS_SRC_SDA
#define TEMP_AXIS_SRC_YDST .dst = TEMP_AXIS_TARGET_Y_SDA, .src = TEMP_AXIS_SRC_SDA

#define TEMP_AXIS_DST_X .dst = TEMP_AXIS_TARGET_X_SDA
#define TEMP_AXIS_DST_Y .dst = TEMP_AXIS_TARGET_Y_SDA


#define DECLARE_AXIS(name, _size) \
const struct name##_type { int16_t dst; int16_t src; uint16_t size; uint16_t data[_size]; } name
#define DECLARE_2DMAP8(name, _xsize) const struct name##_type { uint8_t type; uint8_t offset; int16_t xsrc; uint8_t data[_xsize]; } name
#define DECLARE_2DMAP16(name, _xsize) const struct name##_type { uint16_t type; uint16_t offset; int16_t xsrc; uint16_t data[_xsize]; } name
#define DECLARE_3DMAP8(name, _xsize, _ysize) \
const struct name##_type { uint8_t type; uint8_t offset; int16_t xsrc; int16_t ysrc; uint8_t xsize; uint8_t data[_xsize * _ysize]; } name
#define DECLARE_3DMAP16(name, _xsize, _ysize) \
const struct name##_type { uint16_t type; uint16_t offset; int16_t xsrc; int16_t ysrc; uint16_t xsize; uint16_t data[_xsize * _ysize]; } name


#include <maps_desc.h>

#endif /*MAPS_DECL_H*/
