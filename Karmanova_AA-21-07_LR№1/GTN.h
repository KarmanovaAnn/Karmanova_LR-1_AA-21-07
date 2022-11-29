#pragma once
#include "ClrKarmanova.h"
#include "ComprSt.h"
#include <map>
#include <iostream>
#include <fstream>
#include <set>
#include "Check.h"



class GTN
{
	std::map <int, truba> pipes;
	std::map <int, compress_station> CS_s;

public:
	void Show();
    void Add_pipe();
    void Connect();
    bool IsCsAvailable(int id);

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
        cout << "Введите 1, если хотите сохранить подмножество, 0, если хотите удалить его " << endl;
        int answer3;
        Tryanswer(answer3);
        if (answer3 == 1) {
            objs1 = objs2;
            cout << "Подмножество было успешно сохранено как новое основное множество!" << endl;
        }
        else if (answer3 == 0) {
            if (objs1.size() != 0) {
                for (auto& [pid, truba] : objs2) {
                    objs1.erase(pid);
                }
                cout << "Подмножество было успешно удалено из основного множества!" << endl;
            }
            else {
                cout << "Объектов нет, удалять нечего" << endl;
            }
        }
    }


    template <typename TObj, typename Tp>
    void Edit_Global_pipe(Filter<TObj, Tp> f, Tp param)
    {
        if (pipes.size() != 0) {
            set<int> selected;
            cout << "Введите 1, если хотите искать нужные Вам трубы по названию, 0, если хотите искать по признаку " << endl;
            int a;
            Tryanswer(a);
            map <int, truba> newpipes;
            if (a == 1) {
                string answer;
                cout << "Введите название: " << endl;
                cin.ignore(1000, '\n');
                cin.clear();
                getline(cin, answer);
                selected = FilterObjects(pipes, Names, answer);
            }
            else {
                bool answer;
                cout << "Введите 1, если хотите просмотреть параметры труб в хорошем состоянии, 0, если хотите просмотреть трубы, находящиеся в ремонте" << endl;
                Tryanswer(answer);
                selected = FilterObjects(pipes, Repair, answer);
            }
            int count = 0;
            for (int id : selected) {
                cout << "Параметры трубы №" << id << endl << endl;
                count++;
                cout << pipes[id];
                for (auto& [pid, tr] : pipes) {
                    if (pid == id) {
                        newpipes.emplace(pid, tr);
                    }
                }
            }
            if (count == 0) {
                cout << "Труб по данному признаку не было найдено" << endl;
            }
            cout << "Хотите продолжить работу? Введите 1, если да , введите 0, если нет" << endl;
            int ANSWER;
            Tryanswer(ANSWER);
            if (ANSWER == 1) {
                cout << "Введите 1, если хотите работать с найденным множеством, 0, если хотите выделить отдельное подмножество " << endl;
                int answer2;
                Tryanswer(answer2);
                if (answer2 == 1) {
                    cout << "Введите 1, если хотите отредактировать подмножество, 0, если хотите совершить другие операции " << endl;
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
                        cout << "Параметры трубы №" << id << endl << endl;
                        count++;
                        cout << pipes[id];
                        for (auto& [pid, tr] : pipes) {
                            if (pid == id) {
                                newpipes.emplace(pid, tr);
                            }
                        }
                    }
                    cout << "Хотите продолжить работу? Введите 1, если да , введите 0, если нет" << endl;
                    int ANSWER;
                    Tryanswer(ANSWER);
                    if (ANSWER == 1) {
                        cout << "Введите 1, если хотите отредактировать подмножество, 0, если хотите совершить другие операции " << endl;
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
            cout << "Контейнер пуст" << endl;
        }
    }

    template <typename TObj, typename Tp>
    void Edit_Global_CS(Filter<TObj, Tp> f, Tp param) {
        if (CS_s.size() != 0) {
            set<int> selected;
            cout << "Введите 1, если хотите искать нужные Вам КС по названию, 0, если хотите искать по проценту незадействованных " << endl;
            int a;
            Tryanswer(a);
            map <int, compress_station>newCS_s;
            if (a == 1) {
                string answer;
                cout << "Введите название: " << endl;
                cin.ignore(1000, '\n');
                cin.clear();
                getline(cin, answer);
                selected = FilterObjects(CS_s, Names, answer);
            }
            else {
                double answer;
                cout << "Введите процент неработающих цехов:" << endl;
                cin >> answer;
                selected = FilterObjects(CS_s, Non_working_CS, answer);
            }
            int count = 0;
            for (int id : selected)
            {
                cout << "Параметры КС №" << id << endl << endl;
                count++;
                cout << CS_s[id] << endl;
                for (auto& [pid, cs] : CS_s) {
                    if (pid == id) {
                        newCS_s.emplace(pid, cs);
                    }
                }
            }
            if (count == 0) {
                cout << "КС по данному признаку не было найдено" << endl;
            }
            cout << "Хотите продолжить работу? Введите 1, если да , введите 0, если нет" << endl;
            int ANSWER;
            Tryanswer(ANSWER);
            if (ANSWER == 1) {
                cout << "Введите 1, если хотите работать с найденным множеством, 0, если хотите выделить отдельное подмножество " << endl;
                int answer2;
                Tryanswer(answer2);
                if (answer2 == 1) {
                    Save_Delete_Edit(CS_s, newCS_s);
                }
                else {
                    newCS_s.clear();
                    selected = GetSubset(selected);
                    for (int id : selected) {
                        cout << "Параметры КС №" << id << endl << endl;
                        cout << CS_s[id] << endl;
                        for (auto& [pid, cs] : CS_s) {
                            if (pid == id) {
                                newCS_s.emplace(pid, cs);
                            }
                        }
                    }
                    cout << "Хотите продолжить работу? Введите 1, если да , введите 0, если нет" << endl;
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
            cout << "Контейнер пуст" << endl;
        }
    }

};

