/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: TesterGetFile.h
* 文件描述: 
*  作  者 : %林晓雨%
* 创建日期: 2016-1-11 11:46:55
*******************************************************************************/

#ifndef __TESTERGETFILE_H__
#define __TESTERGETFILE_H__

#include <iostream>
#include <vector>
#include <stdio.h>
						
#include "TypeDef.h"
#include "DataValueInfo.h"
#include "public_function_library.h"
class File
{
	FILE *          		mFile;
	std::string 		    mName;
	std::string            	mMode;

public:
	File(const std::string &name, const std::string &mode)
	:
	mFile(NULL),
	mName(name),
	mMode(mode)
	{
		mFile = ::fopen(mName.c_str(), mMode.c_str());
	}

	~File(void)
	{
		closeFile();
	}

	//功能描述:关闭文件 
	void closeFile()
	{
		if (!mFile)  return;
		::fclose(mFile);
		mFile = NULL;
	}

	//功能描述:判断文件否打开 
	bool isGood() const {return mFile != NULL;}

	//功能描述:写文件 
	bool append(const void* data, const unsigned int &data_len)
	{
		if (mFile == NULL) return false;
		::fseek(mFile, 0, SEEK_END);
		size_t asize = ::fwrite(data, 1, data_len, mFile);
		if (asize < 0 || (unsigned int) asize != data_len)
		{
			return false;
		}
		return true;
	}


	//功能描述:读文件 
	unsigned int  read(void* data, const unsigned int &data_len)
	{
		if (mFile == NULL) return 0;
		unsigned int rr =::fread(data, 1, data_len, mFile);
		return rr;
	}


	int getFileSize() const
	{
		int file_len = 0;
		if (!PubOpt::FileOpt::GetFileSize(mName, file_len))
		{
			return -1;
		}
		return file_len;
	}

	void afflush()
	{
		fflush(mFile);
	}
};


class TesterGetFile
{
public:
	TesterGetFile(void);
	~TesterGetFile(void);

	void initGetFile();

public:
	std::map<std::string, unsigned int> mPointName;
	std::vector<std::vector<double>>	mData;
	unsigned int						mRow;
	bool								mIsWrite;							

	void reset();
	bool nextValue(MapStringToDataValueInfo &pMapDataValueInfo, 
		const long &lStartTime, 
		const long &lEndTime,
		const int iStep);

	bool writeData(const std::string &modelId, 
		const std::string &condId, 
		VectorSampleTimeInfo &pSampleTimeInfo, 
		bool isAll);

	static bool writeData(std::vector<std::vector<double>> &rdata, const std::string &fname);
private:
	bool getSample();

	bool getPointName();

	char * getLine(
		const char *file_db, 
		int &crt_idx);

	bool readPointTableFile(
		const std::string &fname, 
		char *&file_db, 
		const int file_len);
};

#endif