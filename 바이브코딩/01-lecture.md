---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 1강 - AI와 함께하는 웹 개발 입문'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 바이브코딩으로 시작하는 웹 개발

## AI와 함께하는 16시간 여정

**강사명**: 조성호  
**소요시간**: 60분

---

## 📋 1교시 학습 목표

- 바이브코딩 개념과 철학 이해
- 웹 개발의 기본 구조 파악
- VSCode + Copilot 개발환경 구축
- AI 협업을 통한 첫 웹페이지 제작

---

## 🔗 필요한 준비물

- [ ] 노트북 (Windows/Mac 무관)
- [ ] 안정적인 인터넷 연결
- [ ] Chrome 브라우저
- [ ] GitHub 계정 (미리 가입 권장)
- [ ] 학습 의지와 호기심! 🚀

![bg right:40% w:400](https://images.unsplash.com/photo-1498050108023-c5249f4df085?w=400&h=300&fit=crop&crop=top)

---

# 📖 바이브코딩이란?

## 🎯 정의

**바이브코딩(Vibe Coding)**은 AI 도구와 협업하여 효율적이고 창의적으로 코딩하는 현대적 개발 방법론입니다.

![bg right:35% w:350](https://images.unsplash.com/photo-1555066931-4365d14bab8c?w=350&h=250&fit=crop)

---

## ✨ 바이브코딩의 핵심 특징

### 1. **빠른 프로토타이핑**
- 아이디어에서 실제 동작하는 코드까지 최단시간
- AI가 반복적인 코드 작성을 대신 처리
- 창의적 사고에 집중할 수 있는 환경

### 2. **높은 코드 품질**
- AI가 제안하는 베스트 프랙티스 활용
- 실시간 코드 리뷰 및 개선 제안
- 버그 예방과 최적화된 구조

### 3. **학습 곡선 단축**
- 복잡한 문법 암기보다 로직과 구조에 집중
- AI 설명을 통한 즉석 학습
- 실무급 결과물을 빠르게 달성

---

## 🌐 웹 개발의 기본 이해

### **웹사이트 작동 원리**

```
👤 사용자 (클라이언트)
    ↕️ 인터넷
🖥️ 웹서버 (서버)
    ↕️
💾 데이터베이스
```

![bg right:40% w:400](https://images.unsplash.com/photo-1451187580459-43490279c0fa?w=400&h=300&fit=crop)

---

## 프론트엔드 vs 백엔드

| 구분     | 프론트엔드            | 백엔드                   |
| -------- | --------------------- | ------------------------ |
| **역할** | 사용자가 보는 화면    | 서버와 데이터 처리       |
| **기술** | HTML, CSS, JavaScript | Node.js, Python, Java 등 |
| **담당** | 디자인, 사용자 경험   | 데이터, 보안, 성능       |

---

## 🛠️ 웹 개발 3대 기술

### **HTML (구조)**
- 웹페이지의 뼈대와 내용
- 제목, 문단, 링크, 이미지 등 요소 정의
- 시맨틱 태그로 의미있는 구조 생성

### **CSS (디자인)**
- 웹페이지의 모양과 스타일
- 색상, 크기, 위치, 애니메이션 등
- 반응형 디자인으로 모든 기기 대응

### **JavaScript (동작)**
- 웹페이지의 상호작용과 동적 기능
- 버튼 클릭, 폼 제출, 데이터 처리 등
- 사용자 경험을 풍부하게 만드는 핵심

![bg right:35% w:350](https://images.unsplash.com/photo-1627398242454-45a1465c2479?w=350&h=250&fit=crop)

---

## 🆚 전통적 개발 vs AI 협업 개발

### **전통적 개발 방식**
1. 문법과 API 문서 검색
2. 스택오버플로우에서 해답 찾기
3. 시행착오를 통한 디버깅
4. 느린 프로토타이핑

### **AI 협업 개발 (바이브코딩)**
1. 자연어로 원하는 기능 설명
2. AI가 즉시 코드 제안 및 생성
3. 실시간 설명과 최적화 제안
4. 빠른 반복과 개선

---

## 🎯 바이브코딩의 목적

> **"아이디어를 빠르게 현실로 구현하여, 창작의 즐거움을 경험하고 실무급 결과물을 완성한다"**

- 코딩 초보자도 전문가 수준의 웹사이트 제작 가능
- 학습과 실무를 동시에 경험
- AI 시대에 맞는 효율적 개발 역량 습득

![bg right:40% w:400](https://images.unsplash.com/photo-1516321318423-f06f85e504b3?w=400&h=300&fit=crop)

---

# 💻 VSCode + Copilot 통합 환경 구축

## 🛠️ Step 1: VSCode 설치 및 기본 설정

### **VSCode 다운로드**
1. https://code.visualstudio.com 접속
2. 운영체제에 맞는 버전 다운로드
3. 설치 후 실행

![bg right:35% w:350](https://images.unsplash.com/photo-1555066931-4365d14bab8c?w=350&h=250&fit=crop)

---

## 기본 설정 최적화

```json
// settings.json 권장 설정
{
  "editor.fontSize": 14,
  "editor.tabSize": 2,
  "editor.wordWrap": "on",
  "editor.minimap.enabled": true,
  "files.autoSave": "afterDelay",
  "emmet.includeLanguages": {
    "javascript": "javascriptreact"
  }
}
```

---

## 🔌 Step 2: 필수 확장 프로그램 설치

### **반드시 설치할 확장 프로그램들**

1. **Live Server** - 실시간 미리보기
   - 설치: `Extensions → Live Server 검색 → Install`
   - 기능: HTML 파일 실시간 브라우저 연동

2. **GitHub Copilot** - AI 코딩 어시스턴트
   - 설치: `Extensions → GitHub Copilot 검색 → Install`
   - 로그인: GitHub 계정 연동 필요

3. **Auto Rename Tag** - 태그 자동 수정
   - 설치: `Extensions → Auto Rename Tag 검색 → Install`
   - 기능: 여는 태그 수정시 닫는 태그 자동 변경

4. **Prettier** - 코드 자동 정렬
   - 설치: `Extensions → Prettier 검색 → Install`
   - 설정: 저장시 자동 포맷팅 활성화

---

## 🤖 Step 3: GitHub Copilot 연동 설정

### **Copilot 계정 연동**

```bash
# 1. VSCode에서 Copilot 확장 설치 후
# 2. 명령 팔레트 열기 (Ctrl/Cmd + Shift + P)
# 3. "GitHub Copilot: Sign In" 입력
# 4. 브라우저에서 GitHub 로그인 완료
```

### **Copilot 기본 사용법**
- **자동완성**: 타이핑 중 Tab 키로 제안 수락
- **다양한 제안**: `Ctrl + Enter`로 여러 옵션 확인
- **주석 활용**: 원하는 기능을 주석으로 설명하면 코드 생성

![bg right:40% w:400](https://images.unsplash.com/photo-1516259762381-22954d7d3ad2?w=400&h=300&fit=crop)

---

## 🎯 Step 4: 첫 HTML 파일 생성 실습

### **프로젝트 폴더 생성**

```bash
# 1. 바탕화면에 'my-first-website' 폴더 생성
# 2. VSCode에서 폴더 열기 (File → Open Folder)
# 3. 새 파일 생성: index.html
```

---

## Copilot과 함께 HTML 작성

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hello Vibe Coding</title>
    <style>
        /* Copilot이 제안하는 기본 스타일 */
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        
        .container {
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
    </style>
</head>
```

---

## HTML 본문 코드

```html
<body>
    <div class="container">
        <!-- Copilot 활용: 주석으로 원하는 내용 설명 -->
        <!-- 메인 제목과 환영 메시지 -->
        <h1>🎯 안녕하세요, 바이브코딩!</h1>
        
        <div class="intro">
            <p>AI와 함께하는 웹 개발 여정을 시작합니다.</p>
            <p>GitHub Copilot이 도와주는 스마트한 코딩을 경험해보세요!</p>
        </div>
        
        <div class="highlight">
            <strong>바이브코딩의 핵심:</strong>
            아이디어를 빠르게 현실로 만들어내는 것입니다.
        </div>
        
        <!-- Copilot 제안: 간단한 상호작용 버튼 -->
        <div style="text-align: center; margin-top: 30px;">
            <button onclick="showMessage()" 
                    style="background: #2196F3; color: white; border: none; 
                           padding: 10px 20px; border-radius: 5px; cursor: pointer;">
                클릭해보세요!
            </button>
        </div>
    </div>
```

---

## JavaScript 기능 추가

```html
    <script>
        // Copilot이 제안하는 간단한 JavaScript 함수
        function showMessage() {
            alert("🎉 바이브코딩 첫 걸음을 축하합니다!");
        }
    </script>
</body>
</html>
```

---

## 🔴 Step 5: Live Server로 실시간 미리보기

### **Live Server 실행**
1. `index.html` 파일에서 우클릭
2. `"Open with Live Server"` 선택
3. 브라우저에서 자동으로 페이지 열림
4. 코드 수정시 실시간 반영 확인

### **브라우저 개발자 도구 활용**
```bash
# 브라우저에서 F12 키 또는 우클릭 → 검사
# Elements 탭: HTML 구조 확인
# Console 탭: JavaScript 실행 결과 확인
# Network 탭: 파일 로딩 상태 확인
```

![bg right:35% w:350](https://images.unsplash.com/photo-1460925895917-afdab827c52f?w=350&h=250&fit=crop)

---

## ⚡ 핵심 팁: Copilot 효과적 활용법

### **1. 명확한 주석 작성**
```html
<!-- 반응형 네비게이션 메뉴 생성 -->
<!-- 햄버거 메뉴 아이콘 포함 -->
<!-- 모바일에서 토글 기능 -->
```

### **2. 단계별 접근**
```javascript
// 1단계: 기본 기능 구현
// 2단계: 에러 처리 추가
// 3단계: 사용자 경험 개선
```

### **3. 컨텍스트 제공**
```css
/* 모던한 카드 레이아웃 스타일 */
/* Material Design 가이드라인 적용 */
/* 호버 효과와 그림자 포함 */
```

---

## 🚨 주의사항 및 문제 해결

### **자주 발생하는 문제들**

1. **Copilot 제안이 안 나올 때**
   - 인터넷 연결 확인
   - GitHub 로그인 상태 확인
   - VSCode 재시작

2. **Live Server가 안 될 때**
   - 파일 경로에 한글이 없는지 확인
   - 브라우저 캐시 삭제
   - 포트 충돌 확인 (보통 5500번 포트)

3. **코드가 예상과 다를 때**
   - Copilot 제안을 비판적으로 검토
   - 여러 제안 중 최적의 것 선택
   - 기본 문법 이해 후 활용

---

# 🎯 도전과제: "나만의 소개 페이지" 🚀

## 📋 과제 제목
**Copilot과 함께 만드는 개인 소개 웹페이지**

### 🎖️ 난이도
**초급** - 바이브코딩 첫 걸음

![bg right:40% w:400](https://images.unsplash.com/photo-1522202176988-66273c2fd55f?w=400&h=300&fit=crop)

---

## 📝 문제 설명

GitHub Copilot의 도움을 받아 자신을 소개하는 웹페이지를 제작합니다. 이 과제를 통해 바이브코딩의 핵심인 'AI와의 협업'을 직접 경험하게 됩니다.

---

## ✅ 요구사항

### **필수 구현 기능**

1. **개인 정보 섹션**
   - 이름, 나이, 관심분야
   - 간단한 자기소개 (3-4줄)

2. **취미/관심사 섹션**
   - 최소 3개 이상의 취미나 관심사
   - 각각에 대한 짧은 설명

3. **목표 섹션**
   - 웹 개발을 배우는 이유
   - 16시간 후 만들고 싶은 것

4. **상호작용 요소**
   - 클릭할 수 있는 버튼 최소 1개
   - JavaScript 함수를 활용한 간단한 기능

---

## 기술적 요구사항

- [x] HTML5 시맨틱 태그 사용
- [x] CSS로 기본 스타일링 적용
- [x] JavaScript로 간단한 인터랙션 구현
- [x] Live Server로 실시간 확인
- [x] **중요**: Copilot 제안을 최소 5번 이상 활용

---

## 💡 힌트

### **Copilot 활용 팁**

```html
<!-- 이런 식으로 주석을 작성하면 Copilot이 도와줍니다 -->
<!-- 개인 프로필 카드 레이아웃 -->
<!-- 중앙 정렬, 그림자 효과, 둥근 모서리 -->
```

```javascript
// 버튼 클릭시 개인 정보를 토글하는 함수
// 애니메이션 효과 포함
```

```css
/* 모던한 그라데이션 배경 */
/* 카드 형태의 레이아웃 */
/* 호버 효과와 트랜지션 */
```

---

## 구조 제안

```
index.html
├── header (이름과 한 줄 소개)
├── main
│   ├── about (자기소개)
│   ├── interests (관심사)
│   └── goals (목표)
└── footer (연락처나 마무리 인사)
```

### **스타일링 아이디어**
- 배경: 그라데이션 또는 단색
- 레이아웃: 카드 형태의 섹션들
- 색상: 개인 취향에 맞는 2-3가지 컬러
- 폰트: 읽기 쉬운 웹 폰트 사용

---

## ⏰ 예상 소요시간

**15분** (환경 설정 + 코딩 + 테스트)

---

## 🏆 성공 기준

### **완성도 체크리스트**
- [ ] 모든 필수 섹션이 포함되어 있는가?
- [ ] Copilot 제안을 적극 활용했는가?
- [ ] Live Server로 정상 동작 확인했는가?
- [ ] 버튼 클릭 등 상호작용이 작동하는가?
- [ ] 개인의 특색이 잘 드러나는가?

### **추가 도전 요소** (선택사항)
- [ ] 반응형 디자인 적용 (모바일 호환)
- [ ] CSS 애니메이션 효과 추가
- [ ] 이미지나 아이콘 활용
- [ ] 창의적인 JavaScript 기능 구현

---

## 🎯 완성 예시 (참고용)

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>김개발의 소개페이지</title>
    <!-- Copilot이 제안하는 스타일 -->
</head>
<body>
    <header>
        <h1>👋 안녕하세요, 김개발입니다!</h1>
        <p>바이브코딩으로 웹 개발의 세계에 첫 발을 내딛는 초보 개발자</p>
    </header>
    
    <main>
        <section class="about">
            <h2>🧑‍💻 About Me</h2>
            <!-- 자기소개 내용 -->
        </section>
        
        <section class="interests">
            <h2>🎨 My Interests</h2>
            <!-- 관심사 목록 -->
        </section>
        
        <section class="goals">
            <h2>🎯 My Goals</h2>
            <!-- 목표 내용 -->
        </section>
    </main>
```

---

## 🤝 도움이 필요할 때

### **막혔을 때 해결 방법**

1. **Copilot에게 질문하기**
   - 주석으로 원하는 기능 설명
   - 여러 제안 중 최적의 것 선택

2. **브라우저 개발자 도구 활용**
   - F12로 콘솔 확인
   - 에러 메시지 읽고 해결

3. **강사에게 질문하기**
   - 구체적인 에러 상황 설명
   - 시도해본 방법들 공유

---

## 🎉 완성 후 할 일

1. **Live Server로 최종 테스트**
2. **동료들과 결과물 공유**
3. **Copilot 활용 경험 정리**
4. **다음 교시 준비: HTML 심화 학습**

![bg right:40% w:400](https://images.unsplash.com/photo-1517077304055-6e89abbf09b0?w=400&h=300&fit=crop)

---

# 🎊 수고하셨습니다!

## 오늘 배운 내용 정리

- **바이브코딩** 개념과 철학
- **웹 개발 기초** 이해
- **VSCode + Copilot** 환경 구축
- **첫 웹페이지** 제작 경험
- **AI 협업** 개발 방법론

### 다음 시간 예고: HTML 태그 완전 정복! 📚

![bg right:45% w:450](https://images.unsplash.com/photo-1519389950473-47ba0277781c?w=450&h=300&fit=crop)
