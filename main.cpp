#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>
#include <string>


#include <mdf/mdfreader.h>

void testMdf()
{
    mdf::MdfReader reader("");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.resize(1800, 1500);
    return a.exec();
}
