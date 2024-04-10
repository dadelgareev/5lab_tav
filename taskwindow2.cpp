#include "taskwindow2.h"
#include "ui_taskwindow2.h"

taskwindow2::taskwindow2(QWidget *parent, const string &sdnf)
    : QDialog(parent)
    , sdnf(sdnf)
    , ui(new Ui::taskwindow2)
{
    ui->setupUi(this);
}

taskwindow2::~taskwindow2()
{
    delete ui;
}

void taskwindow2::on_pushButton_clicked()
{
    ui->tableWidget->setWindowTitle("Значения переменных");

    vector<string> conjuncts = split(sdnf, '+');
    int rowCount = conjuncts.size(); // количество строк = количество конъюнктов
    int colCount = 5; // количество столбцов (один для каждой переменной и один для конъюнкта)

    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(colCount);

    // Проходим через каждый конъюнкт
    for (size_t i = 0; i < conjuncts.size(); ++i) {
        const string &conjunct = conjuncts[i];

        bool isNegative = false; // Флаг для отслеживания отрицания

        // Переменные для хранения значений переменных A, B, C и D
        int A = 1, B = 1, C = 1, D = 1;

        // Проверяем, есть ли отрицание для каждой переменной в конъюнкте
        for (size_t j = 0; j < conjunct.size(); ++j) {
            char ch = conjunct[j];
            if (ch == '!') {
                isNegative = true;
                continue; // Пропускаем отрицание и двигаемся к следующему символу
            }
            // Если флаг отрицания установлен, устанавливаем значение переменной в 0
            if (isNegative) {
                switch (ch) {
                case 'A':
                    A = 0;
                    break;
                case 'B':
                    B = 0;
                    break;
                case 'C':
                    C = 0;
                    break;
                case 'D':
                    D = 0;
                    break;
                }
                isNegative = false; // Сбрасываем флаг отрицания после обработки переменной
            }
            // Если флаг отрицания не установлен, устанавливаем значение переменной в 1
            else {
                switch (ch) {
                case 'A':
                    A = 1;
                    break;
                case 'B':
                    B = 1;
                    break;
                case 'C':
                    C = 1;
                    break;
                case 'D':
                    D = 1;
                    break;
                }
            }
        }

        // Создаем элементы QTableWidgetItem для каждой переменной и конъюнкта
        QTableWidgetItem *itemA = new QTableWidgetItem(QString::number(A));
        QTableWidgetItem *itemB = new QTableWidgetItem(QString::number(B));
        QTableWidgetItem *itemC = new QTableWidgetItem(QString::number(C));
        QTableWidgetItem *itemD = new QTableWidgetItem(QString::number(D));
        QTableWidgetItem *itemConjunct = new QTableWidgetItem(QString::fromStdString(conjunct));

        // Устанавливаем элементы в таблицу
        ui->tableWidget->setItem(i, 0, itemA);
        ui->tableWidget->setItem(i, 1, itemB);
        ui->tableWidget->setItem(i, 2, itemC);
        ui->tableWidget->setItem(i, 3, itemD);
        ui->tableWidget->setItem(i, 4, itemConjunct);

        // Устанавливаем растягивание столбцов
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}


