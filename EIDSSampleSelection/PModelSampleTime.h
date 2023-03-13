/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PModelSampleTime.h
* 文件描述: 诊断模型样本时间段
*  作  者 : %林晓雨%
* 创建日期: 2016-9-2 14:40:09
*******************************************************************************/

#ifndef __PMODELSAMPLETIME_H__
#define __PMODELSAMPLETIME_H__

#include "TypeDef.h"
#include "DataValueInfo.h"
#include "RDbOperationComplex.h"

#define MODEL_SAMPLE_BUFFER_SIZE            10
#define MODEL_SAMPLE_TIME_VALUE 			"PModelSampleTime"

class PModelSampleTime : public RDbOperationComplex
{
private:
	int					mBufferSize;
public:
    PModelSampleTime(RsdbAdapter * QtOpt);
    virtual ~PModelSampleTime(void);
public:
	bool saveModelSampleTime(
        const std::string &modelId,
        const std::string &train_id,
		const std::string &condId, 
		SampleTimeInfo *timeInfo);

private:
};

#endif
