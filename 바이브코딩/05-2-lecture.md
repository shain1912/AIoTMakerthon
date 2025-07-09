---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 5-2강 - GitHub 연동과 포트폴리오 배포'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 Git 기초 및 GitHub 연동 (2부)

## GitHub 연동과 포트폴리오 배포

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1618401479427-c8ef9465fcc1?w=400&h=300&fit=crop)

---

## 📋 5-2교시 학습 목표

- **GitHub 계정 생성** 및 저장소 만들기
- **원격 저장소 연동** (push, pull)
- **README.md 작성** 및 프로젝트 문서화
- **GitHub Pages 배포**로 포트폴리오 공개

---

## 🔗 5-1교시 복습

- Git 기본 개념과 필요성 이해
- Git 설치 및 초기 설정 완료
- 기본 명령어 (init, add, commit, status, log)
- .gitignore 파일 작성법
- 커밋 히스토리 관리

![bg right:35% w:350](https://images.unsplash.com/photo-1556075798-4825dfaaf498?w=350&h=250&fit=crop)

---

# 🌐 GitHub 계정 생성 및 설정

## GitHub 계정 만들기

### **단계별 가이드**

1. **https://github.com** 접속
2. **Sign up** 클릭
3. **필수 정보 입력**:
   - Username: 프로필 URL이 됨 (신중히 선택)
   - Email: Git config와 동일하게 설정
   - Password: 강력한 비밀번호
4. **이메일 인증** 완료
5. **프로필 설정** (선택사항)

### **좋은 사용자명 예시**
```
johndoe2024           ❌ 너무 일반적
john-doe-dev          ✅ 직업이 드러남
johndoe-frontend      ✅ 전문분야 명시
johndoe-webdev        ✅ 기술스택 힌트
```

![bg right:40% w:400](https://images.unsplash.com/photo-1618401471353-b98afee0b2eb?w=400&h=300&fit=crop)

---

## GitHub 프로필 설정

### **기본 프로필 설정**
- **프로필 사진**: 전문적인 이미지 사용
- **Bio**: 간단한 자기소개 (한 줄)
- **Location**: 거주지 (선택사항)
- **Website**: 포트폴리오 사이트 (나중에 추가)

### **Bio 작성 예시**
```
Frontend Developer | HTML, CSS, JavaScript 🚀
웹 개발을 배우고 있는 신입 개발자입니다 💻
Passionate about creating beautiful web experiences ✨
```

### **README 프로필 만들기**
```
특별한 저장소 이름: 본인의 GitHub 사용자명과 동일
예: johndoe -> johndoe/johndoe 저장소
자동으로 프로필 페이지에 표시됨
```

---

# 📁 원격 저장소 생성

## 새 저장소 만들기

### **GitHub 웹에서 생성**

1. **"New repository"** 클릭 (초록색 버튼)
2. **저장소 정보 입력**:
   - Repository name: `my-profile-website`
   - Description: "My personal portfolio website"
   - Public 선택 (무료 계정은 Public만 Pages 지원)
3. **초기 파일 생성 안 함** (이미 로컬에 있음)
   - ❌ Add a README file
   - ❌ Add .gitignore
   - ❌ Choose a license
4. **"Create repository"** 클릭

### **저장소 설정 권장사항**
```
Repository name: 프로젝트 내용을 명확히 표현
Description: 한 줄로 프로젝트 목적 설명
Public: 포트폴리오는 공개로 설정
```

![bg right:35% w:350](https://images.unsplash.com/photo-1618401481398-5f462cd715da?w=350&h=250&fit=crop)

---

# 🔄 로컬과 원격 저장소 연동

## 원격 저장소 연결

### **GitHub에서 제공하는 명령어 사용**

```bash
# 원격 저장소 추가
git remote add origin https://github.com/사용자명/my-profile-website.git

# 원격 저장소 확인
git remote -v

# 결과 예시:
# origin  https://github.com/johndoe/my-profile-website.git (fetch)
# origin  https://github.com/johndoe/my-profile-website.git (push)
```

### **첫 번째 푸시 (업로드)**

```bash
# 메인 브랜치로 첫 푸시
git push -u origin main

# 이후부터는 간단하게
git push
```

### **인증 설정**
- **GitHub CLI** 사용 (권장)
- **Personal Access Token** 생성
- **SSH 키** 설정

---

## Personal Access Token 생성

### **왜 필요한가?**
- 2021년부터 **패스워드 인증 중단**
- **Token 기반 인증**으로 변경
- **더 안전한 인증** 방식

### **Token 생성 단계**

1. **GitHub → Settings → Developer settings**
2. **Personal access tokens → Tokens (classic)**
3. **Generate new token (classic)**
4. **Token 설정**:
   - Note: "My Profile Website"
   - Expiration: 30 days (초보자 권장)
   - Scopes: `repo` 체크
5. **Generate token** 클릭
6. **Token 복사 및 안전한 곳에 저장**

### **Token 사용법**
```bash
# Git 로그인 시 패스워드 대신 Token 입력
Username: your-username
Password: ghp_xxxxxxxxxxxxxxxxxxxx (생성한 Token)
```

---

# 📝 README.md 작성하기

## README.md란?

**프로젝트의 첫인상을 결정하는 문서**
- 저장소 첫 페이지에 자동 표시
- 프로젝트 소개 및 사용법 설명
- **Markdown 문법** 사용
- 채용 담당자가 가장 먼저 보는 파일

## 기본 Markdown 문법

```markdown
# 제목 1 (가장 큰 제목)
## 제목 2 (부제목)
### 제목 3 (소제목)

**굵은 글씨**
*기울임 글씨*
`코드 스타일`

- 리스트 항목 1
- 리스트 항목 2
- 리스트 항목 3

1. 순서 있는 리스트
2. 두 번째 항목
3. 세 번째 항목

[링크 텍스트](https://example.com)
![이미지 설명](이미지URL)
```

![bg right:40% w:400](https://images.unsplash.com/photo-1586953208448-b95a79798f07?w=400&h=300&fit=crop)

---

## 포트폴리오 README.md 템플릿

```markdown
# 🌟 My Profile Website

개인 포트폴리오 웹사이트입니다.

## 📖 프로젝트 소개

이 프로젝트는 HTML, CSS, JavaScript를 사용하여 제작한 
개인 포트폴리오 웹사이트입니다.

## 🛠️ 사용 기술

- HTML5
- CSS3
- JavaScript (ES6+)
- Git & GitHub

## 🎯 주요 기능

- 반응형 디자인
- 다크/라이트 테마 전환
- 부드러운 스크롤 애니메이션
- 연락처 폼

## 🔗 라이브 데모

[웹사이트 보기](https://사용자명.github.io/my-profile-website/)

## 📱 스크린샷

![메인 페이지 스크린샷](./images/screenshot.png)

## 🏃‍♂️ 로컬 실행 방법

1. 저장소 클론
```bash
git clone https://github.com/사용자명/my-profile-website.git
```

2. 프로젝트 폴더로 이동
```bash
cd my-profile-website
```

3. 웹 서버 실행
```bash
# Live Server 확장프로그램 사용 또는
# Python 3 서버
python -m http.server 8000
```

## 📈 개발 과정

- [x] 기본 HTML 구조 작성
- [x] CSS 스타일링 완료
- [x] JavaScript 인터랙션 추가
- [x] 반응형 디자인 구현
- [x] GitHub Pages 배포

## 🤝 기여하기

개선사항이나 버그를 발견하시면 Issue를 열어주세요!

## 📞 연락처

- 이메일: your.email@example.com
- GitHub: [@사용자명](https://github.com/사용자명)
- 링크드인: [프로필 링크](https://linkedin.com/in/사용자명)

---

⭐ 이 프로젝트가 도움이 되셨다면 스타를 눌러주세요!
```

---

# 🔄 Git 워크플로우 실습

## 일반적인 작업 흐름

```bash
# 1. 파일 수정 (에디터에서)
# 2. 변경사항 확인
git status
git diff

# 3. 스테이징
git add .
# 또는 특정 파일만
git add index.html style.css

# 4. 커밋
git commit -m "Add contact form validation"

# 5. 원격 저장소에 푸시
git push origin main
```

## 파일 수정 → 커밋 → 푸시 실습

### **Step 1: README.md 파일 생성**
```bash
# README.md 파일 생성
touch README.md
# Windows: type nul > README.md
```

### **Step 2: 내용 작성 (에디터에서)**
- 위 템플릿을 참고하여 본인만의 README.md 작성
- 프로젝트 소개, 사용 기술, 주요 기능 등 포함

### **Step 3: 커밋 및 푸시**
```bash
git add README.md
git commit -m "Add comprehensive README.md"
git push origin main
```

---

# 🚀 GitHub Pages 배포

## GitHub Pages란?

**GitHub에서 제공하는 무료 정적 웹사이트 호스팅 서비스**

- **무료 도메인**: `사용자명.github.io/저장소명`
- **자동 배포**: 코드 푸시 시 자동 업데이트
- **HTTPS 지원**: 보안 연결 기본 제공
- **커스텀 도메인**: 원하는 도메인 연결 가능

## 배포 설정하기

### **Step 1: 저장소 설정**
1. **GitHub 저장소 페이지** 접속
2. **Settings** 탭 클릭
3. **Pages** 메뉴 선택

### **Step 2: 소스 설정**
- **Source**: Deploy from a branch
- **Branch**: main 선택
- **Folder**: / (root) 선택
- **Save** 클릭

### **Step 3: 배포 확인**
- 몇 분 후 초록색 체크 표시 확인
- 제공된 URL로 접속하여 사이트 확인

![bg right:35% w:350](https://images.unsplash.com/photo-1551650975-87deedd944c3?w=350&h=250&fit=crop)

---

## 배포 URL 구조

### **기본 URL 패턴**
```
https://사용자명.github.io/저장소명/

예시:
https://johndoe.github.io/my-profile-website/
```

### **특별한 경우**
```
저장소명이 '사용자명.github.io'인 경우:
https://사용자명.github.io/

예시:
https://johndoe.github.io/
```

### **배포 상태 확인**
- **Actions** 탭에서 배포 진행상황 확인
- **Environment** 탭에서 배포 히스토리 확인

---

# 🔧 협업을 위한 추가 기능

## 이슈(Issues) 관리

### **이슈란?**
- 버그 리포트, 기능 요청, 질문 등을 관리
- 프로젝트 진행 상황 추적
- 팀원 간 소통 도구

### **이슈 생성 예시**
```
제목: Add dark mode toggle button
라벨: enhancement
내용:
- [ ] Add theme toggle button to header
- [ ] Implement CSS custom properties for colors
- [ ] Add JavaScript theme switching logic
- [ ] Store theme preference in localStorage
```

## 프로젝트 보드

### **칸반 보드 스타일 프로젝트 관리**
- **To Do**: 할 일 목록
- **In Progress**: 진행 중인 작업
- **Done**: 완료된 작업

### **보드 생성 방법**
1. **Projects** 탭 클릭
2. **New project** 선택
3. **Board** 템플릿 선택
4. 카드 추가 및 관리

---

# 📊 Git 브랜치 기초

## 브랜치란?

**독립적인 개발 라인을 만드는 Git의 핵심 기능**

```
main ──●──●──●──●──●  (안정적인 버전)
        \
         ●──●──●  feature/dark-mode (새 기능 개발)
```

## 기본 브랜치 명령어

```bash
# 현재 브랜치 확인
git branch

# 새 브랜치 생성
git branch feature/contact-form

# 브랜치 전환
git checkout feature/contact-form
# 또는 최신 문법
git switch feature/contact-form

# 브랜치 생성과 전환을 동시에
git checkout -b feature/dark-mode

# 브랜치 삭제
git branch -d feature/completed-feature
```

## 브랜치 전략

### **간단한 프로젝트 (개인)**
```
main: 배포 가능한 안정적인 코드
feature/기능명: 새로운 기능 개발
```

### **브랜치 네이밍 규칙**
```
feature/새로운-기능    (예: feature/dark-mode)
fix/버그-수정         (예: fix/mobile-layout)
docs/문서-업데이트    (예: docs/readme-update)
```

---

# 🎨 프로젝트 개선 아이디어

## 포트폴리오 고도화 방안

### **디자인 개선**
- 📱 더 나은 반응형 디자인
- 🌙 다크 모드 완벽 구현
- ✨ 부드러운 애니메이션 추가
- 🎨 일관된 색상 팔레트

### **기능 추가**
- 📝 블로그 섹션
- 🖼️ 프로젝트 갤러리
- 📊 기술 스택 차트
- 💬 방문자 방명록

### **기술적 개선**
- 🚀 성능 최적화
- 📈 Google Analytics 연동
- 🔍 SEO 최적화
- 🛡️ 보안 강화

### **포트폴리오 확장**
- 🌍 다국어 지원
- 📱 PWA (Progressive Web App) 변환
- 🎯 맞춤형 도메인 연결
- 📧 이메일 자동 발송

---

# 💡 실전 프로젝트 아이디어

## 초급자 프로젝트

### **1. 할 일 관리 앱 (To-Do App)**
```
기능: 할 일 추가, 완료, 삭제
기술: HTML, CSS, JavaScript
학습: 로컬 스토리지, 배열 조작
```

### **2. 날씨 앱 (Weather App)**
```
기능: 현재 날씨 조회, 5일 예보
기술: API 연동, 비동기 처리
학습: fetch API, JSON 파싱
```

### **3. 간단한 블로그**
```
기능: 글 목록, 글 보기, 검색
기술: Static Site Generator 또는 순수 JS
학습: 라우팅, 상태 관리
```

## 중급자 프로젝트

### **1. 온라인 포트폴리오 플랫폼**
```
기능: 사용자 등록, 포트폴리오 공유
기술: React, Node.js, MongoDB
학습: 풀스택 개발, 데이터베이스
```

### **2. 실시간 채팅 앱**
```
기능: 실시간 메시지, 파일 공유
기술: WebSocket, Socket.io
학습: 실시간 통신, 이벤트 처리
```

---

# 🔧 개발 환경 고도화

## 유용한 VS Code 확장프로그램

### **필수 확장프로그램**
```
- Live Server: 실시간 미리보기
- Prettier: 코드 포맷팅
- GitLens: Git 히스토리 시각화
- Bracket Pair Colorizer: 괄호 색상 구분
- Auto Rename Tag: HTML 태그 자동 수정
```

### **추가 권장 확장프로그램**
```
- Emmet: HTML/CSS 빠른 작성
- JavaScript (ES6) code snippets: 코드 스니펫
- CSS Peek: CSS 정의 바로 보기
- HTML CSS Support: HTML에서 CSS 자동완성
- Color Highlight: 색상 코드 시각화
```

## Git GUI 도구

### **초보자 친화적 도구**
```
- GitHub Desktop: 공식 GitHub 클라이언트
- SourceTree: Atlassian 제공 무료 도구
- GitKraken: 시각적 Git 관리 도구
- Fork: Mac/Windows용 Git 클라이언트
```

### **통합 개발 환경**
```
- VS Code: 내장 Git 지원
- WebStorm: JetBrains 제품
- Sublime Text: 플러그인 지원
```

---

# 🎊 5-2교시 마무리

## 오늘 배운 내용 정리

- **GitHub 계정 생성** 및 프로필 설정
- **원격 저장소 연동** (push, pull)
- **README.md 작성** 및 프로젝트 문서화
- **GitHub Pages 배포**로 포트폴리오 공개
- **브랜치 기초** 및 협업 준비

## 다음 단계 제안

### **즉시 실습 과제**
1. 본인만의 README.md 작성 완료
2. GitHub Pages 배포 성공
3. 최소 5개 이상의 의미있는 커밋 만들기
4. 프로젝트에 추가 기능 구현

### **장기 목표**
- 매주 최소 1개의 커밋 유지 (GitHub 잔디 만들기)
- 다양한 프로젝트로 포트폴리오 확장
- 오픈소스 프로젝트 기여 시작
- 기술 블로그 운영 시작

![bg right:45% w:450](https://images.unsplash.com/photo-1618401479427-c8ef9465fcc1?w=450&h=300&fit=crop)

---

# 🏆 성취 배지 및 인증

## GitHub 프로필 꾸미기

### **GitHub Stats 배지**
```markdown
![GitHub Stats](https://github-readme-stats.vercel.app/api?username=사용자명&show_icons=true&theme=radical)
```

### **사용 언어 통계**
```markdown
![Top Languages](https://github-readme-stats.vercel.app/api/top-langs/?username=사용자명&layout=compact)
```

### **기여도 그래프**
```markdown
![GitHub Streak](https://github-readme-streak-stats.herokuapp.com/?user=사용자명&theme=dark)
```

## 포트폴리오 체크리스트

### **기본 요소**
- [ ] 전문적인 프로필 사진
- [ ] 명확한 프로젝트 설명
- [ ] 사용 기술 명시
- [ ] 라이브 데모 링크
- [ ] 연락처 정보

### **고급 요소**
- [ ] 프로젝트 스크린샷
- [ ] 개발 과정 설명
- [ ] 기술적 도전과 해결 방안
- [ ] 향후 개선 계획
- [ ] 다른 프로젝트와의 차별점

![bg right:40% w:400](https://images.unsplash.com/photo-1551650975-87deedd944c3?w=400&h=300&fit=crop)

---

# 🌟 축하합니다!

## 여러분은 이제...

- ✅ **Git과 GitHub 마스터** - 버전 관리의 달인
- ✅ **포트폴리오 배포** - 전 세계에 내 작품 공개
- ✅ **협업 준비 완료** - 팀 프로젝트 참여 가능
- ✅ **지속적 학습** - 매일 성장하는 개발자

## 앞으로의 여정

**매일 코딩하고, 매일 커밋하고, 매일 성장하세요!**

여러분의 GitHub 프로필이 여러분의 성장을 증명할 것입니다.

**Happy Coding! 🚀**

![bg right:50% w:500](https://images.unsplash.com/photo-1556075798-4825dfaaf498?w=500&h=400&fit=crop)
