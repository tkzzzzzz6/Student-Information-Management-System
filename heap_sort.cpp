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
void heapSort(Student *head)
{
    // ����������
    int size = 0;
    Student *current = head;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }

    if (size == 0)
    {
        printf("û��ѧ�����ݣ�\n");
        return;
    }

    // ��������
    Student *arr = (Student *)malloc(size * sizeof(Student));
    if (!arr)
    {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    // �����������鲢�����ܳɼ�
    current = head;
    for (int i = 0; i < size; i++)
    {
        arr[i] = *current;
        arr[i].total_score = calculateTotalScore(&arr[i]);
        current = current->next;
    }

    // ������
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    // ����Ӷ�����ȡԪ��
    for (int i = size - 1; i > 0; i--)
    {
        // ����ǰ���ڵ��Ƶ�ĩβ
        Student temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // �Լ�С�Ķѽ��жѻ�
        heapify(arr, i, 0);
    }

    // ��ӡǰ10��ѧ��
    printf("\n========== ǰ10��ѧ���ɼ����� ==========\n");
    printf("����\t����\tѧ��\t�ܷ�\t����\tѡ��\t����\t����\n");
    printf("------------------------------------------------\n");

    int count = (size < 10) ? size : 10;
    for (int i = size - 1; i >= size - count; i--)
    {
        printf("%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",
               size - i,
               arr[i].name,
               arr[i].id,
               arr[i].total_score,
               arr[i].required_score,
               arr[i].elective_score,
               arr[i].second_score,
               arr[i].innovation_score);
        printf("------------------------------------------------\n");
    }

    // �ͷ��ڴ�
    free(arr);
}