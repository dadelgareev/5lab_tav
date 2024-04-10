#ifndef TASKWINDOW3_H
#define TASKWINDOW3_H

#include <QDialog>

namespace Ui {
class taskwindow3;
}

class taskwindow3 : public QDialog
{
    Q_OBJECT

public:
    explicit taskwindow3(QWidget *parent = nullptr, const QString &sdnf = "");
    ~taskwindow3();

    QString getSDNF(){
        return sdnf;
    }

    void setSDNF(QString sdnf){
        this->sdnf = sdnf;
    }

    QString sdnf;





private:
    Ui::taskwindow3 *ui;
};

#endif // TASKWINDOW3_H
