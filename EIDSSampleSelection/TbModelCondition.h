/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelCondition.h
* 文件描述: 模型监测条件
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 14:06:47
*******************************************************************************/

#ifndef __TBMODELCONDITION_H__
#define __TBMODELCONDITION_H__

#include "TypeDef.h"
#include "RDbOperationComplex.h"

#define COND_VALUEOUTPUT_BUFFER_SIZE                 10
#define COND_VALUECONFIG							 "TbModelCondition"

class TbModelCondition:public RDbOperationComplex
{
private:
	 long mBuffTotalSize;
public:
    TbModelCondition(RsdbAdapter * QtOpt);
	~TbModelCondition(void);

	bool loadDB(std::string &strModelId, MapStringToSampleConditionInfo &pMapSampleCondInfo);
private:
	bool loadValue(MapStringToSampleConditionInfo &pMapSampleCondInfo);
};

#endif
