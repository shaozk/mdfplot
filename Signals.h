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

#include <QObject>
#include <QVector>
#include <QColor>
#include <memory>
#include <mdf/mdfReader.h>

class QString;
class Signals;

class Signals
{
public:
    explicit Signals(const QString& name = "", const QColor& color = QColor(), double value = 0.0f);
    ~Signals();

    QString name() const { return mName; }
    void setName(const QString& name) { mName = name; }
    QColor color() const { return mColor; }
    void setColor(const QColor& color) { mColor = color; }
    double value() const { return mValue; }
    void setValue(double value) { mValue = value; }


private:
    QString mName;
    QColor mColor;
    double mValue;

};

Q_DECLARE_METATYPE(Signals)

 