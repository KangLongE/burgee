#include <emscripten/emscripten.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define MAX_QUESTIONS 100
#define SELECT_COUNT 10
#define MAX_OPTION_LEN 128

typedef struct {
    char question[256];
    char options[5][MAX_OPTION_LEN];
    int answer; // 1~5
} Question;

Question allQuestions[MAX_QUESTIONS];
int totalQuestions = 0;
Question selectedQuestions[SELECT_COUNT];

// 외부에서 문제를 불러올 함수 (예: JS에서 직접 세팅 가능)
EMSCRIPTEN_KEEPALIVE
void loadQuestions(Question* questions, int count) {
    memcpy(allQuestions, questions, sizeof(Question) * count);
    totalQuestions = count;
    srand((unsigned int)time(NULL));
}

// 보기 섞기 함수
void shuffleOptions(Question* q) {
    typedef struct {
        char text[MAX_OPTION_LEN];
        int originalIndex;
    } Option;

    Option tempOptions[5];
    int correctIndex = q->answer - 1;

    for (int i = 0; i < 5; i++) {
        strcpy(tempOptions[i].text, q->options[i]);
        tempOptions[i].originalIndex = i;
    }

    for (int i = 4; i > 0; i--) {
        int j = rand() % (i + 1);
        Option tmp = tempOptions[i];
        tempOptions[i] = tempOptions[j];
        tempOptions[j] = tmp;
    }

    for (int i = 0; i < 5; i++) {
        strcpy(q->options[i], tempOptions[i].text);
        if (tempOptions[i].originalIndex == correctIndex) {
            q->answer = i + 1;
        }
    }
}

// 랜덤 문제 10개 선택 및 정답 보기 섞기
EMSCRIPTEN_KEEPALIVE
void pickRandomQuestions() {
    for (int i = 0; i < SELECT_COUNT; i++) {
        int idx = rand() % totalQuestions;
        selectedQuestions[i] = allQuestions[idx];
        shuffleOptions(&selectedQuestions[i]);
    }
}

// 문제 JSON 형식으로 얻기 (quiz.js에서 문자열로 받을 수 있게)
EMSCRIPTEN_KEEPALIVE
const char* getQuestionJSON(int idx) {
    static char buffer[2048];
    if (idx < 0 || idx >= SELECT_COUNT) return "";

    Question* q = &selectedQuestions[idx];

    char optionsJson[1024] = "";
    for (int i = 0; i < 5; i++) {
        char optEscaped[256] = {0};
        // 간단하게 큰따옴표만 이스케이프
        int j=0, k=0;
        while(q->options[i][j] && k<255) {
            if (q->options[i][j] == '"') {
                optEscaped[k++] = '\\';
                optEscaped[k++] = '"';
            } else {
                optEscaped[k++] = q->options[i][j];
            }
            j++;
        }
        optEscaped[k] = 0;
        char temp[256];
        if(i < 4) snprintf(temp, sizeof(temp), "\"%s\",", optEscaped);
        else snprintf(temp, sizeof(temp), "\"%s\"", optEscaped);
        strcat(optionsJson, temp);
    }

    snprintf(buffer, sizeof(buffer),
        "{\"question\":\"%s\", \"options\":[%s], \"answer\":%d}",
        q->question,
        optionsJson,
        q->answer);

    return buffer;
}

EMSCRIPTEN_KEEPALIVE
int getSelectedCount() {
    return SELECT_COUNT;
}

