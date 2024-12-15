#include "function.h"
#include "heap_sort.h"

int main()
{
    StudentList *list = initStudentList();
    if (list == NULL)
    {
        printf("初始化失败!\n");
        return 1;
    }

    int choice;
    char filename[100];
    printf("请输入要加载的文件名: ");
    scanf("%s", filename);
    printf("\n=== 正在从文件加载学生信息... ===\n");
    // 计算运行时间
    clock_t start_time = clock();
    loadStudentsFromFile(list, filename);
    clock_t end_time = clock();
    double running_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    printf("文件加载完成，用时: %.5f 秒\n", running_time);

    do
    {
        printf("\n==============================================\n");
        printf("         学生信息管理系统           \n");
        printf("==============================================\n");
        printf("│ 1. 显示所有学生信息                   │\n");
        printf("│ 2. 按学号查找学生                     │\n");
        printf("│ 3. 按姓名查找学生                     │\n");
        printf("│ 4. 修改学生成绩                       │\n");
        printf("│ 5. 保存到文件                         │\n");
        printf("│ 6. 从CSV导入学生信息                  │\n");
        printf("│ 7. 绘制成绩分布直方图                 │\n");
        printf("│ 8. 批量修改学生信息                   │\n");
        printf("│ 9. 堆排序并打印前10名学生及其总成绩   │\n");
        printf("│ 0. 退出系统                           │\n");
        printf("==============================================\n");
        printf("请选择操作[0-9]: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("\n========== 所有学生信息 ==========\n");
            Student *current = list->head;
            while (current != NULL)
            {
                printStudent(current);
                current = current->next;
            }
            break;
        }
        case 2:
        {
            char id[20];
            printf("\n========== 按学号查找 ==========\n");
            printf("请输入学号: ");
            scanf("%s", id);
            Student *found = findStudentById(list, id);
            if (found != NULL)
            {
                printf("\n----- 找到以下学生信息 -----\n");
                printStudent(found);
            }
            else
            {
                printf("\n*** 未找到该学生！***\n");
            }
            break;
        }
        case 3:
        {
            char name[50];
            printf("\n========== 按姓名查找 ==========\n");
            printf("请输入姓名: ");
            scanf("%s", name);
            // 计算查找时间
            clock_t start_time = clock();
            Student *found = findStudentByName(list, name);
            clock_t end_time = clock();
            double running_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            printf("查找完成，用时: %.5f 秒\n", running_time);
            if (found != NULL)
            {
                printf("\n----- 找到以下学生信息 -----\n");
                printStudent(found);
            }
            else
            {
                printf("\n*** 未找到该学生！***\n");
            }
            break;
        }
        case 4:
        {
            char id[20];
            printf("\n========== 修改学生信息 ==========\n");
            printf("请输入要修改的学生学号: ");
            scanf("%s", id);
            Student *found = findStudentById(list, id);
            if (found != NULL)
            {
                printf("\n----- 当前学生信息 -----\n");
                printStudent(found);
                modifyStudent(found);
                printf("\n----- 修改后的信息 -----\n");
                printStudent(found);
            }
            else
            {
                printf("\n*** 未找到该学生！***\n");
            }
            break;
        }
        case 5:
        {
            printf("请输入要保存的文件名: ");
            char filename[100];
            scanf("%s", filename);
            printf("\n=== 正在保存到文件... ===\n");
            saveStudentsToFile(list, filename);
            printf("=== 保存成功！===\n");
            break;
        }
        case 6:
        {
            printf("请输入要导入的CSV文件名: ");
            char filename[100];
            scanf("%s", filename);
            printf("\n=== 正在从CSV文件导入学生信息... ===\n");
            if (importStudentsFromCSV(list, filename))
            {
                printf("=== 导入成功！===\n");
            }
            else
            {
                printf("*** 导入失败！***\n");
            }
            break;
        }
        case 7:
        {
            printf("\n========== 成绩分布图 ==========\n");
            printf("请选择要绘制直方图的成绩类型:\n");
            printf("1. 必修成绩\n");
            printf("2. 选修成绩\n");
            printf("3. 二课成绩\n");
            printf("4. 创新创业成绩\n");
            printf("5. 总成绩\n");
            printf("请选择[1-5]: ");
            int score_type;
            scanf("%d", &score_type);
            drawHistogram(list, score_type);
            break;
        }
        case 8:
        {
            printf("\n========== 批量修改学生信息 ==========\n");
            printf("请选择修改类型：\n");
            printf("1. 修改文本信息（系别/年级/班级/专业）\n");
            printf("2. 修改成绩信息\n");
            printf("请选择[1-2]: ");
            int modify_type;
            scanf("%d", &modify_type);

            if (modify_type == 1)
            {
                printf("\n=== 修改文本信息 ===\n");
                printf("请选择筛选条件字段：\n");
                printf("1. 系别\n2. 年级\n3. 班级\n4. 专业\n");
                printf("请选择[1-4]: ");
                int condition_choice;
                scanf("%d", &condition_choice);

                char condition_field[20], condition_value[50];
                switch (condition_choice)
                {
                case 1:
                    strcpy(condition_field, "department");
                    break;
                case 2:
                    strcpy(condition_field, "grade");
                    break;
                case 3:
                    strcpy(condition_field, "class_name");
                    break;
                case 4:
                    strcpy(condition_field, "major");
                    break;
                default:
                    printf("无效选择！\n");
                    continue;
                }

                printf("请输入筛选条件值: ");
                scanf("%s", condition_value);

                printf("请选择要修改的字段：\n");
                printf("1. 系别\n2. 年级\n3. 班级\n4. 专业\n");
                printf("请选择[1-4]: ");
                int modify_choice;
                scanf("%d", &modify_choice);

                char modify_field[20], new_value[50];
                switch (modify_choice)
                {
                case 1:
                    strcpy(modify_field, "department");
                    break;
                case 2:
                    strcpy(modify_field, "grade");
                    break;
                case 3:
                    strcpy(modify_field, "class_name");
                    break;
                case 4:
                    strcpy(modify_field, "major");
                    break;
                default:
                    printf("无效选择！\n");
                    continue;
                }

                printf("请输入新值: ");
                scanf("%s", new_value);

                batchModifyStudents(list, condition_field, condition_value, modify_field, new_value);
            }
            else if (modify_type == 2)
            {
                printf("\n=== 修改成绩信息 ===\n");
                printf("请选择筛选条件字段：\n");
                printf("1. 系别\n2. 年级\n3. 班级\n4. 专业\n");
                printf("请选择[1-4]: ");
                int condition_choice;
                scanf("%d", &condition_choice);

                char condition_field[20], condition_value[50];
                switch (condition_choice)
                {
                case 1:
                    strcpy(condition_field, "department");
                    break;
                case 2:
                    strcpy(condition_field, "grade");
                    break;
                case 3:
                    strcpy(condition_field, "class_name");
                    break;
                case 4:
                    strcpy(condition_field, "major");
                    break;
                default:
                    printf("无效选择！\n");
                    continue;
                }

                printf("请输入筛选条件值: ");
                scanf("%s", condition_value);

                printf("请选择要修改的成绩类型：\n");
                printf("1. 必修成绩\n2. 选修成绩\n3. 二课成绩\n4. 创新创业成绩\n");
                printf("请选择[1-4]: ");
                int score_type;
                scanf("%d", &score_type);

                printf("请输入新成绩(0-100): ");
                int new_score;
                scanf("%d", &new_score);

                batchModifyScores(list, condition_field, condition_value, score_type, new_score);
            }
            break;
        }
        case 9:
        {
            printf("\n=== 堆排序并打印前10名学生及其总成绩 ===\n");
            heapSort(list);
            break;
        }
        case 0:
        {
            printf("\n=== 正在保存并退出... ===\n");
            saveStudentsToFile(list, filename);
            // 释放内存
            freeStudentList(list);
            printf("=== 谢谢使用，再见！===\n");
            break;
        }
        default:
            printf("\n*** 无效的选择！请输入0-8之间的数字 ***\n");
        }
    } while (choice != 0);

    return 0;
}
// g++ -fexec-charset=GB2312 main.cpp function.cpp -o main
