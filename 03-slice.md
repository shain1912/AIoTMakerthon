# 🛠️ Cura 슬라이서 완전 가이드

Cura는 3D 프린팅에서 가장 널리 사용되는 무료 오픈소스 슬라이서 소프트웨어입니다. 3D 모델을 프린터가 이해할 수 있는 G-code로 변환하는 핵심 도구입니다.

![Cura 메인 인터페이스](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2020/01/05104544/cura-slicer-cura-3d-context.jpg)
_▲ Cura의 직관적인 사용자 인터페이스_

---

## 🎯 Cura가 인기 있는 이유

### 1. 균형 잡힌 사용성

- **초보자용 Recommended Mode**: 미리 설정된 프로파일로 쉽게 시작
- **고급자용 Custom Mode**: 500개 이상의 세밀한 설정 옵션

### 2. 무료 & 오픈소스

- 완전 무료 사용
- 지속적인 커뮤니티 기여
- 정기적인 업데이트 (2개월마다)

![Cura 로딩 화면](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2020/01/05115754/cura-3d-splash.jpg)
_▲ Cura 시작 화면_

### 3. 강력한 확장성

- **플러그인 마켓플레이스**: 다양한 확장 기능 지원
- **여러 파일 포맷 지원**: STL, 3MF, OBJ, X3D 등
- **CAD 소프트웨어 연동**: 직접 가져오기 기능

![Cura 마켓플레이스](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2020/01/05104544/cura-slicer-cura-3d-context.jpg)
_▲ 다양한 플러그인을 제공하는 Ultimaker 마켓플레이스_

---

## 📋 3D 프린팅 워크플로우

### 1단계: 3D 모델 준비

