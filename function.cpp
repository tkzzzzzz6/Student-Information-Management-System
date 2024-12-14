#include "function.h"

Student *createStudent(const char *department, const char *grade, const char *class_name,
                       const char *id, const char *name, const char *gender,
                       const char *birth_date, const char *major, const char *education,
                       int years, const char *campus, int required_score,
                       int elective_score, int second_score, int innovation_score)
{
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }

    strcpy(newStudent->department, department);
    strcpy(newStudent->grade, grade);
    strcpy(newStudent->class_name, class_name);
    strcpy(newStudent->id, id);
    strcpy(newStudent->name, name);
    strcpy(newStudent->gender, gender);
    strcpy(newStudent->birth_date, birth_date);
    strcpy(newStudent->major, major);
    strcpy(newStudent->education, education);
    newStudent->years = years;
    strcpy(newStudent->campus, campus);
    newStudent->required_score = required_score;
    newStudent->elective_score = elective_score;
    newStudent->second_score = second_score;
    newStudent->innovation_score = innovation_score;
    newStudent->total_score = required_score + elective_score + second_score + innovation_score;
    newStudent->next = NULL;

    return newStudent;
}

// 打印学生相关信息
void printStudent(const Student *student)
{
    printf("系别: %s\n", student->department);
    printf("年级: %s\n", student->grade);
    printf("班级: %s\n", student->class_name);
    printf("学号: %s\n", student->id);
    printf("姓名: %s\n", student->name);
    printf("性别: %s\n", student->gender);
    printf("出生日期: %s\n", student->birth_date);
    printf("专业: %s\n", student->major);
    printf("培养层次: %s\n", student->education);
    printf("学制: %d\n", student->years);
    printf("校区: %s\n", student->campus);
    printf("必修成绩: %d\n", student->required_score);
    printf("选修成绩: %d\n", student->elective_score);
    printf("二课成绩: %d\n", student->second_score);
    printf("创新创业成绩: %d\n", student->innovation_score);
    printf("总成绩: %d\n", student->total_score);
    printf("\n");
}

// 从excel文件中加载学生信息
void loadStudentsFromFile(Student **head, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("无法打开文件");
        return;
    }

    char line[512];
    int line_count = 0;
    // 跳过标题行
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        line_count++;
        char department[50], grade[10], class_name[20], id[20], name[50];
        char gender[10], birth_date[20], major[50], education[20], campus[20];
        int years, required_score, elective_score, second_score, innovation_score;

        // 解析CSV行
        int result = sscanf(line, "%49[^,],%9[^,],%19[^,],%19[^,],%49[^,],%9[^,],%19[^,],%49[^,],%19[^,],%d,%19[^,],%d,%d,%d,%d",
                            department, grade, class_name, id, name, gender, birth_date,
                            major, education, &years, campus, &required_score,
                            &elective_score, &second_score, &innovation_score);

        if (result != 15)
        {
            printf("警告：第 %d 行数据格式错误，已跳过\n", line_count);
            continue;
        }

        // 验证成绩数据
        if (required_score < 0 || required_score > 100 ||
            elective_score < 0 || elective_score > 100 ||
            second_score < 0 || second_score > 100 ||
            innovation_score < 0 || innovation_score > 100)
        {
            printf("警告：第 %d 行成绩数据无效，已跳过\n", line_count);
            continue;
        }

        Student *newStudent = createStudent(department, grade, class_name, id,
                                            name, gender, birth_date, major,
                                            education, years, campus, required_score,
                                            elective_score, second_score, innovation_score);
        if (newStudent != NULL)
        {
            addStudent(head, newStudent);
        }
    }

    printf("文件读取完成，共处理 %d 行数据\n", line_count);
    fclose(file);
}

// 将学生信息保存到文件中
void saveStudentsToFile(Student *head, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("无法打开文件 %s 进行写入\n", filename);
        return;
    }

    // 写入表头
    fprintf(file, "系别,年级,班级,学号,姓名,性别,出生年月日,专业,培养层次,学制,校区,必修成绩,选修成绩,二课成绩,创新创业成绩,总成绩\n");

    // 写入学生数据
    Student *current = head;
    while (current != NULL)
    {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%d,%d,%d,%d\n",
                current->department, current->grade, current->class_name,
                current->id, current->name, current->gender, current->birth_date,
                current->major, current->education, current->years, current->campus,
                current->required_score, current->elective_score,
                current->second_score, current->innovation_score,current->total_score);
        current = current->next;
    }

    fclose(file);
    printf("数据已成功保存到文件！\n");
}

