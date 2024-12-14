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
        printf("�ڴ����ʧ�ܣ�\n");
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

// ��ӡѧ�������Ϣ
void printStudent(const Student *student)
{
    printf("ϵ��: %s\n", student->department);
    printf("�꼶: %s\n", student->grade);
    printf("�༶: %s\n", student->class_name);
    printf("ѧ��: %s\n", student->id);
    printf("����: %s\n", student->name);
    printf("�Ա�: %s\n", student->gender);
    printf("��������: %s\n", student->birth_date);
    printf("רҵ: %s\n", student->major);
    printf("�������: %s\n", student->education);
    printf("ѧ��: %d\n", student->years);
    printf("У��: %s\n", student->campus);
    printf("���޳ɼ�: %d\n", student->required_score);
    printf("ѡ�޳ɼ�: %d\n", student->elective_score);
    printf("���γɼ�: %d\n", student->second_score);
    printf("���´�ҵ�ɼ�: %d\n", student->innovation_score);
    printf("�ܳɼ�: %d\n", student->total_score);
    printf("\n");
}

// ��excel�ļ��м���ѧ����Ϣ
void loadStudentsFromFile(Student **head, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("�޷����ļ�");
        return;
    }

    char line[512];
    int line_count = 0;
    // ����������
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        line_count++;
        char department[50], grade[10], class_name[20], id[20], name[50];
        char gender[10], birth_date[20], major[50], education[20], campus[20];
        int years, required_score, elective_score, second_score, innovation_score;

        // ����CSV��
        int result = sscanf(line, "%49[^,],%9[^,],%19[^,],%19[^,],%49[^,],%9[^,],%19[^,],%49[^,],%19[^,],%d,%19[^,],%d,%d,%d,%d",
                            department, grade, class_name, id, name, gender, birth_date,
                            major, education, &years, campus, &required_score,
                            &elective_score, &second_score, &innovation_score);

        if (result != 15)
        {
            printf("���棺�� %d �����ݸ�ʽ����������\n", line_count);
            continue;
        }

        // ��֤�ɼ�����
        if (required_score < 0 || required_score > 100 ||
            elective_score < 0 || elective_score > 100 ||
            second_score < 0 || second_score > 100 ||
            innovation_score < 0 || innovation_score > 100)
        {
            printf("���棺�� %d �гɼ�������Ч��������\n", line_count);
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

    printf("�ļ���ȡ��ɣ������� %d ������\n", line_count);
    fclose(file);
}

// ��ѧ����Ϣ���浽�ļ���
void saveStudentsToFile(Student *head, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("�޷����ļ� %s ����д��\n", filename);
        return;
    }

    // д���ͷ
    fprintf(file, "ϵ��,�꼶,�༶,ѧ��,����,�Ա�,����������,רҵ,�������,ѧ��,У��,���޳ɼ�,ѡ�޳ɼ�,���γɼ�,���´�ҵ�ɼ�,�ܳɼ�\n");

    // д��ѧ������
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
    printf("�����ѳɹ����浽�ļ���\n");
}

// ���ѧ����Ϣ
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

// ��ѧ�Ų���ѧ��
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

// ����������ѧ��
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

