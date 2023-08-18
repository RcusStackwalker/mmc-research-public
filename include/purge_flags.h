#ifndef PURGE_FLAGS_H
#define PURGE_FLAGS_H

#define PURGE_FLAGS_AT_H01			0x0001
#define PURGE_FLAGS_LOAD_ABOVE_MAX		0x0002
#define PURGE_FLAGS_LOAD_ABOVE_MIN		0x0004
#define PURGE_FLAGS_RPM_ABOVE_MIN		0x0008
#define PURGE_FLAGS_AT_H10			0x0010
#define PURGE_FLAGS_PURGE_NOT_ADVISABLE		0x0020
#define PURGE_FLAGS_PURGE_NEEDED		0x0040
#define PURGE_FLAGS_H80				0x0080
#define PURGE_FLAGS_AIRFLOW_PREDICTABLE		0x0100
#define PURGE_FLAGS_H200			0x0200
#define PURGE_FLAGS_AIRFLOW_SOME		0x0400
#define PURGE_FLAGS_OLPURGE_RESTRICTED		0x0800
#define PURGE_FLAGS_OLPURGE_NEED_RESTRICTED	0x1000
#define PURGE_FLAGS_STOICH_CROSS_LONG		0x2000
#define PURGE_FLAGS_TOO_RICH			0x4000
#define PURGE_FLAGS_GONE_WRONG			0x8000

#endif /*PURGE_FLAGS_H*/