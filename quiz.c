#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h>

#define MAX_QUESTIONS 100
#define MAX_LINE 256
#define SELECT_COUNT 10

typedef struct {
    char question[256];
    char options[5][128];
    int answer;
} Question;

Question allQuestions[MAX_QUESTIONS];
Question selectedQuestions[SELECT_COUNT];
int totalQuestions = 0;

EMSCRIPTEN_KEEPALIVE
void loadQuestions() {
    FILE *file = fopen("question.txt", "r");
    if (!file) return;

    while (fgets(allQuestions[totalQuestions].question, sizeof(allQuestions[totalQuestions].question), file)) {
        allQuestions[totalQuestions].question[strcspn(allQuestions[totalQuestions].question, "\n")] = '\0';

        for (int i = 0; i < 5; i++) {
            fgets(allQuestions[totalQuestions].options[i], sizeof(allQuestions[totalQuestions].options[i]), file);
            allQuestions[totalQuestions].options[i][strcspn(allQuestions[totalQuestions].options[i], "\n")] = '\0';
        }

        char answerLine[10];
        fgets(answerLine, sizeof(answerLine), file);
        allQuestions[totalQuestions].answer = atoi(answerLine);
        totalQuestions++;
    }

    fclose(file);
}

EMSCRIPTEN_KEEPALIVE
void pickRandomQuestions() {
    for (int i = 0; i < SELECT_COUNT; i++) {
        int idx = rand() % totalQuestions;
        selectedQuestions[i] = allQuestions[idx];
    }
}

EMSCRIPTEN_KEEPALIVE
const char* getQuestionJSON(int index) {
    static char buffer[1024];
    if (index < 0 || index >= SELECT_COUNT) return "{}";

    snprintf(buffer, sizeof(buffer),
        "{\"question\":\"%s\",\"options\":[\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"]}",
        selectedQuestions[index].question,
        selectedQuestions[index].options[0],
        selectedQuestions[index].options[1],
        selectedQuestions[index].options[2],
        selectedQuestions[index].options[3],
        selectedQuestions[index].options[4]
    );
    return buffer;
}

EMSCRIPTEN_KEEPALIVE
int gradeAnswers(int* userAnswers) {
    int correct = 0;
    for (int i = 0; i < SELECT_COUNT; i++) {
        if (userAnswers[i] == selectedQuestions[i].answer) correct++;
    }
    return correct;
}

// 새로 추가: getRandomNumber 함수 (컴파일 시 export할 함수)
EMSCRIPTEN_KEEPALIVE
int getRandomNumber() {
    return rand();
}