// �޸�ѧ�������Ϣ
void modifyStudent(Student *student)
{
    int choice;
    do
    {
        printf("\n=== �޸�ѧ����Ϣ ===\n");
        printf("1. �޸�ϵ��\n");
        printf("2. �޸��꼶\n");
        printf("3. �޸İ༶\n");
        printf("4. �޸�רҵ\n");
        printf("5. �޸ı��޿γɼ�\n");
        printf("6. �޸�ѡ�޿γɼ�\n");
        printf("7. �޸Ķ��γɼ�\n");
        printf("8. �޸Ĵ��´�ҵ�ɼ�\n");
        printf("0. �������˵�\n");
        printf("��ѡ��Ҫ�޸ĵ����� (0-8): ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // ������뻺����

        char temp[50];
        switch (choice)
        {
        case 1:
            printf("�������µ�ϵ��: ");
            scanf("%49s", temp);
            strcpy(student->department, temp);
            break;
        case 2:
            printf("�������µ��꼶: ");
            scanf("%9s", temp);
            strcpy(student->grade, temp);
            break;
        case 3:
            printf("�������µİ༶: ");
            scanf("%19s", temp);
            strcpy(student->class_name, temp);
            break;
        case 4:
            printf("�������µ�רҵ: ");
            scanf("%49s", temp);
            strcpy(student->major, temp);
            break;
        case 5:
            printf("�������µı��޿γɼ�: ");
            scanf("%d", &student->required_score);
            break;
        case 6:
            printf("�������µ�ѡ�޿γɼ�: ");
            scanf("%d", &student->elective_score);
            break;
        case 7:
            printf("�������µĶ��γɼ�: ");
            scanf("%d", &student->second_score);
            break;
        case 8:
            printf("�������µĴ��´�ҵ�ɼ�: ");
            scanf("%d", &student->innovation_score);
            break;
        case 0:
            printf("�����ϼ��˵�\n");
            break;
        default:
            printf("��Ч��ѡ������������\n");
        }

        if (choice >= 1 && choice <= 8)
        {
            printf("\n�޸ĳɹ����޸ĺ����Ϣ��\n");
            printStudent(student);
        }

    } while (choice != 0);
}

// ��xlsx�ļ��е���ѧ����Ϣ������Ϊ����,ѧ����Ϣ�ĸ�ʽΪ
// ϵ�� �꼶 �༶ ѧ�� ���� �Ա� ���������� רҵ ������� ѧ�� У�� ���޳ɼ� ѡ�޳ɼ� ���γɼ� ���´�ҵ�ɼ�
// ������һ��ʾ��
// ��Ϣ����ѧԺ	2023	�����202306	202305071	����	Ů	2004/12/9 �������ѧ�뼼�� ���� 4 �Ű� 99 97 97 83
int importStudentsFromCSV(Student **head, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("�޷����ļ���\n");
        return 0;
    }

    char line[1024];
    // ������ͷ
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        char department[50], grade[10], class_name[20], id[20], name[50];
        char gender[10], birth_date[20], major[50], education[20], campus[20];
        int years, required_score, elective_score, second_score, innovation_score;

        // ����CSV�У�ʹ���Ʊ��(\t)�ָ�
        if (sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%[^\t]\t%d\t%d\t%d\t%d",
                   department, grade, class_name, id, name, gender, birth_date,
                   major, education, &years, campus, &required_score,
                   &elective_score, &second_score, &innovation_score) == 15)
        {

            // ������ѧ���ڵ�
            Student *newStudent = createStudent(department, grade, class_name, id,
                                                name, gender, birth_date, major,
                                                education, years, campus, required_score,
                                                elective_score, second_score, innovation_score);

            if (newStudent != NULL)
            {
                // ���½ڵ���ӵ�����ͷ��
                newStudent->next = *head;
                *head = newStudent;
                printf("�ɹ�����ѧ��: %s\n", name);
            }
            else
            {
                printf("����ѧ���ڵ�ʧ��: %s\n", name);
            }
        }
        else
        {
            printf("������ʧ��: %s\n", line);
        }
    }

    fclose(file);
    return 1;
}

