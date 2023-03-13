/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PublicFunction.h
* 文件描述: 样本筛选与数据相关性分析的公共方法
*  作  者 : %林晓雨%
* 创建日期: 2016-11-9 9:44:03
*******************************************************************************/

#include "PublicFunction.h"

#include "Util.h"
#include "RtdbOpt.h"
#include "StartupServer.h"
#include "ServiceSelectionConfig.h"

PublicFunction::PublicFunction()
{

}

PublicFunction::~PublicFunction()
{

}

bool
PublicFunction::pointIdSourceIdRtdbIsExist(MapStringToDataValueInfo	 &pMapDataValueInfo)
{
    if (!Util::connectRtdbDB())
        return false;

	//积分指标
	MapStringToDataValueInfo_It dItr = pMapDataValueInfo.begin();
	for (; dItr != pMapDataValueInfo.end(); ++dItr)
    {

        std::string sourceId = dItr->second->mPointSource;
		if (sourceId.empty())
		{
            Aos_Assert_S(PubOpt::StringOpt::StringFormat("SourceId is empty (%s);", dItr->second->mStrCode.c_str()).c_str());
			dItr->second->mSourceIdRtdbIsExist = false;
			continue;
		}

		dItr->second->mSourceIdRtdbIsExist = true;
        if (!SINGLETON(RtdbOpt)->rtdbIsExistPoint(sourceId))
        {
            Aos_Assert_S(PubOpt::StringOpt::StringFormat("Rtdb Not Exist Point (%s);", sourceId.c_str()).c_str());
            dItr->second->mSourceIdRtdbIsExist = false;
        }
        else
        {
            dItr->second->mSourceIdRtdbIsExist = true;
        }
	}
	return true;
}


