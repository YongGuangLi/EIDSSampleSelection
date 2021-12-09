/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelMonitPoint.h
* 文件描述: 查询模型监测测点
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 15:20:06
*******************************************************************************/
#ifndef __TBMODELMONITPOINT_H__
#define __TBMODELMONITPOINT_H__
	  
#include "DataValueInfo.h"
#include "RDbOperationComplex.h"

#define MONIT_POINT_BUFFER_SIZE						 100
#define MONIT_POINT_VALUECONFIG						 "TbModelMonitPoint"

class TbModelMonitPoint:public RDbOperationComplex
{
private:
	 int mBufferSize;              // OCI绑定查询缓存定义
public:
    TbModelMonitPoint(RsdbAdapter * mQtOpt);
	~TbModelMonitPoint(void);

	bool loadDB(const std::string &strModelId, MapStringToDataValueInfo &pMapDataValueInfo);

	bool loadCorrDB(const std::string &strModelId, MapStringToDataValueInfo &pMapDataValueInfo);
private:
	bool loadValue(MapStringToDataValueInfo &pMapDataValueInfo);
	bool loadCorrValue(MapStringToDataValueInfo &pMapDataValueInfo);
};

#endif
