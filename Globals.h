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
public:
	inline static const QVector<QString> SnsStr = { 
        "FL", 
        "FLM", 
        "FRM", 
        "FR", 
        "RL", 
        "RLM", 
        "RRM", 
        "RR", 
        "FLS", 
        "FRS", 
        "RLS", 
        "RRS" 
    };

    // 颜色
    inline static const QVector<QColor> SignalColor = {
        Qt::black,
        Qt::darkGray,
        Qt::gray,
        Qt::lightGray,
        Qt::red,
        Qt::green,
        Qt::blue,
        Qt::cyan,
        Qt::magenta,
        Qt::yellow,
        Qt::darkRed,
        Qt::darkGreen,
        Qt::darkBlue,
        Qt::darkCyan,
        Qt::darkMagenta,
        Qt::darkYellow,
        QColor(128,0,0),
        QColor(220,20,60),
        QColor(255,99,71),
        QColor(240,128,128),
        QColor(255,140,0),
        QColor(189,183,107),
        QColor(107,142,35),
        QColor(173,255,47),
        QColor(34,139,34),
        QColor(0,250,154),
        QColor(0,255,255),
        QColor(0,206,209),
        QColor(95,158,160),
        QColor(100,149,237),
        QColor(135,206,250),
        QColor(0,0,139),
        QColor(65,105,225),
        QColor(72,61,139),
        QColor(255,105,180),
        QColor(139,69,19),
        QColor(210,180,140),
        QColor(112,128,144),
        QColor(255,218,185),
        QColor(160,82,45),
        QColor(205,133,63),
        QColor(188,143,143),
        QColor(255,20,147),
        QColor(218,112,214),
        QColor(221,160,221),
        QColor(148,0,211),
        QColor(123,104,238),
        QColor(75,0,130),
        QColor(30,144,255),
        QColor(0,206,209),
        QColor(0,128,128),
        QColor(128,0,0),
        QColor(20,20,60),
        QColor(25,99,71),
        QColor(20,128,128),
        QColor(25,140,0),
        QColor(19,183,107),
        QColor(17,142,35),
        QColor(13,255,47),
        QColor(3,139,34),
        QColor(0,250,154),
        QColor(0,255,255),
        QColor(0,206,209),
        QColor(9,158,160),
        QColor(10,149,237),
        QColor(15,206,250),
        QColor(0,0,139),
        QColor(6,105,225),
        QColor(7,61,139),
        QColor(25,105,180),
        QColor(19,69,19),
        QColor(20,180,140),
        QColor(12,128,144),
        QColor(25,218,185),
        QColor(10,82,45),
        QColor(25,133,63),
        QColor(18,143,143),
        QColor(25,20,147),
        QColor(28,112,214),
        QColor(21,160,221),
        QColor(18,0,211),
        QColor(13,104,238),
        QColor(7,0,130),
        QColor(3,144,255),
        QColor(0,206,209),
        QColor(0,128,128),
        QColor(128,0,0),
        QColor(220,20,60),
        QColor(255,99,71),
        QColor(240,128,128),
        QColor(255,140,0),
        QColor(189,183,107),
        QColor(107,142,35),
        QColor(173,255,47),
        QColor(34,139,34),
        QColor(0,250,154),
        QColor(0,255,255),
        QColor(0,206,209),
        QColor(95,158,160),
        QColor(100,149,237),
        QColor(135,206,250),
        QColor(0,0,139),
        QColor(65,105,225),
        QColor(72,61,139),
        QColor(255,105,180),
        QColor(139,69,19),
        QColor(210,180,140),
        QColor(112,128,144),
        QColor(255,218,185),
        QColor(160,82,45),
        QColor(205,133,63),
        QColor(188,143,143),
        QColor(255,20,147),
        QColor(218,112,214),
        QColor(221,160,221),
        QColor(148,0,211),
        QColor(123,104,238),
        QColor(75,0,130),
        QColor(30,144,255),
        QColor(0,206,209),
        QColor(0,128,128),
        QColor(128,0,0),
        QColor(20,20,60),
        QColor(25,99,71),
        QColor(20,128,128),
        QColor(25,140,0),
        QColor(19,183,107),
        QColor(17,142,35),
        QColor(13,255,47),
        QColor(3,139,34),
        QColor(0,250,154),
        QColor(0,255,255),
        QColor(0,206,209),
        QColor(9,158,160),
        QColor(10,149,237),
        QColor(15,206,250),
        QColor(0,0,139),
        QColor(6,105,225),
        QColor(7,61,139),
        QColor(25,105,180),
        QColor(19,69,19),
        QColor(20,180,140),
        QColor(12,128,144),
        QColor(25,218,185),
        QColor(10,82,45),
        QColor(25,133,63),
        QColor(18,143,143),
        QColor(25,20,147),
        QColor(28,112,214),
        QColor(21,160,221),
        QColor(18,0,211),
        QColor(13,104,238),
        QColor(7,0,130),
        QColor(3,144,255),
        QColor(0,206,209),
        QColor(0,128,128),
        QColor(128, 0, 0),
        QColor(220, 20, 60),
        QColor(255, 99, 71),
        QColor(240, 128, 128),
        QColor(255, 140, 0),
        QColor(189, 183, 107),
        QColor(107, 142, 35),
        QColor(173, 255, 47),
        QColor(34, 139, 34),
        QColor(0, 250, 154),
        QColor(0, 255, 255),
        QColor(0, 206, 209),
        QColor(95, 158, 160),
        QColor(100, 149, 237),
        QColor(135, 206, 250),
        QColor(0, 0, 139),
        QColor(65, 105, 225),
        QColor(72, 61, 139),
        QColor(255, 105, 180),
        QColor(139, 69, 19),
        QColor(210, 180, 140),
        QColor(112, 128, 144),
        QColor(255, 218, 185),
        QColor(160, 82, 45),
        QColor(205, 133, 63),
        QColor(188, 143, 143),
        QColor(255, 20, 147),
        QColor(218, 112, 214),
        QColor(221, 160, 221),
        QColor(148, 0, 211),
        QColor(123, 104, 238),
        QColor(75, 0, 130),
        QColor(30, 144, 255),
        QColor(0, 206, 209),
        QColor(0, 128, 128),
        QColor(128, 0, 0),
        QColor(20, 20, 60),
        QColor(25, 99, 71),
        QColor(20, 128, 128),
        QColor(25, 140, 0),
        QColor(19, 183, 107),
        QColor(17, 142, 35),
        QColor(13, 255, 47),
        QColor(3, 139, 34),
        QColor(0, 250, 154),
        QColor(0, 255, 255),
        QColor(0, 206, 209),
        QColor(9, 158, 160),
        QColor(10, 149, 237),
        QColor(15, 206, 250),
        QColor(0, 0, 139),
        QColor(6, 105, 225),
        QColor(7, 61, 139),
        QColor(25, 105, 180),
        QColor(19, 69, 19),
        QColor(20, 180, 140),
        QColor(12, 128, 144),
        QColor(25, 218, 185),
        QColor(10, 82, 45),
        QColor(25, 133, 63),
        QColor(18, 143, 143),
        QColor(25, 20, 147),
        QColor(28, 112, 214),
        QColor(21, 160, 221),
        QColor(18, 0, 211),
        QColor(13, 104, 238),
        QColor(7, 0, 130),
        QColor(3, 144, 255),
        QColor(0, 206, 209),
        QColor(0, 128, 128),
        QColor(128, 0, 0),
        QColor(220, 20, 60),
        QColor(255, 99, 71),
        QColor(240, 128, 128),
        QColor(255, 140, 0),
        QColor(189, 183, 107),
        QColor(107, 142, 35),
        QColor(173, 255, 47),
        QColor(34, 139, 34),
        QColor(0, 250, 154),
        QColor(0, 255, 255),
        QColor(0, 206, 209),
        QColor(95, 158, 160),
        QColor(100, 149, 237),
        QColor(135, 206, 250),
        QColor(0, 0, 139),
        QColor(65, 105, 225),
        QColor(72, 61, 139),
        QColor(255, 105, 180),
        QColor(139, 69, 19),
        QColor(210, 180, 140),
        QColor(112, 128, 144),
        QColor(255, 218, 185),
        QColor(160, 82, 45),
        QColor(205, 133, 63),
        QColor(188, 143, 143),
        QColor(255, 20, 147),
        QColor(218, 112, 214),
        QColor(221, 160, 221),
        QColor(148, 0, 211),
        QColor(123, 104, 238),
        QColor(75, 0, 130),
        QColor(30, 144, 255),
        QColor(0, 206, 209),
        QColor(0, 128, 128),
        QColor(128, 0, 0),
        QColor(20, 20, 60),
        QColor(25, 99, 71),
        QColor(20, 128, 128),
        QColor(25, 140, 0),
        QColor(19, 183, 107),
        QColor(17, 142, 35),
        QColor(13, 255, 47),
        QColor(3, 139, 34),
        QColor(0, 250, 154),
        QColor(0, 255, 255),
        QColor(0, 206, 209),
        QColor(9, 158, 160),
        QColor(10, 149, 237),
        QColor(15, 206, 250),
        QColor(0, 0, 139),
        QColor(6, 105, 225),
        QColor(7, 61, 139),
        QColor(25, 105, 180),
        QColor(19, 69, 19),
        QColor(20, 180, 140),
        QColor(12, 128, 144),
        QColor(25, 218, 185),
        QColor(10, 82, 45),
        QColor(25, 133, 63),
        QColor(18, 143, 143),
        QColor(25, 20, 147),
        QColor(28, 112, 214),
        QColor(21, 160, 221),
        QColor(18, 0, 211),
        QColor(13, 104, 238),
        QColor(7, 0, 130),
        QColor(3, 144, 255),
        QColor(0, 206, 209),
        QColor(0, 128, 128),
    };

	/// OD分区字符串
	inline static const QVector<QString> ZoneStr = {
        "A",
        "B",
        "C",
        "D",
        "E",
        "U",
        "V",
        "X",
        "Y",
        "Z",
        "F",
        "R" 
    };

    /// 光标变化距离
    inline static const size_t ChangeCursorStyleDistance = 10;

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
    Globals() {}

    static const int mVersionNo;        ///< 版本号 
    static const char* mVersion;        ///< 版本
    static const QDate mReleaseDate;    ///< 发布日期
    static const char* mAuthor;         ///< 作者
    static const char* mName;           ///< 名称
};

