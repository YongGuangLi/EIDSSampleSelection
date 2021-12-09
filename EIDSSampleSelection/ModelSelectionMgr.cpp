/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: ModelSelectionMgr.cpp
* 文件描述: 模型样本筛选
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 11:27:44
*******************************************************************************/

#include "ModelSelectionMgr.h"

#include "Util.h"
#include "ConditionCal.h"
#include "StartupServer.h"
#include "PublicFunction.h"
#include "SampleTimeInfo.h"
#include "PModelSampleTime.h"
#include "TbModelCondition.h"
#include "TbModelMonitPoint.h"
#include "RDbOperationSimple.h"
#include "PModelSampleTimeCon.h"
#include "TbModelSampleTimeCon.h"


ModelSelectionMgr::ModelSelectionMgr()
    :
      mModelId(""),
      mOriginalSTimeInfo(NULL),
      mAfterScreeningSum(0)
{
    mOriginalSTimeInfo = new SampleTimeInfo();
}

ModelSelectionMgr::~ModelSelectionMgr()
{
    Aos_WriteLog_D(PubOpt::StringOpt::StringFormat(
                       "~ModelSelectionMgr mModelId:%s;",mModelId.c_str()).c_str());
    if (mOriginalSTimeInfo != NULL)
    {
        delete mOriginalSTimeInfo;
    }

    MapStringToDataValueInfo_It dItr = mMapDataValueInfo.begin();
    for (; dItr != mMapDataValueInfo.end(); ++dItr)
    {
        if (dItr->second != NULL) delete dItr->second;
    }
    mMapDataValueInfo.clear();

    MapStringToSampleConditionInfo_It cItr = mMapSampleCondInfo.begin();
    for (; cItr != mMapSampleCondInfo.end(); ++cItr)
    {
        if (cItr->second != NULL) delete cItr->second;
    }
    mMapSampleCondInfo.clear();

    VectorSampleTimeConInfo_It tItr = mVectorSampleTimeConInfo.begin();
    for (; tItr != mVectorSampleTimeConInfo.end(); ++tItr)
    {
        if (*tItr != NULL) delete *tItr;
    }

    mVectorSampleTimeConInfo.clear();

    MapStringToVectorSampleTimeInfo_It stItr = mMapVectorSampleTimeInfo.begin();
    for (; stItr != mMapVectorSampleTimeInfo.end(); ++stItr)
    {
        for(unsigned int i = 0; i < stItr->second.size(); i++)
        {
            if (stItr->second[i] != NULL) delete stItr->second[i];
        }
        stItr->second.clear();
    }
    mMapVectorSampleTimeInfo.clear();
}

bool
ModelSelectionMgr::loadModelCondition()
{
    //导入模型模式条件
    TbModelCondition *opt = new TbModelCondition(Util::getRsdbAdapter());
    bool rslt = opt->loadDB(mModelId, mMapSampleCondInfo);
    delete opt;
    return rslt;
}

bool
ModelSelectionMgr::loadModelMonitPoint()
{
    //导入模型测点
    TbModelMonitPoint *opt = new TbModelMonitPoint(Util::getRsdbAdapter());
    bool rslt = opt->loadDB(mModelId, mMapDataValueInfo);
    delete opt;
    return rslt;
}

bool
ModelSelectionMgr::loadSampleTimeCon()
{
    //导入手工过滤条件
    TbModelSampleTimeCon *opt = new TbModelSampleTimeCon(Util::getRsdbAdapter());
    bool rslt = opt->loadDB(mOriginalSTimeInfo->mSampleTimeId, mVectorSampleTimeConInfo);
    delete opt;
    return rslt;
}


bool
ModelSelectionMgr::loadConfigInfo()
{
    //select id, name, local_var, concat(out_var,out_var_func), expression  from tb_eids_model_condition where model_id = '%s'
    Aos_Assert_R(loadModelCondition(), false);

    //select monit_point_id, upper_limit_cond, upper_limit_value, lower_limit_cond,lower_limit_value from tb_eids_model_sample_time_con where sample_time_id = '%s'
    Aos_Assert_R(loadSampleTimeCon(), false);

    parseExpressionToDPoint();

    //select point_code, SOURCE_ID_ORIGINAL from tb_pub_point
    Aos_Assert_R(loadModelMonitPoint(), false);

    bool rslt = PublicFunction::pointIdSourceIdRtdbIsExist(mMapDataValueInfo);
    Aos_Assert_R(rslt, false);
    return true;
}

