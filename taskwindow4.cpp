#include "taskwindow4.h"
#include "ui_taskwindow4.h"

taskwindow4::taskwindow4(QWidget *parent, const string &sdnf)
    : QDialog(parent)
    , sdnf(sdnf)
    , ui(new Ui::taskwindow4)
{
    ui->setupUi(this);

    vector<string> splitSDNF = splitString(sdnf,  " + ");
    vector<string> bitSDNF = convertToBitDNF(splitSDNF);
    vector<string> minSDNF = findMinimalDNF(bitSDNF, 4);
    vector<string> formatedSDNF = convertToReadableDNF(minSDNF);
    string FinalSDNF;

    for (const auto& term : formatedSDNF) {
        FinalSDNF += term;
        FinalSDNF += " + ";
    }
    QString qsdnf = QString::fromStdString(FinalSDNF);
    ui->label->setText(qsdnf);
}

taskwindow4::~taskwindow4()
{
    delete ui;
}
