#ifndef SDNF_FUNCTION_H
#define SDNF_FUNCTION_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>

class SDNFCalculator {
public:
    SDNFCalculator(const int operation1, const int operation2, const int operation3)
        : operation1_(operation1), operation2_(operation2), operation3_(operation3) {}

    std::string getSDNF() const {
        std::vector<std::string> sdnf_terms;

        // Перебираем все возможные значения переменных A, B, C, D
        for (bool A : {false, true}) {
            for (bool B : {false, true}) {
                for (bool C : {false, true}) {
                    for (bool D : {false, true}) {
                        // Если выражение равно true, добавляем набор в СДНФ
                        if (evaluateExpression(A, B, C, D)) {
                            std::string term = "";
                            term += (A ? "A" : "!A");
                            term += (B ? "B" : "!B");
                            term += (C ? "C" : "!C");
                            term += (D ? "D" : "!D");
                            sdnf_terms.push_back(term);
                        }
                    }
                }
            }
        }

        // Объединяем полученные наборы в СДНФ
        std::string sdnf;
        for (size_t i = 0; i < sdnf_terms.size(); ++i) {
            if (i != 0)
                sdnf += " + ";
            sdnf += sdnf_terms[i];
        }
        return sdnf;
    }

private:
    int operation1_;
    int operation2_;
    int operation3_;

    // Функция для вычисления значения выражения с указанной операцией
    bool evaluateExpression(bool A, bool B, bool C, bool D) const {
        std::function<bool(bool, bool)> op1 = getBooleanOperator(operation1_);
        std::function<bool(bool, bool)> op2 = getBooleanOperator(operation2_);
        std::function<bool(bool, bool)> op3 = getBooleanOperator(operation3_);

        // Первая операция между A и B
        bool intermediate_result = op1(A, B);
        // Вторая операция между B и C
        bool intermediate_result_2 = op3(C, D);
        // Третья операция
        return op2(intermediate_result, intermediate_result_2);
    }

    // Функция для получения булевского оператора на основе строки операции
    std::function<bool(bool, bool)> getBooleanOperator(const int operation) const {
        if (operation == 0) {
            return [](bool a, bool b) { return a && b; };
        } else if (operation == 1) {
            return [](bool a, bool b) { return a || b; };
        } else if (operation == 2) {
            return [](bool a, bool b) { return (a || b) && !(a && b); };
        } else if (operation == 3) {
            return [](bool a, bool b) { return !a || b; };
        } else if (operation == 4) {
            return [](bool a, bool b) { return (!a || b) && (!b || a); };
        } else if (operation == 5) {
            return [](bool a, bool b) { return !(a && b); };
        } else if (operation == 6) {
            return [](bool a, bool b) { return !a || !b; };
        } else {
            throw std::invalid_argument("Неподдерживаемая операция");
        }

    }
};




#endif // SDNF_FUNCTION_H
