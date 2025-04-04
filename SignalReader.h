/**
 * @file        MdfReader.h
 * @author      shaozk
 * @date        2025/01/10
 * @brief       读取Mdf文件
 * @details
 */

#pragma once

#include <mdf/mdfreader.h>
#include <mdf/ichannelgroup.h>
#include <mdf/idatagroup.h>

#include <QString>
#include <QStringList>
#include <QVector>
#include "Signals.h"

using mdf::MdfReader;
using mdf::DataGroupList;
using mdf::ChannelObserverPtr;
using mdf::ChannelObserverList;

using ChannelObserverMap = std::map<std::string, mdf::ChannelObserverPtr>;

/**
 * @brief 解析MDF数据工具类
*/
class SignalReader
{
public:
    explicit SignalReader(const QString& filePath);
    ~SignalReader();

    
    /**
     * @brief 判断是否读取正常
     */
    bool isOk() const { return !mChannelMap.empty(); }

    DataGroupList getDataGroupList() const;

    QStringList getSignalNameList() const;
    /**
     * @brief 根据信号名获取对应数据
     * @param signalName 信号名
     */
    QVector<double> getSignalValueList(const QString& signalName) const;

private:

    /**
     * @brief 加载数据
     * @details 加载ChannelObserverPtr并将其存放在成员变量mChannelMap中
     */
    bool loadData();

    /**
     * @brief 清空数据
     * @details 清空DataGroup中的数据
     */
    void cleanData();

private:
    std::unique_ptr<MdfReader> mReader;
    ChannelObserverMap mChannelMap;

};

using SignalReaderPtr = std::unique_ptr<SignalReader>;
