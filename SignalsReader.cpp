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

mdf::DataGroupList SignalsReader::getDataGroupList()
{
    const auto* mdf_file = mReader->GetFile(); // Get the file interface.
    DataGroupList dg_list;                   // Get all measurements.
    mdf_file->DataGroups(dg_list);
#if 0
    // in this example, we read in all sample data and fetch all values.
    for (auto* dg4 : dg_list) {
        // Subscribers holds the sample data for a channel.
        // You should normally only subscribe on some channels.
        // We need a list to hold them.

        channelobserverlist subscriber_list;
        const auto cg_list = dg4->channelgroups();
        for (const auto* cg4 : cg_list ) {
            const auto cn_list = cg4->channels();
            for (const auto* cn4 : cn_list) {
                // create a subscriber and add it to the temporary list
                auto sub = createchannelobserver(*dg4, *cg4, *cn4);

                subscriber_list.emplace_back(std::move(sub));
            }
        }
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
    return dg_list;
}