// 添加学生信息
void addStudent(Student **head, Student *newStudent)
{
    if (*head == NULL)
    {
        *head = newStudent;
    }
    else
    {
        Student *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newStudent;
    }
}

// 按学号查找学生
Student *findStudentById(Student *head, const char *id)
{
    Student *current = head;
    while (current != NULL)
    {
        if (strcmp(current->id, id) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 按姓名查找学生
Student *findStudentByName(Student *head, const char *name)
{
    Student *current = head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 修改学生相关信息
void modifyStudent(Student *student)
{
    int choice;
    do
    {
        printf("\n=== 修改学生信息 ===\n");
        printf("1. 修改系别\n");
        printf("2. 修改年级\n");
        printf("3. 修改班级\n");
        printf("4. 修改专业\n");
        printf("5. 修改必修课成绩\n");
        printf("6. 修改选修课成绩\n");
        printf("7. 修改二课成绩\n");
        printf("8. 修改创新创业成绩\n");
        printf("0. 返回主菜单\n");
        printf("请选择要修改的内容 (0-8): ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // 清除输入缓冲区

        char temp[50];
        switch (choice)
        {
        case 1:
            printf("请输入新的系别: ");
            scanf("%49s", temp);
            strcpy(student->department, temp);
            break;
        case 2:
            printf("请输入新的年级: ");
            scanf("%9s", temp);
            strcpy(student->grade, temp);
            break;
        case 3:
            printf("请输入新的班级: ");
            scanf("%19s", temp);
            strcpy(student->class_name, temp);
            break;
        case 4:
            printf("请输入新的专业: ");
            scanf("%49s", temp);
            strcpy(student->major, temp);
            break;
        case 5:
            printf("请输入新的必修课成绩: ");
            scanf("%d", &student->required_score);
            break;
        case 6:
            printf("请输入新的选修课成绩: ");
            scanf("%d", &student->elective_score);
            break;
        case 7:
            printf("请输入新的二课成绩: ");
            scanf("%d", &student->second_score);
            break;
        case 8:
            printf("请输入新的创新创业成绩: ");
            scanf("%d", &student->innovation_score);
            break;
        case 0:
            printf("返回上级菜单\n");
            break;
        default:
            printf("无效的选择，请重新输入\n");
        }

        if (choice >= 1 && choice <= 8)
        {
            printf("\n修改成功！修改后的信息：\n");
            printStudent(student);
        }

    } while (choice != 0);
}

// 从xlsx文件中导入学生信息并创建为链表,学生信息的格式为
// 系别 年级 班级 学号 姓名 性别 出生年月日 专业 培养层次 学制 校区 必修成绩 选修成绩 二课成绩 创新创业成绩
// 下面是一个示例
// 信息工程学院	2023	计算机202306	202305071	何婷	女	2004/12/9 计算机科学与技术 本科 4 雅安 99 97 97 83
int importStudentsFromCSV(Student **head, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("无法打开文件！\n");
        return 0;
    }

    char line[1024];
    // 跳过表头
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        char department[50], grade[10], class_name[20], id[20], name[50];
        char gender[10], birth_date[20], major[50], education[20], campus[20];
        int years, required_score, elective_score, second_score, innovation_score;

        // 解析CSV行，使用制表符(\t)分隔
        if (sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%[^\t]\t%d\t%d\t%d\t%d",
                   department, grade, class_name, id, name, gender, birth_date,
                   major, education, &years, campus, &required_score,
                   &elective_score, &second_score, &innovation_score) == 15)
        {

            // 创建新学生节点
            Student *newStudent = createStudent(department, grade, class_name, id,
                                                name, gender, birth_date, major,
                                                education, years, campus, required_score,
                                                elective_score, second_score, innovation_score);

            if (newStudent != NULL)
            {
                // 将新节点添加到链表头部
                newStudent->next = *head;
                *head = newStudent;
                printf("成功导入学生: %s\n", name);
            }
            else
            {
                printf("创建学生节点失败: %s\n", name);
            }
        }
        else
        {
            printf("解析行失败: %s\n", line);
        }
    }

    fclose(file);
    return 1;
}

// 批量修改文本字段
void batchModifyStudents(Student *head, const char *condition_field, const char *condition_value,
                        const char *modify_field, const char *new_value)
{
    Student *current = head;
    int count = 0;
    
    while (current != NULL)
    {
        bool match = false;
        
        // 检查条件字段
        if (strcmp(condition_field, "department") == 0)
            match = (strcmp(current->department, condition_value) == 0);
        else if (strcmp(condition_field, "grade") == 0)
            match = (strcmp(current->grade, condition_value) == 0);
        else if (strcmp(condition_field, "class_name") == 0)
            match = (strcmp(current->class_name, condition_value) == 0);
        else if (strcmp(condition_field, "major") == 0)
            match = (strcmp(current->major, condition_value) == 0);
        
        // 如果条件匹配，修改指定字段
        if (match) {
            if (strcmp(modify_field, "department") == 0)
                strcpy(current->department, new_value);
            else if (strcmp(modify_field, "grade") == 0)
                strcpy(current->grade, new_value);
            else if (strcmp(modify_field, "class_name") == 0)
                strcpy(current->class_name, new_value);
            else if (strcmp(modify_field, "major") == 0)
                strcpy(current->major, new_value);
            count++;
        }
        
        current = current->next;
    }
    
    printf("批量修改完成，共修改 %d 条记录\n", count);
}

// 批量修改成绩
void batchModifyScores(Student *head, const char *condition_field, const char *condition_value,
                      int score_type, int new_score)
{
    if (new_score < 0 || new_score > 100) {
        printf("错误：成绩必须在0-100之间！\n");
        return;
    }

    Student *current = head;
    int count = 0;
    
    while (current != NULL)
    {
        bool match = false;
        
        // 检查条件字段
        if (strcmp(condition_field, "department") == 0)
            match = (strcmp(current->department, condition_value) == 0);
        else if (strcmp(condition_field, "grade") == 0)
            match = (strcmp(current->grade, condition_value) == 0);
        else if (strcmp(condition_field, "class_name") == 0)
            match = (strcmp(current->class_name, condition_value) == 0);
        else if (strcmp(condition_field, "major") == 0)
            match = (strcmp(current->major, condition_value) == 0);
        
        // 如果条件匹配，修改指定成绩
        if (match) {
            switch(score_type) {
                case 1:
                    current->required_score = new_score;
                    break;
                case 2:
                    current->elective_score = new_score;
                    break;
                case 3:
                    current->second_score = new_score;
                    break;
                case 4:
                    current->innovation_score = new_score;
                    break;
            }
            count++;
        }
        
        current = current->next;
    }
    
    printf("批量修改完成，共修改 %d 条记录\n", count);
}

// 将学生成绩绘制为频率分布直方图，可选择必修成绩、选修成绩、二课成绩、创新创业成绩以及总成绩
void drawHistogram(Student *head, int score_type)
{
    // 首先收集并验证所有有效成绩
    std::vector<int> valid_scores;
    Student *current = head;
    int invalid_count = 0;
    
    while (current != NULL)
    {
        int selected_score;
        
        // 根据用户选择决定使用哪种成绩
        switch(score_type) {
            case 1:
                selected_score = current->required_score;
                break;
            case 2:
                selected_score = current->elective_score;
                break;
            case 3:
                selected_score = current->second_score;
                break;
            case 4:
                selected_score = current->innovation_score;
                break;
            case 5:
                // 计算总成绩（这里假设各科成绩权重相等）
                selected_score = (current->required_score + 
                                current->elective_score + 
                                current->second_score + 
                                current->innovation_score) / 4;
                break;
            default:
                selected_score = current->required_score;
        }
        
        // 验证成绩是否在有效范围内
        if (selected_score >= 0 && selected_score <= 100) {
            valid_scores.push_back(selected_score);
        } else {
            invalid_count++;
        }
        
        current = current->next;
    }

    // 打印统计信息
    printf("\n=== 统计信息 ===\n");
    printf("处理的总记录数: %d\n", valid_scores.size() + invalid_count);
    printf("有效成绩数: %d\n", valid_scores.size());
    printf("无效成绩数: %d\n", invalid_count);

    if (valid_scores.empty()) {
        printf("没有找到任何有效的成绩数据！\n");
        return;
    }

    // 将成绩数据写入临时文件
    FILE *temp_file = fopen("temp_scores.txt", "w");
    if (!temp_file) {
        printf("无法创建临时文件！\n");
        return;
    }

    for (int score : valid_scores) {
        fprintf(temp_file, "%d\n", score);
    }
    fclose(temp_file);

    // 执行Python脚本，从文件读取数据
    printf("\n准备执行Python绘图脚本...\n");
    int result = system("python ./plot_py/plot_histogram.py -f temp_scores.txt");
    
    if (result != 0) {
        printf("执行Python脚本时出错。请检查：\n");
        printf("1. Python安装状态：");
        system("python --version");
        printf("2. plot_histogram.py文件位置\n");
        printf("3. matplotlib库安装状态\n");
    }

    // 删除临时文件
    remove("temp_scores.txt");
}