void
ModelSelectionMgr::parseExpressionToDPoint()
{
    for (MapStringToSampleConditionInfo_It cItr = mMapSampleCondInfo.begin(); cItr != mMapSampleCondInfo.end(); ++cItr)
    {
         SampleConditionInfo *sampleCondInfo = cItr->second;
        for (unsigned int i = 0; i < sampleCondInfo->mOutFuncVarArray.size(); i++)
        {
            std::string strPointId = sampleCondInfo->mOutFuncVarArray[i];
            MapStringToDataValueInfo_It dItr = mMapDataValueInfo.find(strPointId);
            if (dItr == mMapDataValueInfo.end())
            {
                DataValueInfo *dataValueInfo = new DataValueInfo();
                dataValueInfo->mStrCode = strPointId;
                mMapDataValueInfo.insert(make_pair(strPointId, dataValueInfo));
            }
        }
    }

    for (VectorSampleTimeConInfo_It tItr = mVectorSampleTimeConInfo.begin(); tItr != mVectorSampleTimeConInfo.end(); ++tItr)
    {
        SampleTimeConInfo *pTimeConInfo = *tItr;
        MapStringToDataValueInfo_It dItr = mMapDataValueInfo.find(pTimeConInfo->mMonitPointId);
        if (dItr == mMapDataValueInfo.end())
        {
            DataValueInfo *dataValueInfo = new DataValueInfo();
            dataValueInfo->mStrCode = pTimeConInfo->mMonitPointId;
            mMapDataValueInfo.insert(make_pair(pTimeConInfo->mMonitPointId, dataValueInfo));
        }
    }
}


bool
ModelSelectionMgr::sampleSelection()
{
    long lStartCalTime = mOriginalSTimeInfo->mStartTime;
    long lEndCalTime = mOriginalSTimeInfo->mEndTime;
    long lStep = mOriginalSTimeInfo->mStep;

    Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("run A1(start),id:%s, start_time:%s, end_time:%s, step:%d;",
                                                   mOriginalSTimeInfo->mSampleTimeId.c_str(),
                                                   PubOpt::SystemOpt::DateTmToStr(lStartCalTime).c_str(),
                                                   PubOpt::SystemOpt::DateTmToStr(lEndCalTime).c_str(),
                                                   lStep).c_str());



    Aos_Assert_R(selection(lStartCalTime, lEndCalTime, lStep), false);
    if (StartupServer::smDestory)
        return true;

    saveSampleTimeInfoAll();

    Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("run A3(end), id:%s, start_time:%s, end_time:%s, step:%d;",
                                                   mOriginalSTimeInfo->mSampleTimeId.c_str(),
                                                   PubOpt::SystemOpt::DateTmToStr(lStartCalTime).c_str(),
                                                   PubOpt::SystemOpt::DateTmToStr(lEndCalTime).c_str(),
                                                   lStep).c_str());
    return true;
}

bool
ModelSelectionMgr::selection(const long &lStartCalTime, const long &lEndCalTime, const long &lStep)
{	
    Aos_WriteLog_D(PubOpt::StringOpt::StringFormat(
                       "run A2, id:%s, start_time:%s, end_time:%s, step:%d;",
                       mOriginalSTimeInfo->mSampleTimeId.c_str(),
                       PubOpt::SystemOpt::DateTmToStr(lStartCalTime).c_str(),
                       PubOpt::SystemOpt::DateTmToStr(lEndCalTime).c_str(),lStep).c_str());

    //1.手工筛选条件过滤
    //2.模式分类(开机过程、机组运行、停机过程)
    if (lEndCalTime - lStartCalTime < lStep)
    {
        Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("ModelSelectionMgr;end_time:%s - start_time:%s < step:%d;", PubOpt::SystemOpt::DateTmToStr(lEndCalTime).c_str(), PubOpt::SystemOpt::DateTmToStr(lStartCalTime).c_str(),lStep).c_str());
        return true;
    }


    Aos_Assert_R(loadPointData(lStartCalTime, lEndCalTime, lStep), false);

    for (long lCalTime = lStartCalTime; lCalTime <= lEndCalTime; lCalTime += lStep)
    {
        nextOriginaValue();

        //手工筛选条件
        bool isValidSample = judgeManualFilterCondition(lCalTime);
        if (!isValidSample)
            continue;

        //模式分类
        sampleModeCategor(lCalTime, lStep);
        if (StartupServer::smDestory)
            return true;
    }

    Aos_Assert_R(saveSampleTimeInfo(), false);
    return true;
}

