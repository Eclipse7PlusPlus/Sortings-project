#include "sortirovki.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>

void MenuInterface() {
    std::cout << "Menu" << std::endl;
    std::cout << "1. Ввод и запись в текстовый файл" << std::endl;
    std::cout << "2. Использование датчика случайных чисел и запись в текстовый файл" << std::endl;
    std::cout << "3. Ввод из текстового файла и вывод на консоль" << std::endl;
    std::cout << "11. Выход" << std::endl;
    std::cout << "Введите номер задания: ";
}

void MenuWorkTask() {
    std::cout << "Menu" << std::endl;
    std::cout << "1. Работа со студентами" << std::endl;
    std::cout << "2. Работа с дробными числами" << std::endl;
    std::cout << "3. Работа с целочисленными данными" << std::endl;
    std::cout << "4. Работа с символами" << std::endl;
    std::cout << "Введите номер задания: ";
}

void showSortMenu() {
    std::cout << "\n ВЫБОР СОРТИРОВКИ " << std::endl;
    std::cout << "1. Сортировка пузырьком" << std::endl;
    std::cout << "2. Шейкерная сортировка" << std::endl;
    std::cout << "3. Сортировка расческой" << std::endl;
    std::cout << "4. Сортировка вставками" << std::endl;
    std::cout << "5. Сортировка выбором" << std::endl;
    std::cout << "6. Быстрая сортировка" << std::endl;
    std::cout << "7. Сортировка слиянием" << std::endl;
    std::cout << "8. Пирамидальная сортировка" << std::endl;
    std::cout << "9. BogoSort" << std::endl;
    std::cout << "10. Сортировка подсчетом" << std::endl;
    std::cout << "11. Назад" << std::endl;
    std::cout << "Выберите сортировку: ";
}

void showCriteriaMenu() {
    std::cout << "\n КРИТЕРИЙ СОРТИРОВКИ " << std::endl;
    std::cout << "1. По возрастанию" << std::endl;
    std::cout << "2. По убыванию" << std::endl;
    std::cout << "Выберите критерий: ";
}

void showStudentCriteriaMenu() {
    std::cout << "\n КРИТЕРИЙ СОРТИРОВКИ СТУДЕНТОВ " << std::endl;
    std::cout << "1. По курсу, группе и имени" << std::endl;
    std::cout << "2. По среднему баллу (по убыванию)" << std::endl;
    std::cout << "3. По имени" << std::endl;
    std::cout << "4. Сортировка подсчетом (по курсу)" << std::endl;
    std::cout << "Выберите критерий: ";
}

// ПЕРЕГРУЗКИ ОПЕРАТОРОВ КЛАССА СТУДЕНТ
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.course << " " << s.group << " " << s.name << " " 
       << s.grades[0] << " " << s.grades[1] << " " << s.grades[2];
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    is >> s.course >> s.group;
    is.ignore();
    std::getline(is, s.name);
    is >> s.grades[0] >> s.grades[1] >> s.grades[2];
    return is;
}

bool Student::operator<(const Student& other) const {
    if (course != other.course) 
    {return course < other.course;}
    if (group != other.group) 
    {return group < other.group;}
    {return name < other.name;}
}

bool Student::operator>(const Student& other) const {
    return other < *this;
}

bool Student::operator<=(const Student& other) const {
    return !(*this > other);
}

bool Student::operator>=(const Student& other) const {
    return !(*this < other);
}

template <typename T>
void writeArrayToFile(const std::string& filename, T* array, int32_t size) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }
    
    file << size << std::endl;
    for (int32_t i = 0; i < size; ++i) {
        file << array[i] << std::endl;
    }
    file.close();
}

template <>
void writeArrayToFile<Student>(const std::string& filename, Student* array, int32_t size) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }
    
    file << size << std::endl;
    for (int32_t i = 0; i < size; ++i) {
        file << array[i] << std::endl;
    }
    file.close();
}

template <typename T>
bool readArrayFromFile(const std::string& filename, T*& array, int32_t& size) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла для чтения!" << std::endl;
        return false;
    }
    
    file >> size;
    array = new T[size];
    
    for (int32_t i = 0; i < size; ++i) {
        file >> array[i];
    }
    file.close();
    return true;
}

