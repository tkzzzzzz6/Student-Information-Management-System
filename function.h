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

// ��������
Student *createStudent(const char *department, const char *grade, const char *class_name,
                       const char *id, const char *name, const char *gender,
                       const char *birth_date, const char *major, const char *education,
                       int years, const char *campus, int required_score,
                       int elective_score, int second_score, int innovation_score);
void addStudent(Student **head, Student *newStudent);
void printStudent(const Student *student);
Student *findStudentById(Student *head, const char *id);
Student *findStudentByName(Student *head, const char *name);
void modifyStudent(Student *student);
void saveStudentsToFile(Student *head, const char *filename);
void loadStudentsFromFile(Student **head, const char *filename);
int importStudentsFromCSV(Student **head, const char *filename);
void drawHistogram(Student *head, int score_type);
void batchModifyStudents(Student *head, const char *condition_field, const char *condition_value,
                        const char *modify_field, const char *new_value);
void batchModifyScores(Student *head, const char *condition_field, const char *condition_value,
                      int score_type, int new_score);

#endif // FUNCTION_H