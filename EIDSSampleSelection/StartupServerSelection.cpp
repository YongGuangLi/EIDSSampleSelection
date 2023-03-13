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
    QTime timeCount;
    timeCount.start();
    Aos_Assert_S("Start runSampleSelectionTask!");
    VectorModelSelection pVectorModelSelection;
    //状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算 5:初始化 6:不满足条件)
    //tb_eids_model_sample_time state=2
    bool rslt = loadSampleTime(pVectorModelSelection);
    if (!rslt)
    {
        Aos_Assert_S("loadSampleConState Failure!");
    }

    if (!pVectorModelSelection.empty())
    {
        rslt = runSampleSelectionTask(pVectorModelSelection);
        if (!rslt)
        {
            Aos_Assert_S("runSampleSelectionTask Failure!");
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

    //更新服务状态监测时间(监控服务专用)
    SINGLETON(RDbOperationSimple)->SubmitToControlProcessService();
    while (true)
    {
        if(timeCount.elapsed() > 60 * 1000)
            break;
        else
            PubOpt::SystemOpt::SleepWait(1000);
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
    //修改tb_eids_model_sample_time state = 1
    SINGLETON(RDbOperationSimple)->updateSampleTimeStateToOne(strSampleTimeId);
    bool rslt = modelSelection->loadConfigInfo();
    if (!rslt)
    {
        Aos_Assert_S("loadConfigInfo Failure!");
        return true;
    }

    rslt = modelSelection->sampleSelection();

    if (!rslt)
    {
        SINGLETON(RDbOperationSimple)->updateSampleTimeStateToThree(strSampleTimeId);
        Aos_Assert_S("sampleSelection Failure!");
        return true;
    }

    if (modelSelection->GetAfterScreeningSum() <= 0)
    {
        //如果筛选后没有生成了子记录,修改tb_eids_model_sample_time,State = 6 和 samples_sum = 0
        SINGLETON(RDbOperationSimple)->updateSampleTimeStateToSix(strSampleTimeId);
    }
    else
    {
        //删除初始筛选记录 tb_eids_model_sample_time
        SINGLETON(RDbOperationSimple)->deleteSampleTimeById(strSampleTimeId);

        //筛选成功，把tb_eids_model_sample_time state置0
        //update tb_eids_model_sample_time t set t.state = '0' where t.model_id='%s' and t.state = '1'
        SINGLETON(RDbOperationSimple)->updateSampleTimeStateToZero(modelSelection->mModelId);
    }

    return true;
}
