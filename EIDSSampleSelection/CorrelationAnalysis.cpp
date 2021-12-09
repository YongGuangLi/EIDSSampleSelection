/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: CorrelationAnalysis.cpp
* 文件描述: 数据相关性分析
*  作  者 : %林晓雨%
* 创建日期: 2016-10-24 10:50:32
*******************************************************************************/

#include "CorrelationAnalysis.h"

#include <math.h>
#include <iostream>

CorrelationAnalysis::CorrelationAnalysis()
:
mStrErrorMessage("")
{

}

CorrelationAnalysis::~CorrelationAnalysis()
{
	
}

bool
CorrelationAnalysis::Calculate(
		std::vector<std::vector<double>> &vRdata, 
		std::vector<std::vector<double>> &vTdata,
		std::vector<std::vector<double>> &vT2data)
{
	mStrErrorMessage.clear();
	if (vRdata.size() <= 0) 
	{
		mStrErrorMessage = "In rdata.size() = 0. Please check it.";
		return false; 
	}

	CorMatrixPtr rMatrix = ExtractSample(vRdata);
	if (rMatrix == NULL) return false;
	
	CorMatrixPtr tMatrix, t2Matrix;
	unsigned int iDPointNum = rMatrix->GetCol();
	unsigned int iNSampleNum = rMatrix->GetRow();
	bool rslt = PCorr(rMatrix, iNSampleNum, iDPointNum, tMatrix, t2Matrix);
	if (!rslt || tMatrix == NULL || t2Matrix == NULL)
	{
		mStrErrorMessage = "In pcorr() = 0. Please check it.";
		DestoryPointer(tMatrix);
		DestoryPointer(rMatrix);
		return false;
	}

	DestoryPointer(rMatrix);
	tMatrix->ReadAt(vTdata);
	DestoryPointer(tMatrix);
	t2Matrix->ReadAt(vT2data);
	DestoryPointer(t2Matrix);
	return true;
}

CorMatrixPtr 
CorrelationAnalysis::ExtractSample(std::vector<std::vector<double>> &vRdata)
{
	int iRow = vRdata.size();
	int iCol = vRdata[0].size();

	//样本容量调节数   
	//N <= 1000  iox = 1; N >1000  && N <=10000   iox = 10;  N > 10000  iox = 100;
	int iOx = 1;	
	if (iRow > CORR_ONETHOUSAND  && iRow <= CORR_ONEMILLION) iOx = 10;
	if (iRow > CORR_ONEMILLION) iOx = 100;
	//确定样本容量
	unsigned int iFixVal = iRow / iOx;	 
	if (iFixVal < 50)
	{
		mStrErrorMessage = "样本容量过小. Please check it.";
		return NULL;
	}

	if (iOx * iFixVal >= iRow) 
	{
		mStrErrorMessage = "In iOx * iFixVal >= iRow.";
		return NULL;
	}

	unsigned int iI, iVecIdx;
	CorMatrixPtr rMatrix = new CorMatrix(iFixVal, iCol);
	rMatrix->SetZero();
	for (iI = 0; iI < iFixVal; iI++)
	{
		iVecIdx = (iOx *(iI+1))-1;
		rMatrix->WriteAt(iI, vRdata[iVecIdx]);
	}
	return rMatrix;
}

void
CorrelationAnalysis::DestoryPointer(CorMatrixPtr &matrix)
{
	if (matrix == NULL) return;
	delete matrix;
	matrix = NULL;
}

bool
CorrelationAnalysis::PCorr(
			   CorMatrixPtr &dMatrix, 
			   unsigned int iNSampleNum,
			   unsigned int iDPointNum, 
			   CorMatrixPtr &tMatrix,
			   CorMatrixPtr &t2Matrix)
{
	//求相关度矩阵
	CorMatrixPtr rMatrix = CalCorrDegreeMatrix(dMatrix, iNSampleNum, iDPointNum);
//rMatrix->Display();
	if (rMatrix == NULL)
	{
		mStrErrorMessage = "In rMatrix == NULL. Please check it.";
		DestoryPointer(rMatrix);
		return false;
	}

	//求矩阵r的伴随矩阵
	CorMatrixPtr bCoeffMat = CalCompanionMatrix(rMatrix, iDPointNum);
	DestoryPointer(rMatrix);
//bCoeffMat->Display();
	if (bCoeffMat == NULL)
	{
		mStrErrorMessage = "In cMatrix == NULL. Please check it.";
		DestoryPointer(bCoeffMat);
		return false;
	}

	//偏相关系数矩阵
	tMatrix = CalPartialCorrCoef(bCoeffMat, iDPointNum);
	DestoryPointer(bCoeffMat);
//tMatrix->Display();
	if (tMatrix == NULL)
	{
		mStrErrorMessage = "In rMatrix == NULL. Please check it.";
		return false;
	}

	//对偏相关进行显著性检验
	t2Matrix = CalSignificanceTest(tMatrix, iDPointNum, iNSampleNum);
//t2Matrix->Display();
	if (t2Matrix == NULL)
	{
		mStrErrorMessage = "In t2Matrix == NULL. Please check it.";
		return false;
	}
	return true;
}

