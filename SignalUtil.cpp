#include "SignalUtil.h"

#include <QColor>
#include <QRandomGenerator>

QColor SignalUtil::getColor() 
{
    return QColor::fromHsv(QRandomGenerator::global()->bounded(360), 
                           QRandomGenerator::global()->bounded(100, 255),
                           QRandomGenerator::global()->bounded(150, 255));
}