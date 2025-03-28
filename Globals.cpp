
#include "Globals.h"

#include <QDate>
#include <QIcon>
#include <QMessageBox>
#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>
#include <QtDebug>

const int Globals::mVersionNo = 20250326;
const char* Globals::mVersion = "0.0.1";
const QDate Globals::mReleaseDate = QDate::fromString(QString("03-26-2025"), "dd-MM-yyyy");
const char* Globals::mAuthor = "shaozk";
const char* Globals::mName = "mdfplot";

int Globals::version() 
{ 
    return mVersionNo; 
}

QString Globals::name()
{
    return mName;
}

QString Globals::versionString() 
{ 
    return mVersion; 
}

QString Globals::releaseDateString() 
{
    return mReleaseDate.toString("dd-MM-yyyy");
}

QDate Globals::releaseDate() 
{ 
    return mReleaseDate;
}

QString Globals::author() 
{
    return mAuthor;
}

QString Globals::enumValueToString(int key, const QString& enumName) 
{
    int index = staticMetaObject.indexOfEnumerator(enumName.toUtf8());
    if (index == -1)
    {
        return QString("invalid");
    }
    QMetaEnum meta_enum = staticMetaObject.enumerator(index);
    return QString(meta_enum.valueToKey(key));
}

int Globals::enumStringToValue(const QString& string,
                                 const QString& enumName) 
{
    int index = staticMetaObject.indexOfEnumerator(enumName.toUtf8());
    if (index == -1) return -1;
    QMetaEnum meta_enum = staticMetaObject.enumerator(index);
    return meta_enum.keyToValue(string.toUtf8());
}
