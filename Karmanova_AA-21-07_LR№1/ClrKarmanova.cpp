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
        cout << "���� ��� " << endl;
    }
    else {
        cout << " �� (id=  " << IdInput << ") ��������� � ��(id= " << IdExit << ") � ������� ����� (id= " << pId << ")" << endl;
    }
    
}
int truba::maxPid = 1;

truba::truba()
{
    pId = maxPid++;
}

std::istream& operator>>(std::istream& in, truba& p)
{
    cout << "������� �������� �����:" << endl;
    in.ignore(1000, '\n');
    in.clear();
    getline(in, p.Pname);
    cout << "�������� �����:" << p.Pname << endl;
    p.condition = 1;
    if (p.condition == 1) {
        cout << "����� � ������� ��������� " << endl;
    }
    else {
        cout << "����� � ��������� �������" << endl;
    }
    //������� �����
    cout << "������� ������� �����:" << endl;

    p.diameter = GetCorrectNumber(1, 10000000);
    //����� �����
    cout << "������� ����� �����:" << endl;

    p.length = GetCorrectNumber(1, 10000000);
    p.IdInput = 0;
    p.IdExit = 0;
    return in;
}

std::ostream& operator<<(std::ostream& out, const truba& p)
{
    
    if (p.condition == 1) {
        out << "����� � ������� ��������� " << endl;
    }
    else {
        out << "����� � ��������� �������" << endl;
    }
    out << "�������� �����: " << " " << p.Pname << endl;
    out << "������� �����:" << " " << p.diameter << " " << "������" << endl;
    out << "����� �����" << " " << p.length << " " << "������" << endl << endl;
    return out;
}