//求相关度
double
CorrelationAnalysis::CorrCoef(unsigned int iNSampleNum, CorMatrix &aiMatrix, CorMatrix &ajMatrix)
{
	double dAvgIVal = aiMatrix.Average();
	aiMatrix.Sub(dAvgIVal);

	double dAvgJVal = ajMatrix.Average();
	ajMatrix.Sub(dAvgJVal);

	CorMatrix z1Matrix(iNSampleNum, 1);
	z1Matrix.SetZero();

	z1Matrix.DotMul(aiMatrix, ajMatrix);
	double dZmatVal = z1Matrix.SumVectorRow();

	aiMatrix.Power(2);
	double dAiMatVal = aiMatrix.SumVectorRow();

	ajMatrix.Power(2);
	double dAjCalVal = ajMatrix.SumVectorRow();

	//double calVal = dZmatVal/(sqrt(dAiMatVal)*sqrt(dAjCalVal));
	double dAIJCalVal = sqrt(dAiMatVal)*sqrt(dAjCalVal);
	double calVal = dZmatVal/ dAIJCalVal;
	if (dZmatVal == 0 || dAIJCalVal == 0) calVal = 0;
	return calVal;
}

//计算相关度矩阵
CorMatrixPtr 
CorrelationAnalysis::CalCorrDegreeMatrix(CorMatrixPtr &dMatrix, unsigned int iNSampleNum, unsigned int iDPointNum)
{
	double dCCorrVal;
	unsigned int iI, iJ;
	CorMatrix aiMatrix(iNSampleNum, 1);
	CorMatrix ajMatrix(iNSampleNum, 1);
	CorMatrixPtr rMatrix = new CorMatrix(iDPointNum, iDPointNum);
	for (iI = 0; iI < iDPointNum; iI++)
	{
		for (iJ = 0; iJ < iDPointNum; iJ++)
		{
			aiMatrix.WriteVectorCol(iI, *dMatrix);
			ajMatrix.WriteVectorCol(iJ, *dMatrix);

			dCCorrVal = CorrCoef(iNSampleNum, aiMatrix, ajMatrix);
			rMatrix->WriteElement(iI,iJ, dCCorrVal);
		}
	}
	return rMatrix;
}

//求矩阵r的伴随矩阵
CorMatrixPtr
CorrelationAnalysis::CalCompanionMatrix(CorMatrixPtr &rMatrix, unsigned int iDPointNum)
{
	CorMatrixPtr bCoeffMat = new CorMatrix(iDPointNum, iDPointNum);
	bCoeffMat->SetZero();

	unsigned int iI, iJ;
	CorMatrixPtr detMatrix = NULL;
	std::vector<unsigned int> vNi, vNj;
	double dDetCalVal, dPowCalVal, dBCoeVal, dPowParamVal; 
	for (iI = 0; iI < iDPointNum; iI ++)
	{
		vNi.clear();
		AssiVectorElement(iDPointNum, iI, vNi);
		for (iJ = 0;  iJ < iDPointNum; iJ++)
		{
			vNj.clear();
			AssiVectorElement(iDPointNum, iJ, vNj);
			detMatrix = CreateRDetMatrix(rMatrix, vNi, vNj);
			dDetCalVal = detMatrix->Determinent();
			DestoryPointer(detMatrix);
			dPowParamVal = (iI+1) + (iJ+1);
			dPowCalVal = pow(-1, dPowParamVal);
			dBCoeVal = dPowCalVal * dDetCalVal;
			bCoeffMat->WriteElement(iI, iJ, dBCoeVal);
		}
	}
	return bCoeffMat;
}

