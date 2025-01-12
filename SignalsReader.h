/**
 * @file 		MdfUtil.h
 * @author      shaozk
 * @date		2025/01/10
 * @brief 		读取Mdf文件
 * @details
 */

#pragma once

#include <mdf/mdfreader.h>
#include <mdf/ichannelgroup.h>
#include <mdf/idatagroup.h>

#include <QString>

using mdf::MdfReader;
using mdf::DataGroupList;
using mdf::ChannelObserverPtr;
using mdf::ChannelObserverList;


/**
 * @brief 解析MDF数据工具类
*/
class SignalsReader
{
public:
    explicit SignalsReader(const QString& filePath);
    ~SignalsReader() = default;
    mdf::DataGroupList getDataGroupList();

private:
    std::unique_ptr<mdf::MdfReader> mReader;

};

