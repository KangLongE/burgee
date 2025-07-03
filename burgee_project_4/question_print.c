#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1024
#define ML 256
#define MAX_LOG 10
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


double point = 0;

typedef struct question {

    char question[2][MAX_INDEX];
    // 문제 2줄

    char options[5][MAX_INDEX];
    // 보기 5줄

    int indices[5];
    // 섞인 보기 index

    int correct_answer;
    // 각 문제 정답


} N1;

typedef struct Log {
    char id[50];
    // 포인트 기록 ID & 랭킹용
    // 그냥 이름

    double point;
    // 포인트 기록

    char date[20];
    // 포인트 기록 날짜
} log;

typedef struct pline {
    char header1[ML]; // name
    char header2[ML]; // password
    char all_p[ML]; // 전체 포인트
    char logs[MAX_LOG][ML]; // point 내역 10출
    int log_count;
} pl;

void shuffle(int* arr, int size);
N1* question_suffle(int n);
int* correct_if(int* un, int n);
void save_point(double point);
void ranking();


//문제 출력 파일
//문제를 출력하려면 이 파일을 실행
//포인트 저장, 랭킹 등록, 결과 출력까지 한 번에 다함

void main(int argc, char ** argv) {
// argc: 인자 개수, argv: 인자 배열

    int num = atoi(argv[1]);
	// 문제 개수 (1 ~ 3)

    N1* carry = NULL;
	// 문제를 담을 구조체 포인터


    if (argc == 2) {
// 인자개수가 1이면 문제 출력 모드

        carry = question_suffle(num * 10);
        // question_logic.c (question_data.h)
        // 문제를 섞고 carry구조체 포인터로 가리킴

            if (num >= 1 && num <= 3) {

                for (int i = 0; i < num * 10; i++) {

                    printf("Q:%s\nQ:%s\n", carry[i].question[0], carry[i].question[1]);
					fflush(stdout);
                    // 문제 출력 (문제 번호, 문제 내용)

                    for (int k = 0; k < 5; k++) {
                        printf("A:%s\n", carry[i].options[carry[i].indices[k]]);
                        fflush(stdout);
                        // 섞인 보기 출력 (1~5로 번호 매기기)
                    }

                }

                FILE* fp;
                fp = fopen("correct.txt", "w");

                if (fp == NULL) {
                    printf("E:%d\n", 0);  //실패 신호 [0]
                    fflush(stdout);
                    perror("정답 파일 열기 실패\n");
                    exit(1);
                }

                for (int i = 0; i < num * 10; i++) {
                    fprintf(fp, "%d ", carry[i].correct_answer);
                }
                fclose(fp);
            }

            free(carry);

    }
    else {
// 인자개수가 여려개 이상이면 정답 확인 모드

        int* user_answer = (int*)malloc(sizeof(int) * (num * 10));

        // 사용자가 입력한 정답을 저장할 배열
        

        if (argc < num * 10 + 2) {
            printf("E:%d\n", 0);  //실패 신호 [0]
            fflush(stdout);
            perror("인자 개수 부족\n");
            free(user_answer);
            free(carry);
            exit(1);
        }

        for (int i = 0; i < num * 10; i++) {
			user_answer[i] = atoi(argv[2 + i]);
            // 안자 번호 1은 문제 개수
			// 2번부터는 사용자가 입력한 정답
        }

        correct_if(user_answer, num * 10);
		// question_logic.c     (question_data.h)
		// 정답 확인 함수 호출
        
        save_point(point);
        // point.c      (question_data.h)
        // 정답 확인 및 포인트 저장
		

        point = 0;
        // 문제 풀이 후 점수 초기화

        ranking();
		// ranking.c    (question_data.h)
		// 랭킹 업데이트


        free(user_answer);
    }

}


