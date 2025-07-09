---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 4-2강 - DOM 조작과 이벤트 처리'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 JavaScript 기초 및 DOM 조작 (2부)

## 인터랙티브 웹페이지 만들기

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1555066931-4365d14bab8c?w=400&h=300&fit=crop)

---

## 📋 4-2교시 학습 목표

- **고급 DOM 조작** 기법 마스터
- **폼 처리와 검증** 구현
- **테마 변경** 기능 만들기
- **실전 프로젝트**: 인터랙티브 프로필 페이지 완성

---

## 🔗 4-1교시 복습

- JavaScript 기본 문법 (변수, 함수, 조건문)
- DOM 요소 선택과 기본 조작
- 기본 이벤트 리스너 등록
- 간단한 카운터 앱 구현

![bg right:35% w:350](https://images.unsplash.com/photo-1461749280684-dccba630e2f6?w=350&h=250&fit=crop)

---

# 🚀 고급 DOM 조작 기법

## 요소 생성과 삭제

```javascript
// 새로운 요소 생성
const newParagraph = document.createElement('p');
newParagraph.textContent = '새로운 문단입니다';
newParagraph.classList.add('highlight');

// 부모 요소에 추가
const container = document.querySelector('.container');
container.appendChild(newParagraph);

// 특정 위치에 삽입
const firstChild = container.firstElementChild;
container.insertBefore(newParagraph, firstChild);

// 요소 제거
const elementToRemove = document.querySelector('.old-element');
elementToRemove.remove();
```

![bg right:40% w:400](https://images.unsplash.com/photo-1516259762381-22954d7d3ad2?w=400&h=300&fit=crop)

---

## 효율적인 DOM 조작

```javascript
// ❌ 비효율적: 반복적인 DOM 검색
document.querySelector('#title').textContent = "제목1";
document.querySelector('#title').style.color = "red";
document.querySelector('#title').classList.add('active');

// ✅ 효율적: 한 번만 검색 후 재사용
const title = document.querySelector('#title');
title.textContent = "제목1";
title.style.color = "red";
title.classList.add('active');

// ✅ 여러 스타일을 한 번에 적용
Object.assign(title.style, {
    color: 'red',
    fontSize: '24px',
    fontWeight: 'bold'
});
```

---

# 📝 폼 처리와 검증

## 폼 이벤트 처리

```javascript
// 폼 제출 이벤트
const form = document.querySelector('#contactForm');
form.addEventListener('submit', (event) => {
    event.preventDefault(); // 기본 제출 동작 방지
    
    // 폼 데이터 수집
    const formData = new FormData(form);
    const name = formData.get('name');
    const email = formData.get('email');
    const message = formData.get('message');
    
    console.log('제출된 데이터:', { name, email, message });
});
```

## 실시간 입력 검증

```javascript
const emailInput = document.querySelector('#email');
const emailError = document.querySelector('#email-error');

emailInput.addEventListener('input', (event) => {
    const email = event.target.value;
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    
    if (email && !emailRegex.test(email)) {
        emailError.textContent = '올바른 이메일 형식이 아닙니다';
        emailError.style.color = 'red';
        emailInput.classList.add('error');
    } else {
        emailError.textContent = '';
        emailInput.classList.remove('error');
    }
});
```

---

# 🌓 테마 변경 기능 구현

## HTML 구조

```html
<div class="theme-container">
    <h1 id="title">내 프로필</h1>
    <button id="themeToggle">🌙 다크모드</button>
    <p id="description">웹 개발자입니다.</p>
</div>
```

## CSS 테마 스타일

```css
.light-theme {
    background-color: #ffffff;
    color: #333333;
    transition: all 0.3s ease;
}

.dark-theme {
    background-color: #1a1a1a;
    color: #ffffff;
    transition: all 0.3s ease;
}

.dark-theme .btn {
    background-color: #444;
    color: white;
    border: 1px solid #666;
}

.theme-toggle {
    position: fixed;
    top: 20px;
    right: 20px;
    padding: 10px 15px;
    border: none;
    border-radius: 25px;
    cursor: pointer;
    font-size: 16px;
}
```

![bg right:35% w:350](https://images.unsplash.com/photo-1558655146-9f40138edfeb?w=350&h=250&fit=crop)

---

## JavaScript 테마 변경 로직

```javascript
const themeToggle = document.querySelector('#themeToggle');
const body = document.body;

// 현재 테마 상태 추적
let isDarkMode = false;

// 테마 변경 함수
const toggleTheme = () => {
    if (isDarkMode) {
        // 라이트 모드로 변경
        body.classList.remove('dark-theme');
        body.classList.add('light-theme');
        themeToggle.textContent = '🌙 다크모드';
        isDarkMode = false;
        
        // 로컬 스토리지에 저장
        localStorage.setItem('theme', 'light');
    } else {
        // 다크 모드로 변경
        body.classList.remove('light-theme');
        body.classList.add('dark-theme');
        themeToggle.textContent = '☀️ 라이트모드';
        isDarkMode = true;
        
        // 로컬 스토리지에 저장
        localStorage.setItem('theme', 'dark');
    }
};

// 이벤트 리스너 등록
themeToggle.addEventListener('click', toggleTheme);

// 페이지 로드 시 저장된 테마 적용
const savedTheme = localStorage.getItem('theme');
if (savedTheme === 'dark') {
    toggleTheme();
} else {
    body.classList.add('light-theme');
}
```

---

# 🎨 애니메이션과 효과

## CSS 전환 효과

```css
/* 부드러운 전환 효과 */
.fade-in {
    opacity: 0;
    transform: translateY(20px);
    transition: all 0.5s ease-in-out;
}

.fade-in.show {
    opacity: 1;
    transform: translateY(0);
}

.slide-up {
    transform: translateY(100%);
    transition: transform 0.3s ease;
}

.slide-up.active {
    transform: translateY(0);
}
```

## JavaScript 애니메이션 트리거

```javascript
// 스크롤 기반 애니메이션
const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -50px 0px'
};

const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('show');
        }
    });
}, observerOptions);

// 애니메이션 적용할 요소들 관찰
const animatedElements = document.querySelectorAll('.fade-in');
animatedElements.forEach(el => observer.observe(el));
```

![bg right:40% w:400](https://images.unsplash.com/photo-1517180102446-f3ece451e9d8?w=400&h=300&fit=crop)

---

# 💻 실전 프로젝트: 더 보기 기능

## HTML 구조

```html
<section class="about-section">
    <h2>About Me</h2>
    <p class="intro">안녕하세요! 웹 개발자입니다.</p>
    
    <div class="more-content" id="moreContent" style="display: none;">
        <p>저는 JavaScript를 사랑하는 개발자입니다...</p>
        <p>바이브코딩을 통해 많은 것을 배우고 있습니다.</p>
    </div>
    
    <button id="toggleMore" class="toggle-btn">더 보기</button>
</section>
```

## JavaScript 구현

```javascript
const toggleBtn = document.querySelector('#toggleMore');
const moreContent = document.querySelector('#moreContent');
let isExpanded = false;

const toggleContent = () => {
    if (isExpanded) {
        // 내용 숨기기
        moreContent.style.display = 'none';
        toggleBtn.textContent = '더 보기';
        isExpanded = false;
    } else {
        // 내용 보이기
        moreContent.style.display = 'block';
        toggleBtn.textContent = '접기';
        isExpanded = true;
    }
};

toggleBtn.addEventListener('click', toggleContent);
```

---

# 🔧 이벤트 위임과 최적화

## 이벤트 위임 (Event Delegation)

```javascript
// ❌ 비효율적: 각 버튼에 개별 이벤트 리스너
const buttons = document.querySelectorAll('.btn');
buttons.forEach(btn => {
    btn.addEventListener('click', handleClick);
});

// ✅ 효율적: 부모 요소에 하나의 이벤트 리스너
const buttonContainer = document.querySelector('.button-container');
buttonContainer.addEventListener('click', (event) => {
    // 클릭된 요소가 버튼인지 확인
    if (event.target.classList.contains('btn')) {
        const action = event.target.dataset.action;
        console.log(`${action} 버튼이 클릭됨`);
    }
});
```

## 디바운싱 (Debouncing)

```javascript
// 검색 입력 최적화
const searchInput = document.querySelector('#search');
let debounceTimer;

const handleSearch = (query) => {
    console.log(`검색어: ${query}`);
    // 실제 검색 로직
};

searchInput.addEventListener('input', (event) => {
    clearTimeout(debounceTimer);
    debounceTimer = setTimeout(() => {
        handleSearch(event.target.value);
    }, 300); // 300ms 후 실행
});
```

---

# 🎯 도전과제 미리보기

## 인터랙티브 프로필 페이지 만들기

### **필수 기능**
1. **테마 변경 기능** - 라이트/다크 모드 토글
2. **동적 콘텐츠** - "더 보기" 버튼으로 정보 표시/숨김
3. **폼 검증** - 연락처 폼 실시간 검증

### **보너스 기능**
- 타이핑 애니메이션 효과
- 스크롤 기반 애니메이션
- 이미지 갤러리 모달

### **구현 힌트**
```javascript
// 로컬 스토리지 활용
localStorage.setItem('theme', 'dark');
localStorage.getItem('theme');

// 이메일 검증
const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
```

![bg right:40% w:400](https://images.unsplash.com/photo-1551650975-87deedd944c3?w=400&h=300&fit=crop)

---

# 🛠️ 디버깅 팁과 모범 사례

## 효과적인 디버깅

```javascript
// 1. 콘솔 로그 활용
console.log('함수 시작:', { variable1, variable2 });

// 2. 조건부 로깅
const DEBUG = true;
if (DEBUG) {
    console.log('디버그 정보:', data);
}

// 3. 에러 처리
try {
    // 위험할 수 있는 코드
    const result = riskyFunction();
} catch (error) {
    console.error('에러 발생:', error.message);
}
```

## 코드 작성 모범 사례

```javascript
// ✅ 좋은 예: 명확한 변수명과 함수명
const userEmailInput = document.querySelector('#userEmail');
const validateEmailFormat = (email) => { /* ... */ };

// ✅ 좋은 예: 함수는 하나의 일만 담당
const updateTheme = (isDark) => { /* 테마 변경만 */ };
const saveThemePreference = (theme) => { /* 저장만 */ };

// ✅ 좋은 예: 상수는 대문자로
const MAX_RETRY_COUNT = 3;
const DEFAULT_THEME = 'light';
```

---

# 🎊 수고하셨습니다!

## 오늘 배운 내용 정리

- **고급 DOM 조작** (요소 생성, 삭제, 효율적 조작)
- **폼 처리와 검증** (실시간 검증, 에러 처리)
- **테마 변경 기능** (로컬 스토리지 활용)
- **애니메이션과 효과** (CSS 전환, 스크롤 애니메이션)

## 다음 시간 예고: 프로젝트 통합과 배포! 🚀

### **과제**: 도전과제를 통해 인터랙티브 프로필 페이지 완성하기

![bg right:45% w:450](https://images.unsplash.com/photo-1555066931-4365d14bab8c?w=450&h=300&fit=crop)
