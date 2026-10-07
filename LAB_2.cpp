#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cctype> // для isdigit

using namespace std;

// ==================== Задача 1 ====================
// Генерация массива из 8 случайных чисел в диапазоне [2, 103]
// и сортировка по возрастанию.
void task1() {
    const int SIZE = 8;
    int massiv[SIZE];

    // std::random_device — аппаратный источник случайности (может быть медленным)
    // std::mt19937 — генератор псевдослучайных чисел Mersenne Twister
    // std::uniform_int_distribution — равномерное распределение на отрезке [2, 103]
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(2, 103);

    cout << "Изначальный массив: " << endl;
    for (int i = 0; i < SIZE; i++) {
        massiv[i] = dist(gen);
        cout << massiv[i] << (i == SIZE - 1 ? "\n" : " ");
    }

    // Сортировка выбором по возрастанию:
    // для каждой позиции i ищем минимальный элемент среди massiv[i..SIZE-1]
    // и ставим его на место i.
    for (int i = 0; i < SIZE; i++) {
        for (int k = i; k < SIZE; k++) {
            if (massiv[i] > massiv[k]) {
                swap(massiv[i], massiv[k]);
            }
        }
    }

    cout << "Новый массив по возрастанию: " << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << massiv[i] << (i == SIZE - 1 ? "\n" : " ");
    }
}

// ==================== Задача 2 ====================
// То же, что и задача 1, но сортировка по убыванию.
void task2() {
    const int SIZE = 8;
    int massiv[SIZE];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(2, 103);

    cout << "Изначальный массив: " << endl;
    for (int i = 0; i < SIZE; i++) {
        massiv[i] = dist(gen);
        cout << massiv[i] << (i == SIZE - 1 ? "\n" : " ");
    }

    // Сортировка выбором по убыванию:
    // для каждой позиции i ищем максимальный элемент среди massiv[i..SIZE-1]
    // и ставим его на место i.
    for (int i = 0; i < SIZE; i++) {
        for (int k = i; k < SIZE; k++) {
            if (massiv[i] < massiv[k]) {
                swap(massiv[i], massiv[k]);
            }
        }
    }

    cout << "Новый массив по убыванию: " << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << massiv[i] << (i == SIZE - 1 ? "\n" : " ");
    }
}

// ==================== Задача 3 ====================
// Извлекает только цифры из строки телефонного номера.
string extractDigits(const string& phone) {
    string digits;
    for (char c : phone) {
        // isdigit принимает int, поэтому приводим к unsigned char,
        // чтобы избежать неопределённого поведения для отрицательных char.
        if (isdigit(static_cast<unsigned char>(c))) {
            digits += c;
        }
    }
    return digits;
}

// Сравнивает два телефонных номера по их цифрам.
// Предполагается, что количество цифр одинаково, поэтому
// лексикографическое сравнение строк совпадает с числовым.
bool isLess(const string& phone1, const string& phone2) {
    string digits1 = extractDigits(phone1);
    string digits2 = extractDigits(phone2);
    return digits1 < digits2;
}

// Сортировка выбором для вектора телефонных номеров.
void selectionSort(vector<string>& phones) {
    int n = phones.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (isLess(phones[j], phones[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(phones[i], phones[minIndex]);
        }
    }
}

// Вывод списка телефонов.
void printPhones(const vector<string>& phones) {
    for (const string& phone : phones) {
        cout << phone << endl;
    }
}

void task3() {
    vector<string> phones = {
        "23-45-67",
        "12-34-56",
        "98-76-54",
        "11-22-33",
        "45-67-89",
        "34-56-78",
        "87-65-43",
        "10-20-30"
    };

    cout << "Исходный список телефонов:" << endl;
    printPhones(phones);

    selectionSort(phones);

    cout << "\nОтсортированный список телефонов:" << endl;
    printPhones(phones);
}

int main() {
    cout << "Задача 1" << endl;
    task1();
    cout << endl;

    cout << "Задача 2" << endl;
    task2();
    cout << endl;

    cout << "Задача 3" << endl;
    task3();
    cout << endl;

    return 0;
}