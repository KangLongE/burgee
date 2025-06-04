// signup.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>

struct User {
    char name[MAX_INDEX];
    int password[4];
};

int main(void)
{
    struct User user;

    FILE* fp;
    fp = fopen("UserData.txt", "w");

    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return 1;
    }


    printf("이름을 입력하세요: ");
    fgets(user.name, sizeof(user.name), stdin);

    fprintf(fp, "name: %s", user.name);

    printf(" 비밀번호를 4자리 숫자로 입력하세요: ");
    for (int i = 0; i < 4; i++) {

        scanf_s("%d", &user.password[i]);

        if (user.password[i] < 0 || user.password[i] > 9) {
            printf("잘못된 입력입니다. 0에서 9 사이의 숫자를 입력하세요.\n");
            i--;
        }
    }


    fprintf(fp, "password: ");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d", user.password[i]);
        if (i < 3) {
            fprintf(fp, "-");
        }
    }



    fclose(fp);

    printf("파일에 저장 완료\n");
    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
