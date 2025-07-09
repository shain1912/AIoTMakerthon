---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 2강 - HTML 기초 및 Live Server 실습'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 HTML 기초 및 Live Server 실습

## 웹페이지의 뼈대 만들기

**강사명**: 조성호  
**소요시간**: 60분

![bg right:40% w:400](https://images.unsplash.com/photo-1621839673705-6617adf9e890?w=400&h=300&fit=crop)

---

## 📋 2교시 학습 목표

- HTML5 시맨틱 태그의 이해와 활용
- 웹 접근성을 고려한 마크업 작성
- Live Server를 통한 실시간 개발 환경 구축
- 개인 프로필 페이지 HTML 구조 완성

---

## 🔗 필요한 준비물

- [ ] 1교시에서 설정한 VSCode 환경
- [ ] Live Server 확장 프로그램 (설치 완료)
- [ ] 개인 소개 내용 준비 (이름, 취미, 목표 등)
- [ ] 브라우저 개발자 도구 사용 준비

![bg right:35% w:350](https://images.unsplash.com/photo-1544717297-fa95b6ee9643?w=350&h=250&fit=crop)

---

# 📖 HTML 시맨틱 마크업 기초

## 🎯 HTML5 문서 구조

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>페이지 제목</title>
</head>
<body>
    <!-- 여기에 웹페이지 내용 -->
</body>
</html>
```

---

## 주요 시맨틱 태그들

| 태그 | 용도 | 설명 |
|------|------|------|
| `<header>` | 페이지/섹션 머리말 | 로고, 네비게이션, 제목 등 |
| `<nav>` | 네비게이션 메뉴 | 주요 링크 모음 |
| `<main>` | 주요 콘텐츠 영역 | 페이지의 핵심 내용 |
| `<section>` | 독립적인 구역 | 주제별 내용 그룹 |
| `<article>` | 독립적인 글 | 블로그 포스트, 뉴스 기사 등 |
| `<aside>` | 부가 정보 | 사이드바, 광고 등 |
| `<footer>` | 페이지/섹션 바닥글 | 저작권, 연락처 등 |

---

## 🔧 Live Server의 이해

### **Live Server란?**
- VSCode 확장 프로그램
- 로컬 개발 서버를 실행하여 실시간 미리보기 제공
- 코드 변경시 자동으로 브라우저 새로고침

### **Live Server의 장점**
1. **실시간 반영**: 저장하면 즉시 브라우저에 반영
2. **로컬 서버 환경**: file:// 프로토콜의 제약 해결
3. **다중 기기 테스트**: 네트워크를 통한 모바일 테스트 가능
4. **개발 효율성**: 수동 새로고침 불필요

![bg right:35% w:350](https://images.unsplash.com/photo-1460925895917-afdab827c52f?w=350&h=250&fit=crop)

---

# 💻 Live Server 실습

## 🔴 Step 1: 기본 HTML 파일 생성

```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Live Server 테스트</title>
</head>
<body>
    <h1>Live Server가 잘 작동하나요? 🚀</h1>
    <p>이 텍스트를 수정하고 저장해보세요!</p>
</body>
</html>
```

**실행**: `index.html` 우클릭 → "Open with Live Server"

---

## 🏗️ Step 2: 프로필 페이지 구조

```html
<body>
    <div class="container">
        <header>
            <h1>[본인 이름]</h1>
            <nav>
                <ul>
                    <li><a href="#about">소개</a></li>
                    <li><a href="#interests">관심사</a></li>
                    <li><a href="#goals">목표</a></li>
                    <li><a href="#contact">연락처</a></li>
                </ul>
            </nav>
        </header>
        
        <main>
            <section id="about">
                <h2>👋 About Me</h2>
                <p>안녕하세요! 저는 [본인 이름]입니다.</p>
            </section>
        </main>
        
        <footer>
            <p>&copy; 2024 [본인 이름]. Made with ❤️ and Vibe Coding</p>
        </footer>
    </div>
</body>
```

---

# 🎯 도전과제: "스토리텔링 프로필"

## 📋 과제 요구사항

### **필수 구현 기능**
1. **타임라인 섹션**: 학습 여정 (최소 3개 항목)
2. **스킬 & 학습 섹션**: 관심 있는 기술들
3. **프로젝트 아이디어 섹션**: 만들고 싶은 것들
4. **연락처 폼**: 이름, 이메일, 메시지

### **고급 HTML 요소 활용**
```html
<details>     <!-- 접을 수 있는 상세 내용 -->
<summary>     <!-- details의 제목 -->
<figure>      <!-- 이미지와 캡션 -->
<blockquote>  <!-- 인용구 -->
<time>        <!-- 시간/날짜 -->
```

---

## 💡 완성 예시

```html
<!-- 타임라인 섹션 -->
<section id="timeline">
    <h2>My Journey</h2>
    <ol>
        <li>
            <time datetime="2024-01">2024년 1월</time>
            <h3>코딩에 첫 관심</h3>
            <p>우연히 본 프로그래밍 영상에서 시작된 호기심...</p>
        </li>
    </ol>
</section>

<!-- 접을 수 있는 상세 정보 -->
<details>
    <summary>더 자세한 취미 이야기 보기</summary>
    <p>제가 좋아하는 취미에 대해 더 자세히...</p>
</details>

<!-- 연락처 폼 -->
<form>
    <label for="name">이름:</label>
    <input type="text" id="name" required>
    <button type="submit">메시지 보내기</button>
</form>
```

---

## 🏆 성공 기준

### **기본 완성도 체크리스트**
- [ ] 모든 필수 섹션이 포함되어 있는가?
- [ ] 시맨틱 HTML 태그가 올바르게 사용되었는가?
- [ ] Live Server에서 오류 없이 실행되는가?
- [ ] 고급 HTML 요소를 3개 이상 활용했는가?

### **⏰ 예상 소요시간**: 25분

---

# 🎊 수고하셨습니다!

## 오늘 배운 내용 정리

- **HTML5 시맨틱 태그** 활용법
- **웹 접근성** 기본 원칙
- **Live Server** 실시간 개발 환경
- **개인 프로필 페이지** HTML 구조 완성

### 다음 시간 예고: CSS 스타일링으로 페이지 꾸미기! 🎨

![bg right:45% w:450](https://images.unsplash.com/photo-1519389950473-47ba0277781c?w=450&h=300&fit=crop)
