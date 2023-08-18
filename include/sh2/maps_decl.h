#ifndef MAPS_DECL_H
#define MAPS_DECL_H


#define TEMP_3DMAP_SRC	.type = 3, .xsrc = &temp_axis_target_x, .ysrc = &temp_axis_target_y
#define TEMP_2DMAP_SRC	.type = 2, .xsrc = &temp_axis_target_x
#define TEMP_2DMAPY_SRC	.type = 2, .xsrc = &temp_axis_target_y

#define TEMP_AXIS_SRC_XDST .dst = &temp_axis_target_x, .src = &temp_axis_src
#define TEMP_AXIS_SRC_YDST .dst = &temp_axis_target_y, .src = &temp_axis_src

#define TEMP_AXIS_DST_X .dst = &temp_axis_target_x
#define TEMP_AXIS_DST_X .dst = &temp_axis_target_y

extern uint16_t temp_axis_src;
extern uint16_t temp_axis_target_x;
extern uint16_t temp_axis_target_y;

#define DECLARE_AXIS(name, _size) \
const struct name##_type { uint16_t *dst; uint16_t *src; uint16_t size; uint16_t data[_size]; } __attribute__ ((aligned (2), packed)) name
#define DECLARE_2DMAP8(name, _xsize) const struct name##_type { uint8_t type; uint8_t offset; uint16_t *xsrc; uint8_t data[_xsize]; } __attribute__ ((aligned (2), packed)) name
#define DECLARE_3DMAP8(name, _xsize, _ysize) \
const struct name##_type { uint8_t type; uint8_t offset; uint16_t *xsrc; uint16_t *ysrc; uint8_t xsize; uint8_t data[_xsize * _ysize]; } __attribute__ ((aligned (2), packed))name
#define DECLARE_3DMAP16(name, _xsize, _ysize) \
const struct name##_type { uint16_t type; uint16_t offset; uint16_t *xsrc; uint16_t *ysrc; uint16_t xsize; uint16_t data[_xsize * _ysize]; } __attribute__ ((aligned (2), packed)) name


#include <maps_desc.h>

#endif /*MAPS_DECL_H*/
