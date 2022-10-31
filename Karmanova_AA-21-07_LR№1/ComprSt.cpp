#include "ComprSt.h"
#include "Check.h"
#include <iostream>
using namespace std;

void  compress_station::Edit() {
    cout << "�� ������ ������ ���������� ������� �����:" << " " << amount_Wshop << endl << "�� ������ �������� ���������� ������� �����? ������� 1, ���� ������ ��������� ���-��, ������� 0, ���� ������ ���������" << endl;
    int answer;
    cin >> answer;
    while (true) {
        if (answer == 1) {
            amount_Wshop = amount_Wshop + 1;
            if (amount_Wshop > amount_shop) {
                cout << "������: ���������� ������� ����� �� ����� ��������� ���������� �����" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "�� ������ �������� ������� ���������� ������� �����?" << endl << "������� 1, ���� ������ �������� ������� ��� - ��, ������� 0, ���� ������ ���������" << endl;
                cin >> answer;
                if (answer == 1) {
                    amount_Wshop = amount_Wshop - 1;
                    cout << "���������� ������� �����:" << " " << amount_Wshop << endl;
                    break;
                }
                else {
                    amount_Wshop = amount_Wshop - 2;
                    cout << "���������� ������� �����:" << " " << amount_Wshop << endl;
                    break;
                }
            }
            else {
                cout << "���������� ������� �����:" << " " << amount_Wshop << endl;
                break;
            }
        }
        else if (answer == 0) {
            amount_Wshop = amount_Wshop - 1;
            if (amount_Wshop < 0) {
                cout << "���������� ������� ����� �� ����� ���� ������������� ������" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "�� ������ �������� ������� ���������� ������� �����?" << endl << "������� 1, ���� ������ ��������� ��� - ��, ������� 0, ���� �������� �������" << endl;
                cin >> answer;
                if (answer == 1) {
                    amount_Wshop = amount_Wshop + 2;
                    cout << "���������� ������� �����:" << " " << amount_Wshop << endl;
                    break;
                }
                else {
                    amount_Wshop = amount_Wshop + 1;
                    cout << "���������� ������� �����:" << " " << amount_Wshop << endl;
                    break;
                }
            }
            else {
                cout << "���������� ������� �����:" << " " << amount_Wshop << endl;
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
    //��� �������
    cout << "������� �������� ������������� �������:" << endl;
    cin.ignore(1000, '\n');
    cin.clear();
    getline(cin, cs.Pname);
    cout << "�������� ������������� �������:" << cs.Pname << endl;
    //���������� �����
    cout << "������� ���������� �����:" << endl;
    cs.amount_shop = GetCorrectNumber(1, 10000000);
    //���-�� ������� �����
    while (true) {
        cout << "������� ���������� ������� ����� ������������� ������� :" << endl;
        cin >> cs.amount_Wshop;
        if (cin.good() == true) {
            if (cs.amount_Wshop < 0) {
                cout << "������ �����!" << endl;
                cin.clear(); cin.ignore(1000, '\n');
            }
            else if (cs.amount_Wshop > cs.amount_shop) {
                cout << "������ �����!" << endl;
                cin.clear(); cin.ignore(1000, '\n');
            }
            else if (int(cs.amount_Wshop) != cs.amount_Wshop) {
                cout << "������ �����!" << endl;
                cin.clear(); cin.ignore(1000, '\n');
            }
            else {
                cout << "���������� ������� �����:" << " " << cs.amount_Wshop << endl;
                break;
            }
        }
        else {
            cout << "������ �����!" << endl;
            cin.clear(); cin.ignore(1000, '\n');
        }
    }
    //������ ������ ����
    cs.indicator = (cs.amount_Wshop / cs.amount_shop) * 100;
    cout << "���������� �������������: " << " " << cs.indicator << "%" << endl;
    //������� ����������������� �����
    cs.k = 100 - cs.indicator;
    cout << "������� ����������������� �����: " << " " << cs.k << "%" << endl;
    return in;
}

std::ostream& operator<<(std::ostream& out, compress_station& cs)
{
    cout << "Id: " << cs.csId << endl;
    cout << "�������� ������������� �������: " << " " << cs.Pname << endl;
    cout << "���������� �����: " << " " << cs.amount_shop << endl;
    cout << "���������� ������� �����: " << " " << cs.amount_Wshop << endl;
    cout << "���������� ������������� ������� �����: " << " " << cs.indicator << "%" << endl;
    cout << "������� ����������������� �����: " << " " << cs.k << "%" << endl << endl;

    return out;
}