template <>
bool readArrayFromFile<Student>(const std::string& filename, Student*& array, int32_t& size) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла для чтения!" << std::endl;
        return false;
    }
    
    file >> size;
    array = new Student[size];
    
    for (int32_t i = 0; i < size; ++i) {
        file >> array[i];
    }
    file.close();
    return true;
}

// БАБЛ СОРТ
template <typename T>
void BubbleSort(T* array, int32_t size, bool ascending) {
    for(int32_t i = 0; i < size - 1; ++i) {
        for(int32_t j = 0; j < size - i - 1; ++j) {
            bool condition = ascending ? 
                array[j] > array[j + 1] : 
                array[j] < array[j + 1];
                
            if(condition) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

// ШЕЙКЕРНАЯ СОРТИРОВКА
template <typename T>
void ShakerSort(T* array, int32_t size, bool ascending) {
    int left = 0;
    int right = size - 1;
    bool swapped = true;
    
    while (swapped) {
        swapped = false;
        for(int32_t i = left; i < right; ++i) {
            bool condition = ascending ? 
                array[i] > array[i + 1] : 
                array[i] < array[i + 1];
                
            if(condition) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break;
        
        right--;
        swapped = false;
        
        for(int32_t i = right; i > left; --i) {
            bool condition = ascending ? 
                array[i] < array[i - 1] : 
                array[i] > array[i - 1];
                
            if(condition) {
                std::swap(array[i], array[i - 1]);
                swapped = true;
            }
        }
        left++;
    }
}

template <typename T>
void CombSort(T* array, int32_t size, bool ascending) {
    int32_t gap = size;
    bool swapped = true;
    
    while (gap > 1 || swapped) {
        gap = std::max(1, (int)(gap / 1.247));
        swapped = false;
        
        for(int32_t i = 0; i < size - gap; ++i) {
            bool condition = ascending ? 
                array[i] > array[i + gap] : 
                array[i] < array[i + gap];
                
            if(condition) {
                std::swap(array[i], array[i + gap]);
                swapped = true;
            }
        }
    }
}

// СОРТИРОВКА ВСТАВКАМИ
template <typename T>
void InsertionSort(T* array, int32_t size, bool ascending) {
    for(int32_t i = 1; i < size; ++i) {
        T key = array[i];
        int32_t j = i - 1;
        
        while (j >= 0 && (ascending ? array[j] > key : array[j] < key)) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

// СОРТИРОВКА ВЫБОРОМ
template <typename T>
void SelectionSort(T* array, int32_t size, bool ascending) {
    for(int32_t i = 0; i < size - 1; ++i) {
        int32_t extreme_index = i;
        for (int32_t j = i + 1; j < size; ++j) {
            bool condition = ascending ? 
                array[j] < array[extreme_index] : 
                array[j] > array[extreme_index];
                
            if(condition) {
                extreme_index = j;
            }
        }
        if(extreme_index != i) {
            std::swap(array[extreme_index], array[i]);
        }
    }
}

// БЫСТРАЯ СОРТИРОВКА
template <typename T>
void QuickSortHelper(T* array, int32_t low, int32_t high, bool ascending) {
    if (low < high) {
        T pivot = array[high];
        int32_t i = low - 1;
        
        for (int32_t j = low; j < high; ++j) {
            bool condition = ascending ? 
                array[j] <= pivot : 
                array[j] >= pivot;
                
            if (condition) {
                ++i;
                std::swap(array[i], array[j]);
            }
        }
        
        std::swap(array[i + 1], array[high]);
        int32_t pi = i + 1;
        
        QuickSortHelper(array, low, pi - 1, ascending);
        QuickSortHelper(array, pi + 1, high, ascending);
    }
}

template <typename T>
void QuickSort(T* array, int32_t size, bool ascending) {
    QuickSortHelper(array, 0, size - 1, ascending);
}

// СОРТИРОВКА СЛИЯНИЕМ
template <typename T>
void Merge(T* array, int32_t left, int32_t mid, int32_t right, bool ascending) {
    int32_t n1 = mid - left + 1;
    int32_t n2 = right - mid;

    T* left_arr = new T[n1];
    T* right_arr = new T[n2];

    for (int32_t i = 0; i < n1; ++i) {
        left_arr[i] = array[left + i];
    }

    for (int32_t j = 0; j < n2; ++j) {
        right_arr[j] = array[mid + 1 + j];
    }

    int32_t i = 0;
    int32_t j = 0;
    int32_t k = left;
    
    while (i < n1 && j < n2) {
        bool condition = ascending ? 
            left_arr[i] <= right_arr[j] : 
            left_arr[i] >= right_arr[j];
            
        if (condition) {
            array[k] = left_arr[i];
            ++i;
        } else {
            array[k] = right_arr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        array[k] = left_arr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        array[k] = right_arr[j];
        j++;
        k++;
    }
    
    delete[] left_arr;
    delete[] right_arr;
}

template <typename T>
void MergeSortHelper(T* array, int32_t left, int32_t right, bool ascending) {
    if (left < right) {
        int32_t mid = left + (right - left) / 2;
        
        MergeSortHelper(array, left, mid, ascending);
        MergeSortHelper(array, mid + 1, right, ascending);
        
        Merge(array, left, mid, right, ascending);
    }
}

template <typename T>
void MergeSort(T* array, int32_t size, bool ascending) {
    MergeSortHelper(array, 0, size - 1, ascending);
}

// СОРТИРОВКА КУЧЕЙ
template <typename T>
void heapify(T* array, int32_t size, int32_t root, bool ascending) {
    int32_t extreme = root;
    int32_t left = 2 * root + 1;
    int32_t right = 2 * root + 2;

    if (left < size) {
        bool left_condition = ascending ? 
            array[left] > array[extreme] : 
            array[left] < array[extreme];
            
        if (left_condition) {
            extreme = left;
        }
    }

    if (right < size) {
        bool right_condition = ascending ? 
            array[right] > array[extreme] : 
            array[right] < array[extreme];
            
        if (right_condition) {
            extreme = right;
        }
    }

    if (extreme != root) {
        std::swap(array[root], array[extreme]);
        heapify(array, size, extreme, ascending);
    }
}

template <typename T>
void HeapSort(T* array, int32_t size, bool ascending) {
    for (int32_t i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i, ascending);
    }

    for (int32_t i = size - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0, ascending);
    }
}

template <typename T>
bool isSorted(T* array, int32_t size, bool ascending) {
    if (ascending) {
        for (int32_t i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) return false;
        }
    } else {
        for (int32_t i = 0; i < size - 1; i++) {
            if (array[i] < array[i + 1]) return false;
        }
    }
    return true;
}
// РАНДОМНАЯ СОРТИРОВКА
template <typename T>
void shuffle(T* array, int32_t size) {
    for (int32_t i = 0; i < size; i++) {
        int32_t j = rand() % size;
        std::swap(array[i], array[j]);
    }
}

template <typename T>
void BogoSort(T* array, int32_t size, bool ascending) {
    srand(time(0));
    int32_t step = 0;
    
    while (!isSorted(array, size, ascending)) {
        shuffle(array, size);
        step++;
        
    }
}

// СОРТИРОВКА ПОДСЧЕТОМ
template <>
void CountSort<int>(int* array, int32_t size, bool ascending) {
    if (size == 0) return;
    
    int min_val = array[0];
    int max_val = array[0];
    
    for(int32_t i = 1; i < size; ++i) {
        if(array[i] < min_val) min_val = array[i];
        if(array[i] > max_val) max_val = array[i];
    }
    
    int range = max_val - min_val + 1;
    int* count = new int[range]();
    
    for(int32_t i = 0; i < size; ++i) {
        count[array[i] - min_val]++;
    }
    
    int index = 0;
    if (ascending) {
        for(int32_t i = 0; i < range; ++i) {
            while(count[i] > 0) {
                array[index++] = i + min_val;
                count[i]--;
            }
        }
    } else {
        for(int32_t i = range - 1; i >= 0; --i) {
            while(count[i] > 0) {
                array[index++] = i + min_val;
                count[i]--;
            }
        }
    }
    
    delete[] count;
}

template <>
void CountSort<char>(char* array, int32_t size, bool ascending) {
    if (size == 0) return;
    
    const int range = 256;
    int* count = new int[range]();
    
    for(int32_t i = 0; i < size; ++i) {
        count[static_cast<unsigned char>(array[i])]++;
    }
    
    int index = 0;
    if (ascending) {
        for(int32_t i = 0; i < range; ++i) {
            while(count[i] > 0) {
                array[index++] = static_cast<char>(i);
                count[i]--;
            }
        }
    } else {
        for(int32_t i = range - 1; i >= 0; --i) {
            while(count[i] > 0) {
                array[index++] = static_cast<char>(i);
                count[i]--;
            }
        }
    }
    
    delete[] count;
}


template <>
void CountSort<Student>(Student* array, int32_t size, bool ascending) {
    if (size == 0) return;
    
    int min_course = array[0].course;
    int max_course = array[0].course;
    
    for(int32_t i = 1; i < size; ++i) {
        if(array[i].course < min_course) min_course = array[i].course;
        if(array[i].course > max_course) max_course = array[i].course;
    }
    
    int range = max_course - min_course + 1;
    int* count = new int[range]();
    
    for(int32_t i = 0; i < size; ++i) {
        count[array[i].course - min_course]++;
    }
    
    Student* temp = new Student[size];
    int index = 0;
    
    if (ascending) {
        for(int32_t i = 0; i < range; ++i) {
            for(int32_t j = 0; j < size; ++j) {
                if(array[j].course == i + min_course) {
                    temp[index++] = array[j];
                }
            }
        }
    } else {
        for(int32_t i = range - 1; i >= 0; --i) {
            for(int32_t j = 0; j < size; ++j) {
                if(array[j].course == i + min_course) {
                    temp[index++] = array[j];
                }
            }
        }
    }
    
    for(int32_t i = 0; i < size; ++i) {
        array[i] = temp[i];
    }
    
    delete[] count;
    delete[] temp;
}

template <>
void CountSort<double>(double* array, int32_t size, bool ascending) {
    std::cout << "Сортировка подсчетом не поддерживается для double. Используется быстрая сортировка." << std::endl;
    QuickSort(array, size, ascending);
}

template <typename T>
void printArray(T* arr, int32_t size) {
    std::cout << "\n=== МАССИВ (" << size << " элементов) ===" << std::endl;
    for (int32_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
        if ((i + 1) % 10 == 0) 
        {
        std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void printArray(void* arr, int32_t size, int dataType) {
    switch(dataType) {
        case 1: printArray(static_cast<Student*>(arr), size); break;
        case 2: printArray(static_cast<double*>(arr), size); break;
        case 3: printArray(static_cast<int*>(arr), size); break;
        case 4: printArray(static_cast<char*>(arr), size); break;
    }
}

void manualStudentInput(Student*& array, int32_t size) {
    array = new Student[size];
    for (int32_t i = 0; i < size; i++) {
        std::cout << "Студент " << i + 1 << ":" << std::endl;
        std::cout << "Введите курс: ";
        std::cin >> array[i].course;
        std::cout << "Введите группу: ";
        std::cin >> array[i].group;
        std::cout << "Введите имя: ";
        std::cin.ignore();
        std::getline(std::cin, array[i].name);
        std::cout << "Введите 3 оценки: ";
        std::cin >> array[i].grades[0] >> array[i].grades[1] >> array[i].grades[2];
    }
}

void randomStudentInput(Student*& array, int32_t size) {
    array = new Student[size];
    srand(time(0));
    
    std::string names[] = {"Иванов", "Петров", "Мирин", "Дегтярев", "Мазуров"};
    std::string firstNames[] = {"Иван", "Петр", "Алексей", "Дмитрий", "Сергей"};
    
    for (int32_t i = 0; i < size; i++) {
        int course = 1 + rand() % 4;
        int group = 100 + rand() % 10;
        std::string name = names[rand() % 5] + " " + firstNames[rand() % 5];
        int g1 = 3 + rand() % 3;
        int g2 = 3 + rand() % 3;
        int g3 = 3 + rand() % 3;
        
        array[i] = Student(course, group, name, g1, g2, g3);
    }
}

void sortStudentsByAverage(Student* array, int32_t size, bool ascending) {
    for (int32_t i = 0; i < size - 1; i++) {
        for (int32_t j = 0; j < size - i - 1; j++) {
            bool condition = ascending ? 
                array[j].Average() > array[j + 1].Average() :
                array[j].Average() < array[j + 1].Average();
                
            if (condition) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

void sortStudentsByName(Student* array, int32_t size, bool ascending) {
    for (int32_t i = 0; i < size - 1; i++) {
        for (int32_t j = 0; j < size - i - 1; j++) {
            bool condition = ascending ? 
                array[j].name > array[j + 1].name :
                array[j].name < array[j + 1].name;
                
            if (condition) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

void ResultMenu() {
    int choice;
    int32_t size = 0;
    void* currentArray = nullptr;
    int dataType = 0;

    do {     
        MenuInterface();
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                std::cout << "Введите размер массива: ";
                std::cin >> size;
                
                MenuWorkTask();
                std::cin >> dataType;
                
                switch(dataType) {
                    case 1: {
                        Student* students = nullptr;
                        manualStudentInput(students, size);
                        currentArray = students;
                        break;
                    }
                    case 2: {
                        double* doubles = new double[size];
                        std::cout << "Введите " << size << " дробных чисел:" << std::endl;
                        for(int32_t i = 0; i < size; i++) {
                            std::cout << "Элемент " << i + 1 << ": ";
                            std::cin >> doubles[i];
                        }
                        currentArray = doubles;
                        break;
                    }
                    case 3: {
                        int* ints = new int[size];
                        std::cout << "Введите " << size << " целых чисел:" << std::endl;
                        for(int32_t i = 0; i < size; i++) {
                            std::cout << "Элемент " << i + 1 << ": ";
                            std::cin >> ints[i];
                        }
                        currentArray = ints;
                        break;
                    }
                    case 4: {
                        char* chars = new char[size];
                        std::cout << "Введите " << size << " символов:" << std::endl;
                        for(int32_t i = 0; i < size; i++) {
                            std::cout << "Элемент " << i + 1 << ": ";
                            std::cin >> chars[i];
                        }
                        currentArray = chars;
                        break;
                    }
                }
                
                std::string filename;
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> filename;
                
                switch(dataType) {
                    case 1: writeArrayToFile(filename, static_cast<Student*>(currentArray), size); break;
                    case 2: writeArrayToFile(filename, static_cast<double*>(currentArray), size); break;
                    case 3: writeArrayToFile(filename, static_cast<int*>(currentArray), size); break;
                    case 4: writeArrayToFile(filename, static_cast<char*>(currentArray), size); break;
                }
                
                std::cout << "Массив записан в файл: " << filename << std::endl;
                break;
            }
            case 2: {
                std::cout << "Введите размер массива: ";
                std::cin >> size;
                
                MenuWorkTask();
                std::cin >> dataType;
                
                switch(dataType) {
                    case 1: {
                        Student* students = nullptr;
                        randomStudentInput(students, size);
                        currentArray = students;
                        break;
                    }
                    case 2: {
                        double min, max;
                        std::cout << "Введите диапазон (min max): ";
                        std::cin >> min >> max;
                        double* doubles = new double[size];
                        srand(time(0));
                        for(int32_t i = 0; i < size; i++) {
                            doubles[i] = min + static_cast<double>(rand()) / RAND_MAX * (max - min);
                        }
                        currentArray = doubles;
                        break;
                    }
                    case 3: {
                        int start, end;
                        std::cout << "Введите начало и конец диапазона: ";
                        std::cin >> start >> end;
                        int* ints = new int[size];
                        srand(time(0));
                        for(int32_t i = 0; i < size; i++) {
                            ints[i] = start + rand() % (end - start + 1);
                        }
                        currentArray = ints;
                        break;
                    }
                    case 4: {
                        char* chars = new char[size];
                        srand(time(0));
                        for(int32_t i = 0; i < size; i++) {
                            chars[i] = 'A' + rand() % 26;
                        }
                        currentArray = chars;
                        break;
                    }
                }
                
                std::string filename;
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> filename;
                
                switch(dataType) {
                    case 1: writeArrayToFile(filename, static_cast<Student*>(currentArray), size); break;
                    case 2: writeArrayToFile(filename, static_cast<double*>(currentArray), size); break;
                    case 3: writeArrayToFile(filename, static_cast<int*>(currentArray), size); break;
                    case 4: writeArrayToFile(filename, static_cast<char*>(currentArray), size); break;
                }
                
                std::cout << "Массив записан в файл: " << filename << std::endl;
                break;
            }
            case 3: {
                std::string filename;
                std::cout << "Введите название файла: ";
                std::cin >> filename;
                
                MenuWorkTask();
                std::cin >> dataType;
                
                bool success = false;
                switch(dataType) {
                    case 1: {
                        Student* students = nullptr;
                        success = readArrayFromFile(filename, students, size);
                        currentArray = students;
                        break;
                    }
                    case 2: {
                        double* doubles = nullptr;
                        success = readArrayFromFile(filename, doubles, size);
                        currentArray = doubles;
                        break;
                    }
                    case 3: {
                        int* ints = nullptr;
                        success = readArrayFromFile(filename, ints, size);
                        currentArray = ints;
                        break;
                    }
                    case 4: {
                        char* chars = nullptr;
                        success = readArrayFromFile(filename, chars, size);
                        currentArray = chars;
                        break;
                    }
                }
                
                if (success) {
                    std::cout << "Массив загружен из файла: " << filename << std::endl;
                    printArray(currentArray, size, dataType);
                } else {
                    std::cout << "Ошибка загрузки файла!" << std::endl;
                }
                break;
            }
            case 11: {
                std::cout << "Выход из программы." << std::endl;
                break;
            }
            default: {
                std::cout << "Ошибка! Неверный выбор." << std::endl;
            }
        }
        
        if (currentArray != nullptr && size > 0 && choice != 11) {
            showSortMenu();
            int sortChoice;
            std::cin >> sortChoice;
            
            if (sortChoice != 11) {
                bool ascending = true;
                if (dataType != 1) { 
                    showCriteriaMenu();
                    int criteria;
                    std::cin >> criteria;
                    ascending = (criteria == 1);
                } else { 
                    showStudentCriteriaMenu();
                    int criteria;
                    std::cin >> criteria;
                    
                    
                    if (criteria == 2) {
                        sortStudentsByAverage(static_cast<Student*>(currentArray), size, false);
                        std::cout << "Сортировка по среднему баллу завершена!" << std::endl;
                        continue;
                    } else if (criteria == 3) {
                        sortStudentsByName(static_cast<Student*>(currentArray), size, true);
                        std::cout << "Сортировка по имени завершена!" << std::endl;
                        continue;
                    } else if (criteria == 4) {
                        CountSort(static_cast<Student*>(currentArray), size, true);
                        std::cout << "Сортировка подсчетом по курсу завершена!" << std::endl;
                        continue;
                    } else {
                        ascending = true; 
                    }
                }
                
                // Применение выбранной сортировки
                switch(sortChoice) {
                    case 1: 
                        switch(dataType) {
                            case 1: BubbleSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: BubbleSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: BubbleSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: BubbleSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 2: 
                        switch(dataType) {
                            case 1: ShakerSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: ShakerSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: ShakerSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: ShakerSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 3: 
                        switch(dataType) {
                            case 1: CombSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: CombSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: CombSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: CombSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 4: 
                        switch(dataType) {
                            case 1: InsertionSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: InsertionSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: InsertionSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: InsertionSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 5: 
                        switch(dataType) {
                            case 1: SelectionSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: SelectionSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: SelectionSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: SelectionSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 6: 
                        switch(dataType) {
                            case 1: QuickSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: QuickSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: QuickSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: QuickSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 7: 
                        switch(dataType) {
                            case 1: MergeSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: MergeSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: MergeSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: MergeSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 8: 
                        switch(dataType) {
                            case 1: HeapSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: HeapSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: HeapSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: HeapSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 9: 
                        switch(dataType) {
                            case 1: BogoSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: BogoSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: BogoSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: BogoSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                    case 10: 
                        switch(dataType) {
                            case 1: CountSort(static_cast<Student*>(currentArray), size, ascending); break;
                            case 2: CountSort(static_cast<double*>(currentArray), size, ascending); break;
                            case 3: CountSort(static_cast<int*>(currentArray), size, ascending); break;
                            case 4: CountSort(static_cast<char*>(currentArray), size, ascending); break;
                        }
                        break;
                }
                
                std::cout << "Сортировка завершена!" << std::endl;
                printArray(currentArray, size, dataType);
            }
        }
        
    } while(choice != 11);
    
    if (currentArray != nullptr) {
        switch(dataType) {
            case 1: delete[] static_cast<Student*>(currentArray); break;
            case 2: delete[] static_cast<double*>(currentArray); break;
            case 3: delete[] static_cast<int*>(currentArray); break;
            case 4: delete[] static_cast<char*>(currentArray); break;
        }
    }
}

