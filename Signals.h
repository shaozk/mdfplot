/**
 * @file Signals.h
 * @author shaozk (913667678@qq.com)
 * @brief 信号
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include <QString>
#include <QColor>

class Signals
{
public:
    explicit Signals(const QString& name, const QColor& color, double value);
    ~Signals();

    QString name() const { return mName; }
    QColor color() const { return mColor; }
    double value() const { return mValue; }

private:
    QString mName;
    QColor mColor;
    double mValue;
    
};
 