#pragma once
#include "ClrKarmanova.h"
#include "ComprSt.h"
#include <map>
#include <iostream>
#include <fstream>
#include <set>
#include "Check.h"
#include "Graph.h"
#include "GraphCycle.h"

class GTN
{
	std::map <int, truba> pipes;
	std::map <int, compress_station> CS_s;

public:
	void Show();
    void Add_pipe();
    void Connect();
    bool IsCsAvailable(int id);
    void Graphs();
    void GraphSort();

    bool IsPipeAvailable(int id);
    
    void Add_CS();
    void Edit_pipe();
    void Edit_CS();
	void Save();
	void Download();
	void Delete_pipe();
	void Delete_CS();
    
    static bool Repair(const truba& tr, bool param);
    static bool Diameter(const truba& tr, int  param);
    static bool Non_working_CS(const compress_station& cs, double param);
    template <typename TObj, typename Tp>
    using Filter = bool(*)(const TObj&, Tp);
    template <typename TObj, typename Tp>
    std::set<int> FilterObjects(map <int, TObj>& objs, Filter<TObj, Tp> f, Tp param)
    {
        std::set<int> found;
        for (auto& [id, obj] : objs)
            if (f(obj, param))
                found.emplace(id);
        return found;
    }
    std::set<int> Subject(std::set<int>& Set);
    std::set<int> GetSubset(std::set<int> ids);

    template <typename TObj>
    void Save_Delete_Edit(map <int, TObj>& objs1, map <int, TObj>& objs2) {
        cout << "������� 1, ���� ������ ��������� ������������, 0, ���� ������ ������� ��� " << endl;
        int answer3;
        Tryanswer(answer3);
        if (answer3 == 1) {
            objs1 = objs2;
            cout << "������������ ���� ������� ��������� ��� ����� �������� ���������!" << endl;
        }
        else if (answer3 == 0) {
            if (objs1.size() != 0) {
                for (auto& [pid, truba] : objs2) {
                    objs1.erase(pid);
                }
                cout << "������������ ���� ������� ������� �� ��������� ���������!" << endl;
            }
            else {
                cout << "�������� ���, ������� ������" << endl;
            }
        }
    }


    template <typename TObj, typename Tp>
    void Edit_Global_pipe(Filter<TObj, Tp> f, Tp param)
    {
        if (pipes.size() != 0) {
            set<int> selected;
            cout << "������� 1, ���� ������ ������ ������ ��� ����� �� ��������, 0, ���� ������ ������ �� �������� " << endl;
            int a;
            Tryanswer(a);
            map <int, truba> newpipes;
            if (a == 1) {
                string answer;
                cout << "������� ��������: " << endl;
                cin.ignore(1000, '\n');
                cin.clear();
                getline(cin, answer);
                selected = FilterObjects(pipes, Names, answer);
            }
            else {
                bool answer;
                cout << "������� 1, ���� ������ ����������� ��������� ���� � ������� ���������, 0, ���� ������ ����������� �����, ����������� � �������" << endl;
                Tryanswer(answer);
                selected = FilterObjects(pipes, Repair, answer);
            }
            int count = 0;
            for (int id : selected) {
                cout << "��������� ����� �" << id << endl << endl;
                count++;
                cout << pipes[id];
                for (auto& [pid, tr] : pipes) {
                    if (pid == id) {
                        newpipes.emplace(pid, tr);
                    }
                }
            }
            if (count == 0) {
                cout << "���� �� ������� �������� �� ���� �������" << endl;
            }
            cout << "������ ���������� ������? ������� 1, ���� �� , ������� 0, ���� ���" << endl;
            int ANSWER;
            Tryanswer(ANSWER);
            if (ANSWER == 1) {
                cout << "������� 1, ���� ������ �������� � ��������� ����������, 0, ���� ������ �������� ��������� ������������ " << endl;
                int answer2;
                Tryanswer(answer2);
                if (answer2 == 1) {
                    cout << "������� 1, ���� ������ ��������������� ������������, 0, ���� ������ ��������� ������ �������� " << endl;
                    int answer3;
                    Tryanswer(answer3);
                    if (answer3 == 1) {
                        for (int id : selected) {
                            pipes[id].Edit();
                        }
                    }
                    else {
                        Save_Delete_Edit(pipes, newpipes);
                    }
                }
                else {
                    newpipes.clear();
                    selected = GetSubset(selected);
                    for (int id : selected) {
                        cout << "��������� ����� �" << id << endl << endl;
                        count++;
                        cout << pipes[id];
                        for (auto& [pid, tr] : pipes) {
                            if (pid == id) {
                                newpipes.emplace(pid, tr);
                            }
                        }
                    }
                    cout << "������ ���������� ������? ������� 1, ���� �� , ������� 0, ���� ���" << endl;
                    int ANSWER;
                    Tryanswer(ANSWER);
                    if (ANSWER == 1) {
                        cout << "������� 1, ���� ������ ��������������� ������������, 0, ���� ������ ��������� ������ �������� " << endl;
                        int answer3;
                        Tryanswer(answer3);
                        if (answer3 == 1) {
                            for (int id : selected)
                            {
                                pipes[id].Edit();
                            }
                        }
                        else {
                            Save_Delete_Edit(pipes, newpipes);
                        }
                    }
                    else {}
                }
            }
            else {

            }
        }
        else {
            cout << "��������� ����" << endl;
        }
    }

