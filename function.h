#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <time.h>

// 定义学生结构体
typedef struct Student
{
    char department[50];  // 系别
    char grade[10];       // 年级
    char class_name[20];  // 班级
    char id[20];          // 学号
    char name[50];        // 姓名
    char gender[10];      // 性别
    char birth_date[20];  // 出生年月日
    char major[50];       // 专业
    char education[20];   // 培养层次
    int years;            // 学制
    char campus[20];      // 校区
    int required_score;   // 必修成绩
    int elective_score;   // 选修成绩
    int second_score;     // 二课成绩
    int innovation_score; // 创新创业成绩
    int total_score;      // 总成绩
    struct Student *next;
} Student;

// 添加新的链表管理结构
typedef struct {
    Student* head;    // 指向链表头部
    Student* tail;    // 指向链表尾部
    int count;        // 记录学生总数
} StudentList;

// 函数声明
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