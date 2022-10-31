#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <string>
#include <fstream>
#include <locale.h> 
#include <locale> 
#include <map>
#include <set>
#include "Check.h"
#include "ClrKarmanova.h"
#include "ComprSt.h"
using namespace std;

void showMenu() {
    system("cls");
    cout << "1.Добавить трубу" << endl;
    cout << "2.Добавить компрессорную станцию" << endl;
    cout << "3.Просмотреть все объекты" << endl;
    cout << "4.Изменить параметры трубы" << endl;
    cout << "5.Изменить параметры компрессорной станции" << endl;
    cout << "6.Сохранить данные в файл" << endl;
    cout << "7.Загрузить данные из файла" << endl;
    cout << "8.Удалить трубу" << endl;
    cout << "9.Удалить компрессорную станцию" << endl;
    cout << "10.Поиск компонентов и пакетное редактирование" << endl;
    cout << "11.Выйти" << endl;
}

template <typename T>
void Tryanswer(T& input) {
    while ((cin >> input).fail() || (input != 0 && input != 1)){
        cout << "Ошибка ввода" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void Save (map <int, truba>& pipes, map <int, compress_station>&  CS_s) {
    ofstream fout;
    cout << "Введите название файла:" << endl;
    string file_name;
    cin >> file_name;
    fout.open(file_name, ios::out);
    if (!fout.is_open()) {
        cout << "Ошибка! Не удалось открыть файл" << endl;
    }
    else {
        cout << "Данные успешно записаны!" << endl;
        fout<<pipes.size()<<endl;
        for (auto& [id, truba] : pipes) {
            fout << id <<endl<< truba.Pname << endl << truba.condition << endl << truba.diameter << endl << truba.length << endl;
        }
        fout << CS_s.size() << endl;
        for (auto& [id, cs] : CS_s) {
            fout << id << endl << cs.Pname << endl << cs.amount_shop << endl << cs.amount_Wshop << endl << cs.indicator << endl<<cs.k << endl;
        }
    }
    fout.close();
}

void Download(map <int, truba>& pipes, map <int, compress_station>& CS_s) {
    ifstream fin;
    cout << "Введите название файла:" << endl;
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
        cout << "Ошибка! Не удалось открыть файл" << endl;
    }
    else if (fin.peek() == EOF) {
        cout << "Файл пустой" << endl;
    }
    else {
        cout << "Данные успешно загружены из файла!" << endl;
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
            cout << "Параметры трубы №" << id << endl;
            fin.ignore();
            getline(fin, tr.Pname);
            cout << "Название трубы:" << tr.Pname << endl;
            fin >> tr.condition;
            if (tr.condition == 1) {
                cout << "Труба в хорошем состоянии " << endl;
            }
            else {
                cout << "Труба в состоянии ремонта" << endl;
            }
            fin >> tr.diameter;
            cout << "Диаметр трубы:" << " " << tr.diameter << endl;
            fin >> tr.length;
            cout << "Длина трубы:" << " " << tr.length << endl;
            pipes.emplace( id, tr );
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
            cout << "Параметры компрессорной станции №" << id << endl;
            fin.ignore();
            getline(fin, cs.Pname);
            cout << "Название компрессорной станции:" << cs.Pname << endl;
            fin >> cs.amount_shop;
            cout << "Количество цехов:" << " " << cs.amount_shop << endl;
            fin >> cs.amount_Wshop;
            cout << "Количество рабочих цехов:" << " " << cs.amount_Wshop << endl;
            fin >> cs.indicator;
            cout << "Показатель эффективности рабочих цехов: " << cs.indicator << endl;
            fin >> cs.k;
            cout << "Процент незадействованных цехов: " << cs.indicator << endl;
            CS_s.emplace(id, cs );
        }
    }
    fin.close();
}

void Delete_pipe(map <int, truba>& pipes) {
    if (pipes.size() != 0) {
        cout << "Введите ID трубы, которую вы хотите удалить" << endl;
        int answer, count=0;
        cin >> answer;
        for (auto& [id, tr] : pipes) {
            if (answer == id) {
                count++;
                pipes.erase(id);
                cout << "Компонент был успешно удален!" << endl;
                break;
            }
        }
        if (count == 0) {
            cout << "Комопненты с данным ID не были найдены " << endl;
        }
    }
    else {
        cout << "Труб нет, удалять нечего" << endl;
    }
}

