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
bool truba::IsAvailable()
{
    return IdInput==0 && IdExit==0;
}
void truba::Connect(int in, int out)
{
    this->IdInput = in;
    this->IdExit = out;

}
void truba::PrintConnection()
{
    if ((IdInput == 0) || (IdExit == 0)) {
        return;
    }
    else {
        cout << " КС (id=  " << IdInput << ") соединена с КС(id= " << IdExit << ") с помощью трубы (id= " << pId << ")" << endl;
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
    in.ignore(1000, '\n');
    in.clear();
    getline(in, p.Pname);
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
    p.IdInput = 0;
    p.IdExit = 0;
    return in;
}

std::ostream& operator<<(std::ostream& out, const truba& p)
{
    
    if (p.condition == 1) {
        out << "Труба в хорошем состоянии " << endl;
    }
    else {
        out << "Труба в состоянии ремонта" << endl;
    }
    out << "Название трубы: " << " " << p.Pname << endl;
    out << "Диаметр трубы:" << " " << p.diameter << " " << "метров" << endl;
    out << "Длина трубы" << " " << p.length << " " << "метров" << endl << endl;
    return out;
}