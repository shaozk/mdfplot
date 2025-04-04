#include "Signals.h"

#include <QVector>
#include <QString>
#include <QColor>
Signals::Signals(const QString& name, const QColor& color, double value) 
    : mName(name)
    , mColor(color)
    , mValue(value)
 {
    
 }

Signals::~Signals()
{

}

#if 0
QVector<double> Signals::channelList() const
{
    if (mChannelObserver == nullptr)
    {
        return QVector<double>();
    }

    QVector<double> ret;
    double channelValue = 0.0; // channel value (no scaling)
    for (size_t sample = 0; sample < mChannelObserver->NofSamples(); ++sample)
    {
        const auto channelValid = mChannelObserver->GetChannelValue(sample, channelValue);
        if (channelValid)
        {
            ret.push_back(channelValue);
        }
    }

    return ret;
}
#endif