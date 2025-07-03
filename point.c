#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define ML 256
#define MAX_LOG 10
#define MAX_INDEX 1024
#define ML 256
#define MAX_LOG 10


typedef struct pline {
	char header1[ML]; // name
	char header2[ML]; // password
	char all_p[ML]; // 전체 포인트
	char logs[MAX_LOG][ML]; // point 내역 10출
	int log_count;
} pl;

typedef struct Log {
	char id[50];
	// 포인트 기록 ID & 랭킹용
	// 그냥 이름

	double point;
	// 포인트 기록

	char date[20];
	// 포인트 기록 날짜

} log;


void save_point(double point, char* name);
void ranking();



int main(int argc, char** argv) {

    setlocale(LC_ALL, "");
	double point = atof(argv[1]);
	printf("C파일 실행 성공!\n");
	fflush(stdout);

	save_point(point, argv[2]);
	ranking();
	return 0;
}


void save_point(double point, char* name) {
	//question_print.c에서 호출  [question_data.h]
	//point는 question_logic.c에서 correct_if에서 반환


	printf("p 함수 실행\n");
	fflush(stdout);

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

	FILE* file = fopen("C:/burgee/burgee.1/src/main/java/com/burgee/study/burgee1/UserData.txt", "r");
	//파일 읽기

	if (file == NULL) {
		printf("UD 파일 열기 실패\n");
		fflush(stdout);
		exit(1);
	}

	c2.log_count = 0;
	// 카운트 초기화

	// 헤더 두 줄 읽기
	//name
	if (fgets(c2.header1, ML, file) == NULL) {
		sprintf(c2.header1, "name : %s\n", name);
	}

	fgets(c2.all_p, ML, file);      //총 포인트

	if (c2.all_p[0] == '\0') {
		strcpy(c2.all_p, "전체 포인트: 0\n");
		// 전체 포인트가 비어있으면 초기화
	}
	else {

		total_p = atof(c2.all_p + strcspn(c2.all_p, ":") + 1);
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


	// 예: "name: eum\n"
	strcpy(c1.id, name);

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

	file = fopen("C:/burgee/burgee.1/src/main/java/com/burgee/study/burgee1/UserData.txt", "w");
	//파일 쓰기로 열기
	//파일 다시 쓰기

	if (file == NULL) {
		printf("UD 파일 열기 실패\n");
		fflush(stdout);
		exit(1);
	}

	// 헤더 두 줄과 전체 포인트 쓰기
	fputs(c2.header1, file);
	fputs(c2.all_p, file);

	for (int i = 0; i < MAX_LOG; i++) {
		if (c2.logs[i][0] != '\0')
			fputs(c2.logs[i], file);
	}
	// 최대 10개 내역만 기록

	printf("P 함수 완료\n");
	fflush(stdout);

	fclose(file);
	//파일 닫기
}











void ranking() {
	// 랭킹을 불러와서 정렬하고 저장하는 함수
	// 포인트가 추가 될 때마다 호출됨


	printf("R 함수 불러오기 성공\n");
	fflush(stdout);

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

	FILE* file = fopen("C:/burgee/burgee.1/src/main/java/com/burgee/study/burgee1/UserData.txt", "r");
	// UserData.txt 파일 열기

	if (file == NULL) {
		printf("R 파일 열기 실패\n");
		fflush(stdout);
		exit(1);
	}

	char line[ML];
	// 한 줄씩 읽기 위한 변수	[12줄까지 읽을 수 있도록 설정]
	// 두줄은 헤더로 사용 name, password

	// 남은 10줄은 랭킹 기록용
	// 예: "2025.06.05.12:00/eum : 10\n"

	char name[ML];
	// 닉네임 저장용 변수
    double score = 0;

	while (fgets(line, ML, file) != NULL && c3.log_count < MAX_LOG + 1) {
		// 파일에서 한 줄씩 읽기

		if (c3.log_count >= 1) {
			// 헤더 두 줄을 제외하고 랭킹 기록 읽기

			if (strchr(line, '/') && strrchr(line, ':')) {
				// 예: "2025.06.05.12:00/eum : 10"

				char* slash = strchr(line, '/');
				// /eum 이름 읽을 준비

				char* colon = strrchr(line, ':');
				// : 10 포인트 읽을 준비

				if (colon != NULL) {
					score = atof(colon + 1);
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

					// logs와 점수 저장

					sprintf(c3.logs[c3.log_count - 1], "%s", name);
					// 닉네임만 저장
					rank_p[c3.log_count - 1] = score;
					// rank_p에 점수 저장


					if ((c3.log_count - 1) >= MAX_LOG) break;
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

	file = fopen("C:/burgee/burgee.1/src/main/java/com/burgee/study/burgee1/ranking.txt", "w");
	// 랭킹 파일 열기

	if (file == NULL) {
		printf("R 파일 열기 실패\n");
		fflush(stdout);
		exit(0);
	}

	for (int i = 0; i < MAX_LOG; i++) {
		if (c3.logs[i][0] != '\0') {
			fprintf(file, "%d) %s : %.4f\n", i + 1, c3.logs[i], rank_p[i]);
			// 랭킹 파일에 기록
		}

	}
	printf("랭킹을 ranking.txt에 저장했습니다.\n");
	fflush(stdout);

	fclose(file);


}