- **다운로드**: [무료 STL 파일 사이트](https://www.yeggi.com/)에서 모델 찾기
- **설계**: Tinkercad, Fusion 360 등으로 직접 제작

![Yeggi STL 파일 사이트](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2020/01/05121751/cura-slicer-interface-cura-3d.jpg)
_▲ Yeggi.com에서 다양한 STL 파일을 찾을 수 있습니다_

### 2단계: 슬라이싱 설정

- **파일 형식**: STL, 3MF 등으로 내보내기
- **Cura 가져오기**: 모델을 Cura로 불러오기
- **설정 조정**: 품질, 속도, 서포트 등 설정

### 3단계: G-code 생성

- **슬라이싱 실행**: 모델을 레이어별로 분할
- **G-code 출력**: 프린터가 이해할 수 있는 명령어 생성

---

## ⚙️ Cura 다운로드 & 설치

### Windows 설치

1. [Ultimaker 공식 사이트](https://ultimaker.com/software/ultimaker-cura)에서 다운로드
2. Windows 64bit 버전 설치 프로그램 실행
3. 파일 연결 설정 (3MF, OBJ, X3D 등)

### macOS 설치

1. macOS 설치 프로그램 다운로드
2. 설치 마법사 실행
3. 프로그램 폴더에서 Cura 실행

### Ubuntu Linux 설치

```bash
# AppImage 다운로드 후
chmod +x Cura-x.x.x.AppImage
./Cura-x.x.x.AppImage
```

---

## 🎮 Cura 빠른 시작 가이드

### 1. 머신 프로파일 설정

![Cura 머신 프로파일](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2019/02/17141842/Capture3.jpg)
_▲ 다양한 3D 프린터를 위한 미리 설정된 머신 프로파일_

**사전 설정된 프로파일**

- Ultimaker 프린터: 공식 테스트 및 유지보수
- 서드파티 프린터: 커뮤니티 기여 프로파일
- Custom FFF Printer: 수동 설정 옵션

### 2. 모델 가져오기

- **파일 → 열기** 또는 드래그 앤 드롭
- 지원 형식: STL, OBJ, X3D, 3MF
- 자동 플랫폼 배치

### 3. 인터페이스 사용법

**Scene 뷰**

- **Layer View**: 기본 슬라이싱 뷰
- **X-Ray View**: 내부 구조 확인
- 레이어별 미리보기 슬라이더

![Cura X-Ray 뷰](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2020/01/05100016/xray-view-cura-3d.jpg)
_▲ X-Ray 뷰로 모델 내부 구조 확인_

**모델 조작**

- **이동**: 모델 위치 조정
- **회전**: 90도 단위 또는 자유 회전
- **크기 조정**: 프린트 크기에 맞게 스케일링
- **복제**: 동일 모델 여러 개 배치

---

## 🔧 Recommended Mode 사용법

### 레이어 높이 설정

- **0.4mm 노즐 기준**: 0.2mm 레이어 높이 권장
- **고품질**: 0.15mm (더 세밀하지만 느림)
- **고속 출력**: 0.3mm (빠르지만 거친 표면)

![레이어 높이 효과](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165535/layer_height_quality_zoomed.jpg)
_▲ 레이어 높이에 따른 표면 품질 차이_

### 인필 밀도 설정

- **0%**: 완전 중공
- **10-40%**: 가벼운 인필 (일반적)
- **50-90%**: 중간 강도
- **100%**: 완전 솔리드

![인필 프린팅](https://i.all3dp.com/wp-content/uploads/2020/12/14182452/infill-is-an-influential-element-of-3d-prints-kronr-via-pinshape-201117.jpg)
_▲ 인필 라인이 프린팅되는 모습_

### 서포트 및 접착 설정

- **서포트 생성**: 오버행 부분 지지
- **빌드 플레이트 접착**: 첫 레이어 접착력 향상
  - **Skirt**: 기본 설정 (둘레 라인)
  - **Brim**: 넓은 테두리로 접착력 강화
  - **Raft**: 두꺼운 격자 베이스

---

## 🛠️ Custom Mode 고급 설정

### 품질 제어

**정밀한 레이어 높이**

- 0.06mm: 최고 품질 (24시간+ 소요 가능)
- 용도에 따른 선택: 기능성 vs 미관

### 벽 두께 및 갭 채우기

**벽 두께 계산**

- 노즐 직경의 배수로 설정
- 예: 0.4mm 노즐 → 1.2mm 벽 두께 (3개 벽)

**Z-Seam 정렬**

- **Shortest**: 기본 설정
- **Sharpest Corner**: 모서리에 숨김
- **Random**: 완전 무작위 (시간 소요)

### 다양한 인필 패턴

![Cura 인필 패턴](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2020/01/04152244/cura-slicer-infill-patterns.jpg)
_▲ Cura의 다양한 인필 패턴들_

**2D 패턴** (빠르고 가벼움)

- **Line**: 최소 강도, 최고 속도
- **Grid**: 우수한 강도/무게 비율
- **Triangle**: 측면 하중에 강함

**3D 패턴** (기계적 용도)

- **Cubic**: 등방성 기계적 특성
- **Gyroid**: 에폭시 주입에 적합
- **Lightning**: 천장 지지 최소화

### 속도 및 온도 제어

**프린트 속도 최적화**

- 기본값: 60mm/s
- 단계적 증가: 5mm/s씩 테스트
- 인필 속도 별도 설정 가능

![프린트 속도 효과](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165525/speed_quality.png)
_▲ 프린트 속도가 품질에 미치는 영향_

**쿨링 설정**

- 팬 속도: 80% 권장 (과도한 쿨링 방지)
- 최소 레이어 시간: 5초 (작은 레이어 보호)
- 소재별 쿨링 비활성화 (나일론, PC 등)

---

## 🔧 문제 해결 가이드

### 워핑 방지

![워핑 문제](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165520/warping.jpg)
_▲ 워핑으로 인한 베이스 레이어 들뜸_

**접착 향상 방법**

- **Brim 사용**: 단일 레이어 테두리
- **Raft 사용**: 두꺼운 격자 베이스
- **첫 레이어 높이 증가**
- **첫 레이어 속도 감소**
  ![skirt](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165518/skirt.png)
  ![brim](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165515/brim.png)
  ![raft](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165513/raft.png)

### 필로윙 해결

![필로윙 효과](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165511/pillowing.jpg)
_▲ 상단 표면의 필로윙 현상_

**해결 방법**

- 상단 두께 증가: 레이어 높이 × 6
- 팬 속도 증가
- 인필 밀도 조정

### 스트링 현상 제거

![스트링 문제](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165508/stringing.jpg)
_▲ 심각한 스트링 현상이 발생한 프린트_

**개선 방법**

- **리트랙션 활성화**
- **리트랙션 거리 증가**
- **온도 10도씩 감소 테스트**

---

## 🏗️ 서포트 구조 최적화

![서포트 구조](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2020/01/04155203/cura-3d-overhangs.jpg)
_▲ 오버행 부분을 지지하는 서포트 구조_

### 서포트 배치 제어

- **Everywhere**: 모든 필요한 곳에 생성
- **Touching Buildplate**: 플레이트와 연결된 부분만
  ![where](https://i.all3dp.com/workers/images/fit=scale-down,w=1200,gravity=0.5x0.5,format=auto/wp-content/uploads/2018/02/26165507/support_placement.png)

### 서포트 품질 향상

- **Support Roof**: 표면 마감 개선
- **X/Y Distance**: 벽면 손상 방지
- **Z Distance**: 제거 용이성 조절

---

## 🎛️ 특수 모드들

### Vase Mode (나선 모드)

- 외벽만 연속 프린팅
- 빠른 화분, 용기 제작

### Tree Support

- 나무 가지 형태의 서포트
- 재료 절약 및 제거 용이

### Ironing (다림질)

- 상단 표면 매끄럽게 처리
- 미관 중요한 프린트에 사용

---

## 📤 출력 및 G-code 관리

### 다양한 출력 방법

- **디스크 저장**: 로컬 파일로 저장
- **이동식 드라이브**: SD카드/USB 스틱
- **네트워크 전송**: 네트워크 연결 프린터
- **클라우드 프린팅**: Ultimaker 프린터 전용
- **OctoPrint 연동**: 플러그인을 통한 직접 전송

### G-code 이해하기

```gcode
G0 F7200 X19.698 Y28.262 Z0.36    ; 빠른 이동
G1 F1500 E0                       ; 압출기 리셋
G1 F1350 X22.467 Y26.175 E0.15654 ; 압출하며 이동
```

---

## 🎓 학습 리소스

### 공식 문서

- [Ultimaker Cura 공식 사이트](https://ultimaker.com/software/ultimaker-cura)
- [GitHub 저장소](https://github.com/Ultimaker/Cura/releases)

### 커뮤니티

- Cura 사용자 포럼
- Reddit r/3Dprinting
- YouTube 튜토리얼 채널

### 추천 설정

- **초보자**: Recommended Mode + 기본 설정
- **중급자**: Custom Mode + 필요한 설정만 조정
- **고급자**: 모든 설정 직접 튜닝

---

## 💡 팁 & 요약

### 핵심 포인트

1. **시작은 간단하게**: Recommended Mode로 시작
2. **단계적 발전**: 필요에 따라 Custom 설정 추가
3. **테스트가 중요**: 새 설정은 작은 모델로 먼저 테스트
4. **재료별 프로파일**: 각 필라멘트에 맞는 설정 저장

### 자주 사용하는 설정

- **레이어 높이**: 0.2mm (품질/속도 균형)
- **인필**: 20% (일반적인 강도)
- **벽 두께**: 1.2mm (3개 벽)
- **서포트**: 45도 이상 오버행에만

Cura는 강력하면서도 접근하기 쉬운 슬라이서입니다. 기본 설정으로 시작해서 점진적으로 고급 기능들을 익혀가세요! 🚀
