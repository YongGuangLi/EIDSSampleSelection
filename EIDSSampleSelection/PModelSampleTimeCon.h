/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PModelSampleTimeCon.h
* 文件描述: 模型样本时间段过滤条件
*  作  者 : %林晓雨%
* 创建日期: 2016-9-2 14:40:09
*******************************************************************************/

#ifndef __PMODELSAMPLETIMECON_H__
#define __PMODELSAMPLETIMECON_H__

#include "TypeDef.h"
#include "DataValueInfo.h"
#include "RDbOperationComplex.h"

#define MODEL_SAMPLE_TIME_CON_BUFFER_SIZE            10
#define MODEL_SAMPLE_TIME_CON_VALUE 				"PModelSampleTimeCon"

class PModelSampleTimeCon : public RDbOperationComplex
{
private:
	int					mBufferSize;
public:
    PModelSampleTimeCon();
    virtual ~PModelSampleTimeCon(void);
public:
	bool saveModelSampleTimeCon(
		const std::string &strId, 
		const std::string &strSampleTimeId,
		SampleTimeConInfo *timeConInfo);

private:
};
#endif
