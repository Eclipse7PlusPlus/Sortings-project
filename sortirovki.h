#ifndef SORTIROVKI_H
#define SORTIROVKI_H

#include <iostream>
#include <string>

struct Student {
    int course;
    int group;
    std::string name;
    int grades[3];
    
    Student() : course(0), group(0), name("") { grades[0] = grades[1] = grades[2] = 0; }
    Student(int c, int g, const std::string& n, int g1, int g2, int g3) 
        : course(c), group(g), name(n) { grades[0] = g1; grades[1] = g2; grades[2] = g3; }
    
    double Average() const { return (grades[0] + grades[1] + grades[2]) / 3.0; }
    int getCourse() const { return course; }
    int getGroup() const { return group; }
    std::string getName() const { return name; }
    
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>=(const Student& other) const;
};

std::ostream& operator<<(std::ostream& os, const Student& s);
std::istream& operator>>(std::istream& is, Student& s);

// Функции меню
void MenuInterface();
void MenuWorkTask();
void showSortMenu();
void showCriteriaMenu();
void showStudentCriteriaMenu();

template <typename T>
void BubbleSort(T* array, int32_t size, bool ascending);

template <typename T>
void ShakerSort(T* array, int32_t size, bool ascending);

template <typename T>
void CombSort(T* array, int32_t size, bool ascending);

template <typename T>
void InsertionSort(T* array, int32_t size, bool ascending);

template <typename T>
void SelectionSort(T* array, int32_t size, bool ascending);

template <typename T>
void QuickSort(T* array, int32_t size, bool ascending);

template <typename T>
void MergeSort(T* array, int32_t size, bool ascending);

template <typename T>
void HeapSort(T* array, int32_t size, bool ascending);

template <typename T>
void BogoSort(T* array, int32_t size, bool ascending);

template <typename T>
void CountSort(T* array, int32_t size, bool ascending);

template <>
void CountSort<int>(int* array, int32_t size, bool ascending);

template <>
void CountSort<char>(char* array, int32_t size, bool ascending);

template <>
void CountSort<Student>(Student* array, int32_t size, bool ascending);

template <>
void CountSort<double>(double* array, int32_t size, bool ascending);

// Вспомогательные функции
template <typename T>
void printArray(T* arr, int32_t size);

template <typename T>
void printStep(T* arr, int32_t size, int32_t step, const std::string& message);

void manualStudentInput(Student*& array, int32_t size);
void randomStudentInput(Student*& array, int32_t size);
void sortStudentsByAverage(Student* array, int32_t size, bool ascending);
void sortStudentsByName(Student* array, int32_t size, bool ascending);

void ResultMenu();

#endif
