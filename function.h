#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <time.h>

// ����ѧ���ṹ��
typedef struct Student
{
    char department[50];  // ϵ��
    char grade[10];       // �꼶
    char class_name[20];  // �༶
    char id[20];          // ѧ��
    char name[50];        // ����
    char gender[10];      // �Ա�
    char birth_date[20];  // ����������
    char major[50];       // רҵ
    char education[20];   // �������
    int years;            // ѧ��
    char campus[20];      // У��
    int required_score;   // ���޳ɼ�
    int elective_score;   // ѡ�޳ɼ�
    int second_score;     // ���γɼ�
    int innovation_score; // ���´�ҵ�ɼ�
    int total_score;      // �ܳɼ�
    struct Student *next;
} Student;

// ����µ��������ṹ
typedef struct {
    Student* head;    // ָ������ͷ��
    Student* tail;    // ָ������β��
    int count;        // ��¼ѧ������
} StudentList;

// ��������
StudentList* initStudentList();
void addStudent(StudentList* list, Student* newStudent);
void printStudent(const Student *student);
Student* findStudentById(StudentList* list, const char *id);
Student* findStudentByName(StudentList* list, const char *name);
void modifyStudent(Student *student);
void saveStudentsToFile(StudentList* list, const char *filename);
void loadStudentsFromFile(StudentList* list, const char *filename);
int importStudentsFromCSV(StudentList* list, const char *filename);
void drawHistogram(StudentList* list, int score_type);
void batchModifyStudents(StudentList* list, const char *condition_field, const char *condition_value,
                        const char *modify_field, const char *new_value);
void batchModifyScores(StudentList* list, const char *condition_field, const char *condition_value,
                      int score_type, int new_score);
void freeStudentList(StudentList* list);

#endif // FUNCTION_H