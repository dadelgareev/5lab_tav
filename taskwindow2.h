#ifndef TASKWINDOW2_H
#define TASKWINDOW2_H

#include <QDialog>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Ui {
class taskwindow2;
}

class taskwindow2 : public QDialog
{
    Q_OBJECT

public:
    explicit taskwindow2(QWidget *parent = nullptr, const string &sdnf = "");
    ~taskwindow2();

    vector<string> split(const string &s, char delimiter) {
        vector<string> tokens;
        string token;
        size_t start = 0, end = 0;
        while ((end = s.find(delimiter, start)) != string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(s.substr(start));
        return tokens;
    }


private slots:
    void on_pushButton_clicked();

private:
    string sdnf;
    Ui::taskwindow2 *ui;

};

#endif // TASKWINDOW2_H
