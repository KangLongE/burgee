#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "question_data.h"
#include "sign_log.h"
#include "note.h"

int main(void) {

    char yn;

    int i = 0;
    char buffer[MAX_INDEX];

    FILE* fp;
    fp = fopen("UserData.txt", "r");


    if (fp == NULL) {

        printf("�α����� �Ǿ����� �ʽ��ϴ�.\nȸ������ �Ͻðڽ��ϱ�? : Y / N\n: ");
        scanf("%c", &yn, 1);
        while ((getchar()) != '\n' && !feof(stdin));


        if (yn == 'Y' || yn == 'y')
        {
            signup();
        }
        else if (yn == 'N' || yn == 'n') {
            printf("\n���α׷��� �����մϴ�.\n");
            return 0;
        }
        else {
            printf("\n�߸��� �Է��Դϴ�.\n");
        }


    }
    else {

        fseek(fp, 0, SEEK_END);  
        long size = ftell(fp);   
        rewind(fp);              

        if (size == 0) {
            while (1) {
                printf("�α����� �Ǿ����� �ʽ��ϴ�.\nȸ������ �Ͻðڽ��ϱ�? : Y / N\n: ");
                scanf("%c", &yn, 1);
                while ((getchar()) != '\n' && !feof(stdin));


                if (yn == 'Y' || yn == 'y')
                {
                    signup();
                    break;
                }
                else if (yn == 'N' || yn == 'n') {
                    printf("\n���α׷��� �����մϴ�.\n");
                    return 0;
                }
                else {
                    printf("\n�߸��� �Է��Դϴ�.\n");
                }
            }
        }
        else {
            while (1) {

                login();

                if (success) {
                    break;
                }
                else {

                    i++;

                    if (i < 3) {
                        while (1) {
                            printf("\n�α��� ����. �ٽ� �õ��Ͻðڽ��ϱ�? (Y/N): ");
                            scanf_s(" %c", &yn, 1);
                            while ((getchar()) != '\n' && !feof(stdin));

                            if (yn == 'Y' || yn == 'y') {
                                break;
                            }
                            else if (yn == 'N' || yn == 'n') {
                                printf("\n���α׷��� �����մϴ�.\n");
                                fclose(fp);
                                return 0;
                            }
                            else {
                                printf("\n�߸��� �Է��Դϴ�.\n");
                            }
                        }
                    }


                    if (i >= 3) {

                        printf("\n�α��� �õ� Ƚ���� �ʰ��߽��ϴ�.\n���α׷� ���� : Y\nȸ������ : N\n: ");
                        scanf_s(" %c", &yn, 1);
                        while ((getchar()) != '\n' && !feof(stdin));

                        if (yn == 'Y' || yn == 'y') {
                            printf("\n���α׷��� �����մϴ�.\n");
                            fclose(fp);
                            return 0;
                        }
                        else if (yn == 'N' || yn == 'n') {
                            signup();
                            printf("\nȸ�������� �Ϸ�Ǿ����ϴ�.\n�ٽ� �����Ͽ� �α��� ���ּ���.\n");
                            return 0;
                        }
                        else {
                            printf("\n�߸��� �Է��Դϴ�. ���α׷��� ���� �մϴ�.\n");
                            return 0;
                        }

                    }
                }
            }


        }

    }


    fclose(fp);

    int choice;

    N1* carry = NULL;

    while (1) {
        printf("\n1. ���� 10�� Ǯ��\n2. ���� 20�� Ǯ��\n3. ���� 30�� Ǯ��\n");
		printf("4. ����Ʈ ���� ����\n5. ��ŷ ����\n6. ����ġ��\n");
        printf("�������� �Է��� �ּ��� : ");
        scanf("%d", &choice);
        // ��� ������ Ǯ�� ����

        int* user_answer = (int*)malloc(sizeof(int) * (choice * 10));

        if (choice >= 1 && choice <= 3) {
            printf("%d�� ���� Ǯ�⿡ ���ϴ�.\n\n", choice * 10);

            carry = question_print(choice * 10);


            for (int i = 0; i < choice * 10; i++) {

                printf("\n���� %d: \n%s%s", i + 1, carry[i].question[0], carry[i].question[1]);
                // ���� ��� (���� ��ȣ, ���� ����)

                for (int k = 0; k < 5; k++) {
                    printf("%d. %s", k + 1, carry[i].options[carry[i].indices[k]]);
                    // ���� ���� ��� (1~5�� ��ȣ �ű��)
                }

                // ����� �Է� �ޱ�
                int answer;
                while (1) {
                    printf("1 ~ 5������ ���� �� ������ �Է��� �ּ��� : ");
                    scanf("%d", &answer);
                    if (answer >= 1 && answer <= 5) {
                        user_answer[i] = answer;
                        break;
                    }
                    else {
                        printf("�߸��� �Է��Դϴ�.\n");
                        continue;
                    }
                }
            }


            correct_if(carry, user_answer, choice * 10);
            save_point(point);
			point = 0; // ���� Ǯ�� �� ���� �ʱ�ȭ
			ranking();
        }
        else if(choice == 4) {
            printf("\n����Ʈ ������ Ȯ���մϴ�.\n");
            
            pl c4;
            int i = 0;

			FILE* file = fopen("UserData.txt", "r");
            if (file == NULL) {
                printf("����Ʈ ���� ������ �� �� �����ϴ�.\n");
                return 1;
            }
            
            char line[ML];
            while (fgets(line, sizeof(line), file)) {
				if (i > 1) printf("%s", line);
                i++;
            }

			fclose(file);
            
        }
        else if(choice == 5) {
            printf("\n��ŷ�� Ȯ���մϴ�.\n");
            
			FILE* file = fopen("ranking.txt", "r");
            if (file == NULL) {
                printf("��ŷ ������ �� �� �����ϴ�.\n");
                return 1;
            }
            char line[ML];
            int i = 0;
            while (fgets(line, sizeof(line), file)) {
                    printf("%s", line);
                    i++;
            }
			fclose(file);

        }
        else if(choice == 6) {
            printf("\n���α׷��� �����մϴ�.\n");
            free(user_answer);
            return 0;
		}
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            continue;
        }
    }
}