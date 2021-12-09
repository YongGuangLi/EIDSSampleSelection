/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: RDbOperationSimple.h
* 文件描述: 关系数据库简单操作实现类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-28 9:40:41
*******************************************************************************/

#ifndef __RDBOPERATIONSIMPLE_H__
#define __RDBOPERATIONSIMPLE_H__

#include <QUuid>
#include "AlarmLog.h"
#include "RDbHead.h"
#include "singleton.h"

class RDbOperationSimple
{
private:
	std::string mStrErrorMessage;      // 当前模块执行错误信息
public:
	DECLARE_SINGLETON_INIT(RDbOperationSimple)

public:
	// 功能描述: 获取系统惟一ID
	std::string getSysGuid();
	// 功能描述: 删除已处理的样本时间与手工筛选条件
	bool deleteSampleTimeById(const std::string &strId);

	// 功能描述: tb_eids_model_sample_time的state是'未计算'，将
	// tb_eids_model_sample_time中这个模型state改为'计算中';
	bool updateSampleTimeStateToOne(const std::string &strSampleTimeId);

	// 功能描述: tb_eids_model_sample_time的state是'计算中'，将
	// tb_eids_model_sample_time中这个模型state改为'筛选条件过严-6';
	bool updateSampleTimeStateToSix(const std::string &strSampleTimeId);
	// 功能描述: 将tb_eids_model_sample_time中这个模型state的'计算中'改为"计算失败";
	bool updateSampleTimeStateToThree(const std::string &strSampleTimeId);
	// 功能描述: 将tb_eids_model_sample_time中这个模型state的'新增加'改为"计算完成";
	bool updateSampleTimeStateToZero(const std::string &strModelId);
	// 功能描述: 当tb_eids_model_sample_time 的state是'计算中'，则表示是任务中断过，
	// 然后重新计算，重新计算需要删除上次未完成的计算结果，而结果是
	// 删除tb_eids_model_sample_time的state是'新插入'的记录
	bool deleteSampleTimeState2ByModelId(const std::string &strModelId);
	// 功能描述: 更新数据相关性分析任务状态
	bool updateCorrFinishStatus(const std::string &strModelId);
	// 功能描述: 更新数据相关性分析任务状态
	bool updateCorrFailedStatus(const std::string &strModelId);
	// 功能描述: 更新数据相关性分析任务状态
	bool updateCorrProcessingStatus(const std::string &strModelId);
	// 功能描述: 删除数据相关性分析非完整数据
	bool deleteCorrAnalysisData(const std::string &strModelId);
	// 功能描述: 更新监控服务所需要信息
	bool SubmitToControlProcessService();
	// 功能描述: 更新服务版本信息
	bool UpdateVersionNumber();
private:
	// 功能描述: 更新样本筛选状态
	bool updateSampleConState(const int istate, const std::string &strId);
	// 功能描述: 诊断模型配置状态
	bool updateSampleCorrStatePriv(const std::string &strModelId, const std::string &strState,  const std::string &strCondState);
	// 功能描述: 更新数据相关性分析任务状态
	bool updateSampleTimeCorrStatePriv(const std::string &strCorrState, const std::string &strId);
};
#endif
