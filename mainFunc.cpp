#include "Header.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include <string>

// Вспомогательная функция для ввода
int safeInputInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: необходимо ввести целое число. Попробуйте снова.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

//Stack

struct Stack::Node {
    int x;      // данные
    Node* Next; // указатель на следующий узел
};

// Конструктор по умолчанию
Stack::Stack() : Head(nullptr) {}

// Конструктор копирования
Stack::Stack(const Stack& other) : Head(nullptr) {
    Stack temp; // временный стек для сохранения порядка
    Node* cur = other.Head;
    while (cur) {
        temp.Push(cur->x); // копируем данные в temp
        cur = cur->Next;
    }
    while (!temp.IsEmpty()) {
        Node* node = temp.PopNode(); // извлекаем узел из temp
        PushNode(node);              // перемещаем в текущий стек
    }
}

// Деструктор
Stack::~Stack() {
    Clear();
}

// Очищает стек
void Stack::Clear() {
    while (!IsEmpty()) {
        Node* temp = Head;
        Head = Head->Next;
        delete temp;
    }
}

// Добавляет новый элемент со значением data на вершину стека (создаётся новый узел)
void Stack::Push(int data) {
    Node* newNode = new Node;
    newNode->x = data;
    newNode->Next = Head;
    Head = newNode;
}

// Добавляет уже существующий узел node на вершину стека
void Stack::PushNode(Node* node) {
    node->Next = Head;
    Head = node;
}

// Извлекает узел из вершины стека без удаления
Stack::Node* Stack::PopNode() {
    if (Head == nullptr) return nullptr;
    Node* temp = Head;
    Head = Head->Next;
    return temp;
}

// Проверяет пуст ли стек
bool Stack::IsEmpty() const {
    return Head == nullptr;
}

// Возвращает значение верхнего элемента (без удаления)
int Stack::Top() const {
    return Head->x;
}

// Выводит содержимое стека на экран (от вершины к дну)
void Stack::Print() const {
    Node* cur = Head;
    while (cur) {
        std::cout << cur->x << " ";
        cur = cur->Next;
    }
    std::cout << std::endl;
}

// Возвращает указатель на вершину стека (для вывода адреса)
Stack::Node* Stack::GetHead() const {
    return Head;
}



//Queue

struct Queue::Node {
    int x;
    Node* Next;
};

// Конструктор по умолчанию создаёт пустую очередь
Queue::Queue() : Head(nullptr), Tail(nullptr) {}

// Конструктор копирования
Queue::Queue(const Queue& other) : Head(nullptr), Tail(nullptr) {
    Node* cur = other.Head;
    while (cur) {
        Push(cur->x);
        cur = cur->Next;
    }
}

// Деструктор освобождает память всех узлов
Queue::~Queue() {
    Clear();
}

// Очищает очередь удаляя все узлы
void Queue::Clear() {
    while (!IsEmpty()) {
        Node* temp = Head;
        Head = Head->Next;
        delete temp;
    }
    Tail = nullptr;
}

// Добавляет элемент со значением data в конец очереди (создаётся новый узел)
void Queue::Push(int data) {
    Node* newNode = new Node;
    newNode->x = data;
    newNode->Next = nullptr;
    if (Head == nullptr) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        Tail->Next = newNode;
        Tail = newNode;
    }
}

// Удаляет первый элемент очереди и возвращает его значение
int Queue::Pop() {
    if (IsEmpty()) {
        std::cerr << "Очередь пуста, невозможно удалить.\n";
        return -1;
    }
    Node* temp = Head;
    int val = temp->x;
    Head = Head->Next;
    if (Head == nullptr) {
        Tail = nullptr;
    }
    delete temp;
    return val;
}

// Проверяет, пуста ли очередь
bool Queue::IsEmpty() const {
    return Head == nullptr;
}

// Возвращает указатель на начало очереди
Queue::Node* Queue::GetHead() const {
    return Head;
}

// Возвращает указатель на конец очереди
Queue::Node* Queue::GetTail() const {
    return Tail;
}

