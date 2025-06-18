// quiz.js - Emscripten 모듈이 로드된 뒤 실행되는 JS

const SELECT_COUNT = 10;

function getQuestion(index) {
    const ptr = Module.ccall('getQuestionJSON', 'number', ['number'], [index]);
    const jsonStr = Module.UTF8ToString(ptr);
    return JSON.parse(jsonStr);
}

function renderQuiz() {
    const quizDiv = document.getElementById('quiz');
    quizDiv.innerHTML = '';

    for (let i = 0; i < SELECT_COUNT; i++) {
        const q = getQuestion(i);

        const qDiv = document.createElement('div');
        qDiv.className = 'question';

        const qTitle = document.createElement('h3');
        qTitle.textContent = `${i + 1}. ${q.question}`;
        qDiv.appendChild(qTitle);

        const optionsDiv = document.createElement('div');
        optionsDiv.className = 'options';

        q.options.forEach((opt, idx) => {
            const id = `q${i}_opt${idx+1}`;
            const label = document.createElement('label');
            label.htmlFor = id;

            const input = document.createElement('input');
            input.type = 'radio';
            input.name = `q${i}`;
            input.id = id;
            input.value = idx + 1;

            label.appendChild(input);
            label.appendChild(document.createTextNode(opt));

            optionsDiv.appendChild(label);
        });

        qDiv.appendChild(optionsDiv);
        quizDiv.appendChild(qDiv);
    }
}

function gradeAnswers() {
    const userAnswers = new Int32Array(SELECT_COUNT);

    for (let i = 0; i < SELECT_COUNT; i++) {
        const selected = document.querySelector(`input[name=q${i}]:checked`);
        userAnswers[i] = selected ? parseInt(selected.value) : 0;
    }

    const ptr = Module._malloc(SELECT_COUNT * 4);
    Module.HEAP32.set(userAnswers, ptr >> 2);

    const correctCount = Module.ccall('gradeAnswers', 'number', ['number'], [ptr]);

    Module._free(ptr);

    return correctCount;
}

// Emscripten 모듈 초기화 완료 시
Module.onRuntimeInitialized = () => {
    Module.ccall('loadQuestions', null, [], []);
    Module.ccall('pickRandomQuestions', null, [], []);
    renderQuiz();

    document.getElementById('submitBtn').addEventListener('click', () => {
        const correct = gradeAnswers();
        document.getElementById('result').textContent = `정답 ${correct}개 / ${SELECT_COUNT}개 맞았습니다!`;
    });
};