bool
ModelSelectionMgr::judgeManualFilterCondition(const long &lCalStampTime)
{
    for (VectorSampleTimeConInfo_It tItr = mVectorSampleTimeConInfo.begin(); tItr != mVectorSampleTimeConInfo.end(); ++tItr)
    {
        SampleTimeConInfo * pTimeConInfo = *tItr;
        MapStringToDataValueInfo_It dItr = mMapDataValueInfo.find(pTimeConInfo->mMonitPointId);
        if (dItr == mMapDataValueInfo.end())
        {
            Aos_Assert_S("");
            continue;
        }

        double fVal = dItr->second->getCurrVar();
        if (!pTimeConInfo->judgeManualCondition(lCalStampTime, fVal))
        {
            //LINXIAOYU
            Aos_WriteLog_D((PubOpt::StringOpt::StringFormat(
                                "judgeManualCondition lCalStampTime=%s, %s=%f;",
                                PubOpt::SystemOpt::DateTmToStr(lCalStampTime).c_str(),
                                dItr->second->mStrCode.c_str(), fVal)).c_str());
            return false;
        }
    }
    return true;
}


bool
ModelSelectionMgr::sampleModeCategor(const long &lCalStampTime, const long &lStep)
{
    for (MapStringToSampleConditionInfo_It cItr = mMapSampleCondInfo.begin(); cItr != mMapSampleCondInfo.end(); ++cItr)
    {
        if (StartupServer::smDestory)
            return true;
        SampleConditionInfo *sampleCondInfo = cItr->second;
        SINGLETON(ConditionCal)->calculateCondition(lCalStampTime, mMapDataValueInfo, sampleCondInfo);

        if (sampleCondInfo->mCondCalValue <= 0)
        {
            //LINXIAOYU
            Aos_WriteLog_D((PubOpt::StringOpt::StringFormat(
                                "sampleModeCategor lCalStampTime=%s, %s=%f; Discard;",
                                PubOpt::SystemOpt::DateTmToStr(lCalStampTime).c_str(),
                                sampleCondInfo->mCondId.c_str(), sampleCondInfo->mCondCalValue)).c_str());
            continue;
        }

        setSampleTimeInfo(sampleCondInfo->mCondId, lCalStampTime, lStep);
    }
    return true;
}


bool 
ModelSelectionMgr::loadPointData(const long &lStartCalTime, const long &lEndCalTime, const long &lStep)
{
    return SINGLETON(RtdbOpt)->rtdbGetHisValue(mMapDataValueInfo, lStartCalTime, lEndCalTime, lStep);
}

void
ModelSelectionMgr::nextOriginaValue()
{
    MapStringToDataValueInfo_It itr = mMapDataValueInfo.begin();
    for (; itr != mMapDataValueInfo.end(); ++itr)
    {
        DataValueInfo * dataValueInfo = itr->second;
        dataValueInfo->nextOriginaValue();
    }
}


void
ModelSelectionMgr::setSampleTimeInfo(const std::string &strCondId, const long &lCalStampTime, const long &lStep)
{
    MapStringToVectorSampleTimeInfo_It sItr = mMapVectorSampleTimeInfo.find(strCondId);
    if (sItr == mMapVectorSampleTimeInfo.end())
    {
        VectorSampleTimeInfo vTimeInfo;
        SampleTimeInfo *timeInfo = createSampleTimeInfo(lCalStampTime, lStep);
        vTimeInfo.push_back(timeInfo);
        mMapVectorSampleTimeInfo.insert(make_pair(strCondId, vTimeInfo));
        return;
    }
    unsigned long nSize = sItr->second.size();
    if (nSize > 0)
    {
        unsigned long nLastIndex = nSize -1;
        Aos_Assert(nLastIndex < nSize);

        SampleTimeInfo *lastTimeInfo = (sItr->second)[nLastIndex];
        if (lastTimeInfo->mEndTime + lStep == lCalStampTime)
        {
            lastTimeInfo->mSampleSum ++;
            lastTimeInfo->mEndTime = lCalStampTime;
            return;
        }
        else
        {
            SampleTimeInfo *hisTimeInfo = createSampleTimeInfo(lCalStampTime, lStep);
            hisTimeInfo->mIsHis = true;
            sItr->second.push_back(hisTimeInfo);
        }
    }
}

