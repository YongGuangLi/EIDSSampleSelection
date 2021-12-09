/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: CorMatrix.h
* 文件描述: 矩阵实现
*  作  者 : %林晓雨%
* 创建日期: 2016-1-5 9:46:28
*******************************************************************************/
#ifndef __CORMATRIX_H__
#define __CORMATRIX_H__

#include <vector>
#include <string>

class CorMatrix
{
private:
	double			**mData;   
	unsigned int	mRow;
	unsigned int	mCol;

public:
	//无参数的构造函数
	CorMatrix(void); 
	//析构函数声明
	~CorMatrix(void);

	CorMatrix(const CorMatrix& m);
	CorMatrix(unsigned int row, unsigned int col);
	CorMatrix(unsigned int row, unsigned int col, std::vector<double> &val);
	
	// 功能描述: 获取矩阵列数
	unsigned int GetCol() const;
	// 功能描述: 获取矩阵行数
	unsigned int GetRow() const;
	// 功能描述: 全0矩阵
	void SetZero();
	// 功能描述: f矩阵取绝对值，得到矩阵d
	void Absolute(CorMatrix &m);
	// 功能描述: 赋值矩阵值
	void Assignment(CorMatrix &m);
	// 功能描述: 写入指定行值
	void WriteAt(const unsigned int row, std::vector<double> &val);
	// 功能描述: 打印元素值
	void Display();
	// 功能描述: 写入指定行、列元素值
	void WriteElement(unsigned int row, unsigned int col, double dVal);
	// 功能描述: 字符串输出
	std::string ToString(unsigned int i);
	// 功能描述: 获取指定行、列元素值
	double ReadElement(unsigned int i,unsigned int j);
	// 功能描述: 获取矩阵所有值
	void ReadAt(std::vector<std::vector<double>> &vVal);
	// 功能描述: 写入列向量
	void WriteVectorCol(const unsigned int col, CorMatrix &m);
	// 功能描述: 写入元素值
	void WriteElementCol(
			const unsigned int rhsRow, 
			const unsigned int lhsRow,
			CorMatrix &lhsM);
	// 功能描述: 矩阵相加 
	void Add(const CorMatrix& rhs);
	// 功能描述: 矩阵相减
	void Sub(double d);
	// 功能描述: 矩阵求平均值
	double Average();
	// 功能描述: 行矩阵求和
	double SumVectorRow();
	// 功能描述: 矩阵求幂指数
	void Power(const double d);
	// 功能描述: 矩阵点乘
	void DotMul(const CorMatrix& rhs, const CorMatrix& lhs);
	// 功能描述: 矩阵求行列式
	double Determinent();
private:
	// 功能描述: 矩阵求行列式
	double DeterminentPriv(double **data, int n);
};

typedef CorMatrix*	CorMatrixPtr;
#endif
