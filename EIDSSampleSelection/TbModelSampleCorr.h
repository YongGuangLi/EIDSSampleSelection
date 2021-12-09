/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelSampleCorr.h
* 文件描述: 查询模型监测测点
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 15:20:06
*******************************************************************************/
#ifndef __TBMODELSAMPLECORR_H__
#define __TBMODELSAMPLECORR_H__
	  
#include "TypeDef.h"
#include "RDbOperationComplex.h"

#define MODEL_SAMPLE_BUFFER_SIZE						 10
#define MODEL_SAMPLE_VALUECONFIG						 "TbModelSampleCorr"

class TbModelSampleCorr:public RDbOperationComplex
{
private:
	 int mBufferSize;              // OCI绑定查询缓存定义
public:
	TbModelSampleCorr(void);
	~TbModelSampleCorr(void);

	bool loadDB(VectorString &pVectorModelIdInfo);

private:
	bool loadValue(VectorString &pVectorModelIdInfo);
};

#endif
