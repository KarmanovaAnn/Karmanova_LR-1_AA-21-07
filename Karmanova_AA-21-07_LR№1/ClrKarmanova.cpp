#include "ClrKarmanova.h"
#include "Check.h"
#include <iostream>
using namespace std;

void truba::Edit()
{
    if (condition == 1) {
        condition = 0;
    }
    else {
        condition = 1;
    }
}
int truba::maxPid = 1;
truba::truba()
{
    pId = maxPid++;
}

std::istream& operator>>(std::istream& in, truba& p)
{

    cout << "Введите название трубы:" << endl;
    cin.ignore(1000, '\n');
    cin.clear();
    getline(cin, p.Pname);
    cout << "Название трбуы:" << p.Pname << endl;
    p.condition = 1;
    if (p.condition == 1) {
        cout << "Труба в хорошем состоянии " << endl;
    }
    else {
        cout << "Труба в состоянии ремонта" << endl;
    }
    //диаметр трубы
    cout << "Введите диаметр трубы:" << endl;

    p.diameter = GetCorrectNumber(1, 10000000);
    //длина трубы
    cout << "Введите длину трубы:" << endl;

    p.length = GetCorrectNumber(1, 10000000);
    return in;
}
std::ostream& operator<<(std::ostream& out, truba& p)
{
    cout <<"Id: "<< p.pId << endl;
    if (p.condition == 1) {
        cout << "Труба в хорошем состоянии " << endl;
    }
    else {
        cout << "Труба в состоянии ремонта" << endl;
    }
    cout << "Название трубы: " << " " << p.Pname << endl;
    cout << "Диаметр трубы:" << " " << p.diameter << " " << "метров" << endl;
    cout << "Длина трубы" << " " << p.length << " " << "метров" << endl << endl;
    return out;
}