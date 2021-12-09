/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelSampleTimeCon.h
* 文件描述: 样本时间段过滤条件
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 11:53:43
*******************************************************************************/
#ifndef __TBMODELSAMPLETIMECON_H__
#define __TBMODELSAMPLETIMECON_H__


#include "TypeDef.h"
#include "RDbOperationComplex.h"

#define TIME_CON_BUFFER_SIZE						 5
#define TIME_CON_VALUECONFIG						 "TbModelSampleTimeCon"

class TbModelSampleTimeCon:public RDbOperationComplex
{
private:
	 int			mBufferSize;             // OCI绑定查询缓存定义
public:
    TbModelSampleTimeCon(RsdbAdapter * mQtOpt);
	~TbModelSampleTimeCon(void);

	bool loadDB(std::string &strSampleTimeId, VectorSampleTimeConInfo &pVectorTimeConInfo);
private:
	bool loadValue(VectorSampleTimeConInfo  &pVectorTimeConInfo);
};

#endif
