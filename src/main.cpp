#include <QApplication>
#include <QFile>

#include "mainwindow.h"
#include "model.h"
#include "controller.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Model model;

    Controller controller{model, w};

    if(QFile::exists("save.json")){
        controller.load("save.json");
    }

    w.show();

    return a.exec();
}
