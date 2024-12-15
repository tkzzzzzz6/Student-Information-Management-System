#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "function.h"

// 堆排序相关函数声明
void heapSort(StudentList* list);
void heapify(Student arr[], int n, int i);

#endif // HEAP_SORT_H