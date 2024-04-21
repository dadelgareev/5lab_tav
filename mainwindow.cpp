#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sdnf_function.h"
#include <QString> // Добавляем заголовочный файл <QString> для использования QString
#include "taskwindow2.h"
#include "taskwindow3.h"
#include "taskwindow4.h"

string sdnf;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int index_comboBox_1 = ui->comboBox->currentIndex();
    int index_comboBox_2 = ui->comboBox_2->currentIndex();
    int index_comboBox_3 = ui->comboBox_3->currentIndex();
    // Создаем экземпляр класса и получаем СДНФ

    SDNFCalculator calculator(index_comboBox_1, index_comboBox_2, index_comboBox_3);
    sdnf = calculator.getSDNF();
    qsdnf = QString::fromStdString(sdnf);
    // Устанавливаем текст с использованием HTML-разметки для создания переноса строк
    ui->label_5->setText(qsdnf);



}


void MainWindow::on_pushButton_2_clicked()
{
    taskwindow2 task_window(nullptr,sdnf);
    task_window.setModal(true);
    task_window.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    taskwindow3 task_window(nullptr,qsdnf);
    task_window.setModal(true);
    task_window.exec();
}


void MainWindow::on_pushButton_4_clicked()
{
    taskwindow4 task_window(nullptr,sdnf);
    task_window.setModal(true);
    task_window.exec();
}

