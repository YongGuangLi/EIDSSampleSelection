/*******************************************************************************
* Copyright（C）,2010-2016,DTXY.Tech .Co.Ltd;
* 文 件 名: alarm.h
* 文件描述: 程序报警
*  作  者 : %林晓雨%，
* 创建日期: 2014-8-18 10:49:28
*******************************************************************************/

#ifndef __ALARM_LOG_H__
#define __ALARM_LOG_H__

#include "log.h"
#include "ServiceSelectionConfig.h"


#ifdef __cplusplus
extern "C" {
#endif

    extern void AosAlarmBreakPoint();
#ifdef __cplusplus
}
#endif

#endif

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL                     ("DEBUG")
#endif//DEBUG_LEVEL

#ifndef WARN_LEVEL
#define WARN_LEVEL                      ("WARN")
#endif//WARN_LEVEL

#ifndef ERROR_LEVEL
#define ERROR_LEVEL                     ("ERROR")
#endif//ERROR_LEVEL

#ifndef SUPER_LEVEL
#define SUPER_LEVEL                     ("SUPER")
#endif//SUPER_LEVEL


#ifndef Aos_Assert
#define Aos_Assert(cond)										\
    if (!(cond))												\
{															\
	SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", WARN_LEVEL, __FILE__, __LINE__, ""), SINGLETON(ServiceSelectionConfig)->isShowLog());\
    	AosAlarmBreakPoint();									\
    return;													\
 }
#endif


#ifndef Aos_Assert_R
#define Aos_Assert_R(cond, returncode)							\
    if (!(cond))												\
{															\
	SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", WARN_LEVEL, __FILE__, __LINE__, ""), SINGLETON(ServiceSelectionConfig)->isShowLog());\
    	AosAlarmBreakPoint();									\
    return (returncode);									\
 }
#endif

#ifndef Aos_Assert_RS
#define Aos_Assert_RS(cond, returncode, msg)							\
    if (!(cond))												\
{															\
	SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", WARN_LEVEL, __FILE__, __LINE__, msg), SINGLETON(ServiceSelectionConfig)->isShowLog());\
    	AosAlarmBreakPoint();									\
    return (returncode);									\
 }
#endif

#ifndef Aos_Assert_S
#define Aos_Assert_S(msg)							\
SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", WARN_LEVEL, __FILE__, __LINE__, msg), SINGLETON(ServiceSelectionConfig)->isShowLog());\
	AosAlarmBreakPoint();									\

#endif

#ifndef Aos_Assert_ERS
#define Aos_Assert_ERS(cond, returncode, msg)							\
    if (!(cond))												\
{															\
	SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", ERROR_LEVEL, __FILE__, __LINE__, msg), SINGLETON(ServiceSelectionConfig)->isShowLog());\
    	AosAlarmBreakPoint();									\
    return (returncode);									\
 }
#endif


#ifndef	Aos_Assert_CB 
#define Aos_Assert_CB(cond)							\
	if (!(cond))												\
{														\
	SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", ERROR_LEVEL, __FILE__, __LINE__, ""), SINGLETON(ServiceSelectionConfig)->isShowLog());\
	AosAlarmBreakPoint();									\
}
#endif

#ifndef Aos_WriteLog_D 
#define Aos_WriteLog_D(msg)           \
SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", DEBUG_LEVEL, __FILE__, __LINE__, msg), SINGLETON(ServiceSelectionConfig)->isShowLog());\

#endif

#ifndef Aos_WriteLog 
#define Aos_WriteLog(msg)           \
SINGLETON(Log)->WriteLog(SINGLETON(Log)->StringFormat("[%s][%s:%d]: %s", SUPER_LEVEL, __FILE__, __LINE__, msg), true);\

#endif




