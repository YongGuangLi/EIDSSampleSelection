/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: TesterGetFile.cpp
* 文件描述:
*  作  者 : %林晓雨%
* 创建日期: 2016-1-11 11:47:13
*******************************************************************************/

#include "TesterGetFile.h"

#include "Util.h"
#include "public_function_library.h"
#include <iostream> 
#include <vector>
#include <string.h>

TesterGetFile::TesterGetFile(void)
:
mIsWrite(false),
mRow(0)
{
	initGetFile();
}

TesterGetFile::~TesterGetFile(void)
{
}

void
TesterGetFile::initGetFile()
{
	 getPointName();
	 getSample();
}

char *
TesterGetFile::getLine(
				  const char *file_db, 
				  int &crt_idx)
{
	char* psz_db = (char *)(file_db + crt_idx);
	int bit = 0;
	while (psz_db[bit] != '\0')
	{
		if ((psz_db[bit++] == '\n')) break;
	}

	// 文件结束
	if (bit == 0)  return NULL;

	// 处理Windows行以\r\n结束符情况
	if (psz_db[bit - 2] == '\r')
	{
		psz_db[bit - 2] = '\0';
	}
	psz_db[bit-1] = '\0';
	crt_idx += bit;
	return psz_db;
}


bool
TesterGetFile::readPointTableFile(
		  const std::string &fname, 
		 char *&file_db, 
		 const int file_len)
{
	File * file = new File(fname.c_str(), "rb");
	if(!file->isGood())
	{
		delete file;
		return false;
	}

	if (file->read(file_db, file_len) == 0)
	{
		delete file;
		return false;
	}
	delete file;
	return  true;
}

bool
TesterGetFile::getPointName()
{
	//数据相关性分析
	//std::string file_path = "D:\\other\\pointname_corr.txt";
	//样本筛选
	std::string file_path = "D:\\other\\pointname.txt";
	int file_len = 0;
	bool rslt = PubOpt::FileOpt::GetFileSize(file_path, file_len);

	char* file_db = new char[file_len +1];
	memset(file_db, 0, file_len);

	if(!readPointTableFile(file_path, file_db, file_len))
	{
		delete [] file_db;
		return false;
	}

	int crt_idx = 0;
	char *group_str;
	std::vector<std::string> lt_ret;
	file_db[file_len] = '\0';

	unsigned int index = 0;
	while((group_str = getLine(file_db, crt_idx)) != NULL)
	{
		std::vector<double> data1;
		lt_ret.clear();
        Util::StringSplit(group_str, lt_ret, ",");
		for (unsigned int i =0 ; i < lt_ret.size(); i++)
		{
			mPointName.insert(make_pair(lt_ret[i], index));
			index ++;
		}		
	}	
	delete [] file_db;
	return true;
}


bool
TesterGetFile::getSample()
{	  
	//样本筛选
	std::string file_path = "D:\\other\\sample28085.txt";
	//数据相关性分析
	//std::string file_path = "D:\\other\\c_ycfj.txt";
	int file_len = 0;
	bool rslt = PubOpt::FileOpt::GetFileSize(file_path, file_len);

	char* file_db = new char[file_len +1];
	memset(file_db, 0, file_len);

	if(!readPointTableFile(file_path, file_db, file_len))
	{
		delete [] file_db;
		return false;
	}

	int crt_idx = 0;
	char *group_str;
	std::vector<std::string> lt_ret;
	file_db[file_len] = '\0';
	
	while((group_str = getLine(file_db, crt_idx)) != NULL)
	{
		std::vector<double> data;
		lt_ret.clear();
		Util::StringSplit(group_str, lt_ret, ",");
		for (unsigned int i =0 ; i < lt_ret.size(); i++)
		{
			double vv = atof(lt_ret[i].c_str());
			data.push_back(vv);
		}
	    mData.push_back(data);
	}	
	delete [] file_db;
	return true;
}

void
TesterGetFile::reset()
{
	mRow = 0;
	mIsWrite = false;
}

