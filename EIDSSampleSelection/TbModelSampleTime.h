/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelSampleTime.h
* 文件描述: 
*  作  者 : %林晓雨%
* 创建日期: 2016-11-2 16:02:07
*******************************************************************************/
#ifndef __TBMODELSAMPLETIME_H__
#define __TBMODELSAMPLETIME_H__

#include "TypeDef.h"
#include "ModelSelectionMgr.h"
#include "RDbOperationComplex.h"

#define TB_SAMPEL_TIME_BUFFER_SIZE						  5
#define TB_SAMPEL_TIME_VALUECONFIG						 "TbModelSampleTime"

class TbModelSampleTime:public RDbOperationComplex
{
private:
	int				mBufferSize;              // OCI绑定查询缓存定义
public:
    TbModelSampleTime(RsdbAdapter * QtOpt);
	~TbModelSampleTime(void);

	bool loadDB(VectorModelSelection &pVectorModelSelection);
	bool loadCorrDB(const std::string &strModelId, VectorSampleTimeInfo &pVectorSampleTime);
private:
	bool loadValue(VectorModelSelection &pVectorModelSelection);
	bool loadCorrValue(VectorSampleTimeInfo &pVectorSampleTime);
};

#endif
