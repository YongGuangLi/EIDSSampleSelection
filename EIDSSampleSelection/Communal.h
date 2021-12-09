/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: Communal.h
* 文件描述: 
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-2 15:43:49
*******************************************************************************/

#ifndef __COMMUNAL_H__
#define __COMMUNAL_H__

#define M_SET_GMH            "_gdbmF"                       //机组的供电标煤耗
#define M_SET_FMH            "_fdbmF"                       //机组的发电标煤耗
#define M_SUB                "SUB@"							//自减函数函数名称，当前值减上一个周期的值预测值函数
#define M_NOW   			 "NOW@"						    //表示当前时间,系统时间 "小时.分"函数名称
#define M_YEAR               "YEAR@"						//当前时间的年函数名称
#define M_MONTH              "MONTH@"						//当前时间的月函数名称
#define M_WEEK				 "WEEK@"						//当前时间的周函数名称
#define M_DAY                "DAY@"							//当前时间的日函数名称
#define M_PERIODTIME         "PERIODTIME@"					//系统实时计算周期 单位秒的函数名称
#define M_LOG				 "LOG@"						    //LOG函数名称
#define M_PRE                "PRE@"						    //预测值函数的函数名称
#define M_FILT				 "FILT@"						//滤波（平滑）值函数的函数名称

#define M_AIMU3D			 "AIMU3D@"						//上限值函数函数名称
#define M_AIMU2D			 "AIMU2D@"						//上限值函数函数名称
#define M_MAX			     "MAX@"						    //(最大值)上限值函数函数名称
#define M_AIMD3D             "AIMD3D@"						//下限值函数函数名称
#define M_AIMD2D             "AIMD2D@"						//下限值函数函数名称
#define M_MIN                "MIN@"						    //最小值函数名称

#endif
