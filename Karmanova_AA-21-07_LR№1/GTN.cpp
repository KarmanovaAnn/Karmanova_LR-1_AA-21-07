#include "GTN.h"
#include "Check.h"
#include <iostream>
#include <string>


using namespace std;


void GTN::Add_pipe() {
    truba p;
    cin >> p;
    pipes.emplace(p.pId, p);
}

void GTN::Connect()
{
    int in;
    do
    {
        cout << "������� ID �� �����: " << endl;
        in= GetCorrectNumber(1, 1000000);
    } while (!IsCsAvailable(in));
    int out;
    do
    {
        cout << "������� ID �� ������: " << endl;
        out = GetCorrectNumber(1, 1000000);
    } while (!IsCsAvailable(out) || in == out);
    //������
    cout << "������� �������: " << endl;
    int answer = GetCorrectNumber(1, 1000000);
    set<int> selected = FilterObjects(pipes, Diameter, answer);
    int count = 0;
    for (int id : selected)
    {
        if (IsPipeAvailable(id))
        {
            pipes[id].Connect(in, out);
            pipes[id].PrintConnection();
            count++;
            return;
        }
    }
    if (count == 0) {
        cout << "����� � ����� ��������� �� ����������. ������� 1, ���� ������ ������� �����, 0, ���� ������ ����� " << endl;
        int a;
        Tryanswer(a);
        if (a == 1) {
            Add_pipe();
            cout << "����� ������� �������! " << endl;
        }
        cout << "������� �������: " << endl;
        int answer = GetCorrectNumber(1, 1000000);
        set<int> selected = FilterObjects(pipes, Diameter, answer);
        for (int id : selected)
        {
            if (IsPipeAvailable(id))
            {
                pipes[id].Connect(in, out);
                pipes[id].PrintConnection();
                return;
            }
        }
    }
}

bool GTN::IsCsAvailable(int id)
{
    if (!CS_s.contains(id)){
        cout << "�� � ����� ID �� ������� " << endl;
    }
    return CS_s.contains(id);
}

bool GTN::IsPipeAvailable(int id)
{
    if (! pipes.contains(id)) {
        cout << "����� � �����  ID �� ������� " << endl;
    }
    return pipes.contains(id) && pipes[id].IsAvailable();
}


void GTN::Add_CS() {
    compress_station cs;
    cin >> cs;
    CS_s.emplace(cs.csId, cs);
}

void GTN::Edit_pipe() {
    if (pipes.size() != 0) {
        cout << "������� ID �����:" << endl;
        int answer{}, count = 0;
        cin >> answer;
        if (pipes.contains(answer))
        {
            pipes[answer].Edit();
            count++;
            cout << "�������������� ������ �������!" << endl;
        }
        if (count == 0) {
            cout << "��������� � ������ ID �� ��� ������" << endl;
        }
    }
    else {
        cout << "����������� ���. ������������� ������" << endl;
    }
}

void GTN::Edit_CS() {
    if (CS_s.size() != 0) {
        cout << "������� ID ��:" << endl;
        int answer{}, count = 0;
        cin >> answer;
        if (CS_s.contains(answer))
        {
            CS_s[answer].Edit();
            count++;
        }
        if (count == 0) {
            cout << "��������� � ������ ID �� ��� ������" << endl;
        }
    }
    else {
        cout << "����������� ���. ������������� ������" << endl;
    }
}


void GTN::Show()
{
    cout << "��������� �����:" << endl;
    for (auto& [key,value] : pipes)
    {
        cout << "ID �����:" << key << endl;
        cout << value << endl;
    }
    cout << "��������� ��:" << endl;

    for (auto& [key,value] : CS_s)
    {
        cout << "ID ��:" << key << endl;
        cout << value << endl;
    }
    cout << "���������������� ����:" << endl;

    for (auto& [key, value] : pipes)
    {
        pipes[key].PrintConnection();
    }
    
}



void GTN::Save() {
    ofstream fout;
    cout << "������� �������� �����:" << endl;
    string file_name;
    cin >> file_name;
    fout.open(file_name, ios::out);
    if (!fout.is_open()) {
        cout << "������! �� ������� ������� ����" << endl;
    }
    else {
        cout << "������ ������� ��������!" << endl;
        fout << pipes.size() << endl;
        for (auto& [id, truba] : pipes) {
            fout << id << endl << truba.Pname << endl << truba.condition << endl << truba.diameter << endl << truba.length << endl;
        }
        fout << CS_s.size() << endl;
        for (auto& [id, cs] : CS_s) {
            fout << id << endl << cs.Pname << endl << cs.amount_shop << endl << cs.amount_Wshop << endl << cs.indicator << endl << cs.k << endl;
        }
    }
    fout.close();
}

