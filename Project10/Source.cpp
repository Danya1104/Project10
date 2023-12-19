#include <Windows.h>  
#include <iostream>
#include "Set.h"
using namespace std;
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try {
        int maxPower,maxPower1;
        cout << "Введите максимальную мощность для  первого множества: ";
        cin >> maxPower;
        maxPower += 1;
        cout << "Введите максимальную мощность для второго множества: ";
        cin >> maxPower1;
        maxPower1 += 1;
        Set set1(maxPower);
        Set set2(maxPower1);
        cin >> set1;
        cin >> set2;
        int choice;
        do {
            cout << "\nВыберите операцию:\n";
            cout << "1. Объединение множеств\n";
            cout << "2. Пересечение множеств\n";
            cout << "3. Разность множеств\n";
            cout << "4. Дополнение первого множества\n";
            cout << "5. Дополнение второго множества\n";
            cout << "6. Сравнение множеств\n";
            cout << "0. Выход\n";
            cout << "Ваш выбор: ";
            cin >> choice;
            switch (choice) {
            case 1: {
                Set unionSet = set1 + set2;
                cout << "Объединение множеств:\n" << unionSet;
                break;
            }
            case 2: {
                Set intersectionSet = set1 * set2;
                cout << "Пересечение множеств:\n" << intersectionSet;
                break;
            }
            case 3: {
                int element;
                cout << "Введите элемент для разности: ";
                cin >> element;

                Set differenceSet = set1 - element;
                cout << "Разность множеств:\n" << differenceSet;
                break;
            }
            case 4: {
                Set complementSet = ~set1;
                cout << "Дополнение первого множества:\n" << complementSet;
                break;
            }
            case 5: {
                Set complementSet1 = ~set2;
                cout << "Дополнение второго множества:\n" << complementSet1;
                break;
            }
            case 6: {
                if (set1 == set2) {
                    cout << "Множества равны.\n";
                }
                else {
                    cout << "Множества не равны.\n";
                }
                break;
            }
            case 0: {
                cout << "Программа завершена.\n";
                break;
            }
            default: {
                cout << "Некорректный выбор. Попробуйте снова.\n";
                break;
            }
            }
        } while (choice != 0);
    }
    catch (const char* msg) {
        cerr << "Ошибка: " << msg << endl;
    }
    return 0;
}