    template <typename TObj, typename Tp>
    void Edit_Global_CS(Filter<TObj, Tp> f, Tp param) {
        if (CS_s.size() != 0) {
            set<int> selected;
            cout << "������� 1, ���� ������ ������ ������ ��� �� �� ��������, 0, ���� ������ ������ �� �������� ����������������� " << endl;
            int a;
            Tryanswer(a);
            map <int, compress_station>newCS_s;
            if (a == 1) {
                string answer;
                cout << "������� ��������: " << endl;
                cin.ignore(1000, '\n');
                cin.clear();
                getline(cin, answer);
                selected = FilterObjects(CS_s, Names, answer);
            }
            else {
                double answer;
                cout << "������� ������� ������������ �����:" << endl;
                cin >> answer;
                selected = FilterObjects(CS_s, Non_working_CS, answer);
            }
            int count = 0;
            for (int id : selected)
            {
                cout << "��������� �� �" << id << endl << endl;
                count++;
                cout << CS_s[id] << endl;
                for (auto& [pid, cs] : CS_s) {
                    if (pid == id) {
                        newCS_s.emplace(pid, cs);
                    }
                }
            }
            if (count == 0) {
                cout << "�� �� ������� �������� �� ���� �������" << endl;
            }
            cout << "������ ���������� ������? ������� 1, ���� �� , ������� 0, ���� ���" << endl;
            int ANSWER;
            Tryanswer(ANSWER);
            if (ANSWER == 1) {
                cout << "������� 1, ���� ������ �������� � ��������� ����������, 0, ���� ������ �������� ��������� ������������ " << endl;
                int answer2;
                Tryanswer(answer2);
                if (answer2 == 1) {
                    Save_Delete_Edit(CS_s, newCS_s);
                }
                else {
                    newCS_s.clear();
                    selected = GetSubset(selected);
                    for (int id : selected) {
                        cout << "��������� �� �" << id << endl << endl;
                        cout << CS_s[id] << endl;
                        for (auto& [pid, cs] : CS_s) {
                            if (pid == id) {
                                newCS_s.emplace(pid, cs);
                            }
                        }
                    }
                    cout << "������ ���������� ������? ������� 1, ���� �� , ������� 0, ���� ���" << endl;
                    int ANSWER;
                    Tryanswer(ANSWER);
                    if (ANSWER == 1) {
                        Save_Delete_Edit(CS_s, newCS_s);
                    }
                    else {}
                }
            }
            else {}
        }
        else {
            cout << "��������� ����" << endl;
        }
    }

};

