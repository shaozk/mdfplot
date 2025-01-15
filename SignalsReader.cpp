#include "SignalsReader.h"

#include <QDebug>

using namespace mdf;

SignalsReader::SignalsReader(const QString& filePath)
    : mReader(nullptr)
    , mChannelMap(new ChannelObserverMap)
{
    if (mReader == nullptr)
    {
        auto stdFilePath = filePath.toStdString();
        mReader.reset(new mdf::MdfReader(stdFilePath));
    }

    if (!mReader->IsOk())
    {
        qDebug() << "MdfReader is not ok";
        return;
    }

    if (!mReader->ReadHeader())
    {
        qDebug() << "MdfReader can't read header";
        return;
    }

    if (!mReader->ReadEverythingButData())
    {
        qDebug() << "MdfReader can't read everything but data";
        return;
    }

    if (!loadData())
    {
        qDebug() << "MdfReader get channel observer error";
        return;
    }
}

SignalsReader::~SignalsReader()
{
    cleanData();
}

mdf::DataGroupList SignalsReader::getDataGroupList() const
{
    const auto* mdfFile = mReader->GetFile(); // Get the file interface.
    DataGroupList dgList;                   // Get all measurements.
    mdfFile->DataGroups(dgList);
    return dgList;
}

QStringList SignalsReader::getSignalList() const
{
    if (!isOk())
    {
        return {};
    }
    QStringList channelList;
    for (auto iter = mChannelMap->cbegin(); iter != mChannelMap->cend(); ++iter)
    {
        channelList.push_back(QString::fromStdString(iter->second->Name()));
    }
    return channelList;
}

QVector<double> SignalsReader::getSignalValueList(const QString &signalName) const
{
    if (!isOk())
    {
        return {};
    }
    auto iter = mChannelMap->find(signalName.toStdString());
    if (iter == mChannelMap->end())
    {
        return {};
    }
    QVector<double> ret;
    double channelValue = 0.0; // channel value (no scaling)
    for (size_t sample = 0; sample < iter->second->NofSamples(); ++sample)
    {
        const auto channelValid = iter->second->GetChannelValue(sample, channelValue);
        if (channelValid)
        {
            ret.push_back(channelValue);
        }
    }

    return ret;

}

bool SignalsReader::loadData()
{
    auto dgList = getDataGroupList();
    for (auto* dg4 : dgList)
    {
        const auto cgList = dg4->ChannelGroups();
        for (const auto* cg4 : cgList )
        {
            const auto cn_list = cg4->Channels();
            for (const auto* cn4 : cn_list)
            {
                auto sub = CreateChannelObserver(*dg4, *cg4, *cn4);
                (*mChannelMap)[cn4->Name()] = std::move(sub);
            }
        }
        if (!mReader->ReadData(*dg4))
        {
            return false;
        }

    }
    return true;
}

void SignalsReader::cleanData()
{
    auto dgList = getDataGroupList();
    for (auto* dg4 : dgList)
    {
        dg4->ClearData();
    }
}
