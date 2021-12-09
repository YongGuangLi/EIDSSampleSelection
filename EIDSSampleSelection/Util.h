/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: Util.h
* 文件描述: 基础函数类
*  作  者 : 林晓雨，
* 创建日期: 2015-05-14 15:38:21
*******************************************************************************/

#ifndef __UTIL_H__
#define __UTIL_H__

#include "RtdbOpt.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <string.h>
#include "AlarmLog.h"
#include "RsdbAdapter.h"
#include "StartupServer.h"
#include "public_function_library.h"

using namespace std;

namespace Util
{
    ////功能描述: 类型转换
    template<class in_type,class out_type>
    out_type Convert(const in_type & t)
    {
        out_type result;
        std::stringstream stream;
        stream << t;
        stream >> result;
        return result;
    }

    ////功能描述: 类型转换
    template<class out_type>
    out_type CharPointerConvert2Number(const char * t)
    {
        if (strlen(t) == 0)
        {
            return 0;
        }
        out_type result;
        std::stringstream stream;
        stream << t;
        stream >> result;
        return result;
    }

    //Util::Convert<char, string>(a)

    // 功能描述: 将数字类型转换为字符串
    template<class NumberType>
    std::string Number2String(NumberType vv)
    {
        std::string result = Convert<NumberType, std::string>(vv);
        result.erase(std::remove(result.begin(), result.end(),','), result.end());
        return result;
    }


    // 功能描述: 字符串切割处理函数
    bool StringSplit(const std::string &strSrc,
        std::vector<std::string> &lstRet,
        const std::string &strSplit);
    // 功能描述: 连接实时数据库
    bool connectRtdbDB();
    // 功能描述: 获取本机系统时间
    unsigned long getNowTime();

    // 功能描述: 检测关系数据库是否连接
    bool IsQtConnect();

    bool  SQLDirectExecute(std::string sql);

    RsdbAdapter *getRsdbAdapter();


    // 功能描述: 将long将为整分钟
    long convertIntMinute(const long &ltime);

    int getMinute(const time_t & c_time);

};

#endif
