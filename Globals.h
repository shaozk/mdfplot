/**
 * @file Globals.h
 * @author shaozk (913667678@qq.com)
 * @brief 全局变量
 * @version 0.1
 * @date 2025-03-26
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include <QColor>
#include <QObject>
#include <QDate>
#include <QString>

//! 全局常量和枚举定义
class Globals : public QObject 
{
    Q_OBJECT

private:
    Globals() {}

 public:
    virtual ~Globals() {}

    /// 返回版本号
    static int version();

    /// 返回APP名
    static QString name();

    /// 返回版本字符串
    static QString versionString();

    /// 返回发布日期字符串
    static QString releaseDateString();

    /// 返回发布日期
    static QDate releaseDate();

    /// 返回作者
    static QString author();

    /**
     * @brief 枚举值转字符串
     * @param key 枚举值
     * @param enumName 枚举字符串
     * @return 
    */
    static QString enumValueToString(int key, const QString& enumName);

    /**
     * @brief 枚举字符串转值
     * @param string 枚举字符串
     * @param enumName 枚举值
     * @return 
    */
    static int enumStringToValue(const QString& string, const QString& enumName);


 private:

    static const int mVersionNo;        ///< 版本号 
    static const char* mVersion;        ///< 版本
    static const QDate mReleaseDate;    ///< 发布日期
    static const char* mAuthor;         ///< 作者
    static const char* mName;           ///< 名称
};

