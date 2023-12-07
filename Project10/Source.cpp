#include <Windows.h>  
#include <iostream>
#include "Set.h"
#include "Bitefield.h"

int main() {
    using namespace std;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try {
        int maxPower, maxPower1;
        cout << "������� ������������ �������� ������� ���������: ";
        cin >> maxPower;
        cout << "������� ������������ �������� ������� ���������: ";
        cin >> maxPower1;

        if (maxPower <= 0 || maxPower1 <= 0) {
            cerr << "������������ �������� ������ ���� ������������� ������." << endl;
            return 1;
        }

        Set set1(maxPower);
        Set set2(maxPower1);

        cout << "������� �������� ������� ��������� ����� ������: ";
        cin >> set1;

        cout << "������� �������� ������� ��������� ����� ������: ";
        cin >> set2;

        int choice;
        do {
            cout << "\n�������� ��������:\n";
            cout << "1. ����������� ��������\n";
            cout << "2. ����������� ��������\n";
            cout << "3. �������� ��������\n";
            cout << "4. ���������� ������� ���������\n";
            cout << "5. ��������� ��������\n";
            cout << "0. �����\n";
            cout << "��� �����: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                Set unionSet = set1 + set2;
                cout << "����������� ��������:\n" << unionSet;
                break;
            }
            case 2: {
                Set intersectionSet = set1 * set2;
                cout << "����������� ��������:\n" << intersectionSet;
                break;
            }
            case 3: {
                int element;
                cout << "������� ������� ��� ��������: ";
                cin >> element;

                Set differenceSet = set1 - element;
                cout << "�������� ��������:\n" << differenceSet;
                break;
            }
            case 4: {
                Set complementSet = ~set1;
                cout << "���������� ������� ���������:\n" << complementSet;
                break;
            }
            case 5: {
                if (set1 == set2) {
                    cout << "��������� �����.\n";
                }
                else {
                    cout << "��������� �� �����.\n";
                }
                break;
            }
            case 0: {
                cout << "��������� ���������.\n";
                break;
            }
            default: {
                cout << "������������ �����. ���������� �����.\n";
                break;
            }
            }
        } while (choice != 0);
    }
    catch (const std::exception& ex) {
        cerr << "������: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
