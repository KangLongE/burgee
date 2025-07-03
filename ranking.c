#define MAX_INDEX 1024
#define ML 256
#define MAX_LOG 10
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct pline {
    char header1[ML]; // name
    char header2[ML]; // password
    char all_p[ML]; // 전체 포인트
    char logs[MAX_LOG][ML]; // point 내역 10출
    int log_count;
} pl;

void ranking();

int main(int argc, char ** argv){
printf("넘겨받은 점수: %s\n", argv[1]);
fflush(stdout);
printf("실행 성공\n");
fflush(stdout);
ranking();
return 1;
}

void ranking() {
// 랭킹을 불러와서 정렬하고 저장하는 함수
// 포인트가 추가 될 때마다 호출됨

	pl c3;
	// pl 구조체 변수 c3 선언 [pl <- pline` 구조체]

	double rank_p[10] = {0};
	// 랭킹 포인트 배열 초기화

	c3.log_count = 0;
	// 로그 개수 초기화
	// 0 ~ 9까지 10개	[MAX_LOG]

	for(int i = 0; i < MAX_LOG; i++) {
		c3.logs[i][0] = '\0';
	}
	// logs 배열 초기화

	FILE* file = fopen("C:/burgee/burgee.1/src/main/java/com/burgee/study/burgee1/UserData.txt", "r");
	// UserData.txt 파일 열기

	if (file == NULL) {
		printf("파일 열기 실패\n");
		fflush(stdout);
		exit(1);
	}

	printf("랭킹을 불러오는 중...\n");
	fflush(stdout);

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

		for(int i = 0; i < MAX_LOG; i++) {
			for(int j = i + 1; j < MAX_LOG; j++) {

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
			printf("파일 열기 실패\n");
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