SampleTimeInfo*
ModelSelectionMgr::createSampleTimeInfo(const long &lCalStampTime, const long &lStep)
{
    mAfterScreeningSum ++;
    SampleTimeInfo* timeInfo = new SampleTimeInfo();
    timeInfo->mStep = lStep;
    timeInfo->mEndTime = lCalStampTime;
    timeInfo->mStartTime = lCalStampTime;
    timeInfo->mSampleTimeId = SINGLETON(RDbOperationSimple)->getSysGuid();

    return timeInfo;
}

bool
ModelSelectionMgr::saveSampleTimeInfo()
{
    return saveSampleTimeInfoPriv();
}

bool
ModelSelectionMgr::saveSampleTimeInfoAll()
{
    return saveSampleTimeInfoPriv(true);
}

bool
ModelSelectionMgr::saveSampleTimeInfoPriv(const bool isAll)
{
    if (mMapVectorSampleTimeInfo.empty())
        return true;

    for (MapStringToVectorSampleTimeInfo_It cItr = mMapVectorSampleTimeInfo.begin(); cItr != mMapVectorSampleTimeInfo.end(); ++cItr)
    {
        bool rslt = saveModelSampleTimeAndTimeCon(cItr->first, cItr->second, isAll);

        cleanHisSampleTimeInfo(cItr->second, isAll);

        Aos_Assert_R(rslt, false);
    }
    return true;
}

bool
ModelSelectionMgr::saveModelSampleTimeAndTimeCon(const std::string &condId, VectorSampleTimeInfo &pSampleTimeInfo, bool isAll)
{
    for (VectorSampleTimeInfo_It sItr = pSampleTimeInfo.begin(); sItr != pSampleTimeInfo.end(); ++sItr)
    {
        SampleTimeInfo *timeInfo = *sItr;
        if (!isAll && !timeInfo->mIsHis)
            continue;

        PModelSampleTime *opt = new PModelSampleTime(Util::getRsdbAdapter());

        //insert into tb_eids_model_sample_time
        opt->saveModelSampleTime(mModelId, condId, timeInfo);
        delete opt;

        //insert into tb_eids_model_sample_time_cond
        //saveModelSampleTimeCon(timeInfo->mSampleTimeId);
    }
    return true;
}

bool
ModelSelectionMgr::saveModelSampleTimeCon(const std::string &strSampleTimeId)
{
    VectorSampleTimeConInfo_It tItr = mVectorSampleTimeConInfo.begin();
    for (;tItr != mVectorSampleTimeConInfo.end(); ++tItr)
    {
        SampleTimeConInfo *timeConInfo = *tItr;
        std::string strId = SINGLETON(RDbOperationSimple)->getSysGuid();

        PModelSampleTimeCon *cOpt = new PModelSampleTimeCon();

        //insert into tb_eids_model_sample_time_con
        cOpt->saveModelSampleTimeCon(strId, strSampleTimeId, timeConInfo);
        delete cOpt;
    }
    return true;
}

void
ModelSelectionMgr::cleanHisSampleTimeInfo(VectorSampleTimeInfo &vecSampleTimeInfo, const bool isAll)
{
    for (VectorSampleTimeInfo_It sItr = vecSampleTimeInfo.begin(); sItr != vecSampleTimeInfo.end();)
    {
        SampleTimeInfo *timeInfo = *sItr;
        if (isAll || timeInfo->mIsHis)
        {
            delete timeInfo;
            timeInfo = NULL;
            sItr = vecSampleTimeInfo.erase(sItr);
            continue;
        }
        ++sItr;
    }
}
