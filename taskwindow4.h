#ifndef TASKWINDOW4_H
#define TASKWINDOW4_H

#include <QDialog>
#include <vector> // Включаем заголовочный файл для std::vector
#include <string> // Включаем заголовочный файл для std::string
#include <iostream>
#include <algorithm>
#include <QString>

using namespace std;

namespace Ui {
class taskwindow4;
}

class taskwindow4 : public QDialog
{
    Q_OBJECT

public:
    explicit taskwindow4(QWidget *parent = nullptr, const string &sdnf = "");
    ~taskwindow4();
    // Структура для представления импликанты
    struct Implicant {
        string binary; // Бинарное представление
        bool covered;  // Флаг, указывающий, была ли импликанта покрыта
    };

    // Функция для проверки, различаются ли два бинарных представления на один бит
    bool differByOneBit(const string& a, const string& b) {
        int diffCount = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                ++diffCount;
                if (diffCount > 1) return false;
            }
        }
        return diffCount == 1;
    }

    // Функция для объединения двух импликант с разницей в одном бите
    Implicant mergeImplicants(const Implicant& a, const Implicant& b) {
        Implicant merged = a;
        for (size_t i = 0; i < a.binary.size(); ++i) {
            if (a.binary[i] != b.binary[i]) {
                merged.binary[i] = '-';
            }
        }
        return merged;
    }

    // Функция для поиска минимальной ДНФ
    vector<string> findMinimalDNF(const vector<string>& minterms, int numVars) {
        vector<Implicant> implicants;
        // Создаем импликанты из множества minterms
        for (const auto& minterm : minterms) {
            implicants.push_back({ minterm, false });
        }
        vector<string> minimalDNF;
        while (!implicants.empty()) {
            // Группируем импликанты по количеству единиц в бинарном представлении
            vector<vector<Implicant>> groups(numVars + 1);
            for (const auto& implicant : implicants) {
                int oneCount = std::count(implicant.binary.begin(), implicant.binary.end(), '1');
                groups[oneCount].push_back(implicant);
            }

            // Сокращаем группы
            for (int i = 0; i < numVars; ++i) {
                for (size_t j = 0; j < groups[i].size(); ++j) {
                    for (size_t k = 0; k < groups[i + 1].size(); ++k) {
                        if (differByOneBit(groups[i][j].binary, groups[i + 1][k].binary)) {
                            Implicant merged = mergeImplicants(groups[i][j], groups[i + 1][k]);
                            groups[i][j].covered = true;
                            groups[i + 1][k].covered = true;
                            minimalDNF.push_back(merged.binary);
                        }
                    }
                }
            }
            // Удаляем покрытые импликанты
            implicants.clear();
            for (auto& group : groups) {
                for (auto& implicant : group) {
                    if (!implicant.covered) {
                        implicants.push_back(implicant);
                    }
                }
            }
        }
        return minimalDNF;
    }
    // Функция для преобразования бинарной строки в удобочитаемый формат
    string convertToReadableTerm(const string& term) {
        string readableTerm;
        char var = 'A';
        for (char c : term) {
            if (c == '1') {
                readableTerm += var;
            }
            else if (c == '0') {
                readableTerm += '!';
                readableTerm += var;
            }
            else if (var != '-') {
                var++;
                continue;
            }
            var++;
        }
        return readableTerm;
    }

    // Функция для преобразования строки минимальной ДНФ в удобочитаемый формат
    vector<string> convertToReadableDNF(const vector<string>& minimalDNF) {
        vector<string> readableDNF;
        for (const auto& term : minimalDNF) {
            readableDNF.push_back(convertToReadableTerm(term));
        }
        return readableDNF;
    }
    string convertToBitTerm(const string& term) {
        string readableTerm;
        //char var = 'A';
        for (int i = 0; i < term.size(); i++) {
            if (term[i] == '!') {
                readableTerm += '0';
                i++;
            }
            else {
                readableTerm += '1';
            }
        }
        return readableTerm;
    }
    vector<string> convertToBitDNF(const vector<string>& minimalDNF) {
        vector<string> readableDNF;
        for (const auto& term : minimalDNF) {
            readableDNF.push_back(convertToBitTerm(term));
        }
        return readableDNF;
    }
    std::vector<std::string> splitString(const std::string& expression, const std::string& delimiter) {
        std::vector<std::string> result;
        size_t pos = 0;
        size_t end;
        while ((end = expression.find(delimiter, pos)) != std::string::npos) {
            result.push_back(expression.substr(pos, end - pos));
            pos = end + delimiter.length();
        }
        result.push_back(expression.substr(pos));
        return result;
    }




private:
    string sdnf;
    Ui::taskwindow4 *ui;
};

#endif // TASKWINDOW4_H