int* correct_if(int* un, int n) {
    // un: 사용자가 입력한 정답 배열
    // n: 문제 개수

    int* true_answer = (int*)malloc(sizeof(int) * n);
    // true_answer: 정답 여부를 저장할 배열 (1: 맞음, 0: 틀림)

    if (true_answer == NULL) {
        printf("E:%d\n", 0);  //실패 [0]
        perror("메모리 할당 실패\n");
        exit(1);
    }

    FILE* fp;
    fp = fopen("correct.txt", "r");

    if (fp == NULL) {
        printf("E:%d\n", 0);   //실패 [0]
        fflush(stdout);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        // 문제 개수만큼 반복

        int correct;
        if (fscanf(fp, "%d", &correct) != 1) { // 파일에서 정답 읽기
            printf("E:%d\n", 0); //실패 신호 [0]
            perror("정답 파일 읽기 오류\n");
            exit(1);
        }

        if (un[i] == correct) {

            true_answer[i] = 1;
            printf("R:%d\n", 1);  //맟히면 [1]
            fflush(stdout);
            point++;
        }
        else {
            true_answer[i] = 0;
            printf("R:%d\n", 0);  //못 맞히면 [0]
            fflush(stdout);
        }
        // 정답 비교 (정답이면 1, 틀리면 0 저장)

    }


    printf("S:%d\n", (int)point);   //    [맞힌 총 점수]
    fflush(stdout);
    printf("P:%.4f%%\n", (float)point / n * 100); //  [점수 백분율]
    fflush(stdout);
    // 점수 출력 (맞춘 문제 수, 총 문제 수, 백분율)

    point = (point / n) * 100;
    // 포인트 저장

    return true_answer;
}


N1* question_suffle(int n) {
    // n: 문제 개수 (10 ~ 30)

    N1* q = (N1*)malloc(sizeof(N1) * n);
    // 문제 구조체 배열 동적 할당  [메모리 공간 아끼기 위해]


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            q[i].indices[j] = j;
        }
    }
    // 보기 배열 초기화

    srand((unsigned int)time(NULL));

    FILE* fp;
    fp = fopen("question.txt", "r");
    // 문제가 저장된 파일 열기

    if (fp == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    int i = 0;
    int* number = (int*)malloc(sizeof(int) * n);
    // 랜덤 번호 저장 배열 동적 할당    [메모리 공간 아끼기 위해]

    while (i < n) {

        int random = rand() % 30; // 파일에 있는 총 문제 수 입력
        int nk = 1;

        for (int j = 0; j < i; j++) {
            if (number[j] == random) {
                nk = 0;
                break;
            }
        }
        // 중복 체크


        if (nk) {
            number[i] = random;
            i++;
        }
        // 중복되지 않는 랜덤 번호 생성
    }

    for (int i = 0; i < n; i++) {
        // 문제 수 만큼 출력 반복

        rewind(fp);
        // 파일 포인터를 처음으로 되돌림

        char line[MAX_INDEX];
        // 한 줄씩 읽기 위한 변수

        int target = number[i];
        // 랜덤으로 선택된 읽을 문제 번호

        int start_line = target * 8;
        // 문제 번호에 해당하는 줄 번호 계산
        // 해당 문제 시작 줄 (문제당 8줄)

        int curr_line = 0;
        // 현재 줄 번호
        int correct_idx = -1;
        // 정답 인덱스 번호

        // 질문, 보기, 정답 읽기
        while (fgets(line, sizeof(line), fp)) {
            // 한 줄씩 읽고 line에 저장

            line[strcspn(line, "\n")] = '\0';
            // 개행 문자 제거

            if (curr_line == start_line) strcpy(q[i].question[0], line);
            // line과 start_line이 같으면
            // 질문 읽기 1
            else if (curr_line == start_line + 1) strcpy(q[i].question[1], line);
            // line과 start_line + 1이 같으면    [두번째 줄]
            // 질문 읽기 2
            else if (curr_line >= start_line + 2 && curr_line < start_line + 7) {
                // line이 질문 두개를 읽고 정답읽기 전까지     [3포함 ~ 7포함 줄]
                // 보기 범위 2~6줄 읽기    [총 다섯 줄]
                strcpy(q[i].options[curr_line - start_line - 2], line);
            }
            else if (curr_line == start_line + 7) {
                // 질문, 보기 읽고 마지막 줄 읽기   [8번째 줄]
                correct_idx = atoi(line) - 1;
                // 정답 인덱스 읽기
                break;
            }
            curr_line++;
            // 현재 줄 번호 증가
        }

        shuffle(q[i].indices, 5);
        // 보기 섞기

        int new_correct = -1;
        // 새로운 정답 인덱스

        for (int k = 0; k < 5; k++) {
            if (q[i].indices[k] == correct_idx) {
                // 섞인 보기에서 정답 인덱스 찾기
                new_correct = k + 1;
                q[i].correct_answer = new_correct;
                // 해당 문제에 정답 저장 (사용자 보기 1~5로 번호 매기기)
                break;
            }
        }

    }

    free(number);
    // 동적 할당된 번호 배열 해제

    fclose(fp);
    // 파일 닫기

    return q;
    // 섞인 문제 구조체 배열 반환 [carry 구조체 포인터로 받음]

}


