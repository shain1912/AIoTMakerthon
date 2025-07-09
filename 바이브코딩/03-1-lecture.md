---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 3-1강 - CSS 기초와 박스모델'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 CSS 스타일링 및 반응형 디자인 (1부)

## 웹페이지에 생명을 불어넣기

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?w=400&h=300&fit=crop)

---

## 📋 3-1교시 학습 목표

- CSS 기초 문법과 셀렉터 완전 이해
- 박스 모델과 레이아웃 시스템 마스터
- CSS 단위와 색상 시스템 활용
- 웹 접근성을 고려한 스타일링

---

## 🔗 필요한 준비물

- [ ] 2교시에서 완성한 HTML 프로필 페이지
- [ ] VSCode + Live Server 환경
- [ ] 브라우저 개발자 도구 사용 준비
- [ ] 색상과 디자인에 대한 열린 마음 🎨

![bg right:35% w:350](https://images.unsplash.com/photo-1558655146-d09347e92766?w=350&h=250&fit=crop)

---

# 📖 CSS 기초 및 작동 원리

## 🎯 CSS란?

**Cascading Style Sheets** - 웹페이지의 시각적 표현을 담당하는 언어

### **CSS의 핵심 개념**
```
선택자(Selector) + 속성(Property) + 값(Value) = 스타일 규칙
```

```css
h1 {                    /* 선택자: h1 태그 */
    color: blue;        /* 속성: color, 값: blue */
    font-size: 24px;    /* 속성: font-size, 값: 24px */
}
```

![bg right:40% w:400](https://images.unsplash.com/photo-1609921212029-bb5a28e60960?w=400&h=300&fit=crop)

---

## 🔍 CSS 셀렉터의 이해

### **기본 셀렉터 종류**

| 셀렉터 | 문법 | 설명 | 예시 |
|--------|------|------|------|
| **태그** | `태그명` | HTML 태그 직접 선택 | `h1 { }` |
| **클래스** | `.클래스명` | class 속성으로 선택 | `.header { }` |
| **ID** | `#아이디명` | id 속성으로 선택 | `#main { }` |
| **속성** | `[속성명]` | 특정 속성을 가진 요소 | `[type="text"]` |

---

## 조합 셀렉터와 가상 클래스

### **조합 셀렉터**
```css
/* 후손 선택자: header 안의 모든 h1 */
header h1 { color: red; }

/* 자식 선택자: header의 직접 자식 h1만 */
header > h1 { color: blue; }

/* 인접 형제: h1 바로 다음 p */
h1 + p { margin-top: 0; }
```

### **가상 클래스 셀렉터**
```css
/* 마우스 호버시 */
a:hover { color: red; }

/* 첫 번째 자식 */
li:first-child { font-weight: bold; }

/* n번째 자식 */
li:nth-child(odd) { background: #f5f5f5; }
```

---

# 📦 박스 모델의 완전한 이해

## 박스 모델 구조

```
┌─────────────────────────────────┐
│           MARGIN               │
│  ┌───────────────────────────┐  │
│  │        BORDER             │  │
│  │  ┌─────────────────────┐  │  │
│  │  │      PADDING        │  │  │
│  │  │  ┌───────────────┐  │  │  │
│  │  │  │   CONTENT     │  │  │  │
│  │  │  └───────────────┘  │  │  │
│  │  └─────────────────────┘  │  │
│  └───────────────────────────┘  │
└─────────────────────────────────┘
```

![bg right:40% w:400](https://images.unsplash.com/photo-1551288049-bebda4e38f71?w=400&h=300&fit=crop)

---

## 박스 모델 속성 실습

```css
.box {
    /* 콘텐츠 영역 */
    width: 300px;
    height: 200px;
    
    /* 안쪽 여백 */
    padding: 20px;           /* 모든 방향 */
    padding: 10px 20px;      /* 상하 좌우 */
    padding: 10px 15px 20px 25px; /* 상 우 하 좌 */
    
    /* 테두리 */
    border: 2px solid #333;
    border-radius: 10px;     /* 둥근 모서리 */
    
    /* 바깥쪽 여백 */
    margin: 20px auto;       /* 중앙 정렬 */
}
```

---

## box-sizing 속성

### **기본값 vs 권장값**

```css
/* 기본값: content-box */
.content-box {
    box-sizing: content-box;
    width: 300px;  /* 콘텐츠만 300px */
    padding: 20px; /* 실제 너비: 340px */
}

/* 권장: border-box */
.border-box {
    box-sizing: border-box;
    width: 300px;  /* 전체 너비가 300px */
    padding: 20px; /* 콘텐츠: 260px */
}

/* 전역 설정 */
* {
    box-sizing: border-box;
}
```

![bg right:35% w:350](https://images.unsplash.com/photo-1609921212029-bb5a28e60960?w=350&h=250&fit=crop)

---

# 🎨 CSS 단위와 색상

## 길이 단위

| 단위 | 설명 | 용도 |
|------|------|------|
| `px` | 픽셀 (고정) | 정확한 크기 지정 |
| `em` | 부모 요소 기준 | 상대적 크기 |
| `rem` | 루트 요소 기준 | 일관된 상대 크기 |
| `%` | 부모 요소 비율 | 반응형 너비 |
| `vw/vh` | 뷰포트 너비/높이 | 화면 기준 크기 |

```css
.responsive-text {
    font-size: 1.2rem;      /* 루트 기준 1.2배 */
    width: 80%;             /* 부모의 80% */
    height: 50vh;           /* 화면 높이의 50% */
    margin: 2em;            /* 현재 폰트 크기의 2배 */
}
```

---

## 색상 표현 방법

```css
.color-examples {
    /* 키워드 */
    color: red;
    
    /* HEX 코드 */
    background-color: #3498db;
    
    /* RGB */
    border-color: rgb(255, 99, 71);
    
    /* RGBA (투명도 포함) */
    box-shadow: rgba(0, 0, 0, 0.3);
    
    /* HSL (색상, 채도, 명도) */
    background: hsl(200, 50%, 50%);
}
```

![bg right:40% w:400](https://images.unsplash.com/photo-1558655146-9f40138edfeb?w=400&h=300&fit=crop)

---

# 🎯 CSS 우선순위와 상속

## CSS 우선순위 (Specificity)

```
1. !important     (가장 높음)
2. 인라인 스타일   (style="...")
3. ID 셀렉터      (#id)
4. 클래스/속성    (.class, [attr])
5. 태그 셀렉터    (div, p)
6. 상속된 스타일   (가장 낮음)
```

### **점수 계산 예시**
```css
p { color: black; }                    /* 점수: 1 */
.intro { color: blue; }                /* 점수: 10 */
#header { color: red; }                /* 점수: 100 */
p.intro { color: green; }              /* 점수: 11 */
#header p.intro { color: purple; }     /* 점수: 111 */
```

---

## 상속되는/안되는 속성

### **상속되는 속성들**
```css
.parent {
    color: blue;           /* 자식에게 상속됨 */
    font-family: Arial;    /* 자식에게 상속됨 */
    font-size: 16px;       /* 자식에게 상속됨 */
    line-height: 1.5;      /* 자식에게 상속됨 */
}
```

### **상속되지 않는 속성들**
```css
.parent {
    margin: 20px;          /* 상속 안됨 */
    padding: 10px;         /* 상속 안됨 */
    border: 1px solid;     /* 상속 안됨 */
    background-color: red; /* 상속 안됨 */
}
```

---

# 💻 첫 번째 CSS 실습

## Step 1: CSS 파일 생성

**프로젝트 구조**
```
profile-website/
├── index.html
└── style.css  ← 새로 생성
```

**HTML에 CSS 연결하기**
```html
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>내 프로필</title>
    <link rel="stylesheet" href="style.css">
</head>
```

---

## Step 2: 기본 스타일 적용

```css
/* 전역 설정 */
* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}

body {
    font-family: 'Arial', sans-serif;
    line-height: 1.6;
    color: #333;
    background-color: #f4f4f4;
}

.container {
    max-width: 800px;
    margin: 0 auto;
    padding: 20px;
    background: white;
    border-radius: 10px;
    box-shadow: 0 0 10px rgba(0,0,0,0.1);
}

/* 헤더 스타일 */
header {
    text-align: center;
    padding: 30px 0;
    border-bottom: 2px solid #eee;
    margin-bottom: 30px;
}

header h1 {
    color: #2c3e50;
    margin-bottom: 10px;
}
```

---

## Step 3: 실시간 확인

1. **Live Server 실행**: HTML 파일 우클릭 → "Open with Live Server"
2. **CSS 수정하며 확인**: 색상, 크기, 간격 조정
3. **개발자 도구 활용**: F12 → Elements 탭에서 실시간 테스트

### **즉시 확인할 수 있는 변화들**
- 배경색 변경
- 폰트 변경
- 여백과 간격 조정
- 텍스트 색상 변경

![bg right:35% w:350](https://images.unsplash.com/photo-1517077304055-6e89abbf09b0?w=350&h=250&fit=crop)

---

# 🎊 3-1교시 마무리

## 오늘 배운 내용 정리

- **CSS 기본 문법**과 작동 원리
- **다양한 셀렉터** 활용법
- **박스 모델** 완전 이해
- **CSS 단위와 색상** 시스템
- **우선순위와 상속** 개념

## 다음 시간 (3-2교시) 예고

- **Flexbox 레이아웃** 마스터
- **반응형 디자인** 구현
- **고급 CSS 효과** 적용
- **완성된 프로필 페이지** 스타일링

![bg right:45% w:450](https://images.unsplash.com/photo-1558655146-d09347e92766?w=450&h=300&fit=crop)
