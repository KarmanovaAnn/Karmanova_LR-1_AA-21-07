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
#include "GTN.h"
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
    cout << "11.Создание газотранспортной сети" << endl;
    cout << "12.Выйти" << endl;
}

void Exit(GTN gtn) {
    system("cls");
    cout << "Вы хотите сохранить текущее данные в файл или очистить его? Введите 1, если да, введите 0, если нет" << endl;
    int answer;
    cin >> answer;
    if (answer == 1) {
        gtn.Save();
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
    GTN gtn;
    const int POINT_OF_MENU = 12;
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
                gtn.Add_pipe();
                system("pause");
            }
            else if (activeMenuItem == 1) {
                system("cls");
               
                gtn.Add_CS();
                system("pause");
              
            }
            else if (activeMenuItem == 2) {
                system("cls");
                gtn.Show();

                system("pause");
               
            }
            else if (activeMenuItem == 3) {
                system("cls");
                gtn.Edit_pipe();
                system("pause");

            }
            else if (activeMenuItem == 4) {
                system("cls");
                gtn.Edit_CS();
                system("pause");
            }
            else if (activeMenuItem == 5) {
                system("cls");
                gtn.Save();
                system("pause");
            }
            else if (activeMenuItem == 6) {
                system("cls");
                gtn.Download();
                system("pause");
            }
            else if (activeMenuItem == 7) {
                system("cls");
                gtn.Delete_pipe();
                system("pause");
                
            }
            else if (activeMenuItem == 8) {
                system("cls");
                gtn.Delete_CS();
                system("pause");
            }
            else if (activeMenuItem == 9) {
                system("cls");
                cout << "Введите 1, если хотите искать необходимое множество по трубам, 0, если хотите искать по КС " << endl;
                int answer1;
                Tryanswer(answer1);
                if (answer1 == 1) {
                    string s;
                    gtn.Edit_Global_pipe<truba, string>(Names, s);
                }
                else {
                    string s;
                    gtn.Edit_Global_CS<compress_station, string>(Names, s);
                }
                system("pause");
            }
            else if (activeMenuItem == 10) {
                system("cls");
                gtn.Connect();
                system("pause");
            }

            else if (activeMenuItem == 11) {
                Exit(gtn);
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


