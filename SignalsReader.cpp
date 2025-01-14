#include "SignalsReader.h"

#include <QDebug>

using namespace mdf;

SignalsReader::SignalsReader(const QString& filePath)
    : mReader(nullptr)
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

}

mdf::DataGroupList SignalsReader::getDataGroupList() const
{
    const auto* mdfFile = mReader->GetFile(); // Get the file interface.
    DataGroupList dgList;                   // Get all measurements.
    mdfFile->DataGroups(dgList);
    return dgList;
}

ChannelObserverList SignalsReader::getChannelObserverList() const
{
    auto dgList = getDataGroupList();
    ChannelObserverList subscriberList;
    for (auto* dg4 : dgList)
    {
        const auto cgList = dg4->ChannelGroups();
        for (const auto* cg4 : cgList )
        {
            const auto cn_list = cg4->Channels();
            for (const auto* cn4 : cn_list)
            {
                auto sub = CreateChannelObserver(*dg4, *cg4, *cn4);
                subscriberList.emplace_back(std::move(sub));
            }
        }
    }
    return subscriberList;
}

#if 0
        // now it is time to read in all samples
        reader.readdata(*dg4); // read raw data from file
        double channel_value = 0.0; // channel value (no scaling)
        double eng_value = 0.0; // engineering value
        for (auto& obs : subscriber_list) {
            for (size_t sample = 0; sample < obs->nofsamples(); ++sample) {
                const auto channel_valid = obs->getchannelvalue(sample, channel_value);
                const auto eng_valid = obs->getengvalue(sample, eng_value);
                // you should do something with data here

            }

        }

        // not needed in this example as we delete the subscribers,
        // but it is good practise to remove samples data from memory
        // when it is no longer needed.
        dg4->ClearData();
    }
    reader.Close(); // Close the file
#endif
