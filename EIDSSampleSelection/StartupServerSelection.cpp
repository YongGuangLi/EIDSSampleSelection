/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: StartupServerSelection.cpp
* 文件描述: 主控类
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-2 10:23:06
*******************************************************************************/
#include "StartupServerSelection.h"

#include "Util.h"
#include "AlarmLog.h"
#include "TbModelSampleTime.h"
#include "RDbOperationSimple.h"

#include<algorithm>


StartupServerSelection::StartupServerSelection(void)
{
    Aos_WriteLog_D("StartupServerSelection::StartupServerSelection");
}

StartupServerSelection::~StartupServerSelection(void)
{

}

bool
StartupServerSelection::cleanSampleTimeData(const std::string &strModelId)
{
    //状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算 5:初始化)
    return SINGLETON(RDbOperationSimple)->deleteSampleTimeState2ByModelId(strModelId);
}


bool
StartupServerSelection::loadSampleTime(VectorModelSelection &pVectorModelSelection)
{
    TbModelSampleTime * opt = new TbModelSampleTime(Util::getRsdbAdapter());
    bool rslt = opt->loadDB(pVectorModelSelection);
    delete opt;
    sort(pVectorModelSelection.begin(), pVectorModelSelection.end(), ModelSelectionMgr::cmp);
    return rslt;
}



bool
StartupServerSelection::calculate()
{
    VectorModelSelection pVectorModelSelection;
    //状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算 5:初始化 6:不满足条件)
    //tb_eids_model_sample_time state=1 or state=4
    bool rslt = loadSampleTime(pVectorModelSelection);
    if (!rslt)
    {
        Aos_Assert_S("loadSampleConState Faild!");
    }

    if (!pVectorModelSelection.empty())
    {
        rslt = runSampleSelectionTask(pVectorModelSelection);
        if (!rslt)
        {
            Aos_Assert_S("runSampleSelectionTask Faild!");
        }
        if (smDestory)
            return true;
    }


    for (VectorModelSelection_It sItr = pVectorModelSelection.begin(); sItr != pVectorModelSelection.end(); ++sItr)
    {
        if (*sItr != NULL)
            delete *sItr;
    }

    pVectorModelSelection.clear();

    //1分钟
    for (long iWait = 0; iWait < 1; iWait ++)
    {
        //更新服务状态监测时间(监控服务专用)
        SINGLETON(RDbOperationSimple)->SubmitToControlProcessService();
        for (long i = 0; i < 60; i++)
        {
            if (smDestory)
                return true;
            PubOpt::SystemOpt::SleepWait(1000);
        }
    }
    return true;
}

//执行样本筛选任务
bool
StartupServerSelection::runSampleSelectionTask(VectorModelSelection &pVectorModelSelection)
{
    Aos_WriteLog_D("runSampleSelectionTask Start!");

    for (VectorModelSelection_It sItr = pVectorModelSelection.begin(); sItr != pVectorModelSelection.end(); ++sItr)
    {
        ModelSelectionMgr * modelSelection = *sItr;
        std::string strLastModelId = modelSelection->mModelId;
        //删除state为新插入; 状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算 5:初始化)
        //删除 tb_eids_model_sample_time_con tb_eids_model_sample_time  state=2
        cleanSampleTimeData(strLastModelId);

        runSubTask(modelSelection);
        if (smDestory)
            return true;
    }

    Aos_WriteLog_D("runSampleSelectionTask End!");
    return true;
}


bool
StartupServerSelection::runSubTask(ModelSelectionMgr * modelSelection)
{
    std::string strSampleTimeId = modelSelection->mOriginalSTimeInfo->mSampleTimeId;
    //状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算)
    //tb_eids_model_sample_time state=1
    SINGLETON(RDbOperationSimple)->updateSampleTimeStateToOne(strSampleTimeId);
    bool rslt = modelSelection->loadConfigInfo();
    if (!rslt)
    {
        Aos_Assert_S("loadConfigInfo Faild!");
        return true;
    }
    if (smDestory)
        return true;

    rslt = modelSelection->sampleSelection();
    if (!rslt)
    {
        SINGLETON(RDbOperationSimple)->updateSampleTimeStateToThree(strSampleTimeId);
        Aos_Assert_S("sampleSelection Faild!");
        return true;
    }

    if (smDestory)
        return true;

    //筛选后，如果筛选后生成了子记录则删除'筛选时间段信息'记录;
    //否则不删除'筛选时间段信息'记录,只修改'筛选时间段信息'记录(tb_eids_model_sample_time)的State = 6和samples_sum = 0
    if (modelSelection->GetAfterScreeningSum() <= 0)
    {
        SINGLETON(RDbOperationSimple)->updateSampleTimeStateToSix(strSampleTimeId);
    }
    else
    {
        SINGLETON(RDbOperationSimple)->deleteSampleTimeById(strSampleTimeId);
        //update tb_eids_model_sample_time t set t.state = '0' where t.model_id='%s' and t.state = '2'
        SINGLETON(RDbOperationSimple)->updateSampleTimeStateToZero(modelSelection->mModelId);
    }

    return true;
}
