// login.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024

#include <stdio.h>
#include <string.h>

struct User {
    char name[MAX_INDEX];
    int password[4];
};

struct ReadUser {
    char name[MAX_INDEX];
    int password[4];
};

int main(void)
{
    struct User user;
    struct ReadUser readuser;

    FILE* fp = fopen("C:\\Users\\user\\Desktop\\project\\signup\\UserData.txt", "r");

    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return 1;
    }

    // 사용자 입력
    printf("이름을 입력하세요: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
	// 사용자가 이름 입력

    printf("비밀번호를 4자리 숫자로 입력하세요 (각 숫자 입력 후 Enter): ");
    for (int i = 0; i < 4; i++) {
        scanf_s("%d", &user.password[i]);

        if (user.password[i] < 0 || user.password[i] > 9) {
            printf("잘못된 입력입니다. 0에서 9 사이의 숫자를 입력하세요.\n");
            i--;
        }
		// 사용자가 비밀번호 입력
    }


    // 파일에서 데이터 읽기
    char nameLine[MAX_INDEX];
    char passwordLine[MAX_INDEX];

    fgets(nameLine, sizeof(nameLine), fp); // name 줄 읽기
    fgets(passwordLine, sizeof(passwordLine), fp); // password 줄 읽기

    sscanf_s(nameLine, "name: %[^\n]", readuser.name, MAX_INDEX); // 파일에서 이름 추출
    sscanf_s(passwordLine, "password: %d-%d-%d-%d",
        &readuser.password[0], &readuser.password[1],
        &readuser.password[2], &readuser.password[3]);
	// 파일에서 비밀번호 추출

    // 비교
    int match = 0;
    if (strcmp(user.name, readuser.name) == 0) {
        match = 1;
        for (int i = 0; i < 4; i++) {
            if (user.password[i] != readuser.password[i]) {
                match = 0;
                break;
            }
        }

        if (match) {
            printf("로그인 성공!\n");
        }
        else {
            printf("비밀번호가 일치하지 않습니다.\n");
        }
    }
    else {
        printf("이름이 일치하지 않습니다.\n");
    }
	// 파일에 저장된 사용자 이름과 비밀번호와 비교하여 로그인 성공 여부 출력

    fclose(fp);
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