bool
TesterGetFile::nextValue(MapStringToDataValueInfo &pMapDataValueInfo, 
						 const long &lStartTime, 
						 const long &lEndTime,
						 const int iStep)
{
	unsigned int col;
	if (mData.size() <= mRow) 
	{
		return false;
	}

	std::string strCode;
	MapStringToDataValueInfo_It dItr;
	std::map<std::string, unsigned int>::iterator itr;
	for (long lCalTime = lStartTime; lCalTime <= lEndTime; lCalTime += iStep)
	{
		if (mData.size() <= mRow) 
		{
			return false;
		}
		for (dItr = pMapDataValueInfo.begin(); dItr != pMapDataValueInfo.end(); ++dItr)
		{
			strCode = dItr->second->mStrCode;

			itr = mPointName.find(strCode);
			if (itr != mPointName.end())
			{
				 col = itr->second;
				 if (col >= mData[mRow].size())	
				 {
					 dItr->second->moveToOriginalValues(0);
					 continue;
				 }

				 dItr->second->moveToOriginalValues(mData[mRow][col]);
			}
			else
			{
			   dItr->second->moveToOriginalValues(0);
			}
		}
		mRow ++;
	}
	return true;
}


bool
TesterGetFile::writeData(const std::string &modelId, 
						 const std::string &condId, 
						 VectorSampleTimeInfo &pSampleTimeInfo, 
						 bool isAll)
{
	std::string full_name = "D:\\other\\gen\\sampleselection.txt";
	if (!mIsWrite)
	{
		File * file = new File(full_name.c_str(), "w+");
		if(!file->isGood())
		{
			delete file;
			return false;
		}
		file->closeFile();
		delete file;
		mIsWrite = true;
	}
	bool isopen = false;
	std::string str_msg; 
	SampleTimeInfo *timeInfo;
	VectorSampleTimeInfo_It sItr;
	std::string strStartDate, strEndDate;
	for (sItr = pSampleTimeInfo.begin(); sItr != pSampleTimeInfo.end(); ++sItr)
	{
		timeInfo = *sItr;
		if (!isAll && !timeInfo->mIsHis) continue;

		strEndDate = PubOpt::SystemOpt::DateTmToStr(timeInfo->mEndTime);
		strStartDate = PubOpt::SystemOpt::DateTmToStr(timeInfo->mStartTime);
	
		str_msg = PubOpt::StringOpt::StringFormat("%s,%s,%s,%d,%s,%s,%ld \r\n", 
			timeInfo->mSampleTimeId.c_str(),
			strStartDate.c_str(),
			strEndDate.c_str(),
			timeInfo->mStep,
			modelId.c_str(),
			condId.c_str(),
			timeInfo->mSampleSum);

		File *file = new File(full_name.c_str(), "r+");
		if(!file->isGood())
		{
			delete file;
			return false;
		}
		
		//str_msg = PubOpt::StringOpt::StringFormat("%s \r\n", str_msg.c_str());	
		bool rslt = file->append(str_msg.c_str(), str_msg.size());
		if (!rslt)
        {
			return false;
		}
		file->afflush();
		file->closeFile();
		str_msg.clear();
	}
	return true;
}



bool
TesterGetFile::writeData(std::vector<std::vector<double>> &rdata, const std::string &fname)
{
	std::string full_name = "D:\\other\\rslt\\";
	full_name += fname;
	full_name += ".txt";
	File * file = new File(full_name.c_str(), "wb");
	if(!file->isGood())
	{
		delete file;
		return false;
	}

	int num = 0;
	std::string str_msg;
	for (unsigned int i = 0; i < rdata.size(); i++)
	{
		for (unsigned int j = 0; j < rdata[i].size(); j++)
		{
			std::string vStr = Util::Number2String<double>(rdata[i][j]);
			if (str_msg.empty())
			{
				str_msg = PubOpt::StringOpt::StringFormat("%s",vStr.c_str());
			}
			else
			{
				str_msg = PubOpt::StringOpt::StringFormat("%s, %s", str_msg.c_str(), vStr.c_str());
			}
		}
		str_msg = PubOpt::StringOpt::StringFormat("%s \r\n", str_msg.c_str());
		file->append(str_msg.c_str(), str_msg.size());
		str_msg.clear();
	}
	//file->fflush();
	file->closeFile();
	delete file;
	return true;
}
