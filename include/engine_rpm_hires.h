#ifndef ENGINE_RPM_HIRES_H
#define ENGINE_RPM_HIRES_H

extern uint16_t engine_rpm_hires;

#define RPM_TO_HIRESTICKS(x) ((unsigned)((x)*2.048))

#endif /*ENGINE_RPM_HIRES_H*/
