---
marp: true
theme: default
paginate: true
header: 'Vibe Coding 6-1강 - React 기초와 컴포넌트'
footer: '조성호 | 바이브코딩 시리즈'
---

# 🎯 React 기초 및 컴포넌트 개발 (1부)

## 모던 프론트엔드 개발의 시작

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1633356122544-f134324a6cee?w=400&h=300&fit=crop)

---

## 📋 6-1교시 학습 목표

- **React란 무엇인지** 이해하고 필요성 파악
- **개발 환경 설정** 및 프로젝트 생성
- **JSX 문법** 기초 마스터
- **컴포넌트 개념** 이해 및 첫 컴포넌트 만들기

---

## 🔗 지금까지의 여정

- **1-2강**: HTML/CSS로 정적 웹페이지 제작
- **3강**: CSS 고급 기법과 반응형 디자인
- **4강**: JavaScript로 인터랙티브 기능 추가
- **5강**: Git/GitHub로 버전 관리 및 배포

### **이제 우리는...**
- 기본적인 웹 개발 지식 보유 ✅
- 포트폴리오 웹사이트 완성 ✅
- Git으로 협업 준비 완료 ✅

![bg right:35% w:350](https://images.unsplash.com/photo-1517077304055-6e89abbf09b0?w=350&h=250&fit=crop)

---

# 🤔 왜 React를 배워야 할까?

## 기존 방식의 한계

### **순수 JavaScript의 어려움**
```html
<!-- HTML -->
<div id="todo-list"></div>
<input id="todo-input" type="text">
<button id="add-btn">추가</button>

<script>
// JavaScript - 복잡하고 반복적인 DOM 조작
const todoList = document.getElementById('todo-list');
const input = document.getElementById('todo-input');
const button = document.getElementById('add-btn');

let todos = [];

function renderTodos() {
    todoList.innerHTML = '';
    todos.forEach((todo, index) => {
        const div = document.createElement('div');
        div.innerHTML = `
            <span>${todo}</span>
            <button onclick="deleteTodo(${index})">삭제</button>
        `;
        todoList.appendChild(div);
    });
}

function addTodo() {
    const value = input.value.trim();
    if (value) {
        todos.push(value);
        input.value = '';
        renderTodos();
    }
}

function deleteTodo(index) {
    todos.splice(index, 1);
    renderTodos();
}

button.addEventListener('click', addTodo);
renderTodos();
</script>
```

---

## React의 해결책

### **같은 기능을 React로**
```jsx
function TodoApp() {
    const [todos, setTodos] = useState([]);
    const [inputValue, setInputValue] = useState('');

    const addTodo = () => {
        if (inputValue.trim()) {
            setTodos([...todos, inputValue]);
            setInputValue('');
        }
    };

    const deleteTodo = (index) => {
        setTodos(todos.filter((_, i) => i !== index));
    };

    return (
        <div>
            <div>
                {todos.map((todo, index) => (
                    <div key={index}>
                        <span>{todo}</span>
                        <button onClick={() => deleteTodo(index)}>삭제</button>
                    </div>
                ))}
            </div>
            <input 
                value={inputValue}
                onChange={(e) => setInputValue(e.target.value)}
                type="text" 
            />
            <button onClick={addTodo}>추가</button>
        </div>
    );
}
```

### **React의 장점**
- **간결한 코드**: DOM 조작 코드 대폭 감소
- **선언적 방식**: "어떻게"가 아닌 "무엇을" 보여줄지 집중
- **상태 관리**: 데이터 변경 시 UI 자동 업데이트
- **재사용성**: 컴포넌트 단위로 코드 재사용

---

# 📱 React란 무엇인가?

## 🎯 정의 및 특징

**React**는 Facebook(Meta)에서 개발한 사용자 인터페이스를 만들기 위한 JavaScript 라이브러리입니다.

### **핵심 특징**
- **컴포넌트 기반**: 재사용 가능한 UI 조각들
- **가상 DOM**: 성능 최적화된 렌더링
- **단방향 데이터 흐름**: 예측 가능한 상태 관리
- **생태계**: 풍부한 서드파티 라이브러리

### **React가 인기한 이유**
```
⭐ GitHub Stars: 220k+
💼 채용 공고: 프론트엔드 필수 기술
🏢 사용 기업: Facebook, Netflix, Airbnb, Uber...
📈 트렌드: 꾸준한 성장세
```

![bg right:40% w:400](https://images.unsplash.com/photo-1587620962725-abab7fe55159?w=400&h=300&fit=crop)

---

## 🔄 React의 핵심 개념

### **1. 컴포넌트 (Component)**
```jsx
// 버튼 컴포넌트
function Button({ text, onClick }) {
    return <button onClick={onClick}>{text}</button>;
}

// 사용
<Button text="클릭하세요" onClick={handleClick} />
```

### **2. JSX (JavaScript XML)**
```jsx
// HTML과 비슷하지만 JavaScript 안에서 사용
const element = <h1>Hello, React!</h1>;

// JavaScript 표현식 사용 가능
const name = "React";
const element = <h1>Hello, {name}!</h1>;
```

### **3. State (상태)**
```jsx
// 컴포넌트의 데이터
const [count, setCount] = useState(0);

// 상태 변경
setCount(count + 1);
```

### **4. Props (속성)**
```jsx
// 부모에서 자식으로 데이터 전달
function Greeting({ name }) {
    return <h1>안녕하세요, {name}님!</h1>;
}

// 사용
<Greeting name="홍길동" />
```

---

# 🛠️ 개발 환경 설정

## Node.js 설치

### **Node.js가 필요한 이유**
- React 개발 도구 실행을 위해 필요
- npm(Node Package Manager) 사용
- 모던 JavaScript 개발의 필수 도구

### **설치 방법**
1. **https://nodejs.org** 접속
2. **LTS 버전** 다운로드 (안정적인 버전)
3. 설치 후 확인:
```bash
node --version    # v18.0.0 이상
npm --version     # 8.0.0 이상
```

### **Windows 추가 설정**
```bash
# PowerShell 실행 정책 변경 (관리자 권한)
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

![bg right:35% w:350](https://images.unsplash.com/photo-1629654297299-c8506221ca97?w=350&h=250&fit=crop)

---

## React 프로젝트 생성

### **Create React App 사용**
```bash
# React 프로젝트 생성
npx create-react-app my-react-portfolio
cd my-react-portfolio

# 개발 서버 실행
npm start
```

### **생성된 프로젝트 구조**
```
my-react-portfolio/
├── public/
│   ├── index.html      # 메인 HTML 파일
│   └── favicon.ico     # 파비콘
├── src/
│   ├── App.js          # 메인 App 컴포넌트
│   ├── App.css         # App 스타일
│   ├── index.js        # 진입점
│   └── index.css       # 전역 스타일
├── package.json        # 프로젝트 설정
└── README.md          # 프로젝트 설명
```

### **개발 서버 접속**
- 브라우저에서 **http://localhost:3000** 접속
- 코드 변경 시 **자동 새로고침** (Hot Reload)
- 개발자 도구에서 **에러 및 경고** 확인

---

## 프로젝트 초기 설정

### **불필요한 파일 정리**
```bash
# src 폴더에서 삭제할 파일들
rm src/App.test.js
rm src/reportWebVitals.js
rm src/setupTests.js
rm src/logo.svg
```

### **package.json 스크립트**
```json
{
  "scripts": {
    "start": "react-scripts start",      // 개발 서버 실행
    "build": "react-scripts build",      // 프로덕션 빌드
    "test": "react-scripts test",        // 테스트 실행
    "eject": "react-scripts eject"       // 설정 노출 (주의!)
  }
}
```

### **유용한 VS Code 확장프로그램**
```
ES7+ React/Redux/React-Native snippets  # React 코드 스니펫
Auto Rename Tag                         # JSX 태그 자동 수정
Bracket Pair Colorizer                  # 괄호 색상 구분
Prettier                               # 코드 포맷팅
```

---

# 📝 JSX 문법 기초

## JSX란?

**JSX (JavaScript XML)**는 React에서 UI를 표현하기 위한 문법 확장입니다.

### **JSX vs HTML 비교**
```jsx
// HTML
<div class="container">
    <h1>제목</h1>
    <p onclick="handleClick()">클릭하세요</p>
</div>

// JSX
<div className="container">
    <h1>제목</h1>
    <p onClick={handleClick}>클릭하세요</p>
</div>
```

### **주요 차이점**
- `class` → `className`
- `onclick` → `onClick` (camelCase)
- 속성값에 JavaScript 표현식 사용: `{}`

## JSX 기본 문법

### **1. JavaScript 표현식 삽입**
```jsx
function Welcome() {
    const name = "React";
    const isLoggedIn = true;
    
    return (
        <div>
            <h1>안녕하세요, {name}!</h1>
            <p>{isLoggedIn ? "로그인됨" : "로그인 필요"}</p>
            <p>현재 시간: {new Date().toLocaleTimeString()}</p>
        </div>
    );
}
```

### **2. 조건부 렌더링**
```jsx
function UserGreeting({ user }) {
    return (
        <div>
            {user ? (
                <h1>환영합니다, {user.name}님!</h1>
            ) : (
                <h1>로그인해주세요</h1>
            )}
            
            {/* 간단한 조건부 렌더링 */}
            {user && <p>마지막 로그인: {user.lastLogin}</p>}
        </div>
    );
}
```

### **3. 리스트 렌더링**
```jsx
function TodoList() {
    const todos = ["React 공부", "프로젝트 만들기", "포트폴리오 업데이트"];
    
    return (
        <ul>
            {todos.map((todo, index) => (
                <li key={index}>{todo}</li>
            ))}
        </ul>
    );
}
```

---

## JSX 주의사항

### **1. 단일 루트 엘리먼트**
```jsx
// ❌ 잘못된 예시
function App() {
    return (
        <h1>제목</h1>
        <p>내용</p>
    );
}

// ✅ 올바른 예시
function App() {
    return (
        <div>
            <h1>제목</h1>
            <p>내용</p>
        </div>
    );
}

// ✅ Fragment 사용 (React 16.2+)
function App() {
    return (
        <>
            <h1>제목</h1>
            <p>내용</p>
        </>
    );
}
```

### **2. JSX에서 주석**
```jsx
function App() {
    return (
        <div>
            {/* JSX 주석은 이렇게 작성 */}
            <h1>제목</h1>
            
            {/* 
                여러 줄 주석도 가능
                하지만 JSX 표현식 안에서만
            */}
            <p>내용</p>
        </div>
    );
}
```

### **3. 예약어 피하기**
```jsx
// ❌ JavaScript 예약어
<div class="container" for="input">

// ✅ JSX 속성명
<div className="container" htmlFor="input">
```

---

# 🧩 컴포넌트 기초

## 함수형 컴포넌트

### **기본 구조**
```jsx
// 1. import React (React 18부터 선택사항)
import React from 'react';

// 2. 컴포넌트 정의
function Header() {
    return (
        <header>
            <h1>My Portfolio</h1>
            <nav>
                <a href="#about">About</a>
                <a href="#projects">Projects</a>
                <a href="#contact">Contact</a>
            </nav>
        </header>
    );
}

// 3. export (다른 파일에서 사용할 수 있도록)
export default Header;
```

### **Arrow Function 방식**
```jsx
const Header = () => {
    return (
        <header>
            <h1>My Portfolio</h1>
            <nav>
                <a href="#about">About</a>
                <a href="#projects">Projects</a>
                <a href="#contact">Contact</a>
            </nav>
        </header>
    );
};

export default Header;
```

## 컴포넌트 사용

### **App.js에서 컴포넌트 조합**
```jsx
// 컴포넌트 import
import Header from './components/Header';
import About from './components/About';
import Projects from './components/Projects';
import Contact from './components/Contact';

function App() {
    return (
        <div className="App">
            <Header />
            <About />
            <Projects />
            <Contact />
        </div>
    );
}

export default App;
```

### **컴포넌트 파일 구조**
```
src/
├── components/
│   ├── Header.js
│   ├── Header.css
│   ├── About.js
│   ├── About.css
│   ├── Projects.js
│   ├── Projects.css
│   ├── Contact.js
│   └── Contact.css
├── App.js
├── App.css
└── index.js
```

---

# 🎨 Props (속성) 전달

## Props의 개념

**Props**는 부모 컴포넌트에서 자식 컴포넌트로 데이터를 전달하는 방법입니다.

### **기본 Props 사용**
```jsx
// Button 컴포넌트 정의
function Button(props) {
    return (
        <button className={props.className} onClick={props.onClick}>
            {props.text}
        </button>
    );
}

// 사용 방법
function App() {
    const handleClick = () => {
        alert('버튼 클릭됨!');
    };

    return (
        <div>
            <Button 
                text="클릭하세요" 
                className="primary-btn" 
                onClick={handleClick} 
            />
            <Button 
                text="취소" 
                className="secondary-btn" 
                onClick={() => console.log('취소')} 
            />
        </div>
    );
}
```

### **구조 분해 할당으로 Props 받기**
```jsx
// 더 깔끔한 방식
function Button({ text, className, onClick }) {
    return (
        <button className={className} onClick={onClick}>
            {text}
        </button>
    );
}

// 기본값 설정
function Button({ text = "버튼", className = "btn", onClick }) {
    return (
        <button className={className} onClick={onClick}>
            {text}
        </button>
    );
}
```

## 실전 예제: 프로젝트 카드

### **ProjectCard 컴포넌트**
```jsx
function ProjectCard({ title, description, image, technologies, liveUrl, githubUrl }) {
    return (
        <div className="project-card">
            <img src={image} alt={title} className="project-image" />
            <div className="project-content">
                <h3 className="project-title">{title}</h3>
                <p className="project-description">{description}</p>
                
                <div className="project-tech">
                    {technologies.map((tech, index) => (
                        <span key={index} className="tech-tag">{tech}</span>
                    ))}
                </div>
                
                <div className="project-links">
                    {liveUrl && (
                        <a href={liveUrl} target="_blank" rel="noopener noreferrer">
                            Live Demo
                        </a>
                    )}
                    {githubUrl && (
                        <a href={githubUrl} target="_blank" rel="noopener noreferrer">
                            GitHub
                        </a>
                    )}
                </div>
            </div>
        </div>
    );
}
```

### **Projects 컴포넌트에서 사용**
```jsx
function Projects() {
    const projects = [
        {
            id: 1,
            title: "포트폴리오 웹사이트",
            description: "HTML, CSS, JavaScript로 만든 반응형 포트폴리오",
            image: "/images/portfolio.png",
            technologies: ["HTML", "CSS", "JavaScript"],
            liveUrl: "https://myname.github.io/portfolio",
            githubUrl: "https://github.com/myname/portfolio"
        },
        {
            id: 2,
            title: "할 일 관리 앱",
            description: "React로 만든 인터랙티브한 할 일 관리 애플리케이션",
            image: "/images/todo-app.png",
            technologies: ["React", "CSS", "Local Storage"],
            liveUrl: "https://myname.github.io/todo-app",
            githubUrl: "https://github.com/myname/todo-app"
        }
    ];

    return (
        <section className="projects">
            <h2>My Projects</h2>
            <div className="projects-grid">
                {projects.map(project => (
                    <ProjectCard 
                        key={project.id}
                        title={project.title}
                        description={project.description}
                        image={project.image}
                        technologies={project.technologies}
                        liveUrl={project.liveUrl}
                        githubUrl={project.githubUrl}
                    />
                ))}
            </div>
        </section>
    );
}
```

---

# 💻 첫 번째 React 컴포넌트 만들기

## 실습: Header 컴포넌트

### **1. 컴포넌트 파일 생성**
```bash
# src/components 폴더 생성
mkdir src/components

# Header 컴포넌트 파일 생성
touch src/components/Header.js
touch src/components/Header.css
```

### **2. Header.js 작성**
```jsx
import './Header.css';

function Header() {
    return (
        <header className="header">
            <div className="container">
                <div className="logo">
                    <h1>조성호</h1>
                    <span>Frontend Developer</span>
                </div>
                
                <nav className="nav">
                    <a href="#about" className="nav-link">About</a>
                    <a href="#skills" className="nav-link">Skills</a>
                    <a href="#projects" className="nav-link">Projects</a>
                    <a href="#contact" className="nav-link">Contact</a>
                </nav>
                
                <button className="theme-toggle">🌙</button>
            </div>
        </header>
    );
}

export default Header;
```

### **3. Header.css 작성**
```css
.header {
    background: #fff;
    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
    position: fixed;
    top: 0;
    left: 0;
    right: 0;
    z-index: 1000;
}

.header .container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 1rem 2rem;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.logo h1 {
    margin: 0;
    font-size: 1.5rem;
    color: #333;
}

.logo span {
    font-size: 0.9rem;
    color: #666;
    margin-left: 0.5rem;
}

.nav {
    display: flex;
    gap: 2rem;
}

.nav-link {
    text-decoration: none;
    color: #333;
    font-weight: 500;
    transition: color 0.3s ease;
}

.nav-link:hover {
    color: #007bff;
}

.theme-toggle {
    background: none;
    border: none;
    font-size: 1.2rem;
    cursor: pointer;
    padding: 0.5rem;
    border-radius: 50%;
    transition: background-color 0.3s ease;
}

.theme-toggle:hover {
    background-color: #f0f0f0;
}

@media (max-width: 768px) {
    .nav {
        display: none;
    }
    
    .header .container {
        padding: 1rem;
    }
}
```

---

## App.js 수정

### **Header 컴포넌트 적용**
```jsx
import './App.css';
import Header from './components/Header';

function App() {
    return (
        <div className="App">
            <Header />
            
            <main style={{ marginTop: '80px' }}>
                <section style={{ padding: '4rem 2rem', textAlign: 'center' }}>
                    <h1>Welcome to My React Portfolio</h1>
                    <p>React로 만든 포트폴리오 웹사이트입니다.</p>
                </section>
            </main>
        </div>
    );
}

export default App;
```

### **확인 사항**
1. **개발 서버 실행**: `npm start`
2. **브라우저 접속**: http://localhost:3000
3. **Header 컴포넌트 렌더링** 확인
4. **반응형 동작** 확인 (모바일 화면에서 네비게이션 숨김)

---

# 🎊 6-1교시 마무리

## 오늘 배운 내용 정리

- **React 필요성** 이해 및 장점 파악
- **개발 환경 설정** 완료 (Node.js, Create React App)
- **JSX 문법** 기초 마스터
- **컴포넌트** 개념 이해 및 첫 컴포넌트 생성
- **Props** 전달 방법 학습

## 다음 시간 (6-2교시) 예고

- **State와 useState Hook** 마스터
- **이벤트 처리** 및 상호작용 구현
- **조건부 렌더링** 고급 기법
- **리스트 렌더링** 및 key 속성
- **실전 프로젝트**: 인터랙티브 포트폴리오 완성

![bg right:45% w:450](https://images.unsplash.com/photo-1633356122544-f134324a6cee?w=450&h=300&fit=crop)

---

# 📚 복습 과제

## 스스로 해보기

### **과제 1: About 컴포넌트 만들기**
```jsx
// 요구사항:
// 1. src/components/About.js 파일 생성
// 2. 자기소개 섹션 구현
// 3. Props로 개인 정보 전달받기
// 4. CSS로 스타일링

function About({ name, title, description, skills }) {
    // 여기에 구현
}
```

### **과제 2: Skill 컴포넌트 만들기**
```jsx
// 요구사항:
// 1. 개별 스킬을 보여주는 컴포넌트
// 2. 스킬명, 레벨(%), 아이콘 표시
// 3. 프로그레스 바 구현

function Skill({ name, level, icon }) {
    // 여기에 구현
}
```

### **과제 3: 컴포넌트 조합하기**
```jsx
// App.js에서 모든 컴포넌트 조합
// Header + About + Skills 섹션 완성
```

## 추가 학습 자료

- **React 공식 문서**: https://react.dev
- **Create React App**: https://create-react-app.dev
- **JSX 심화**: https://react.dev/learn/writing-markup-with-jsx
- **Component와 Props**: https://react.dev/learn/passing-props-to-a-component

![bg right:40% w:400](https://images.unsplash.com/photo-1517077304055-6e89abbf09b0?w=400&h=300&fit=crop)
