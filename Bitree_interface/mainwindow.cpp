#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <algorithm>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->keyLine->setValidator(
    new QRegularExpressionValidator( QRegularExpression("[0-9]{4,4}/[0-9]{2,2}/[0-9]{2,2}"), this ));
    ui->sequenceEraseLine->setValidator(
    new QRegularExpressionValidator( QRegularExpression("[0-9]{4,4}/[0-9]{2,2}/[0-9]{2,2}"), this ));
    ui->valueLine->setValidator(
    new QRegularExpressionValidator( QRegularExpression("[a-zA-z_]{0,256}"), this ));

    updateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTable()
{
    ui->tableWidget->setRowCount(0); // remove all data
    ui->tableWidget->setRowCount(tree_size.size());

    int curRow=0;

    for(const auto &i : tree_size.keys())
    {
        QString k = QString::fromStdString(i),
                v = QString::fromStdString(tree_size[i]);

        for(int i = 0; i < 2; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(
                    (curRow+1)*(1)));

            switch(i)
            {
            case 0:
                item->setText(k);
                break;

            case 1:
                item->setText(v);
                break;
            }

            ui->tableWidget->setItem(curRow, i, item);
        }
        curRow++;
    }

    ui->clearButton->setEnabled(bool(tree_size.size()));
    ui->eraseButton->setEnabled(bool(tree_size.size()));
    ui->writeButton->setEnabled(bool(tree_size.size()));
    ui->retranslateUi(this);
}

void MainWindow::first_test()
{
    // Insertion test
    ui->keyLine->setText("2021/11/26");
    ui->valueLine->setText("Vanya");
    on_insertButton_clicked();
    assert(tree_size.size()==1);
}

void MainWindow::second_test()
{
    // Deletion test
    ui->sequenceEraseLine->setText("2021/11/26");
    on_eraseButton_clicked();
    assert(tree_size.size()==0);
}

void MainWindow::third_test()
{
    QString name = "D:/Documents/TestLaba2.txt";
    tree_size["2021/11/27"] = "Sasha";
    tree_size["2021/11/26"] = "Vanya";
    tree_size["2021/10/25"] = "Tanya";

    ui->readLine->setText(name);
    ui->writeLine->setText(name);

    on_writeButton_clicked();
    on_clearButton_clicked();
    on_readButton_clicked();

    assert(tree_size.size()==3);
}

void MainWindow::fourth_test()
{
    // List events test
    on_listEventsButton_clicked();
    assert(ui->sequenceOutputLine->text()=="Tanya, Vanya, Sasha");
}


void MainWindow::on_insertButton_clicked()
{
    QString key = ui->keyLine->text();
    QString val = ui->valueLine->text();

    if(!(val.size() && key.size()))
    {
        QMessageBox box;
        box.setText("Key and value can't be empty");
        box.exec();
        return;
    }

    QRegularExpression re("^(\\d\\d\\d\\d)/(\\d\\d)/(\\d\\d)$");
    QRegularExpressionMatch match = re.match(key);
    if (match.hasMatch())
    {
        tree_size.paste(key.toStdString(), val.toStdString());
        updateTable();
    }
    else
    {
        QMessageBox box;
        box.setText("Invalid date");
        box.exec();
        return;
    }

    if(!(val.size() && key.size()))
    {
        QMessageBox box;
        box.setText("Key and value can't be empty");
        box.exec();
        return;
    }

}

void MainWindow::on_eraseButton_clicked()
{
    QString key = ui->sequenceEraseLine->text();
    QRegularExpression re("^(\\d\\d\\d\\d)/(\\d\\d)/(\\d\\d)$");
    QRegularExpressionMatch match = re.match(key);
    if (match.hasMatch())
    {
        if(!tree_size.contains(key.toStdString()))
        {
            QMessageBox box;
            box.setText("Key not found, nothing has been deleted");
            box.exec();
            return;
        }
        tree_size.remove(key.toStdString());
        updateTable();

    }
    else
    {
        QMessageBox box;
        box.setText("Invalid date");
        box.exec();
        return;
    }

}


void MainWindow::on_readButton_clicked()
{
    QString name = ui->readLine->text();
    tree_size.read(name.toStdString());
    updateTable();
}


void MainWindow::on_writeButton_clicked()
{
    QString name = ui->writeLine->text();
    tree_size.write(name.toStdString());
}


void MainWindow::on_clearButton_clicked()
{
    tree_size.clearAll();
    updateTable();
}


void MainWindow::on_listEventsButton_clicked()
{
   std::list<std::string> valList =
   tree_size.values();
   if(!valList.size())
   {
       QMessageBox box;
       box.setText("The tree is empty");
       box.exec();
       return;
   }
   QString ans;
   for(auto &word : valList)
   {
       for(const auto &c : word)
           ans.push_back(c);
       ans.push_back(", ");
    }
   ans.chop(2); // same as pop_back for std::string
   ui->sequenceOutputLine->setText(ans);
}
