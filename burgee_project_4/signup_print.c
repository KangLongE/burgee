
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int success = 0;

typedef struct User {
    char name[MAX_INDEX];
    int password[4];
} User;

int signup(char* name, int* password);
int login(char* name, int* password);


//signup 파일
//회원 가입 하려면 이 파일을 실행

int main(int argc, char** argv) {
// argc: 인자 개수, argv: 인자 배열
    // 인자개수 1은 값을 보내지 않음
	// 인자개수 2는 값을 한개 보낸거임

    int i = 0;

    FILE* fp;
    fp = fopen("UserData.txt", "r, ccs=UTF-8");
	// UserData.txt 파일 열기
    
    if (fp == NULL) {
        perror("파일 열기 실패\n");
        exit(1);
	}

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
	// 파일 크기 확인


    if (argc == 1) {
//인자개수가 1   [값을 보내지 않음]
// 값을 보내지 않으면 로그인 상태 확인

        if (fp == NULL || size == 0) {
	    // 파일이 비어있거나 존재하지 않으면

            printf("E:%d\n", 0);    //로그인이 가능하지 않다는 신호를 보냄    [0]
			fflush(stdout);
            perror("로그인이 되어있지 않습니다.");

        }
        else {
        // 파일이 존재하고 비어있지 않으면

			printf("E:%d\n", 1);    //로그인 가능 신호 보냄    [1]
            fflush(stdout);
        }
    }


    if (argc >= 2) {
	// 인자 개수가 2이면 회원기압 및 로그인 여부 확인
	//회원가입 하겠다   [1]
	// 프로그램 종료    [0]

        if (argv[1]) {
        //회원가입 하겠다   [1]


        int success = 0;

        User u1;
            
        strcpy(u1.name, argv[2]);

            for (int i = 0; i < 4; i++) {

                char* endptr;
                long val = strtol(argv[3 + i], &endptr, 10);
                //argv의 값을 10진법의 형식으로 val에 변환된 값을 넣음
                //변환이 안 되면 endptr에 0을 반환

                if (*endptr != '\0' || val < 0 || val > 9) {
                    printf("E:%d\n", 0);	//중단 신호		[0]
                    fflush(stdout);
                    printf("EC:%s\n", argv[3 + i]);		//중단의 원인 출력
                    fflush(stdout);
                    exit(1);
                }
                else {
                    u1.password[i] = val;
                }

            }

            success = signup(u1.name, u1.password);
            // signup.c     [sign_log.h]
            // 회원가입 함수 호출

            if (success) {
                printf("E:%d\n", 1);  //성공 신호 [1]
                fflush(stdout);
                perror("%성공!\n");
            }
            else {
                printf("E:%d\n", 0);    //실패 신호 [0]
                fflush(stdout);
                perror("실패!\n");
            }

        }
        else {
        //프로그렘 종료   [0]

            printf("E:%d\n", 0); //종료 신호를 보냄    [0]
            fflush(stdout);
            perror("프로그렘을 종료합니다.\n");
        }
    }

}


int signup(char* name, int* password)
{

    FILE* fp;
    fp = fopen("UserData.txt", "w, ccs=UTF-8");
    // UserData.txt 파일 열기

    if (fp == NULL) {
        perror("파일 열기 실패\n");
        return 0;
    }

    // UserData.txt 파일에 이름 입력
    fprintf(fp, "name: %s", name);

    fprintf(fp, "password: ");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d", password[i]);
        if (i < 3) {
            fprintf(fp, "-");
        }
    }
    fprintf(fp, "\n");
    // UserData.txt 파일에 비밀번호 입력



    fclose(fp);

    perror("파일에 저장 완료");
    return 1;
}