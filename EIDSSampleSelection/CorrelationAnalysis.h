/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: CorrelationAnalysis.h
* 文件描述: 数据相关性分析
*  作  者 : %林晓雨%
* 创建日期: 2016-10-24 10:48:31
*******************************************************************************/

#ifndef __CORRELATIONANALYSIS_H__
#define __CORRELATIONANALYSIS_H__

#include "CorMatrix.h"
#include <string>


#define CORR_ONETHOUSAND			1000
#define CORR_ONEMILLION				10000

class CorrelationAnalysis
{
	enum E
	{
		eTaCheck  = 2
	};
	std::string				mStrErrorMessage;
public:
	// 功能描述: 无参数的构造函数
	CorrelationAnalysis();

	// 功能描述: 析构函数声明
	~CorrelationAnalysis();

	// 功能描述: 数据相关性分析
	bool Calculate(
		std::vector<std::vector<double>> &rdata, 
		std::vector<std::vector<double>> &vTdata,
		std::vector<std::vector<double>> &vT2data);

	// 功能描述: 获取错误信息
	std::string GetStrErrorMessage() {return mStrErrorMessage;}
private:
	// 功能描述: 相关性分析
	bool PCorr(CorMatrixPtr &dMatrix, 
				unsigned int iNSampleNum,
				unsigned int iDPointNum,
				CorMatrixPtr &tMatrix,
				CorMatrixPtr &t2Matrix);

	// 功能描述: 求相关度
	double CorrCoef(unsigned int iNSampleNum, CorMatrix &aiMatrix, CorMatrix &ajMatrix);
	// 功能描述: 提取样本
	CorMatrixPtr ExtractSample(std::vector<std::vector<double>> &vRdata);
	// 功能描述: 释放指标内存空间
	void DestoryPointer(CorMatrixPtr &matrix);
	// 功能描述: 计算相关度矩阵
	CorMatrixPtr CalCorrDegreeMatrix(CorMatrixPtr &dMatrix, unsigned int iNSampleNum, unsigned int iDPointNum);
	// 功能描述: 求矩阵r的伴随矩阵
	CorMatrixPtr CalCompanionMatrix(CorMatrixPtr &rMatrix, unsigned int iDPointNum);
	// 功能描述: 构造求行列式矩阵
	CorMatrixPtr CreateRDetMatrix(CorMatrixPtr &rMatrix, std::vector<unsigned int> &vNi, std::vector<unsigned int> &vNj);
	// 功能描述: 减去第i行
	void AssiVectorElement(unsigned int iDPointNum, unsigned int iDiscVal, std::vector<unsigned int> &vN);
	// 功能描述: 偏相关系数矩阵
	CorMatrixPtr CalPartialCorrCoef(CorMatrixPtr &bCoeffMatrix, unsigned int iDPointNum);
	// 功能描述: 对偏相关进行显著性检验
	CorMatrixPtr CalSignificanceTest(CorMatrixPtr &tMatrix, unsigned int iDPointNum, unsigned int iNSampleNum);
};
#endif
