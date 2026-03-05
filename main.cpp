#include "Header.h"
#include <iostream>
#include <limits>

int main() {
    std::setlocale(LC_ALL, "RU");
    int V;
    do {
        std::cout << "Выберите задачу: " << std::endl << std::endl;
        std::cout << "1 - Стек: разделение на чётные и нечётные" << std::endl;
        std::cout << "2 - Очередь: добавление элемента в конец" << std::endl;
        std::cout << "3 - Найти девятый элемент списка" << std::endl;
        std::cout << "4 - Вставить M перед каждым вторым элементом" << std::endl;
        std::cout << "5 - Упорядоченный список из файла" << std::endl;
        std::cout << "0 - Завершить работу" << std::endl << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> V;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (V) {
        case 1:
            N_1();
            break;
        case 2:
            N_2();
            break;
        case 3:
            N_3();
            break;
        case 4:
            N_4();
            break;
        case 5:
            N_5();
            break;
        case 0:
            std::cout << "Программа завершена." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, введите число от 0 до 5." << std::endl;
        }
        std::cout << std::endl;
    } while (V != 0);
    return 0;
}