void Delete_CS(map <int, compress_station>& CS_s) {
    if (CS_s.size() != 0) {
        cout << "Введите ID КС, которую вы хотите удалить" << endl;
        int answer,count=0;
        cin >> answer;
        for (auto& [id, cs] : CS_s) {
            if (answer == id) {
                count++;
                CS_s.erase(id);
                cout << "Компонент был успешно удален!" << endl;
                break;
            }
        }
        if (count == 0) {
            cout << "Комопненты с данным ID не были найдены " << endl;
        }
    }
    else {
        cout << "КС нет, удалять нечего" << endl;
    }
}

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
using Filter = bool(*)(const TObj&, Tp);

template <typename TObj>
bool Names(const TObj& obj, string param) {
    return(strstr(obj.Pname.c_str(), param.c_str()));
}

bool Repair(const truba&tr, bool param) {
    if (param == tr.condition) {
        return 1;
    }
    else {
        return 0;
    }
}

bool Non_working_CS(const compress_station& cs, double param) {
    if (param == cs.k) {
        return 1;
    }
    else {
        return 0;
    }
}

set <int> Subject(set<int>& Set) {
    int subset_element{};
    set <int> subset;
    while (subset_element != 0) {
        if (Set.contains(subset_element)) {
            subset.emplace(subset_element);
        }
    }
    return subset;

}
set<int> GetSubset(set<int> ids)
{
    set<int>subset;
    int id=-1;
    while (id)
    {
        cout << "Введите ID трубы. Когда захотите выйти, введите 0" << endl;
        cin >> id;
        if (ids.contains(id))
            subset.insert(id);
        else
        {
            cout << "Трубы с данным ID не найдено" << endl;
        }
    }
    return subset;
}
template <typename TObj, typename Tp>

set<int> FilterObjects(map <int, TObj>& objs, Filter<TObj, Tp> f, Tp param)
{
    set<int> found;
    for (auto& [id, obj] : objs) 
        if (f(obj, param))
            found.emplace(id);
    return found;
}

template <typename TObj, typename Tp>

