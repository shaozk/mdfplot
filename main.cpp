#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>
#include <string>

#include "mdf/mdfreader.h"


int main(int argc, char *argv[])
{
    std::cout << "hello mdfplot" << std::endl;
    std::string mdfpath = "";
    mdf::MdfReader reader(mdfpath);

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "mdfplot_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();

}
