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

    cout << "������� �������� �����:" << endl;
    cin.ignore(1000, '\n');
    cin.clear();
    getline(cin, p.Pname);
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
    return in;
}
std::ostream& operator<<(std::ostream& out, truba& p)
{
    cout <<"Id: "<< p.pId << endl;
    if (p.condition == 1) {
        cout << "����� � ������� ��������� " << endl;
    }
    else {
        cout << "����� � ��������� �������" << endl;
    }
    cout << "�������� �����: " << " " << p.Pname << endl;
    cout << "������� �����:" << " " << p.diameter << " " << "������" << endl;
    cout << "����� �����" << " " << p.length << " " << "������" << endl << endl;
    return out;
}