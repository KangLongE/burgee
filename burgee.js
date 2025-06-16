// burgee.js

document.addEventListener('DOMContentLoaded', () => {
  const memoInput = document.querySelector('.memo-input');

  // 저장된 메모 불러오기
  const savedMemo = localStorage.getItem('memoContent');
  if (savedMemo) {
    memoInput.value = savedMemo;
  }

  // 입력 시 자동 저장
  memoInput.addEventListener('input', () => {
    localStorage.setItem('memoContent', memoInput.value);
  });
});