// Выводит содержимое очереди на экран (от начала к концу)
void Queue::Print() const {
    Node* cur = Head;
    while (cur) {
        std::cout << cur->x << " ";
        cur = cur->Next;
    }
    std::cout << std::endl;
}

//CommonList

struct CommonList::Node {
    int x;
    Node* Next;
};

// Конструктор по умолчанию
CommonList::CommonList() : Head(nullptr) {}

// Конструктор копирования
CommonList::CommonList(const CommonList& other) : Head(nullptr) {
    Node* cur = other.Head;
    while (cur) {
        PushBack(cur->x);
        cur = cur->Next;
    }
}

// Деструктор освобождает память
CommonList::~CommonList() {
    Clear();
}

// Очищает список удаляет все узлы
void CommonList::Clear() {
    while (Head) {
        Node* temp = Head;
        Head = Head->Next;
        delete temp;
    }
}

// Добавляет элемент в конец списка
void CommonList::PushBack(int data) {
    Node* newNode = new Node;
    newNode->x = data;
    newNode->Next = nullptr;
    if (!Head) {
        Head = newNode;
    }
    else {
        Node* cur = Head;
        while (cur->Next) cur = cur->Next; // идём до последнего
        cur->Next = newNode;
    }
}

// Возвращает указатель на узел по индексу (начиная с 0)
CommonList::Node* CommonList::GetNode(int index) const {
    Node* cur = Head;
    int cnt = 0;
    while (cur && cnt < index) {
        cur = cur->Next;
        cnt++;
    }
    return cur; // может быть nullptr
}

// Вставка значения M перед каждым вторым элементом исходного списка
// Возвращает указатель на последний элемент после вставок
CommonList::Node* CommonList::InsertBeforeSecond(int M) {
    if (!Head) return nullptr;
    Node* prev = nullptr;
    Node* curr = Head;
    int pos = 1; // позиция текущего узла в исходном списке
    while (curr) {
        if (pos % 2 == 0) { // чётная позиция – вставляем перед
            Node* newNode = new Node;
            newNode->x = M;
            newNode->Next = curr;
            if (!prev) Head = newNode; // вставка в начало (не должно случиться но пусть будет)
            else prev->Next = newNode;
            prev = curr; // теперь предыдущим становится исходный узел
            curr = curr->Next; // переходим к следующему исходному
            pos++;
        }
        else {
            prev = curr;
            curr = curr->Next;
            pos++;
        }
    }
    return prev; // последний элемент после вставок
}

// Вставка элемента с сохранением упорядоченности по убыванию
void CommonList::InsertSorted(int data) {
    Node* newNode = new Node;
    newNode->x = data;
    newNode->Next = nullptr;
    if (!Head) {
        Head = newNode;
        return;
    }
    // Если новый элемент больше или равен первому – в начало
    if (data >= Head->x) {
        newNode->Next = Head;
        Head = newNode;
        return;
    }
    // Ищем место вставки
    Node* cur = Head;
    while (cur->Next && cur->Next->x > data) {
        cur = cur->Next;
    }
    newNode->Next = cur->Next;
    cur->Next = newNode;
}

// Возвращает указатель на последний элемент списка
CommonList::Node* CommonList::GetLast() const {
    if (!Head) return nullptr;
    Node* cur = Head;
    while (cur->Next) cur = cur->Next;
    return cur;
}

// Выводит содержимое списка на экран
void CommonList::Print() const {
    Node* cur = Head;
    while (cur) {
        std::cout << cur->x << " ";
        cur = cur->Next;
    }
    std::cout << std::endl;
}

