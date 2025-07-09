---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 5-1강 - Git 기초와 로컬 저장소'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 Git 기초 및 GitHub 연동 (1부)

## 버전 관리의 시작, Git 마스터하기

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1556075798-4825dfaaf498?w=400&h=300&fit=crop)

---

## 📋 5-1교시 학습 목표

- **Git 버전 관리 시스템** 이해 및 설치
- **기본 Git 명령어** 마스터 (add, commit, log)
- **로컬 저장소** 생성 및 관리
- **커밋 히스토리** 만들기

---

## 🤔 왜 Git을 배워야 할까?

### **😱 이런 경험 있으신가요?**
- "작업하다가 파일을 잘못 건드려서 다 망가졌어요..."
- "어제 코드가 더 좋았는데 되돌릴 수 없나요?"
- "팀원과 코드를 어떻게 공유하고 합칠까요?"
- "내 프로젝트를 포트폴리오로 보여주고 싶어요!"

### **✅ Git으로 해결!**
- **시간 여행**: 언제든 이전 버전으로 되돌리기
- **안전한 백업**: 클라우드에 코드 자동 저장
- **협업의 기본**: 전 세계 개발자들의 표준 도구
- **포트폴리오**: GitHub으로 내 실력 증명

![bg right:40% w:400](https://images.unsplash.com/photo-1618401471353-b98afee0b2eb?w=400&h=300&fit=crop)

---

# 📖 Git이란 무엇인가?

## 🎯 정의

**Git**은 파일의 변경사항을 추적하고 관리하는 분산형 버전 관리 시스템입니다.

- 코드의 모든 변경 이력을 체계적으로 저장
- 여러 사람이 동시에 작업할 수 있는 협업 도구
- 리누스 토르발스(Linux 창시자)가 개발

![bg right:40% w:400](https://images.unsplash.com/photo-1607799632518-da91dd151b38?w=400&h=300&fit=crop)

---

## ✨ Git 핵심 개념

### **1. 스냅샷 방식**
```
시간 순서대로 프로젝트의 "사진"을 찍어서 저장
├── 📸 첫 번째 커밋 (HTML 파일 생성)
├── 📸 두 번째 커밋 (CSS 스타일 추가)
├── 📸 세 번째 커밋 (JavaScript 기능 추가)
└── 📸 네 번째 커밋 (버그 수정)
```

### **2. 세 가지 영역**
```
Working Directory    Staging Area       Repository
(작업 영역)         (스테이징 영역)     (저장소)
     📝                   📋                🗃️
   수정 중인             커밋 준비된         확정된
   파일들               파일들              버전들

   git add  ➡️          git commit ➡️
```

---

## 🌐 Git vs GitHub

| 구분 | Git | GitHub |
|------|-----|--------|
| **정의** | 버전 관리 도구 | Git 저장소 호스팅 서비스 |
| **위치** | 내 컴퓨터 (로컬) | 클라우드 서버 (원격) |
| **역할** | 파일 변경사항 추적 | 코드 공유, 협업, 백업 |
| **사용법** | 명령어 입력 | 웹사이트 + Git 명령어 |

### **🔄 로컬 ↔ 원격 동기화**
```
내 컴퓨터 (Git)           GitHub (원격 저장소)
     📁                        ☁️
  로컬 저장소              원격 저장소

     push ➡️              ⬅️ pull
   (업로드)               (다운로드)
```

---

# 🛠️ Git 설치 및 초기 설정

## Git 설치

### **Windows**
1. https://git-scm.com 접속
2. "Download for Windows" 클릭
3. 설치 파일 실행 (기본 설정 그대로 OK)

### **Mac**
```bash
# Homebrew로 설치 (권장)
brew install git

# 또는 Xcode Command Line Tools
xcode-select --install
```

### **설치 확인**
```bash
# Git 버전 확인
git --version

# 결과 예시: git version 2.42.0
```

![bg right:35% w:350](https://images.unsplash.com/photo-1629654297299-c8506221ca97?w=350&h=250&fit=crop)

---

## 사용자 정보 설정 (최초 1회)

```bash
# 전역 사용자 이름 설정
git config --global user.name "당신의이름"

# 전역 이메일 설정 (GitHub 계정과 동일해야 함)
git config --global user.email "your.email@example.com"

# 기본 브랜치를 main으로 설정 (권장)
git config --global init.defaultBranch main

# 설정 확인
git config --global --list
```

### **왜 설정이 필요한가?**
- 모든 커밋에 **작성자 정보**가 기록됨
- GitHub와 **연동**할 때 동일한 이메일 필요
- **협업**시 누가 무엇을 변경했는지 추적 가능

---

# 💻 로컬 저장소 생성 및 기본 명령어

## 저장소 초기화

```bash
# 프로젝트 폴더로 이동
cd my-profile-website

# Git 저장소 초기화
git init

# 결과: .git 폴더 생성됨 (숨김 폴더)
```

### **초기화 후 변화**
- **.git 폴더** 생성 (Git 관련 모든 정보 저장)
- 현재 폴더가 **Git 저장소**가 됨
- 앞으로 이 폴더의 모든 변경사항을 **추적 가능**

![bg right:40% w:400](https://images.unsplash.com/photo-1618401479427-c8ef9465fcc1?w=400&h=300&fit=crop)

---

## 파일 상태 확인

```bash
# 현재 상태 확인
git status
```

### **상태 메시지 해석**
- **Untracked files**: 아직 Git이 추적하지 않는 새 파일
- **Changes not staged**: 수정되었지만 아직 스테이징되지 않은 파일
- **Changes to be committed**: 커밋 준비된 파일
- **Nothing to commit**: 모든 변경사항이 커밋됨

### **파일 상태 흐름**
```
Untracked ➡️ Staged ➡️ Committed
   (새 파일)   (git add)   (git commit)
      ⬇️         ⬇️          ⬇️
   빨간색      초록색     기록됨
```

---

## 파일 스테이징 (git add)

```bash
# 특정 파일 스테이징
git add index.html
git add style.css

# 여러 파일 동시 스테이징
git add index.html style.css script.js

# 모든 파일 스테이징
git add .

# 특정 확장자 파일만 스테이징
git add *.css
git add *.js
```

### **스테이징이란?**
- **커밋할 준비**를 하는 단계
- 변경된 파일 중 **선택적으로** 커밋 가능
- 커밋 전에 **최종 검토** 기회 제공

---

## 커밋 (git commit)

```bash
# 커밋 메시지와 함께 저장
git commit -m "첫 번째 커밋: 기본 HTML 구조 추가"

# 좋은 커밋 메시지 예시:
git commit -m "Add responsive navigation menu"
git commit -m "Fix mobile layout overflow issue"
git commit -m "Update contact form validation"
```

### **좋은 커밋 메시지 작성법**
- **동사원형**으로 시작 (Add, Fix, Update, Remove)
- **50자 이내**로 간결하게
- **무엇을 왜**가 아닌 **무엇을** 했는지 명시
- **영어 사용** 권장 (국제적 표준)

![bg right:35% w:350](https://images.unsplash.com/photo-1618401471353-b98afee0b2eb?w=350&h=250&fit=crop)

---

# 📋 .gitignore 파일 작성

## .gitignore란?

**Git이 추적하지 않을 파일들을 지정**하는 설정 파일

### **왜 필요한가?**
- **민감한 정보** 보호 (API 키, 패스워드)
- **자동 생성 파일** 제외 (로그, 캐시)
- **개발 환경 설정** 제외 (에디터 설정)
- **의존성 폴더** 제외 (node_modules)

## .gitignore 파일 생성 및 작성

```bash
# .gitignore 파일 생성
touch .gitignore
# Windows에서는: type nul > .gitignore
```

### **기본 .gitignore 내용**
```gitignore
# 에디터 설정
.vscode/
.idea/

# 운영체제 생성 파일
.DS_Store
Thumbs.db

# 로그 파일
*.log

# 임시 파일
*.tmp
*.temp

# 환경 변수 (나중에 필요)
.env
.env.local

# 의존성 폴더 (나중에 필요)
node_modules/
```

---

# 📊 커밋 히스토리 관리

## 커밋 로그 확인

```bash
# 기본 로그 보기
git log

# 한 줄로 요약해서 보기 (권장)
git log --oneline

# 그래프 형태로 보기
git log --oneline --graph

# 최근 3개 커밋만 보기
git log -3
```

### **로그 정보 해석**
- **커밋 해시**: 각 커밋의 고유 ID (노란색)
- **커밋 메시지**: 변경사항 설명
- **작성자**: 누가 커밋했는지
- **날짜**: 언제 커밋했는지

![bg right:40% w:400](https://images.unsplash.com/photo-1551650975-87deedd944c3?w=400&h=300&fit=crop)

---

## 파일 변경사항 확인

```bash
# 현재 수정된 내용 확인 (스테이징 전)
git diff

# 스테이징된 내용 확인 (커밋 전)
git diff --staged

# 특정 파일의 변경사항만 확인
git diff index.html

# 이전 커밋과 비교
git diff HEAD~1
```

### **diff 출력 해석**
- **빨간색 (-)**: 삭제된 라인
- **초록색 (+)**: 추가된 라인
- **@@**: 변경된 라인 번호 정보

---

# 💻 실전 예제: 첫 번째 커밋 만들기

## 단계별 실습

### **Step 1: 저장소 초기화**
```bash
cd my-profile-website
git init
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

### **Step 2: .gitignore 생성**
```bash
echo ".DS_Store" > .gitignore
echo "*.log" >> .gitignore
echo ".vscode/" >> .gitignore
```

### **Step 3: 첫 번째 커밋**
```bash
git add .
git commit -m "Initial commit: Add basic project structure"
```

### **Step 4: 히스토리 확인**
```bash
git log --oneline
git status
```

---

# 🎊 5-1교시 마무리

## 오늘 배운 내용 정리

- **Git 기본 개념**과 필요성 이해
- **Git 설치 및 초기 설정** 완료
- **기본 명령어** (init, add, commit, status, log)
- **.gitignore** 파일 작성법
- **커밋 히스토리** 관리

## 다음 시간 (5-2교시) 예고

- **GitHub 계정 생성** 및 저장소 만들기
- **원격 저장소 연동** (push, pull)
- **README.md 작성** 및 프로젝트 문서화
- **GitHub Pages 배포**로 포트폴리오 공개

![bg right:45% w:450](https://images.unsplash.com/photo-1556075798-4825dfaaf498?w=450&h=300&fit=crop)