CorMatrixPtr
CorrelationAnalysis::CreateRDetMatrix(
				  CorMatrixPtr &rMatrix, 
				  std::vector<unsigned int> &vNi, 
				  std::vector<unsigned int> &vNj)
{
	double dVal;
	unsigned int iI, iJ, iK, iP;
	unsigned int iRow = vNi.size();
	unsigned int iCol = vNj.size();
	CorMatrixPtr detCalMatrix = new CorMatrix(iRow, iCol);
	for (iK = 0, iI = 0; iI < iRow; iI ++, iK ++)
	{
		for (iP = 0, iJ = 0; iJ < iCol; iJ++, iP ++)
		{
		   dVal = rMatrix->ReadElement(vNi[iI], vNj[iJ]);
		   detCalMatrix->WriteElement(iK, iP, dVal);
		}
	}
	return detCalMatrix;
}

void
CorrelationAnalysis::AssiVectorElement(
				unsigned int iDPointNum, 
				unsigned int iDiscVal, 
				std::vector<unsigned int> &vN)
{
	unsigned int iI = 0;
	for (iI = 0; iI < iDPointNum; iI++)
	{
		if (iI != iDiscVal) 
		{
		   vN.push_back(iI);
		}
	}
}


//偏相关系数矩阵
CorMatrixPtr
CorrelationAnalysis::CalPartialCorrCoef(CorMatrixPtr &bCoeffMatrix, unsigned int iDPointNum)
{
   double dCoeCalVal;
   unsigned int iI, iJ;
   CorMatrixPtr tMatrix = new CorMatrix(iDPointNum, iDPointNum);
   tMatrix->SetZero();
   for (iI = 0; iI < iDPointNum; iI ++)
   {
	   double bCoeIIVal = bCoeffMatrix->ReadElement(iI, iI);
	   for (iJ = iI; iJ < iDPointNum; iJ++)
	   {
		   dCoeCalVal = 1;
		   if (iI != iJ)
		   {
			  double bCoeIJVal = bCoeffMatrix->ReadElement(iI, iJ);
			  double bCoeJJVal = bCoeffMatrix->ReadElement(iJ, iJ);
			  //dCoeCalVal = -bCoeIJVal/sqrt(bCoeIIVal * bCoeJJVal);
			  double bSqrtCalVal = sqrt(fabs(bCoeIIVal * bCoeJJVal));
			  dCoeCalVal = -bCoeIJVal/ bSqrtCalVal;
			  if (bCoeIJVal == 0 || bSqrtCalVal == 0) dCoeCalVal = 0;
			  if (dCoeCalVal > 1) 
			  {
				  dCoeCalVal = 0.99;
			  }
			  else if (dCoeCalVal < -1) 
			  {
				  dCoeCalVal = -0.99;
			  }
		   }

		  tMatrix->WriteElement(iI, iJ, dCoeCalVal);
	   }
   }
   return tMatrix;
}

//对偏相关进行显著性检验
CorMatrixPtr 
CorrelationAnalysis::CalSignificanceTest(CorMatrixPtr &tMatrix, unsigned int iDPointNum, unsigned int iNSampleNum)
{
	unsigned int iI, iJ;
	double dTmatVal, dCalVal, dT1matCalVal, dAssumeVal;
	double dConstVal = (int)iNSampleNum - (int)iDPointNum -2;
	CorMatrixPtr t2Matrix = new CorMatrix(iDPointNum, iDPointNum);
	t2Matrix->SetZero();
	for (iI = 0; iI < iDPointNum; iI++)
	{
		for (iJ = iI; iJ < iDPointNum; iJ++)
		{
			dAssumeVal = 0; 
			if (iI != iJ)
			{
				dTmatVal = tMatrix->ReadElement(iI, iJ);
				dCalVal = 1 - pow(dTmatVal, 2);	
				//dT1matCalVal = dTmatVal * sqrt(dConstVal)/sqrt(dCalVal);
				double dTmatConstVal = dTmatVal * sqrt(dConstVal);
				double dSqCalVal = sqrt(dCalVal);
				dT1matCalVal = dTmatConstVal/dSqCalVal;
				if(dTmatConstVal == 0 || dSqCalVal == 0) dT1matCalVal = 0;
							
				//0代表拒绝原假设，显著相关，1代表接受原假设
				if (fabs(dT1matCalVal) >= eTaCheck)
				{
					dAssumeVal = 1;
					if (dT1matCalVal < 0) dAssumeVal = -1; 
				} 
			}
			t2Matrix->WriteElement(iI, iJ, dAssumeVal);	
		}
	}
	return t2Matrix;
}