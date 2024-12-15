// heap_sort.cpp
#include "heap_sort.h"
#include <stdio.h>
#include <stdlib.h>

// 计算总成绩
int calculateTotalScore(Student *student)
{
    return student->required_score +
           student->elective_score +
           student->second_score +
           student->innovation_score;
}

// 堆化函数
void heapify(Student arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 计算当前节点和左右子节点的总成绩
    int largest_score = calculateTotalScore(&arr[largest]);

    // 如果左子节点大于根节点
    if (left < n)
    {
        int left_score = calculateTotalScore(&arr[left]);
        if (left_score > largest_score)
        {
            largest = left;
            largest_score = left_score;
        }
    }

    // 如果右子节点大于最大值
    if (right < n)
    {
        int right_score = calculateTotalScore(&arr[right]);
        if (right_score > largest_score)
        {
            largest = right;
        }
    }

    // 如果最大值不是根节点
    if (largest != i)
    {
        Student temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 递归堆化受影响的子树
        heapify(arr, n, largest);
    }
}

// 堆排序主函数
void heapSort(StudentList* list)
{
    if (list->count == 0)
    {
        printf("没有学生数据！\n");
        return;
    }

    // 创建数组
    Student* arr = (Student*)malloc(list->count * sizeof(Student));
    if (!arr)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 复制链表到数组
    Student* current = list->head;
    int i = 0;
    while (current != NULL && i < list->count)
    {
        arr[i] = *current;
        current = current->next;
        i++;
    }

    // 构建最大堆
    for (int i = list->count / 2 - 1; i >= 0; i--)
    {
        heapify(arr, list->count, i);
    }

    // 逐个从堆中提取元素
    for (int i = list->count - 1; i > 0; i--)
    {
        // 将当前根节点（最大值）移到末尾
        Student temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 对减小的堆进行堆化
        heapify(arr, i, 0);
    }

    // 打印排序结果（前10名）
    printf("\n=== 成绩排名（前10名）===\n");
    printf("排名\t学号\t\t姓名\t总成绩\t必修\t选修\t二课\t创新\n");
    
    int display_count = list->count < 10 ? list->count : 10;
    for (i = list->count - 1; i >= list->count - display_count; i--)
    {
        printf("%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",
               list->count - i,
               arr[i].id,
               arr[i].name,
               calculateTotalScore(&arr[i]),
               arr[i].required_score,
               arr[i].elective_score,
               arr[i].second_score,
               arr[i].innovation_score);
    }

    // 更新链表中的顺序
    current = list->head;
    for (i = list->count - 1; i >= 0; i--)
    {
        if (current != NULL)
        {
            *current = arr[i];
            current = current->next;
        }
    }

    // 释放临时数组
    free(arr);
    printf("\n排序完成！\n");
}