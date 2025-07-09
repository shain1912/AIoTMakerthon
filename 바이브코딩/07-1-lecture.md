---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 7-1강 - Node.js와 모던 개발환경'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 Node.js 및 모던 개발환경 구축 (1부)

## 바닐라에서 모던까지, 개발 환경의 진화

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1629654297299-c8506221ca97?w=400&h=300&fit=crop)

---

## 📋 7-1교시 학습 목표

- **Node.js 개발환경** 이해 및 설치
- **npm 패키지 관리 시스템** 마스터
- **모듈 시스템** 이해 (CommonJS vs ES Modules)
- **package.json** 프로젝트 설정 파일 활용

---

## 🔗 지금까지의 여정

- **1-2강**: HTML/CSS로 정적 웹페이지 제작
- **3강**: CSS 고급 기법과 반응형 디자인
- **4강**: JavaScript로 인터랙티브 기능 추가
- **5강**: Git/GitHub로 버전 관리 및 배포
- **6강**: React로 컴포넌트 기반 개발

### **이제 우리는...**
- 프론트엔드 개발 기초 완료 ✅
- 컴포넌트 기반 사고방식 습득 ✅
- 협업을 위한 Git 활용 가능 ✅

![bg right:35% w:350](https://images.unsplash.com/photo-1517077304055-6e89abbf09b0?w=350&h=250&fit=crop)

---

# 🤔 왜 Node.js를 배워야 할까?

## 기존 개발 방식의 한계

### **순수 HTML/CSS/JS의 어려움**
- **새로고침 반복**: 코드 수정할 때마다 F5
- **파일 관리 어려움**: 프로젝트가 커질수록 복잡
- **라이브러리 설치**: CDN 링크나 파일 다운로드
- **최적화 부족**: 압축, 번들링 수동 작업

### **현실적인 문제들**
```html
<!-- 수십 개의 CSS 파일 -->
<link rel="stylesheet" href="reset.css">
<link rel="stylesheet" href="common.css">
<link rel="stylesheet" href="header.css">
<link rel="stylesheet" href="main.css">
<!-- ... 계속 늘어남 -->

<!-- 수십 개의 JS 파일 -->
<script src="jquery.js"></script>
<script src="utils.js"></script>
<script src="header.js"></script>
<script src="main.js"></script>
<!-- ... 순서도 중요함 -->
```

![bg right:40% w:400](https://images.unsplash.com/photo-1618401471353-b98afee0b2eb?w=400&h=300&fit=crop)

---

## Node.js의 해결책

### **모던 개발환경의 장점**
- **자동 새로고침**: 코드 저장하면 브라우저 즉시 업데이트
- **모듈 시스템**: 파일을 논리적으로 분리하고 관리
- **패키지 관리**: npm으로 라이브러리 쉽게 설치/관리
- **자동 최적화**: 빌드 도구가 압축, 번들링 자동 처리

### **개발 생산성 비교**
```bash
# 기존 방식: 라이브러리 설치
1. 구글에서 라이브러리 검색
2. 공식 사이트 방문
3. 다운로드 링크 찾기
4. HTML에 <script> 태그 추가
5. 버전 업데이트 시 1-4 반복

# 모던 방식: npm으로 설치
npm install lodash
# 끝! 자동으로 프로젝트에 연결됨
```

---

# 📖 Node.js란 무엇인가?

## 🎯 정의 및 특징

**Node.js**는 Chrome V8 JavaScript 엔진으로 빌드된 JavaScript 런타임 환경입니다.

### **핵심 개념**
- **런타임 환경**: 브라우저 밖에서도 JavaScript 실행
- **V8 엔진**: 구글이 만든 빠른 JavaScript 엔진
- **이벤트 기반**: 비동기 처리로 높은 성능
- **크로스 플랫폼**: Windows, macOS, Linux 모두 지원

### **Node.js가 할 수 있는 일**
```javascript
// 서버 개발
const http = require('http');
const server = http.createServer();

// 파일 시스템 조작
const fs = require('fs');
fs.readFile('data.txt', 'utf8', callback);

// 개발 도구 제작
const { exec } = require('child_process');
exec('npm install', callback);

// 스크립트 실행
console.log('Hello from Node.js!');
```

![bg right:40% w:400](https://images.unsplash.com/photo-1587620962725-abab7fe55159?w=400&h=300&fit=crop)

---

## 🌐 런타임 환경 vs 브라우저 환경

### **브라우저 환경 (Client-side)**
```javascript
// 브라우저에서만 사용 가능한 API
window.alert('Hello!');
document.querySelector('#app');
localStorage.setItem('key', 'value');
navigator.geolocation.getCurrentPosition();

// DOM 조작
const button = document.createElement('button');
button.textContent = 'Click me';
document.body.appendChild(button);
```

### **Node.js 환경 (Server-side)**
```javascript
// Node.js에서만 사용 가능한 API
const fs = require('fs');
const path = require('path');
const os = require('os');

console.log(__dirname);  // 현재 디렉토리
console.log(__filename); // 현재 파일명
console.log(os.platform()); // 운영체제 정보

// 파일 읽기/쓰기
fs.writeFileSync('output.txt', 'Hello Node.js!');
```

### **공통 영역 (Both)**
```javascript
// 양쪽 모두에서 사용 가능
const data = [1, 2, 3, 4, 5];
const doubled = data.map(x => x * 2);
const sum = data.reduce((acc, x) => acc + x, 0);

console.log('결과:', doubled); // [2, 4, 6, 8, 10]
console.log('합계:', sum);     // 15
```

---

# 🛠️ Node.js 설치 및 설정

## Node.js 설치

### **공식 사이트에서 설치**
1. **https://nodejs.org** 접속
2. **LTS 버전** 다운로드 (Long Term Support - 안정적)
3. 설치 파일 실행 (기본 설정으로 진행)
4. 설치 완료 후 재부팅 (Windows)

### **설치 확인**
```bash
# 터미널/명령 프롬프트에서 실행
node --version
# 결과 예시: v18.17.0

npm --version
# 결과 예시: 9.6.7

# Node.js 대화형 모드 실행
node
> console.log('Hello Node.js!');
Hello Node.js!
> .exit  // 종료
```

### **버전 관리 (선택사항)**
```bash
# nvm (Node Version Manager) - macOS/Linux
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.0/install.sh | bash

# nvm-windows - Windows
# GitHub에서 설치 파일 다운로드

# 사용법
nvm install 18.17.0
nvm use 18.17.0
nvm list
```

![bg right:35% w:350](https://images.unsplash.com/photo-1629654297299-c8506221ca97?w=350&h=250&fit=crop)

---

## VS Code 터미널 설정

### **통합 터미널 활용**
```bash
# VS Code에서 터미널 열기
Ctrl + ` (백틱)
# 또는 View > Terminal

# PowerShell 설정 (Windows)
# 기본 터미널을 PowerShell로 설정
Ctrl + Shift + P > "Terminal: Select Default Profile"
```

### **유용한 터미널 명령어**
```bash
# 현재 위치 확인
pwd        # macOS/Linux
cd         # Windows

# 폴더 내용 보기
ls         # macOS/Linux
dir        # Windows

# 폴더 이동
cd my-project
cd ..      # 상위 폴더
cd ~       # 홈 폴더

# 폴더 생성
mkdir my-new-project
```

---

# 📦 npm (Node Package Manager)

## npm이란?

**npm**은 세계 최대의 소프트웨어 레지스트리이자 JavaScript 패키지 관리 도구입니다.

### **npm의 역할**
- **패키지 설치**: 외부 라이브러리 다운로드 및 설치
- **의존성 관리**: 패키지 간의 의존 관계 자동 관리
- **스크립트 실행**: 개발/빌드/테스트 명령어 실행
- **버전 관리**: 패키지 버전 업데이트 및 호환성 관리

### **npm vs 기존 방식 비교**
```html
<!-- 기존 방식: CDN 링크 -->
<script src="https://cdnjs.cloudflare.com/ajax/libs/lodash.js/4.17.21/lodash.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/axios/1.4.0/axios.min.js"></script>

<!-- 문제점: 버전 관리 어려움, 오프라인에서 작동 안 함 -->
```

```bash
# npm 방식: 명령어로 설치
npm install lodash axios

# 장점: 자동 버전 관리, 오프라인 작동, 의존성 자동 해결
```

![bg right:40% w:400](https://images.unsplash.com/photo-1618401479427-c8ef9465fcc1?w=400&h=300&fit=crop)

---

## 기본 npm 명령어

### **프로젝트 초기화**
```bash
# 새 프로젝트 생성
mkdir my-awesome-project
cd my-awesome-project

# package.json 파일 생성
npm init
# 또는 기본값으로 빠르게 생성
npm init -y
```

### **패키지 설치**
```bash
# 프로덕션 의존성 설치
npm install lodash
npm install axios moment

# 개발 의존성 설치 (개발 중에만 필요)
npm install --save-dev vite
npm install -D eslint prettier

# 전역 설치 (시스템 전체에서 사용)
npm install -g create-react-app
npm install -g live-server
```

### **패키지 관리**
```bash
# 설치된 패키지 목록 보기
npm list
npm list --depth=0  # 최상위 레벨만

# 패키지 정보 확인
npm info lodash
npm view axios version

# 패키지 업데이트
npm update
npm update lodash

# 패키지 제거
npm uninstall lodash
npm remove axios
```

---

## package.json 이해하기

### **package.json의 역할**
```json
{
  "name": "my-awesome-project",
  "version": "1.0.0",
  "description": "멋진 프로젝트입니다",
  "main": "index.js",
  "scripts": {
    "start": "node index.js",
    "dev": "vite",
    "build": "vite build",
    "test": "jest"
  },
  "dependencies": {
    "axios": "^1.4.0",
    "lodash": "^4.17.21"
  },
  "devDependencies": {
    "vite": "^4.4.0",
    "eslint": "^8.0.0"
  },
  "keywords": ["javascript", "web", "frontend"],
  "author": "조성호",
  "license": "MIT"
}
```

### **주요 필드 설명**
- **name**: 프로젝트 이름 (npm에 발행 시 고유해야 함)
- **version**: 프로젝트 버전 (시맨틱 버저닝)
- **scripts**: 실행 가능한 명령어들
- **dependencies**: 프로덕션에서 필요한 패키지
- **devDependencies**: 개발 중에만 필요한 패키지

---

## 의존성 관리

### **dependencies vs devDependencies**
```json
{
  "dependencies": {
    "axios": "^1.4.0",      // API 호출 라이브러리
    "lodash": "^4.17.21",   // 유틸리티 라이브러리
    "react": "^18.2.0"      // UI 라이브러리
  },
  "devDependencies": {
    "vite": "^4.4.0",       // 빌드 도구
    "eslint": "^8.0.0",     // 코드 품질 검사
    "prettier": "^2.8.0"    // 코드 포맷팅
  }
}
```

### **버전 명시 방법**
```json
{
  "dependencies": {
    "exact": "1.2.3",        // 정확히 1.2.3 버전
    "caret": "^1.2.3",       // 1.x.x (major 고정)
    "tilde": "~1.2.3",       // 1.2.x (minor 고정)
    "range": ">=1.2.3 <2.0.0", // 범위 지정
    "latest": "*"            // 최신 버전
  }
}
```

### **package-lock.json**
```json
// package-lock.json - 정확한 버전 고정
{
  "name": "my-project",
  "lockfileVersion": 2,
  "requires": true,
  "packages": {
    "node_modules/lodash": {
      "version": "4.17.21",
      "resolved": "https://registry.npmjs.org/lodash/-/lodash-4.17.21.tgz",
      "integrity": "sha512-v2kDEe57lecTulaDIuNTPy3Ry4gLGJ6Z1O3vE1krgXZNrsQ+LFTGHVxVjcXPs17LhbZVGedAJv8XZ1tvj5FvSg=="
    }
  }
}
```

---

# 🔄 모듈 시스템

## CommonJS vs ES Modules

### **CommonJS (Node.js 전통 방식)**
```javascript
// utils.js - 내보내기
function add(a, b) {
    return a + b;
}

function multiply(a, b) {
    return a * b;
}

// 개별 내보내기
exports.add = add;
exports.multiply = multiply;

// 또는 한 번에 내보내기
module.exports = {
    add,
    multiply
};

// 기본 내보내기
module.exports = function greet(name) {
    return `Hello, ${name}!`;
};
```

```javascript
// main.js - 가져오기
const { add, multiply } = require('./utils');
const greet = require('./greet');

console.log(add(2, 3));      // 5
console.log(multiply(4, 5)); // 20
console.log(greet('Node.js')); // Hello, Node.js!
```

---

### **ES Modules (모던 방식)**
```javascript
// utils.js - 내보내기
export function add(a, b) {
    return a + b;
}

export function multiply(a, b) {
    return a * b;
}

// 기본 내보내기
export default function greet(name) {
    return `Hello, ${name}!`;
}

// 또는 한 번에 내보내기
const calculator = { add, multiply };
export default calculator;
```

```javascript
// main.js - 가져오기
import greet, { add, multiply } from './utils.js';
import calculator from './calculator.js';

console.log(add(2, 3));      // 5
console.log(multiply(4, 5)); // 20
console.log(greet('ES Modules')); // Hello, ES Modules!
```

### **ES Modules 활성화**
```json
// package.json에 추가
{
  "type": "module"
}
```

---

## npm 스크립트 활용

### **자주 사용하는 스크립트**
```json
{
  "scripts": {
    "start": "node server.js",
    "dev": "vite --host",
    "build": "vite build",
    "preview": "vite preview",
    "test": "jest",
    "lint": "eslint src/",
    "format": "prettier --write src/",
    "clean": "rm -rf dist/",
    "deploy": "npm run build && gh-pages -d dist"
  }
}
```

### **스크립트 실행**
```bash
# 기본 스크립트
npm start
npm test

# 커스텀 스크립트
npm run dev
npm run build
npm run lint

# 인자 전달
npm run dev -- --port 3001
npm run test -- --watch
```

### **스크립트 조합**
```json
{
  "scripts": {
    "prebuild": "npm run clean",
    "build": "vite build",
    "postbuild": "npm run test",
    
    "ci": "npm run lint && npm run test && npm run build",
    "release": "npm run ci && npm publish"
  }
}
```

---

# 💻 첫 번째 Node.js 프로젝트

## 실습: 간단한 웹 서버 만들기

### **프로젝트 생성**
```bash
# 프로젝트 폴더 생성
mkdir my-first-node-project
cd my-first-node-project

# package.json 생성
npm init -y

# 필요한 패키지 설치
npm install express
npm install -D nodemon
```

### **server.js 작성**
```javascript
// server.js
const express = require('express');
const path = require('path');

const app = express();
const PORT = 3000;

// 정적 파일 서빙
app.use(express.static('public'));

// 루트 경로
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// API 엔드포인트
app.get('/api/hello', (req, res) => {
    res.json({
        message: 'Hello from Node.js!',
        timestamp: new Date().toISOString()
    });
});

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});
```

### **public/index.html 작성**
```html
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>My First Node.js Project</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 2rem;
            text-align: center;
        }
        button {
            background: #007bff;
            color: white;
            border: none;
            padding: 1rem 2rem;
            border-radius: 5px;
            cursor: pointer;
            font-size: 1rem;
        }
        button:hover {
            background: #0056b3;
        }
        #result {
            margin-top: 2rem;
            padding: 1rem;
            background: #f8f9fa;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <h1>🎉 첫 번째 Node.js 프로젝트</h1>
    <p>Node.js 서버가 성공적으로 실행되고 있습니다!</p>
    
    <button onclick="fetchData()">API 호출하기</button>
    
    <div id="result"></div>

    <script>
        async function fetchData() {
            try {
                const response = await fetch('/api/hello');
                const data = await response.json();
                
                document.getElementById('result').innerHTML = `
                    <h3>API 응답:</h3>
                    <p><strong>메시지:</strong> ${data.message}</p>
                    <p><strong>시간:</strong> ${data.timestamp}</p>
                `;
            } catch (error) {
                document.getElementById('result').innerHTML = `
                    <p style="color: red;">오류: ${error.message}</p>
                `;
            }
        }
    </script>
</body>
</html>
```

---

## package.json 스크립트 설정

### **개발용 스크립트 추가**
```json
{
  "name": "my-first-node-project",
  "version": "1.0.0",
  "description": "첫 번째 Node.js 프로젝트",
  "main": "server.js",
  "scripts": {
    "start": "node server.js",
    "dev": "nodemon server.js",
    "test": "echo \"테스트가 아직 없습니다\" && exit 0"
  },
  "dependencies": {
    "express": "^4.18.2"
  },
  "devDependencies": {
    "nodemon": "^3.0.1"
  }
}
```

### **서버 실행 및 테스트**
```bash
# 개발 모드로 실행 (파일 변경 시 자동 재시작)
npm run dev

# 브라우저에서 http://localhost:3000 접속
# API 호출 버튼 클릭하여 테스트
```

---

# 🎊 7-1교시 마무리

## 오늘 배운 내용 정리

- **Node.js 개념** 이해 및 설치 완료
- **npm 패키지 관리 시스템** 기본 사용법
- **모듈 시스템** (CommonJS vs ES Modules)
- **package.json** 설정 및 스크립트 활용
- **첫 번째 Node.js 프로젝트** 생성 및 실행

## 다음 시간 (7-2교시) 예고

- **Vite 빌드 도구** 설치 및 설정
- **Hot Module Replacement** 체험
- **프로덕션 빌드** 및 최적화
- **기존 프로젝트를 Vite로 마이그레이션**

![bg right:45% w:450](https://images.unsplash.com/photo-1629654297299-c8506221ca97?w=450&h=300&fit=crop)