// Удаляет первое вхождение элемента со значением val
bool CommonList::RemoveFirst(int val) {
    if (!Head) return false;
    if (Head->x == val) {
        Node* temp = Head;
        Head = Head->Next;
        delete temp;
        return true;
    }
    Node* prev = Head;
    Node* curr = Head->Next;
    while (curr) {
        if (curr->x == val) {
            prev->Next = curr->Next;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->Next;
    }
    return false;
}

// Поиск узла по значению возвращает указатель на узел или nullptr
CommonList::Node* CommonList::Find(int val) const {
    Node* cur = Head;
    while (cur) {
        if (cur->x == val) return cur;
        cur = cur->Next;
    }
    return nullptr;
}

//Задача 1

void N_1() {
    std::setlocale(LC_ALL, "RU");
    Stack P1; // исходный стек

    // Меню выбора способа заполнения
    std::cout << "\nВыберите способ заполнения стека:\n";
    std::cout << "1 - С клавиатуры\n";
    std::cout << "2 - Из файла\n";
    std::cout << "3 - Случайными числами\n";
    int method = safeInputInt("Ваш выбор: ");

    if (method == 1) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        std::cout << "Введите " << count << " целых чисел:\n";
        for (int i = 0; i < count; i++) {
            int value = safeInputInt("");
            P1.Push(value);
        }
    }
    else if (method == 2) {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::getline(std::cin, filename);

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
            return;
        }

        int value;
        while (file >> value) {
            P1.Push(value);
        }
        if (file.bad()) {
            std::cerr << "Ошибка чтения файла." << std::endl;
        }
        file.close();
    }
    else if (method == 3) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        int minVal = safeInputInt("Введите минимальное значение: ");
        int maxVal = safeInputInt("Введите максимальное значение: ");
        if (minVal > maxVal) std::swap(minVal, maxVal);

        std::srand(std::time(nullptr));
        for (int i = 0; i < count; ++i) {
            int value = minVal + std::rand() % (maxVal - minVal + 1);
            P1.Push(value);
        }
    }
    else {
        std::cout << "Неверный выбор. Возврат в меню задач.\n";
        return;
    }

    std::cout << "Исходный стек (вершина слева): ";
    P1.Print();

    int choice;
    do {
        std::cout << "\n--- Меню (стек) ---\n";
        std::cout << "1 - Добавить элемент\n";
        std::cout << "2 - Удалить элемент с вершины\n";
        std::cout << "3 - Найти элемент\n";
        std::cout << "4 - Решение задачи (разделить на чётные/нечётные)\n";
        std::cout << "0 - Выход\n";
        choice = safeInputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            int val = safeInputInt("Введите значение для добавления: ");
            P1.Push(val);
            std::cout << "Элемент добавлен. Текущий стек: ";
            P1.Print();
            break;
        }
        case 2: {
            if (P1.IsEmpty()) {
                std::cout << "Стек пуст, удаление невозможно.\n";
            }
            else {
                Stack::Node* node = P1.PopNode();
                std::cout << "Удалён элемент: " << node->x << std::endl;
                delete node;
            }
            break;
        }
        case 3: {
            int val = safeInputInt("Введите значение для поиска: ");
            Stack::Node* cur = P1.GetHead();
            bool found = false;
            while (cur) {
                if (cur->x == val) {
                    found = true;
                    break;
                }
                cur = cur->Next;
            }
            if (found)
                std::cout << "Элемент найден.\n";
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 4: {
            // Решение задачи разделение на чётные и нечётные
            Stack even, odd;
            while (!P1.IsEmpty()) {
                Stack::Node* node = P1.PopNode();
                if (node->x % 2 == 0) {
                    even.PushNode(node);
                }
                else {
                    odd.PushNode(node);
                }
            }
            std::cout << "Адрес вершины стека с чётными: " << even.GetHead() << std::endl;
            std::cout << "Адрес вершины стека с нечётными: " << odd.GetHead() << std::endl;
            std::cout << "Стек с чётными (вершина слева): ";
            even.Print();
            std::cout << "Стек с нечётными (вершина слева): ";
            odd.Print();
            break;
        }
        case 0:
            std::cout << "Выход из задачи.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

//Задача 2

void N_2() {
    std::setlocale(LC_ALL, "RU");
    Queue q;

    std::cout << "\nВыберите способ заполнения очереди:\n";
    std::cout << "1 - С клавиатуры\n";
    std::cout << "2 - Из файла\n";
    std::cout << "3 - Случайными числами\n";
    int method = safeInputInt("Ваш выбор: ");

    if (method == 1) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        std::cout << "Введите " << count << " целых чисел:\n";
        for (int i = 0; i < count; ++i) {
            int value = safeInputInt("");
            q.Push(value);
        }
    }
    else if (method == 2) {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::getline(std::cin, filename);

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
            return;
        }

        int value;
        while (file >> value) {
            q.Push(value);
        }
        if (file.bad()) {
            std::cerr << "Ошибка чтения файла." << std::endl;
        }
        file.close();
    }
    else if (method == 3) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        int minVal = safeInputInt("Введите минимальное значение: ");
        int maxVal = safeInputInt("Введите максимальное значение: ");
        if (minVal > maxVal) std::swap(minVal, maxVal);

        std::srand(std::time(nullptr));
        for (int i = 0; i < count; ++i) {
            int value = minVal + std::rand() % (maxVal - minVal + 1);
            q.Push(value);
        }
    }
    else {
        std::cout << "Неверный выбор. Возврат в меню задач.\n";
        return;
    }

    std::cout << "Исходная очередь (начало -> конец): ";
    q.Print();

    int choice;
    do {
        std::cout << "\n--- Меню (очередь) ---\n";
        std::cout << "1 - Добавить элемент в конец\n";
        std::cout << "2 - Удалить элемент из начала\n";
        std::cout << "3 - Найти элемент\n";
        std::cout << "4 - Решение задачи (добавить D)\n";
        std::cout << "0 - Выход\n";
        choice = safeInputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            int val = safeInputInt("Введите значение для добавления: ");
            q.Push(val);
            std::cout << "Элемент добавлен. Текущая очередь: ";
            q.Print();
            break;
        }
        case 2: {
            if (q.IsEmpty()) {
                std::cout << "Очередь пуста, удаление невозможно.\n";
            }
            else {
                int val = q.Pop();
                std::cout << "Удалён элемент из начала: " << val << std::endl;
            }
            break;
        }
        case 3: {
            int val = safeInputInt("Введите значение для поиска: ");
            Queue::Node* cur = q.GetHead();
            bool found = false;
            while (cur) {
                if (cur->x == val) {
                    found = true;
                    break;
                }
                cur = cur->Next;
            }
            if (found)
                std::cout << "Элемент найден.\n";
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 4: {
            int D = safeInputInt("Введите число D для добавления в конец очереди: ");
            q.Push(D);
            std::cout << "Новые адреса: P1 = " << q.GetHead() << ", P2 = " << q.GetTail() << std::endl;
            std::cout << "Очередь после добавления: ";
            q.Print();
            break;
        }
        case 0:
            std::cout << "Выход из задачи.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

//Задача 3

void N_3() {
    std::setlocale(LC_ALL, "RU");
    CommonList list;
    int count = 0;

    // Меню выбора способа заполнения
    std::cout << "\nВыберите способ заполнения списка:\n";
    std::cout << "1 - С клавиатуры\n";
    std::cout << "2 - Из файла\n";
    std::cout << "3 - Случайными числами\n";
    int method = safeInputInt("Ваш выбор: ");

    if (method == 1) {
        count = safeInputInt("Введите количество элементов (не менее 9): ");
        if (count < 9) {
            std::cout << "Ошибка: количество элементов должно быть не менее 9.\n";
            return;
        }
        std::cout << "Введите " << count << " целых чисел:\n";
        for (int i = 0; i < count; ++i) {
            int value = safeInputInt("");
            list.PushBack(value);
        }
    }
    else if (method == 2) {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::getline(std::cin, filename);

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
            return;
        }

        int value;
        while (file >> value) {
            list.PushBack(value);
            count++;
        }
        if (file.bad()) {
            std::cerr << "Ошибка чтения файла." << std::endl;
        }
        file.close();

        if (count < 9) {
            std::cout << "В файле меньше 9 элементов. Операция невозможна.\n";
            return;
        }
    }
    else if (method == 3) {
        count = safeInputInt("Введите количество элементов (не менее 9): ");
        if (count < 9) {
            std::cout << "Ошибка: количество элементов должно быть не менее 9.\n";
            return;
        }
        int minVal = safeInputInt("Введите минимальное значение: ");
        int maxVal = safeInputInt("Введите максимальное значение: ");
        if (minVal > maxVal) std::swap(minVal, maxVal);

        std::srand(std::time(nullptr));
        for (int i = 0; i < count; ++i) {
            int value = minVal + std::rand() % (maxVal - minVal + 1);
            list.PushBack(value);
        }
    }
    else {
        std::cout << "Неверный выбор. Возврат в меню задач.\n";
        return;
    }

    std::cout << "Исходный список (от головы к хвосту): ";
    list.Print();

    int choice;
    do {
        std::cout << "\n--- Меню (список, задача 3) ---\n";
        std::cout << "1 - Добавить элемент в конец\n";
        std::cout << "2 - Удалить элемент по значению\n";
        std::cout << "3 - Найти элемент\n";
        std::cout << "4 - Решение задачи (вывести девятый элемент)\n";
        std::cout << "0 - Выход\n";
        choice = safeInputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            int val = safeInputInt("Введите значение для добавления: ");
            list.PushBack(val);
            std::cout << "Элемент добавлен. Текущий список: ";
            list.Print();
            break;
        }
        case 2: {
            int val = safeInputInt("Введите значение для удаления: ");
            if (list.RemoveFirst(val))
                std::cout << "Элемент удалён.\n";
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 3: {
            int val = safeInputInt("Введите значение для поиска: ");
            CommonList::Node* found = list.Find(val);
            if (found)
                std::cout << "Элемент найден, адрес: " << found << std::endl;
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 4: {
            // Получаем девятый элемент (индекс 8)
            CommonList::Node* p9 = list.GetNode(8);
            std::cout << "Указатель на девятый элемент P9 = " << p9 << std::endl;
            if (p9)
                std::cout << "Значение девятого элемента: " << p9->x << std::endl;
            break;
        }
        case 0:
            std::cout << "Выход из задачи.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

//Задача 4

void N_4() {
    std::setlocale(LC_ALL, "RU");
    CommonList list;

    // Меню выбора способа заполнения
    std::cout << "\nВыберите способ заполнения списка:\n";
    std::cout << "1 - С клавиатуры\n";
    std::cout << "2 - Из файла\n";
    std::cout << "3 - Случайными числами\n";
    int method = safeInputInt("Ваш выбор: ");

    if (method == 1) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        std::cout << "Введите " << count << " целых чисел:\n";
        for (int i = 0; i < count; ++i) {
            int value = safeInputInt("");
            list.PushBack(value);
        }
    }
    else if (method == 2) {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::getline(std::cin, filename);

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
            return;
        }

        int value;
        while (file >> value) {
            list.PushBack(value);
        }
        if (file.bad()) {
            std::cerr << "Ошибка чтения файла." << std::endl;
        }
        file.close();
    }
    else if (method == 3) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        int minVal = safeInputInt("Введите минимальное значение: ");
        int maxVal = safeInputInt("Введите максимальное значение: ");
        if (minVal > maxVal) std::swap(minVal, maxVal);

        std::srand(std::time(nullptr));
        for (int i = 0; i < count; ++i) {
            int value = minVal + std::rand() % (maxVal - minVal + 1);
            list.PushBack(value);
        }
    }
    else {
        std::cout << "Неверный выбор. Возврат в меню задач.\n";
        return;
    }

    std::cout << "Исходный список: ";
    list.Print();

    int choice;
    do {
        std::cout << "\n--- Меню (список, задача 4) ---\n";
        std::cout << "1 - Добавить элемент в конец\n";
        std::cout << "2 - Удалить элемент по значению\n";
        std::cout << "3 - Найти элемент\n";
        std::cout << "4 - Решение задачи (вставить M перед каждым вторым)\n";
        std::cout << "0 - Выход\n";
        choice = safeInputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            int val = safeInputInt("Введите значение для добавления: ");
            list.PushBack(val);
            std::cout << "Элемент добавлен. Текущий список: ";
            list.Print();
            break;
        }
        case 2: {
            int val = safeInputInt("Введите значение для удаления: ");
            if (list.RemoveFirst(val))
                std::cout << "Элемент удалён.\n";
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 3: {
            int val = safeInputInt("Введите значение для поиска: ");
            CommonList::Node* found = list.Find(val);
            if (found)
                std::cout << "Элемент найден, адрес: " << found << std::endl;
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 4: {
            int M = safeInputInt("Введите значение M для вставки перед каждым вторым элементом: ");
            CommonList::Node* last = list.InsertBeforeSecond(M);
            std::cout << "Список после вставок: ";
            list.Print();
            std::cout << "Указатель на последний элемент P2 = " << last << std::endl;
            if (last)
                std::cout << "Значение последнего элемента: " << last->x << std::endl;
            break;
        }
        case 0:
            std::cout << "Выход из задачи.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

//Задача 5

void N_5() {
    std::setlocale(LC_ALL, "RU");
    CommonList list;          // упорядоченный список
    std::vector<int> original; // вектор для хранения исходных чисел в порядке ввода

    // Меню выбора способа заполнения
    std::cout << "\nВыберите способ заполнения списка:\n";
    std::cout << "1 - С клавиатуры\n";
    std::cout << "2 - Из файла (в формате: число N, затем N чисел)\n";
    std::cout << "3 - Случайными числами\n";
    int method = safeInputInt("Ваш выбор: ");

    if (method == 1) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        std::cout << "Введите " << count << " целых чисел:\n";
        for (int i = 0; i < count; i++) {
            int value = safeInputInt("");
            original.push_back(value);
        }
    }
    else if (method == 2) {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::getline(std::cin, filename);

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
            return;
        }

        int N;
        file >> N;
        if (file.fail() || N <= 0) {
            std::cerr << "Ошибка: некорректное значение N в файле." << std::endl;
            return;
        }

        int value;
        for (int i = 0; i < N; i++) {
            file >> value;
            if (file.fail()) {
                std::cerr << "Ошибка: недостаточно чисел в файле." << std::endl;
                return;
            }
            original.push_back(value);
        }
        file.close();
    }
    else if (method == 3) {
        int count = safeInputInt("Введите количество элементов: ");
        if (count <= 0) {
            std::cout << "Количество должно быть положительным. Возврат в меню.\n";
            return;
        }
        int minVal = safeInputInt("Введите минимальное значение: ");
        int maxVal = safeInputInt("Введите максимальное значение: ");
        if (minVal > maxVal) std::swap(minVal, maxVal);

        std::srand(std::time(nullptr));
        for (int i = 0; i < count; ++i) {
            int value = minVal + std::rand() % (maxVal - minVal + 1);
            original.push_back(value);
        }
    }
    else {
        std::cout << "Неверный выбор. Возврат в меню задач.\n";
        return;
    }

    // Выводим исходный список (неупорядоченный)
    std::cout << "Исходный список (в порядке ввода): ";
    for (size_t i = 0; i < original.size(); i++) {
        std::cout << original[i] << " ";
    }
    std::cout << std::endl;

    int choice;
    do {
        std::cout << "\n--- Меню (упорядоченный список) ---\n";
        std::cout << "1 - Добавить элемент (с сортировкой)\n";
        std::cout << "2 - Удалить элемент по значению\n";
        std::cout << "3 - Найти элемент\n";
        std::cout << "4 - Решение задачи (построить упорядоченный список)\n";
        std::cout << "0 - Выход\n";
        choice = safeInputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            int val = safeInputInt("Введите значение для добавления: ");
            list.InsertSorted(val);
            std::cout << "Элемент добавлен. Текущий список: ";
            list.Print();
            break;
        }
        case 2: {
            int val = safeInputInt("Введите значение для удаления: ");
            if (list.RemoveFirst(val))
                std::cout << "Элемент удалён.\n";
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 3: {
            int val = safeInputInt("Введите значение для поиска: ");
            CommonList::Node* found = list.Find(val);
            if (found)
                std::cout << "Элемент найден, адрес: " << found << std::endl;
            else
                std::cout << "Элемент не найден.\n";
            break;
        }
        case 4: {
            // Решение задачи строим упорядоченный список заново из исходных данных
            list.Clear();
            for (size_t i = 0; i < original.size(); i++) {
                list.InsertSorted(original[i]);
            }
            std::cout << "Упорядоченный по убыванию список: ";
            list.Print();
            break;
        }
        case 0:
            std::cout << "Выход из задачи.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}