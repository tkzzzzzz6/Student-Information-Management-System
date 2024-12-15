#include "function.h"
#include "heap_sort.h"

int main()
{
    StudentList *list = initStudentList();
    if (list == NULL)
    {
        printf("��ʼ��ʧ��!\n");
        return 1;
    }

    int choice;
    char filename[100];
    printf("������Ҫ���ص��ļ���: ");
    scanf("%s", filename);
    printf("\n=== ���ڴ��ļ�����ѧ����Ϣ... ===\n");
    // ��������ʱ��
    clock_t start_time = clock();
    loadStudentsFromFile(list, filename);
    clock_t end_time = clock();
    double running_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    printf("�ļ�������ɣ���ʱ: %.5f ��\n", running_time);

    do
    {
        printf("\n==============================================\n");
        printf("         ѧ����Ϣ����ϵͳ           \n");
        printf("==============================================\n");
        printf("�� 1. ��ʾ����ѧ����Ϣ                   ��\n");
        printf("�� 2. ��ѧ�Ų���ѧ��                     ��\n");
        printf("�� 3. ����������ѧ��                     ��\n");
        printf("�� 4. �޸�ѧ���ɼ�                       ��\n");
        printf("�� 5. ���浽�ļ�                         ��\n");
        printf("�� 6. ��CSV����ѧ����Ϣ                  ��\n");
        printf("�� 7. ���Ƴɼ��ֲ�ֱ��ͼ                 ��\n");
        printf("�� 8. �����޸�ѧ����Ϣ                   ��\n");
        printf("�� 9. �����򲢴�ӡǰ10��ѧ�������ܳɼ�   ��\n");
        printf("�� 0. �˳�ϵͳ                           ��\n");
        printf("==============================================\n");
        printf("��ѡ�����[0-9]: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("\n========== ����ѧ����Ϣ ==========\n");
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
            printf("\n========== ��ѧ�Ų��� ==========\n");
            printf("������ѧ��: ");
            scanf("%s", id);
            Student *found = findStudentById(list, id);
            if (found != NULL)
            {
                printf("\n----- �ҵ�����ѧ����Ϣ -----\n");
                printStudent(found);
            }
            else
            {
                printf("\n*** δ�ҵ���ѧ����***\n");
            }
            break;
        }
        case 3:
        {
            char name[50];
            printf("\n========== ���������� ==========\n");
            printf("����������: ");
            scanf("%s", name);
            // �������ʱ��
            clock_t start_time = clock();
            Student *found = findStudentByName(list, name);
            clock_t end_time = clock();
            double running_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            printf("������ɣ���ʱ: %.5f ��\n", running_time);
            if (found != NULL)
            {
                printf("\n----- �ҵ�����ѧ����Ϣ -----\n");
                printStudent(found);
            }
            else
            {
                printf("\n*** δ�ҵ���ѧ����***\n");
            }
            break;
        }
        case 4:
        {
            char id[20];
            printf("\n========== �޸�ѧ����Ϣ ==========\n");
            printf("������Ҫ�޸ĵ�ѧ��ѧ��: ");
            scanf("%s", id);
            Student *found = findStudentById(list, id);
            if (found != NULL)
            {
                printf("\n----- ��ǰѧ����Ϣ -----\n");
                printStudent(found);
                modifyStudent(found);
                printf("\n----- �޸ĺ����Ϣ -----\n");
                printStudent(found);
            }
            else
            {
                printf("\n*** δ�ҵ���ѧ����***\n");
            }
            break;
        }
        case 5:
        {
            printf("������Ҫ������ļ���: ");
            char filename[100];
            scanf("%s", filename);
            printf("\n=== ���ڱ��浽�ļ�... ===\n");
            saveStudentsToFile(list, filename);
            printf("=== ����ɹ���===\n");
            break;
        }
        case 6:
        {
            printf("������Ҫ�����CSV�ļ���: ");
            char filename[100];
            scanf("%s", filename);
            printf("\n=== ���ڴ�CSV�ļ�����ѧ����Ϣ... ===\n");
            if (importStudentsFromCSV(list, filename))
            {
                printf("=== ����ɹ���===\n");
            }
            else
            {
                printf("*** ����ʧ�ܣ�***\n");
            }
            break;
        }
        case 7:
        {
            printf("\n========== �ɼ��ֲ�ͼ ==========\n");
            printf("��ѡ��Ҫ����ֱ��ͼ�ĳɼ�����:\n");
            printf("1. ���޳ɼ�\n");
            printf("2. ѡ�޳ɼ�\n");
            printf("3. ���γɼ�\n");
            printf("4. ���´�ҵ�ɼ�\n");
            printf("5. �ܳɼ�\n");
            printf("��ѡ��[1-5]: ");
            int score_type;
            scanf("%d", &score_type);
            drawHistogram(list, score_type);
            break;
        }
        case 8:
        {
            printf("\n========== �����޸�ѧ����Ϣ ==========\n");
            printf("��ѡ���޸����ͣ�\n");
            printf("1. �޸��ı���Ϣ��ϵ��/�꼶/�༶/רҵ��\n");
            printf("2. �޸ĳɼ���Ϣ\n");
            printf("��ѡ��[1-2]: ");
            int modify_type;
            scanf("%d", &modify_type);

            if (modify_type == 1)
            {
                printf("\n=== �޸��ı���Ϣ ===\n");
                printf("��ѡ��ɸѡ�����ֶΣ�\n");
                printf("1. ϵ��\n2. �꼶\n3. �༶\n4. רҵ\n");
                printf("��ѡ��[1-4]: ");
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
                    printf("��Чѡ��\n");
                    continue;
                }

                printf("������ɸѡ����ֵ: ");
                scanf("%s", condition_value);

                printf("��ѡ��Ҫ�޸ĵ��ֶΣ�\n");
                printf("1. ϵ��\n2. �꼶\n3. �༶\n4. רҵ\n");
                printf("��ѡ��[1-4]: ");
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
                    printf("��Чѡ��\n");
                    continue;
                }

                printf("��������ֵ: ");
                scanf("%s", new_value);

                batchModifyStudents(list, condition_field, condition_value, modify_field, new_value);
            }
            else if (modify_type == 2)
            {
                printf("\n=== �޸ĳɼ���Ϣ ===\n");
                printf("��ѡ��ɸѡ�����ֶΣ�\n");
                printf("1. ϵ��\n2. �꼶\n3. �༶\n4. רҵ\n");
                printf("��ѡ��[1-4]: ");
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
                    printf("��Чѡ��\n");
                    continue;
                }

                printf("������ɸѡ����ֵ: ");
                scanf("%s", condition_value);

                printf("��ѡ��Ҫ�޸ĵĳɼ����ͣ�\n");
                printf("1. ���޳ɼ�\n2. ѡ�޳ɼ�\n3. ���γɼ�\n4. ���´�ҵ�ɼ�\n");
                printf("��ѡ��[1-4]: ");
                int score_type;
                scanf("%d", &score_type);

                printf("�������³ɼ�(0-100): ");
                int new_score;
                scanf("%d", &new_score);

                batchModifyScores(list, condition_field, condition_value, score_type, new_score);
            }
            break;
        }
        case 9:
        {
            printf("\n=== �����򲢴�ӡǰ10��ѧ�������ܳɼ� ===\n");
            heapSort(list);
            break;
        }
        case 0:
        {
            printf("\n=== ���ڱ��沢�˳�... ===\n");
            saveStudentsToFile(list, filename);
            // �ͷ��ڴ�
            freeStudentList(list);
            printf("=== ллʹ�ã��ټ���===\n");
            break;
        }
        default:
            printf("\n*** ��Ч��ѡ��������0-8֮������� ***\n");
        }
    } while (choice != 0);

    return 0;
}
// g++ -fexec-charset=GB2312 main.cpp function.cpp -o main
