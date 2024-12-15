// heap_sort.cpp
#include "heap_sort.h"
#include <stdio.h>
#include <stdlib.h>

// �����ܳɼ�
int calculateTotalScore(Student *student)
{
    return student->required_score +
           student->elective_score +
           student->second_score +
           student->innovation_score;
}

// �ѻ�����
void heapify(Student arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // ���㵱ǰ�ڵ�������ӽڵ���ܳɼ�
    int largest_score = calculateTotalScore(&arr[largest]);

    // ������ӽڵ���ڸ��ڵ�
    if (left < n)
    {
        int left_score = calculateTotalScore(&arr[left]);
        if (left_score > largest_score)
        {
            largest = left;
            largest_score = left_score;
        }
    }

    // ������ӽڵ�������ֵ
    if (right < n)
    {
        int right_score = calculateTotalScore(&arr[right]);
        if (right_score > largest_score)
        {
            largest = right;
        }
    }

    // ������ֵ���Ǹ��ڵ�
    if (largest != i)
    {
        Student temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // �ݹ�ѻ���Ӱ�������
        heapify(arr, n, largest);
    }
}

// ������������
void heapSort(StudentList* list)
{
    if (list->count == 0)
    {
        printf("û��ѧ�����ݣ�\n");
        return;
    }

    // ��������
    Student* arr = (Student*)malloc(list->count * sizeof(Student));
    if (!arr)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // ������������
    Student* current = list->head;
    int i = 0;
    while (current != NULL && i < list->count)
    {
        arr[i] = *current;
        current = current->next;
        i++;
    }

    // ��������
    for (int i = list->count / 2 - 1; i >= 0; i--)
    {
        heapify(arr, list->count, i);
    }

    // ����Ӷ�����ȡԪ��
    for (int i = list->count - 1; i > 0; i--)
    {
        // ����ǰ���ڵ㣨���ֵ���Ƶ�ĩβ
        Student temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // �Լ�С�Ķѽ��жѻ�
        heapify(arr, i, 0);
    }

    // ��ӡ��������ǰ10����
    printf("\n=== �ɼ�������ǰ10����===\n");
    printf("����\tѧ��\t\t����\t�ܳɼ�\t����\tѡ��\t����\t����\n");
    
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

    // ���������е�˳��
    current = list->head;
    for (i = list->count - 1; i >= 0; i--)
    {
        if (current != NULL)
        {
            *current = arr[i];
            current = current->next;
        }
    }

    // �ͷ���ʱ����
    free(arr);
    printf("\n������ɣ�\n");
}