void GTN::Download() {
    ifstream fin;
    cout << "������� �������� �����:" << endl;
    string file_name;
    cin >> file_name;
    /*pipes.clear();
    CS_s.clear();
    truba p;
    p.maxPid = 1;
    compress_station cs;
    cs.maxCSid = 1;*/
    fin.open(file_name, ios::in);
    if (!fin.is_open()) {
        cout << "������! �� ������� ������� ����" << endl;
    }
    else if (fin.peek() == EOF) {
        cout << "���� ������" << endl;
    }
    else {
        cout << "������ ������� ��������� �� �����!" << endl;
        int count1;
        fin >> count1;
        if (pipes.size() == 0) {
            for (auto& [pid, tr] : pipes) {
                pipes.erase(pid);
            }
        }
        for (int i = 1; i <= count1; i++) {
            truba tr;
            int id = 0;
            fin >> id;
            cout << "��������� ����� �" << id << endl;
            fin.ignore();
            getline(fin, tr.Pname);
            cout << "�������� �����:" << tr.Pname << endl;
            fin >> tr.condition;
            if (tr.condition == 1) {
                cout << "����� � ������� ��������� " << endl;
            }
            else {
                cout << "����� � ��������� �������" << endl;
            }
            fin >> tr.diameter;
            cout << "������� �����:" << " " << tr.diameter << endl;
            fin >> tr.length;
            cout << "����� �����:" << " " << tr.length << endl;
            pipes.emplace(id, tr);
        }
        int count2;
        fin >> count2;
        if (CS_s.size() == 0) {
            for (auto& [pid, cs] : CS_s) {
                CS_s.erase(pid);
            }
        }
        for (int i = 1; i <= count2; i++) {
            compress_station cs;
            int id = 0;
            fin >> id;
            cout << "��������� ������������� ������� �" << id << endl;
            fin.ignore();
            getline(fin, cs.Pname);
            cout << "�������� ������������� �������:" << cs.Pname << endl;
            fin >> cs.amount_shop;
            cout << "���������� �����:" << " " << cs.amount_shop << endl;
            fin >> cs.amount_Wshop;
            cout << "���������� ������� �����:" << " " << cs.amount_Wshop << endl;
            fin >> cs.indicator;
            cout << "���������� ������������� ������� �����: " << cs.indicator << endl;
            fin >> cs.k;
            cout << "������� ����������������� �����: " << cs.indicator << endl;
            CS_s.emplace(id, cs);
        }
    }
    fin.close();
}

void GTN::Delete_pipe() {
    if (pipes.size() != 0) {
        cout << "������� ID �����, ������� �� ������ �������" << endl;
        int answer, count = 0;
        cin >> answer;
        for (auto& [id, tr] : pipes) {
            if (answer == id) {
                count++;
                pipes.erase(id);
                cout << "��������� ��� ������� ������!" << endl;
                break;
            }
        }
        if (count == 0) {
            cout << "���������� � ������ ID �� ���� ������� " << endl;
        }
    }
    else {
        cout << "���� ���, ������� ������" << endl;
    }
}

void GTN::Delete_CS() {
    if (CS_s.size() != 0) {
        cout << "������� ID ��, ������� �� ������ �������" << endl;
        int answer, count = 0;
        cin >> answer;
        for (auto& [id, cs] : CS_s) {
            if (answer == id) {
                count++;
                CS_s.erase(id);
                cout << "��������� ��� ������� ������!" << endl;
                break;
            }
        }
        if (count == 0) {
            cout << "���������� � ������ ID �� ���� ������� " << endl;
        }
    }
    else {
        cout << "�� ���, ������� ������" << endl;
    }
}


bool GTN::Repair(const truba& tr, bool param) {
    if (param == tr.condition) {
        return 1;
    }
    else {
        return 0;
    }
}

bool GTN::Diameter (const truba& tr, int param) {
    return tr.diameter == param;
}

bool GTN::Non_working_CS(const compress_station& cs, double param) {
    if (param == cs.k) {
        return 1;
    }
    else {
        return 0;
    }
}

set <int> GTN::Subject(set<int>& Set) {
    int subset_element{};
    set <int> subset;
    while (subset_element != 0) {
        if (Set.contains(subset_element)) {
            subset.emplace(subset_element);
        }
    }
    return subset;

}
set<int> GTN::GetSubset(set<int> ids)
{
    set<int>subset;
    int id = -1;
    while (id)
    {
        cout << "������� ID �����. ����� �������� �����, ������� 0" << endl;
        cin >> id;
        if (ids.contains(id))
            subset.insert(id);
        else
        {
            cout << "����� � ������ ID �� �������" << endl;
        }
    }
    return subset;
}
