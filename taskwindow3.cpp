#include "taskwindow3.h"
#include "ui_taskwindow3.h"
#include <QStringList>

taskwindow3::taskwindow3(QWidget *parent, const QString &sdnf)
    : QDialog(parent)
    , sdnf(sdnf)
    , ui(new Ui::taskwindow3)

{
    ui->setupUi(this);
    // Разделяем строку с использованием пробелов и плюсов

    //ui->label->setText(sdnf);

    QStringList terms = sdnf.split(QRegExp("[ +]+"), QString::SkipEmptyParts);
    for (const QString &term : terms) {
        ui->comboBox->addItem(term);
    }
}

taskwindow3::~taskwindow3()
{
    delete ui;
}
