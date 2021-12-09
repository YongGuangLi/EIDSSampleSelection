/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: CorMatrix.cpp
* 文件描述: 矩阵实现
*  作  者 : %林晓雨%
* 创建日期: 2016-1-5 9:47:01
*******************************************************************************/

#include "CorMatrix.h"

#include <math.h>
#include <numeric> 
#include <algorithm>
#include <functional>
#include <stdio.h>

#include <iostream>

using namespace std;

CorMatrix::CorMatrix(void)
:
mRow(0),
mCol(0),
mData(NULL)
{
}


CorMatrix::~CorMatrix(void)
{
	if(mData != NULL)
	{
		for(unsigned int i=0;i<mRow;i++)
		{
			delete[] mData[i];
		}
		delete[] mData;
	}
	mRow = 0;
	mCol = 0;
}



// constructor
CorMatrix::CorMatrix(unsigned int row, unsigned int col)
:
mRow(row),
mCol(col)
{
	mData=new double*[row];
	for(unsigned int i=0;i<row;i++)
	{
		mData[i]=new double[col];
	}
}

CorMatrix::CorMatrix(unsigned int row, unsigned int col, vector<double> &val)
:
mRow(row),
mCol(col)
{
	mData=new double*[row];
	for(unsigned int i=0;i<row;i++)
	{
		mData[i]=new double[col];
	}

	unsigned int k = 0;
	for (unsigned int i=0; i<mRow; i++)
	{
		for(unsigned int j=0;j<mCol;j++) 
		{
			mData[i][j]=val[k++];
		}
	}
}


//copy  constructor
CorMatrix::CorMatrix(const CorMatrix& m)
:
mRow(m.mRow),
mCol(m.mCol)
{
	mData = new double*[mRow];
	for(unsigned int i=0;i<mRow;i++)
	{
		mData[i] = new double[mCol];
	}

	for(unsigned int i=0;i<mRow;i++)
	{
		copy(m.mData[i],m.mData[i]+mCol,mData[i]);
	}

}


unsigned int 
CorMatrix::GetRow() const
{
	return mRow;
}


unsigned int 
CorMatrix::GetCol() const
{
	return mCol;
}


void 
CorMatrix::SetZero()
{
    for(unsigned int i=0;i<mRow;i++)
        fill(mData[i],mData[i]+mCol,0);
}

void
CorMatrix::Absolute(CorMatrix &m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j]=fabs(m.mData[i][j]);
		}
	}
}


void
CorMatrix::Assignment(CorMatrix &m)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		copy(m.mData[i],m.mData[i]+mCol,mData[i]);
	}
}

void 
CorMatrix::Display()
{
    unsigned int i,j;
    for(i=0;i<mRow;i++)
    {
        for(j=0;j<mCol;j++)
			cout << mData[i][j] << "  ";
            //printf("%lf  ",mData[i][j]);
       cout << endl;
    }
	cout << "--------------------------- " << endl;
}


void
CorMatrix::WriteElement(unsigned int row, unsigned int col, double dVal)
{
	mData[row][col] = dVal;
}


double 
CorMatrix::ReadElement(unsigned int i,unsigned int j)
{
	return mData[i][j];
}


void 
CorMatrix::WriteAt(const unsigned int row, std::vector<double> &val)
{
	for (unsigned int j = 0; j < mCol; j++)
	{
		mData[row][j] = val[j];
	}
}

void
CorMatrix::WriteVectorCol(const unsigned int col, CorMatrix &m)
{
	//从thisQuery矩阵复制row行所有元素到新矩阵中
	for (unsigned int i = 0; i < mRow; i++)
	{
		mData[i][0] = m.mData[i][col];
	}
}

void
CorMatrix::WriteElementCol(
		const unsigned int rhsRow, 
		const unsigned int lhsRow,
		CorMatrix &lhsM)
{
	for (unsigned int i = 0; i < mCol; i++)
	{
		mData[rhsRow][i] = lhsM.mData[lhsRow][i];
	}
}


void
CorMatrix::Add(const CorMatrix& rhs) 
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for (unsigned int j=0; j<mCol;j++)
		{
			mData[i][j] = rhs.mData[i][j] + mData[i][j];
		}	
	}
}

void
CorMatrix::Sub(double d)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j] = mData[i][j] - d;
		}
	}
}


double
CorMatrix::Average()
{
	int num = 0;
	double sum = 0;
	for(unsigned int i=0;i<mRow;i++)
	{
		for (unsigned int j=0; j<mCol;j++)
		{
			sum += mData[i][j];
			num ++;
		}	
	}
	double avg = sum / num;
	return avg;
}


void
CorMatrix::DotMul(const CorMatrix& rhs, const CorMatrix& lhs)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j] = rhs.mData[i][j]*lhs.mData[i][j];
		}
	}
}


double 
CorMatrix::SumVectorRow() 
{			  
	double sum = 0;
	for(unsigned int i=0;i<mRow;i++)
	{
		sum += mData[i][0];
	}
	return sum;
}


void
CorMatrix::Power(const double d)
{
	for(unsigned int i=0;i<mRow;i++)
	{
		for(unsigned int j=0;j<mCol;j++)
		{
			mData[i][j] = pow(mData[i][j], d);
		}
	}
}



//#define zero(x) (fabs(x) < 1e-10)
#define zero(x) (fabs(x) < 1e-308)

//化为三角形行列式
double 
CorMatrix::Determinent()
{
	return DeterminentPriv(mData, mRow);
}

double 
CorMatrix::DeterminentPriv(double **data, int n)
{
	unsigned int j, sign = 0;
	double ret = 1, t; 

	double **b = new double*[n];
	for (unsigned int i = 0; i < n; i++)
	{
		b[i] = new double[n];
		for (unsigned int j=0; j < n; j++)
		{
			b[i][j] = data[i][j];
		}
	}

	for (unsigned int i = 0; i < n; i++)
	{
		if (zero(b[i][i]))
		{
			for (j = i+1; j < n; j++)
			{
				if (!zero(b[j][i]))
				{
					break;
				}
			}
			if (j == n) 
			{
				if(b != NULL)
				{
					for(i=0;i<n;i++)
					{
						delete[] b[i];
					}
					delete[] b;
				}
				return 0;
			}

			for (unsigned int k = i; k < n; k++)
			{
				t = b[i][k], b[i][k] = b[j][k], b[j][k] = t;
			}
			sign++;	
		}
		ret *= b[i][i];
		for (unsigned int k = i+1; k < n; k++)
		{
			b[i][k]/=b[i][i];
		}
		for (j = i+1; j < n; j++)
		{
			for (unsigned int k = i +1; k < n; k++)
			{
				b[j][k]-=b[j][i]*b[i][k];
			}
		}
	}

	if (sign & 1) ret =-ret;

	if(b != NULL)
	{
		for(unsigned int i=0;i<n;i++)
		{
			delete[] b[i];
		}
		delete[] b;
	}
	return ret;
}


void 
CorMatrix::ReadAt(std::vector<std::vector<double>> &vVal)
{
	for (unsigned int i = 0; i < mRow; i++)
	{
		std::vector<double> vColVal;
		for (unsigned int j = 0; j < mCol; j++)
		{
			vColVal.push_back(mData[i][j]);
		}
		vVal.push_back(vColVal);
	}
}