void Edit_Global_pipe(map <int, TObj>& pipes, Filter<TObj, Tp> f, Tp param){   
    if (pipes.size() != 0) {
        set<int> selected;
        cout << "Введите 1, если хотите искать нужные Вам трубы по названию, 0, если хотите искать по признаку " << endl;
        int a;
        Tryanswer(a);
        map <int, truba> newpipes;
        if (a == 1){
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
        for (int id : selected){
            cout << "Параметры трубы №" << id << endl << endl;
            count++;
            cout<<pipes[id];
            for (auto& [pid, tr] : pipes) {
                if (pid == id) {
                    newpipes.emplace(pid, tr);
                }
            }
        }
        if (count == 0) {
            cout << "Труб по данному признаку не было найдено" << endl;
        }
        cout << "Введите 1, если хотите работать с найденным множеством, 0, если хотите выделить отдельное подмножество " << endl;
        int answer2;
        Tryanswer(answer2);
        if (answer2 == 1) {
            cout << "Введите 1, если хотите отредактировать подмножество, 0, если хотите совершить другие операции " << endl;
            int answer3;
            Tryanswer(answer3);
            if (answer3 == 1) {
                for (int id : selected){
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
            for (int id : selected){
                cout << "Параметры трубы №" << id << endl << endl;
                count++;
                cout << pipes[id];
                for (auto& [pid, tr] : pipes) {
                    if (pid == id) {
                        newpipes.emplace(pid, tr);
                    }
                }
            }
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
    }
    else {
        cout << "Контейнер пуст" << endl;
    }
}

template <typename TObj, typename Tp>
void Edit_Global_CS(map <int, TObj>& CS_s, Filter<TObj, Tp> f, Tp param) {
    if (CS_s.size() != 0) {
        set<int> selected;
        cout << "Введите 1, если хотите искать нужные Вам КС по названию, 0, если хотите искать по проценту незадействованных " << endl;
        int a;
        Tryanswer(a);
        map <int, compress_station>newCS_s;
        if (a == 1){
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
        cout << "Введите 1, если хотите работать с найденным множеством, 0, если хотите выделить отдельное подмножество " << endl;
        int answer2;
        Tryanswer(answer2);
        if (answer2 == 1) {
            Save_Delete_Edit(CS_s, newCS_s);
        }
        else {
            newCS_s.clear();
            selected = GetSubset(selected);
            for (int id : selected){
                cout << "Параметры КС №" << id << endl << endl;
                cout << CS_s[id] << endl;
                for (auto& [pid, cs] : CS_s) {
                    if (pid == id) {
                        newCS_s.emplace(pid, cs);
                    }
                }
            }
            Save_Delete_Edit(CS_s, newCS_s);
        }
    }
    else {
        cout<<"Контейнер пуст" << endl;
    }
}

void Exit(map <int, truba>& pipes, map <int, compress_station>& CS_s) {
    system("cls");
    cout << "Вы хотите сохранить текущее данные в файл или очистить его? Введите 1, если да, введите 0, если нет" << endl;
    int answer;
    cin >> answer;
    if (answer == 1) {
        Save(pipes, CS_s);
    }
    else {
        cout << "Введите название файла:" << endl;
        string file_name;
        cin >> file_name;
        ofstream ofs;
        ofs.open(file_name, ofstream::out | ofstream::trunc);
        ofs.close();
        cout << "Файл был очищен" << endl;
    }
}
 
 
//https://www.youtube.com/watch?v=PQyVWMaAJLg  - структура меню
void gotoxy(short x, short y) {
    COORD p = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
int main(){
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    system("cls");//очистка экрана
    map <int, truba> pipes;
    map <int, compress_station> CS_s;
    const int POINT_OF_MENU = 11;
    int activeMenuItem = 0;
    int ch = 0;
    bool exit = false;
    while (!exit) {
        showMenu();
        //Функция помещает курсор к выбранному пункту меню
        gotoxy(0, activeMenuItem);
        //Функция getch нужна считывания символа с клавиатуры
        ch = _getch();
        if (ch == 224) {
            ch = _getch();
        }
        //обработка нажатых клавиш
        switch (ch) {
        case 27:
            exit = true;
            break;
        case 72:
            activeMenuItem--;
            break;
        case 80:
            activeMenuItem++;
            break;
        case 13:
            if (activeMenuItem == 0) {
                system("cls");
                truba p;
                cin >> p;
                pipes.emplace(p.pId, p);
                system("pause");
            }
            else if (activeMenuItem == 1) {
                system("cls");
                compress_station cs;
                cin >> cs;
                CS_s.emplace(cs.csId, cs);
                system("pause");
              
            }
            else if (activeMenuItem == 2) {
                system("cls");
                cout << "Параметры труб:" << endl;
                for (auto& [id,truba]:pipes) {
                    cout << truba;
                }
                cout << "Параметры КС:" << endl;
                for (auto& [id, cs] : CS_s) {
                    cout << cs;
                }
                system("pause");
               
            }
            else if (activeMenuItem == 3) {
                system("cls");
                if (pipes.size() != 0) {
                    cout << "Введите ID трубы:" << endl;
                    int answer{}, count = 0;
                    cin >> answer;
                    if (pipes.contains(answer))
                    {
                        pipes[answer].Edit();
                        count++;
                        cout << "Редактирование прошло успешно!" << endl;
                    }
                    if (count == 0) {
                        cout << "Компонент с данным ID не был найден" << endl;
                    }
                }
                else {
                    cout << "Компонентов нет. Редактировать нечего" << endl;
                }
                system("pause");

            }
            else if (activeMenuItem == 4) {
                system("cls");
                if (CS_s.size() != 0) {
                    cout << "Введите ID КС:" << endl;
                    int answer{}, count = 0;
                    cin >> answer;
                    if (CS_s.contains(answer))
                    {
                        CS_s[answer].Edit();
                        count++;
                    }
                    if (count == 0) {
                        cout << "Компонент с данным ID не был найден" << endl;
                    }
                }
                else {
                    cout << "Компонентов нет. Редактировать нечего" << endl;
                }
                system("pause");
            }
            else if (activeMenuItem == 5) {
                system("cls");
                Save(pipes, CS_s);
                system("pause");
            }
            else if (activeMenuItem == 6) {
                system("cls");
                Download(pipes, CS_s);
                system("pause");
            }
            else if (activeMenuItem == 7) {
                system("cls");
                Delete_pipe(pipes);
                system("pause");
                
            }
            else if (activeMenuItem == 8) {
                system("cls");
                Delete_CS(CS_s);
                system("pause");
            }
            else if (activeMenuItem == 9) {
                system("cls");
                cout << "Введите 1, если хотите искать необходимое множество по трубам, 0, если хотите искать по КС " << endl;
                int answer1;
                Tryanswer(answer1);
                if (answer1 == 1) {
                    string s;
                    Edit_Global_pipe(pipes, Names, s);
                }
                else {
                    string s;
                    Edit_Global_CS(CS_s, Names, s);
                }
                system("pause");
            }
            else if (activeMenuItem == 10) {
                Exit(pipes,CS_s);
                exit = true;
            }
            break;
        }
        //ограничение перехода курсора по меню
        if (activeMenuItem < 0) {
            activeMenuItem = 0;
        }
        if (activeMenuItem > POINT_OF_MENU - 1) {
            activeMenuItem = POINT_OF_MENU - 1;
        }
    }
    return 0;
}


