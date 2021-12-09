/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: SampleTimeInfo.h
* 文件描述: 诊断模型样本时间段
*  作  者 : %林晓雨%
* 创建日期: 2016-8-30 15:08:07
*******************************************************************************/

#ifndef __SAMPLETIMEINFO_H__
#define __SAMPLETIMEINFO_H__

#include <string>

struct SampleTimeInfo
{
	std::string					mSampleTimeId;	//样本时间段
	long						mStartTime;		//开始时间
	long						mEndTime;		//结束时间
	long						mStep;			//步长
	long						mSampleSum;		//样本条数
	bool						mIsHis;			//状态(0:当前，1:历史)

	SampleTimeInfo(void)
	:
	mStartTime(0),
	mEndTime(0),
	mStep(0),
	mSampleSum(1),
	mIsHis(false)
	{

	}

	~SampleTimeInfo()
	{

	}

};
#endif
