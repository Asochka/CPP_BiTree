#include "mainwindow.h"
#include "bitree.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.first_test();
    w.second_test();
    w.third_test();
    w.fourth_test();

    std::cout << "ALL tests passed!" << std::endl;
    return a.exec();
}
