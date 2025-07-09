---
marp: true
theme: default
paginate: true
header: "Vibe Coding 10-1강 - 정적 페이지 미니 프로젝트"
footer: "조성호 | 바이브코딩 시리즈"
---

# 🎯 정적 페이지 미니 프로젝트 (1부)

## 모든 기술을 통합한 개인 웹사이트 제작

**강사명**: 조성호  
**소요시간**: 30분

![bg right:40% w:400](https://images.unsplash.com/photo-1607746882042-944635dfe10e?w=400&h=300&fit=crop)

---

## 📋 10-1교시 학습 목표

- 프로젝트 기획 및 디자인 시스템 적용
- Vite 기반 정적 사이트 개발 실습
- Figma 디자인을 코드로 변환하는 MCP 활용
- 반응형 레이아웃 및 퍼포먼스 최적화 기본 이해

---

## 🔗 필요한 준비물

- [ ] Figma 계정 및 프로젝트 준비
- [ ] MCP 연동 플러그인 설치
- [ ] VSCode + Live Server + Vite 환경
- [ ] GitHub 프로젝트 저장소 생성

![bg right:35% w:350](https://images.unsplash.com/photo-1557804506-669a67965ba0?w=350&h=250&fit=crop)

---

# 📖 프로젝트 개요

## 정적 사이트란?

> 서버 사이드 로직 없이 HTML, CSS, JS로 완성하는 고성능 웹사이트  
> Jamstack 아키텍처 기반  
> 빠른 로딩, 높은 보안, 글로벌 배포 최적화

### **개발 스택**

- **Design**: Figma + MCP
- **Build**: Vite
- **Language**: HTML, CSS, ES6+
- **Deploy**: GitHub Pages 또는 Netlify

---

## ✨ 오늘 목표 결과물

- Figma 디자인을 코드로 변환
- Vite 프로젝트 구조 완성
- 반응형 헤더 및 히어로 섹션 제작
- 개인 브랜드 포트폴리오 기본 뼈대 구축

---

## 🚀 프로젝트 옵션

1. **개인 포트폴리오 사이트**
2. **서비스/제품 랜딩 페이지**
3. **기술 문서/가이드 사이트**

> _모두 Figma MCP 연동 필수_

---

# ⚙️ Figma MCP 설정 방법

## 플러그인 설치

- Figma → Plugins → "MCP Context Exporter" 검색
- 설치 후 프로젝트 열기
- [ ] 디자인 토큰 추출 준비

---

## MCP 연동 및 코드 변환

### 디자인 토큰 자동화

```bash
npm install @mcp/design-tokens
npm run design:sync
```

**추출 항목**

- 색상 시스템 → CSS Custom Properties
- 타이포그래피 → 폰트 및 계층 시스템
- 스페이싱 → 여백 클래스 자동 생성
- 아이콘 → SVG 최적화
