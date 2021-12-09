/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PublicFunction.h
* 文件描述: 样本筛选与数据相关性分析的公共方法
*  作  者 : %林晓雨%
* 创建日期: 2016-11-9 9:44:03
*******************************************************************************/

#include "DataValueInfo.h"
class PublicFunction
{
public:
	PublicFunction();
	~PublicFunction();

	static	bool pointIdSourceIdRtdbIsExist(MapStringToDataValueInfo &pMapDataValueInfo);
};