// �����޸��ı��ֶ�
void batchModifyStudents(Student *head, const char *condition_field, const char *condition_value,
                        const char *modify_field, const char *new_value)
{
    Student *current = head;
    int count = 0;
    
    while (current != NULL)
    {
        bool match = false;
        
        // ��������ֶ�
        if (strcmp(condition_field, "department") == 0)
            match = (strcmp(current->department, condition_value) == 0);
        else if (strcmp(condition_field, "grade") == 0)
            match = (strcmp(current->grade, condition_value) == 0);
        else if (strcmp(condition_field, "class_name") == 0)
            match = (strcmp(current->class_name, condition_value) == 0);
        else if (strcmp(condition_field, "major") == 0)
            match = (strcmp(current->major, condition_value) == 0);
        
        // �������ƥ�䣬�޸�ָ���ֶ�
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
    
    printf("�����޸���ɣ����޸� %d ����¼\n", count);
}

// �����޸ĳɼ�
void batchModifyScores(Student *head, const char *condition_field, const char *condition_value,
                      int score_type, int new_score)
{
    if (new_score < 0 || new_score > 100) {
        printf("���󣺳ɼ�������0-100֮�䣡\n");
        return;
    }

    Student *current = head;
    int count = 0;
    
    while (current != NULL)
    {
        bool match = false;
        
        // ��������ֶ�
        if (strcmp(condition_field, "department") == 0)
            match = (strcmp(current->department, condition_value) == 0);
        else if (strcmp(condition_field, "grade") == 0)
            match = (strcmp(current->grade, condition_value) == 0);
        else if (strcmp(condition_field, "class_name") == 0)
            match = (strcmp(current->class_name, condition_value) == 0);
        else if (strcmp(condition_field, "major") == 0)
            match = (strcmp(current->major, condition_value) == 0);
        
        // �������ƥ�䣬�޸�ָ���ɼ�
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
    
    printf("�����޸���ɣ����޸� %d ����¼\n", count);
}

// ��ѧ���ɼ�����ΪƵ�ʷֲ�ֱ��ͼ����ѡ����޳ɼ���ѡ�޳ɼ������γɼ������´�ҵ�ɼ��Լ��ܳɼ�
void drawHistogram(Student *head, int score_type)
{
    // �����ռ�����֤������Ч�ɼ�
    std::vector<int> valid_scores;
    Student *current = head;
    int invalid_count = 0;
    
    while (current != NULL)
    {
        int selected_score;
        
        // �����û�ѡ�����ʹ�����ֳɼ�
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
                // �����ܳɼ������������Ƴɼ�Ȩ����ȣ�
                selected_score = (current->required_score + 
                                current->elective_score + 
                                current->second_score + 
                                current->innovation_score) / 4;
                break;
            default:
                selected_score = current->required_score;
        }
        
        // ��֤�ɼ��Ƿ�����Ч��Χ��
        if (selected_score >= 0 && selected_score <= 100) {
            valid_scores.push_back(selected_score);
        } else {
            invalid_count++;
        }
        
        current = current->next;
    }

    // ��ӡͳ����Ϣ
    printf("\n=== ͳ����Ϣ ===\n");
    printf("������ܼ�¼��: %d\n", valid_scores.size() + invalid_count);
    printf("��Ч�ɼ���: %d\n", valid_scores.size());
    printf("��Ч�ɼ���: %d\n", invalid_count);

    if (valid_scores.empty()) {
        printf("û���ҵ��κ���Ч�ĳɼ����ݣ�\n");
        return;
    }

    // ���ɼ�����д����ʱ�ļ�
    FILE *temp_file = fopen("temp_scores.txt", "w");
    if (!temp_file) {
        printf("�޷�������ʱ�ļ���\n");
        return;
    }

    for (int score : valid_scores) {
        fprintf(temp_file, "%d\n", score);
    }
    fclose(temp_file);

    // ִ��Python�ű������ļ���ȡ����
    printf("\n׼��ִ��Python��ͼ�ű�...\n");
    int result = system("python ./plot_py/plot_histogram.py -f temp_scores.txt");
    
    if (result != 0) {
        printf("ִ��Python�ű�ʱ�������飺\n");
        printf("1. Python��װ״̬��");
        system("python --version");
        printf("2. plot_histogram.py�ļ�λ��\n");
        printf("3. matplotlib�ⰲװ״̬\n");
    }

    // ɾ����ʱ�ļ�
    remove("temp_scores.txt");
}