void shuffle(int* arr, int size) {
    //보기 섞음
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // 0부터 i까지 중 랜덤 인덱스
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}



void save_point(double point) {
    //question_print.c에서 호출  [question_data.h]
    //point는 question_logic.c에서 correct_if에서 반환

    log c1;     //[question_data.h]
    //id[50]
    //point
    //date[20]

    pl c2;      //[question_data.h]
    //header1[ML]       name
    //header2[ML]       password
    //all_p[ML]         총 포인트 점수를 읽을 줄
    //logs[MAX_LOG][ML] 포인트 내역
    //log_count         로그 카운트

    double total_p = 0;
    // 총 포인트 점수를 받을 변수

    for (int i = 0; i < MAX_LOG; i++) {
        c2.logs[i][0] = '\0';
    }
    // logs 배열 초기화

    FILE* file = fopen("UserData.txt", "r");
    //파일 읽기

    if (file == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    c2.log_count = 0;
    // 카운트 초기화

    // 헤더 세 줄 읽기
    fgets(c2.header1, ML, file);    //name
    fgets(c2.header2, ML, file);    //password
    fgets(c2.all_p, ML, file);      //총 포인트

    if (c2.all_p[0] == '\0') {
        strcpy(c2.all_p, "전체 포인트: 0\n");
        // 전체 포인트가 비어있으면 초기화
    }
    else {

        total_p = atoi(c2.all_p + strcspn(c2.all_p, ":") + 1);
        // 총 포인트 점수 줄을 읽고
        //전체 포인트 숫자 추출
        c2.all_p[strcspn(c2.all_p, "\n")] = '\0'; // 개행 문자 제거
    }


    while (c2.log_count < MAX_LOG && fgets(c2.logs[c2.log_count], ML, file) != NULL) {
        c2.log_count++;
    }
    // 기존 포인트 내역 읽기 (최대 10개)

    fclose(file);
    //읽기 파일 닫기


    // ID 추출 (header1에서)
    // 예: "name: eum\n"
    sscanf(c2.header1, "name: %s", c1.id);

    // 전체 포인트 갱신
    total_p += point;
    sprintf(c2.all_p, "전체 포인트: %.4f\n", total_p);

    //포인트 값 넣기
    c1.point = point;

    // 날짜 생성
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(c1.date, sizeof(c1.date), "%Y-%m-%d-%H:%M", tm_info);

    // 새 로그 만들기
    char new_log[ML];
    snprintf(new_log, ML, "%s/%s : %.4f\n", c1.date, c1.id, c1.point);
    //예 : 2025-06-05-12:30/eum 12.2222


    // logs 배열 한 칸씩 아래로 밀기 (맨 아래 내역은 사라짐)
    for (int i = MAX_LOG - 1; i > 0; i--) {
        strcpy(c2.logs[i], c2.logs[i - 1]);
    }
    strcpy(c2.logs[0], new_log); // 새 로그를 맨 위에 추가

    file = fopen("UserData.txt", "w, ccs=UTF-8");
    //파일 쓰기로 열기
    //파일 다시 쓰기

    if (file == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    // 헤더 두 줄과 전체 포인트 쓰기
    fputs(c2.header1, file);
    fputs(c2.header2, file);
    fputs(c2.all_p, file);

    for (int i = 0; i < MAX_LOG; i++) {
        if (c2.logs[i][0] != '\0')
            fputs(c2.logs[i], file);
    }
    // 최대 10개 내역만 기록

    fclose(file);
    //파일 닫기
}
        
void ranking() {
    // 랭킹을 불러와서 정렬하고 저장하는 함수
    // 포인트가 추가 될 때마다 호출됨

    pl c3;
    // pl 구조체 변수 c3 선언 [pl <- pline` 구조체]

    double rank_p[10] = { 0 };
    // 랭킹 포인트 배열 초기화

    c3.log_count = 0;
    // 로그 개수 초기화
    // 0 ~ 9까지 10개	[MAX_LOG]

    for (int i = 0; i < MAX_LOG; i++) {
        c3.logs[i][0] = '\0';
    }
    // logs 배열 초기화

    FILE* file = fopen("UserData.txt", "r");
    // UserData.txt 파일 열기

    if (file == NULL) {
        perror("파일 열기 실패");
        exit(1);
    }

    printf("랭킹을 불러오는 중...\n");

    char line[ML];
    // 한 줄씩 읽기 위한 변수	[12줄까지 읽을 수 있도록 설정]
    // 두줄은 헤더로 사용 name, password

    // 남은 10줄은 랭킹 기록용
    // 예: "2025.06.05.12:00/eum : 10\n"

    char name[ML];
    // 닉네임 저장용 변수

    while (fgets(line, ML, file) != NULL && c3.log_count < MAX_LOG + 2) {
        // 파일에서 한 줄씩 읽기

        if (c3.log_count >= 2) {
            // 헤더 두 줄을 제외하고 랭킹 기록 읽기

            if (strchr(line, '/') && strrchr(line, ':')) {
                // 예: "2025.06.05.12:00/eum : 10"

                char* slash = strchr(line, '/');
                // /eum 이름 읽을 준비

                char* colon = strrchr(line, ':');
                // : 10 포인트 읽을 준비

                if (colon != NULL) {
                    double score = atof(colon + 1);
                    // ':' 다음 위치부터 숫자 추출
                    // : 점수
                }

                if (slash && colon) {
                    // 이름 추출
                    slash++;  // '/' 다음 문자부터
                    char* end = strchr(slash, ' ');  // 공백 전까지가 닉네임
                    if (!end) continue;
                    int name_len = end - slash;
                    // 이름 길이 계산
                    if (name_len >= ML) name_len = ML - 1;
                    // 길이의 크기가 name의 크기보더 클 수 있어서
                    strncpy(name, slash, name_len);
                    // 이름 복사
                    name[name_len] = '\0';
                    // 문자열 끝에 널 문자 추가


                    int score = atoi(colon + 1);
                    // :을 제외한 점수 읽기	[숫자만 추출]

                    // logs와 점수 저장
                    sprintf(c3.logs[c3.log_count - 2], "%s", name);
                    // 닉네임만 저장
                    rank_p[c3.log_count - 2] = score;
                    // rank_p에 점수 저장


                    if (c3.log_count >= MAX_LOG) break;
                    // 로그 개수가 최대치에 도달하면 중단
                }
            }
        }
        c3.log_count++;
        // 로그 개수 증가
    }

    fclose(file);

    char aemp[ML];
    // 임시 변수 aemp 선언	[사용자 바꾸기 위함]
    double bemp;
    // 임시 변수 bemp 선언	[포인트 바꾸기 위함]

    for (int i = 0; i < MAX_LOG; i++) {
        for (int j = i + 1; j < MAX_LOG; j++) {

            if (rank_p[i] < rank_p[j]) {
                // 랭킹 포인트 비교
                // i번째 포인트가 j번째 포인트보다 낮으면

                strcpy(aemp, c3.logs[i]);
                strcpy(c3.logs[i], c3.logs[j]);
                strcpy(c3.logs[j], aemp);
                //가장 높은 포인트를 가진 사용자 데이터를 위로 올림

                bemp = rank_p[i];
                rank_p[i] = rank_p[j];
                rank_p[j] = bemp;
                //가장 높은 포인트를 위로 올림


            }
        }
    }

    file = fopen("ranking.txt", "w");
    // 랭킹 파일 열기

    if (file == NULL) {
        perror("파일 열기 실패");
        exit(0);
    }

    for (int i = 0; i < MAX_LOG; i++) {
        if (c3.logs[i][0] != '\0') {
            fprintf(file, "%d) %s : %.4f\n", i + 1, c3.logs[i], rank_p[i]);
            // 랭킹 파일에 기록
        }

    }
    printf("랭킹을 ranking.txt에 저장했습니다.\n");
    fclose(file);


}