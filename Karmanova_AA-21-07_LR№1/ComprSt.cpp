#include "ComprSt.h"
#include "Check.h"
#include <iostream>
using namespace std;

void  compress_station::Edit() {
    cout << "На данный момент количество рабочих цехов:" << " " << amount_Wshop << endl << "Вы хотите изменить количество рабочих цехов? Введите 1, если хотите увеличить кол-во, введите 0, если хотите уменьшить" << endl;
    int answer;
    cin >> answer;
    while (true) {
        if (answer == 1) {
            amount_Wshop = amount_Wshop + 1;
            if (amount_Wshop > amount_shop) {
                cout << "Ошибка: количество рабочих цехов не может превышать количество цехов" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Вы хотите оставить прежнее количество рабочих цехов?" << endl << "Введите 1, если хотите оставить прежнее кол - во, введите 0, если хотите уменьшить" << endl;
                cin >> answer;
                if (answer == 1) {
                    amount_Wshop = amount_Wshop - 1;
                    cout << "Количество рабочих цехов:" << " " << amount_Wshop << endl;
                    break;
                }
                else {
                    amount_Wshop = amount_Wshop - 2;
                    cout << "Количество рабочих цехов:" << " " << amount_Wshop << endl;
                    break;
                }
            }
            else {
                cout << "Количество рабочих цехов:" << " " << amount_Wshop << endl;
                break;
            }
        }
        else if (answer == 0) {
            amount_Wshop = amount_Wshop - 1;
            if (amount_Wshop < 0) {
                cout << "Количество рабочих цехов не может быть отрицательным числом" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Вы хотите оставить прежнее количество рабочих цехов?" << endl << "Введите 1, если хотите увеличить кол - во, введите 0, если оставить прежним" << endl;
                cin >> answer;
                if (answer == 1) {
                    amount_Wshop = amount_Wshop + 2;
                    cout << "Количество рабочих цехов:" << " " << amount_Wshop << endl;
                    break;
                }
                else {
                    amount_Wshop = amount_Wshop + 1;
                    cout << "Количество рабочих цехов:" << " " << amount_Wshop << endl;
                    break;
                }
            }
            else {
                cout << "Количество рабочих цехов:" << " " << amount_Wshop << endl;
                break;
            }

        }

    }
    indicator = (amount_Wshop / amount_shop) * 100;
    k = 100 - indicator;

    
}

int compress_station::maxCSid = 1;
compress_station::compress_station()
{
    csId = maxCSid++;
}

std::istream& operator>>(std::istream& in, compress_station& cs) {
    //имя станции
    cout << "Введите название компрессорной станции:" << endl;
    cin.ignore(1000, '\n');
    cin.clear();
    getline(cin, cs.Pname);
    cout << "Название компрессорной станции:" << cs.Pname << endl;
    //количество цехов
    cout << "Введите количество цехов:" << endl;
    cs.amount_shop = GetCorrectNumber(1, 10000000);
    //кол-во рабочих цехов
    while (true) {
        cout << "Введите количество рабочих цехов компрессорной станции :" << endl;
        cin >> cs.amount_Wshop;
        if (cin.good() == true) {
            if (cs.amount_Wshop < 0) {
                cout << "Ошибка ввода!" << endl;
                cin.clear(); cin.ignore(1000, '\n');
            }
            else if (cs.amount_Wshop > cs.amount_shop) {
                cout << "Ошибка ввода!" << endl;
                cin.clear(); cin.ignore(1000, '\n');
            }
            else if (int(cs.amount_Wshop) != cs.amount_Wshop) {
                cout << "Ошибка ввода!" << endl;
                cin.clear(); cin.ignore(1000, '\n');
            }
            else {
                cout << "Количество рабочих цехов:" << " " << cs.amount_Wshop << endl;
                break;
            }
        }
        else {
            cout << "Ошибка ввода!" << endl;
            cin.clear(); cin.ignore(1000, '\n');
        }
    }
    //оценка работы цеха
    cs.indicator = (cs.amount_Wshop / cs.amount_shop) * 100;
    cout << "Показатель эффективности: " << " " << cs.indicator << "%" << endl;
    //процент незайдествованных цехов
    cs.k = 100 - cs.indicator;
    cout << "Процент незадействованных цехов: " << " " << cs.k << "%" << endl;
    return in;
}

std::ostream& operator<<(std::ostream& out, compress_station& cs)
{
    cout << "Id: " << cs.csId << endl;
    cout << "Название компрессорной станции: " << " " << cs.Pname << endl;
    cout << "Количество цехов: " << " " << cs.amount_shop << endl;
    cout << "Количество рабочих цехов: " << " " << cs.amount_Wshop << endl;
    cout << "Показатель эффективности рабочих цехов: " << " " << cs.indicator << "%" << endl;
    cout << "Процент незадействованных цехов: " << " " << cs.k << "%" << endl << endl;

    return out;
}