#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bitree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateTable();

    void first_test();
    void second_test();
    void third_test();
    void fourth_test();

private slots:
    void on_insertButton_clicked();

    void on_eraseButton_clicked();

    void on_readButton_clicked();

    void on_writeButton_clicked();

    void on_clearButton_clicked();

    void on_listEventsButton_clicked();

private:
    Ui::MainWindow *ui;
    BiTree<std::string, std::string> tree_size;
};
#endif // MAINWINDOW_H
