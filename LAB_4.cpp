#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

// ==================== Задача 1 ====================
// Задана последовательность из 1000 целых чисел.
// Переставить элементы так, чтобы они располагались по возрастанию.
// Используем стандартную сортировку std::sort.
void task1() {
    const int SIZE = 1000;
    vector<int> sequence(SIZE);

    // Генерация 1000 случайных целых чисел (диапазон не указан, выберем 1..10000)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10000);

    for (int i = 0; i < SIZE; i++) {
        sequence[i] = dist(gen);
    }

    cout << "Первые 10 элементов до сортировки: ";
    for (int i = 0; i < 10; i++) cout << sequence[i] << " ";
    cout << "..." << endl;

    // Сортировка по возрастанию
    sort(sequence.begin(), sequence.end());

    cout << "Первые 10 элементов после сортировки: ";
    for (int i = 0; i < 10; i++) cout << sequence[i] << " ";
    cout << "..." << endl;

    cout << "Последние 10 элементов после сортировки: ";
    for (int i = SIZE - 10; i < SIZE; i++) cout << sequence[i] << " ";
    cout << endl;
}

// ==================== Задача 2 ====================
// Сортировка одномерного массива случайных целых чисел из интервала {50, 100}
// по возрастанию с использованием быстрой сортировки (quicksort).

// Функция разделения (partition) для quicksort.
// Выбираем опорный элемент — последний в диапазоне.
// Все элементы меньше опорного перемещаем влево, больше — вправо.
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // опорный элемент
    int i = low - 1;       // индекс для меньших элементов

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1; // возвращаем индекс опорного элемента
}

// Рекурсивная быстрая сортировка
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void task2() {
    const int SIZE = 15; // для наглядности возьмём 15 элементов
    int arr[SIZE];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(50, 100); // интервал {50, 100} включительно

    cout << "Исходный массив: ";
    for (int i = 0; i < SIZE; i++) {
        arr[i] = dist(gen);
        cout << arr[i] << " ";
    }
    cout << endl;

    quickSort(arr, 0, SIZE - 1);

    cout << "Отсортированный массив по возрастанию: ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ==================== Задача 3 ====================
// Сортировка по возрастанию первого столбца двумерного массива целых чисел
// с использованием быстрой сортировки. Массив заполняется случайными числами
// из интервала {5, 61}.

void task3() {
    const int ROWS = 6;
    const int COLS = 5;
    int matrix[ROWS][COLS];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(5, 61); // интервал {5, 61} включительно

    // Заполнение матрицы случайными числами
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = dist(gen);
        }
    }

    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Извлекаем первый столбец в отдельный массив
    int firstCol[ROWS];
    for (int i = 0; i < ROWS; i++) {
        firstCol[i] = matrix[i][0];
    }

    // Сортируем первый столбец с помощью быстрой сортировки
    quickSort(firstCol, 0, ROWS - 1);

    // Записываем отсортированные значения обратно в первый столбец
    for (int i = 0; i < ROWS; i++) {
        matrix[i][0] = firstCol[i];
    }

    cout << "\nМатрица после сортировки первого столбца по возрастанию:" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// ==================== Задача 4 ====================
// Сортировка списка студентов группы по алфавиту
// с использованием стандартной функции qsort.

struct Student {
    char name[50];
    int age;
};

// Функция сравнения для qsort.
// Принимает указатели на элементы массива (в данном случае на Student).
// Возвращает отрицательное число, если первый студент должен идти раньше,
// положительное — если позже, и 0 — если имена равны.
int compareStudents(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return strcmp(s1->name, s2->name); // лексикографическое сравнение строк
}

void task4() {
    const int SIZE = 6;
    Student group[SIZE] = {
        {"Иванов", 19},
        {"Петров", 18},
        {"Сидоров", 20},
        {"Алексеев", 19},
        {"Николаев", 18},
        {"Борисов", 20}
    };

    cout << "Список студентов до сортировки:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << group[i].name << " (" << group[i].age << " лет)" << endl;
    }

    // qsort(указатель на массив, количество элементов, размер элемента, функция сравнения)
    qsort(group, SIZE, sizeof(Student), compareStudents);

    cout << "\nСписок студентов после сортировки по алфавиту:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << group[i].name << " (" << group[i].age << " лет)" << endl;
    }
}

int main() {
    // Настройка локали для корректного вывода кириллицы (опционально)
    setlocale(LC_ALL, "Russian");

    cout << "Задача 1" << endl;
    task1();
    cout << endl;

    cout << "Задача 2" << endl;
    task2();
    cout << endl;

    cout << "Задача 3" << endl;
    task3();
    cout << endl;

    cout << "Задача 4" << endl;
    task4();
    cout << endl;

    return 0;
}