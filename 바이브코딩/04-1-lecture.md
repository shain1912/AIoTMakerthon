---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 4-1강 - JavaScript 기초 문법'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 JavaScript 기초 및 DOM 조작 (1부)

## 웹을 살아 움직이게 하는 JavaScript

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1627398242454-45a1465c2479?w=400&h=300&fit=crop)

---

## 📋 4-1교시 학습 목표

- **JavaScript 핵심 문법 이해**: 변수, 함수, 조건문
- **DOM 기초**: 웹 요소를 JavaScript로 선택하기
- **기본 이벤트 처리**: 클릭 이벤트 다루기
- **실전 예제**: 간단한 인터랙션 구현

---

## 🔗 필요한 준비물

- [ ] VSCode + Live Server
- [ ] 이전 교시 HTML/CSS 파일
- [ ] Chrome 브라우저 개발자 도구
- [ ] JavaScript에 대한 호기심! 💻

![bg right:35% w:350](https://images.unsplash.com/photo-1461749280684-dccba630e2f6?w=350&h=250&fit=crop)

---

# 📖 JavaScript란 무엇인가?

## 🎯 정의

**JavaScript**는 웹페이지에 생명을 불어넣는 프로그래밍 언어입니다.

- **HTML**(구조) + **CSS**(디자인) + **JavaScript**(동작)
- 브라우저에서 실행되는 클라이언트 사이드 언어
- 동적이고 인터랙티브한 웹페이지 제작 가능

![bg right:40% w:400](https://images.unsplash.com/photo-1555066931-4365d14bab8c?w=400&h=300&fit=crop)

---

## ✨ JavaScript 핵심 특징

### **1. 동적 타입 언어**
```javascript
let message = "안녕하세요"; // 문자열
message = 42;              // 숫자로 변경 가능
message = true;            // 불린값으로 변경 가능
```

### **2. 이벤트 기반 프로그래밍**
- 사용자 클릭, 키보드 입력, 마우스 움직임에 반응
- 비동기적 처리로 부드러운 사용자 경험

### **3. 객체 기반 언어**
- 모든 것이 객체 (문자열, 숫자, 함수도 객체)
- DOM을 통해 HTML 요소 조작

---

## 💡 HTML vs CSS vs JavaScript

| 역할 | HTML | CSS | JavaScript |
|------|------|-----|------------|
| **목적** | 구조/내용 | 디자인/스타일 | 동작/상호작용 |
| **예시** | `<button>클릭</button>` | `button { color: blue; }` | `button.addEventListener('click', ...)` |
| **결과** | 버튼 생성 | 파란색 버튼 | 클릭하면 동작 |

---

# 🛠️ JavaScript 기본 문법

## 변수 선언 (let, const)

```javascript
// 모던 JavaScript 변수 선언
let userName = "바이브코딩";        // 변경 가능한 변수
const API_KEY = "abc123";         // 상수 (변경 불가)
let age = 25;                     // 숫자
let isStudent = true;             // 불린값

// 변수 재할당
userName = "새로운 이름";          // ✅ 가능
// API_KEY = "new123";            // ❌ 에러! const는 변경 불가
```

### **var은 사용하지 말자!**
```javascript
// 구식 선언 (사용 지양)
var oldVariable = "사용하지 마세요";
```

![bg right:40% w:400](https://images.unsplash.com/photo-1516259762381-22954d7d3ad2?w=400&h=300&fit=crop)

---

## 함수 선언 방법

```javascript
// 1. 함수 선언문
function greetUser(name) {
    return `안녕하세요, ${name}님!`;
}

// 2. 화살표 함수 (ES6) - 권장
const greetUser = (name) => {
    return `안녕하세요, ${name}님!`;
};

// 3. 간단한 화살표 함수
const greetUser = name => `안녕하세요, ${name}님!`;

// 함수 호출
const greeting = greetUser("바이브코딩");
console.log(greeting); // "안녕하세요, 바이브코딩님!"
```

---

## 조건문과 반복문

### **조건문 (if/else)**
```javascript
const age = 20;

if (age >= 18) {
    console.log("성인입니다");
} else if (age >= 13) {
    console.log("청소년입니다");
} else {
    console.log("어린이입니다");
}

// 삼항 연산자 (간단한 조건)
const message = age >= 18 ? "성인" : "미성년자";
```

### **반복문 (for/while)**
```javascript
// for 반복문
for (let i = 0; i < 5; i++) {
    console.log(`카운트: ${i}`);
}

// 배열 반복
const fruits = ["사과", "바나나", "오렌지"];
for (const fruit of fruits) {
    console.log(fruit);
}
```

---

# 🎯 DOM 기초 - 웹 요소 선택하기

## DOM이란?

**Document Object Model** - HTML 문서를 JavaScript로 조작할 수 있게 해주는 인터페이스

```
HTML 문서 ➜ DOM ➜ JavaScript로 조작 가능
```

### **querySelector 활용법**
```javascript
// ID로 선택
const header = document.querySelector('#header');

// 클래스로 선택
const button = document.querySelector('.btn');

// 태그로 선택
const paragraph = document.querySelector('p');

// 복합 선택자
const menuItem = document.querySelector('nav .menu-item:first-child');

// 모든 요소 선택
const allButtons = document.querySelectorAll('.btn');
```

![bg right:40% w:400](https://images.unsplash.com/photo-1551650975-87deedd944c3?w=400&h=300&fit=crop)

---

## 요소 내용 조작

```javascript
// 텍스트 내용 변경
const title = document.querySelector('h1');
title.textContent = "새로운 제목";
title.innerHTML = "<span>HTML 포함 제목</span>";

// 속성 조작
const image = document.querySelector('img');
image.src = "new-image.jpg";
image.alt = "새로운 이미지";

// CSS 클래스 조작
const button = document.querySelector('.btn');
button.classList.add('active');       // 클래스 추가
button.classList.remove('disabled');  // 클래스 제거
button.classList.toggle('hidden');    // 클래스 토글

// 스타일 직접 변경
button.style.backgroundColor = 'blue';
button.style.color = 'white';
```

---

# 🚀 이벤트 처리 기초

## 기본 이벤트 리스너

```javascript
// 클릭 이벤트
const button = document.querySelector('#myButton');
button.addEventListener('click', function() {
    alert('버튼이 클릭되었습니다!');
});

// 화살표 함수로 간단하게 (권장)
button.addEventListener('click', () => {
    console.log('버튼 클릭됨');
});

// 함수를 별도로 정의
const handleButtonClick = () => {
    console.log('버튼이 클릭되었습니다!');
};

button.addEventListener('click', handleButtonClick);
```

![bg right:35% w:350](https://images.unsplash.com/photo-1461749280684-dccba630e2f6?w=350&h=250&fit=crop)

---

## 다양한 이벤트 타입

```javascript
const input = document.querySelector('#nameInput');

// 입력값 변화 감지
input.addEventListener('input', (event) => {
    const inputValue = event.target.value;
    console.log(`입력된 값: ${inputValue}`);
});

// 포커스 이벤트
input.addEventListener('focus', () => {
    input.style.borderColor = 'blue';
});

input.addEventListener('blur', () => {
    input.style.borderColor = 'gray';
});

// 키보드 이벤트
input.addEventListener('keydown', (event) => {
    if (event.key === 'Enter') {
        console.log('엔터키가 눌렸습니다!');
    }
});
```

---

# 💻 실전 예제 - 간단한 카운터

## HTML 구조
```html
<div class="counter-app">
    <h2 id="counter-display">0</h2>
    <button id="increment-btn">증가</button>
    <button id="decrement-btn">감소</button>
    <button id="reset-btn">리셋</button>
</div>
```

## JavaScript 구현
```javascript
// 요소 선택
const display = document.querySelector('#counter-display');
const incrementBtn = document.querySelector('#increment-btn');
const decrementBtn = document.querySelector('#decrement-btn');
const resetBtn = document.querySelector('#reset-btn');

// 카운터 변수
let count = 0;

// 화면 업데이트 함수
const updateDisplay = () => {
    display.textContent = count;
};

// 이벤트 리스너 등록
incrementBtn.addEventListener('click', () => {
    count++;
    updateDisplay();
});

decrementBtn.addEventListener('click', () => {
    count--;
    updateDisplay();
});

resetBtn.addEventListener('click', () => {
    count = 0;
    updateDisplay();
});
```

---

# 🛠️ 디버깅과 개발자 도구

## 콘솔 활용법

```javascript
// 디버깅을 위한 콘솔 로그
console.log('변수 값:', userName);
console.error('오류 메시지');
console.warn('경고 메시지');

// 객체나 배열 출력
const user = { name: '바이브코딩', age: 25 };
console.table(user);

// 실행 시간 측정
console.time('처리시간');
// ... 코드 실행 ...
console.timeEnd('처리시간');
```

## 개발자 도구 사용법

1. **F12** 키로 개발자 도구 열기
2. **Console 탭**에서 JavaScript 코드 실행
3. **Elements 탭**에서 DOM 구조 확인
4. **Sources 탭**에서 JavaScript 파일 디버깅

![bg right:40% w:400](https://images.unsplash.com/photo-1517077304055-6e89abbf09b0?w=400&h=300&fit=crop)

---

# 🎊 4-1교시 마무리

## 오늘 배운 내용 정리

- **JavaScript 기본 문법** (변수, 함수, 조건문)
- **DOM 요소 선택**과 조작 방법
- **기본 이벤트 처리** (클릭, 입력)
- **실전 예제**로 카운터 앱 구현

## 다음 시간 (4-2교시) 예고

- **고급 DOM 조작** 기법
- **폼 검증**과 사용자 입력 처리
- **테마 변경** 기능 구현
- **인터랙티브 프로필 페이지** 완성

![bg right:45% w:450](https://images.unsplash.com/photo-1627398242454-45a1465c2479?w=450&h=300&fit=crop)
