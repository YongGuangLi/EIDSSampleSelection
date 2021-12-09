/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: ModelSelectionMgr.h
* 文件描述: 模型样本筛选
*  作  者 : %林晓雨%
* 创建日期: 2016-8-30 14:57:35
*******************************************************************************/

#ifndef __MODELSELECTIONMGR_H__
#define __MODELSELECTIONMGR_H__

#include "RtdbOpt.h"
#include "TypeDef.h"
#include "SampleTimeInfo.h"
#include "DataValueInfo.h"

class ModelSelectionMgr
{
	enum E
	{
		eLoadDataNum = 30  //30条数据
	};
public:
	std::string							mModelId;					//模型ID
	SampleTimeInfo*						mOriginalSTimeInfo;			//筛选时间段信息
																
private:
	MapStringToDataValueInfo			mMapDataValueInfo;		  //测点
	MapStringToSampleConditionInfo		mMapSampleCondInfo;		  //模型监测条件(模式筛选配置)
	VectorSampleTimeConInfo				mVectorSampleTimeConInfo; //样本时间段筛选条件(手工筛选配置)

	MapStringToVectorSampleTimeInfo		mMapVectorSampleTimeInfo;  //模型模式分类时间段结果

	int									mAfterScreeningSum;			//筛选后记录条数

public:
	ModelSelectionMgr(void);
	~ModelSelectionMgr(void);

	static bool cmp(const ModelSelectionMgr *lhs, const ModelSelectionMgr *rhs)   //升序排序
	{
		return (strcmp(lhs->mModelId.c_str(), rhs->mModelId.c_str()) < 0);
	}

public:
	// 功能描述: 从关系数据库中导入服务基础配置
	bool loadConfigInfo();
	// 功能描述: 样本筛选
	bool sampleSelection();

	int GetAfterScreeningSum(){return mAfterScreeningSum;}
private:
	// 功能描述: 导入模型模式条件
	bool loadModelCondition();
	// 功能描述: 导入模型测点
	bool loadModelMonitPoint();
	// 功能描述: 导入手工过滤条件
	bool loadSampleTimeCon();
	//// 功能描述: 判断DCS点在实时数据库中是否存在
	//bool pointIdSourceIdRtdbIsExist();
	// 功能描述: 执行样本筛选 
	bool selection(const long &lStartCalTime, const long &lEndCalTime, const long &lStep);
	// 功能描述: 判断手工过滤条件 
	bool judgeManualFilterCondition(const long &lCalStampTime);
	// 功能描述: 执行模型模式分类
	bool sampleModeCategor(const long &lCalStampTime, const long &lStep);
	// 功能描述: 导入测点、手工点值
	bool loadPointData(const long &lStartCalTime, const long &lEndCalTime, const long &lStep);
	// 功能描述: 下移数据缓存器
	void nextOriginaValue();
	// 功能描述: 构建样本时间段
	void setSampleTimeInfo(const std::string &strCondId, const long &lCalStampTime, const long &lStep);
	// 功能描述: 保存完整样本时间段
	bool saveSampleTimeInfo();
	// 功能描述: 保存所有的时间段
	bool saveSampleTimeInfoAll();
	
	bool saveSampleTimeInfoPriv(const bool isAll = false);

	bool saveModelSampleTimeAndTimeCon(const std::string &condId, VectorSampleTimeInfo &pSampleTimeInfo, bool isAll);
	
	bool saveModelSampleTimeCon(const std::string &strSampleTimeId);
	// 功能描述: 清除缓存数据
    void cleanHisSampleTimeInfo(VectorSampleTimeInfo &vecSampleTimeInfo, const bool isAll = false);

	void parseExpressionToDPoint();
	// 功能描述: 构造时间段对象
    SampleTimeInfo *createSampleTimeInfo(const long &lCalStampTime, const long &lStep);
};

typedef std::vector<ModelSelectionMgr *>		VectorModelSelection;
typedef VectorModelSelection::iterator			VectorModelSelection_It;
#endif
