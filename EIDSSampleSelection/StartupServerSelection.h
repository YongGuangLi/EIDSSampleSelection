/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: StartupServerSelect.h
* 文件描述: 主控类
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-2 10:23:42
*******************************************************************************/
#ifndef __STARTUPSERVERSELECTION_H__
#define __STARTUPSERVERSELECTION_H__

#include <list>

#include "StartupServer.h"
#include "ModelSelectionMgr.h"

class StartupServerSelection : public StartupServer
{
public:
	StartupServerSelection(void);
	~StartupServerSelection(void);

	/* 
	 * 功能描述:  导入所有配置信息并开始计算
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	bool	calculate();

private:
	// 功能描述: 诊断模型样本时间段
	bool	loadSampleTime(VectorModelSelection &pVectorModelSelection);
	// 功能描述: 清除新插入
	bool	cleanSampleTimeData(const std::string &strModelId);
	// 功能描述: 执行
	bool	runSubTask(ModelSelectionMgr * modelSelection);
	// 功能描述: 执行样本筛选任务
	bool	runSampleSelectionTask(VectorModelSelection &pVectorModelSelection);
};

#endif
