# Supabase 연동

## 개요

오픈소스 Firebase 대안인 Supabase를 이용한 IoT 데이터 저장 및 관리

## 주요 특징

- PostgreSQL 기반 데이터베이스
- 실시간 구독 기능
- REST API 제공
- 오픈소스 및 셀프호스팅 가능

## 파일 구조

- `supabase_insert.ino` - Supabase에 데이터 삽입하는 예제
- `supabase_select.ino` - Supabase에서 데이터 조회하는 예제
- `supabase_realtime.ino` - 실시간 데이터 구독 예제
- `config.h` - Supabase 설정 파일
- `README.md` - 튜토리얼 및 설명

## 튜토리얼

# ESP32에서 Supabase로 데이터 전송 강의

## 개요

이 강의에서는 Arduino Stuff를 배우고 있는 과정에서 1학년 컴퓨팅 기초 모듈의 그룹 프로젝트를 위해 하드웨어 제품을 구축하는 방법을 다룹니다.

**작성자**: Chamal Senarathna  
**게시일**: 2024년 11월 21일  
**읽기 시간**: 4분

## 프로젝트 배경

최근 Arduino 관련 학습을 하고 있는데, 1학년 컴퓨팅 기초 모듈의 그룹 프로젝트에서 하드웨어 제품을 구축해야 합니다.

우리 팀은 이 프로젝트를 위해 헬스케어 카테고리를 선택했습니다. 다음과 같은 기능을 구현할 예정입니다:

- 사용자로부터 체온, 심박수 같은 건강 지표 수집
- ESP32로 데이터 전송
- 16x2 LCD에 데이터 표시

하지만 소프트웨어 개발자로서, 이 프로젝트에 소프트웨어 구성 요소를 추가하고 싶었습니다. 따라서 팀에게 다음을 제안했습니다:

- 이 데이터를 클라우드 데이터베이스로 전송
- 웹 애플리케이션에서 데이터 시각화

## 데이터베이스 플랫폼 선택

이제 본격적인 주제로 들어가서, 이러한 데이터를 저장할 플랫폼/데이터베이스가 필요합니다. 일반적으로 대부분의 프로젝트에서 Supabase를 데이터베이스로 사용하고 있으며, 이 프로젝트에서도 Supabase를 사용하기로 결정했습니다.

하지만 ESP32에서 DB로 데이터를 삽입하는 것은 조금 도전적입니다. Supabase에서 공식적으로 제공하는 라이브러리가 없기 때문입니다.

인터넷에서 검색한 결과, **ESPSupabase**라는 멋진 라이브러리를 발견했습니다. 이 라이브러리는 **REST API**와 **WebSockets**을 통해 ESP32/8266을 Supabase에 연결해줍니다.

## 시작하기 전 준비사항

시작하기 전에 다음 사항들이 준비되어 있는지 확인하세요:

- ESP32 마이크로컨트롤러
- Arduino IDE
- Supabase 계정

## 단계별 구현 과정

### 1. Supabase 설정

먼저 Supabase 대시보드로 이동하여 새 프로젝트를 생성합니다. 이 데모에서는 모의 심박수와 체온 데이터를 데이터베이스로 전송할 예정입니다.

프로젝트에서 테이블 섹션으로 이동하여 `health_data`라는 새 테이블을 생성하고, 심박수와 체온을 저장할 두 개의 컬럼을 추가합니다.

![Supabase 테이블 생성](https://miro.medium.com/v2/resize:fit:1100/format:webp/1*f6UpxfG_upo-qp1_4B6iEQ.png)
_Supabase에서 health_data 테이블 생성 화면_

**중요**: 이 예제에서는 자세히 다루지 않을 것이므로, 상단의 체크박스를 클릭하여 RLS(Row Level Security)를 비활성화해야 합니다.

### 2. Arduino IDE 설정

ESP32를 Arduino IDE와 함께 사용해본 경험이 있기를 바랍니다. 만약 그렇지 않다면, ESP32를 Arduino IDE와 설정하는 방법에 대한 다음 비디오를 참고하세요: https://youtu.be/CD8VJl27n94?si=kWZK5QMFF67o9KZH

ESP32를 Arduino IDE와 설정한 후, 라이브러리 관리자 섹션으로 이동하여 ESPSupabase를 검색하고 Install을 클릭합니다.

![Arduino IDE ESPSupabase 설치](https://miro.medium.com/v2/resize:fit:1100/format:webp/1*GtmaYtHX1QAm0YX5bliAsA.png)
_Arduino IDE 라이브러리 매니저에서 ESPSupabase 검색 및 설치_

### 3. 프로그램 구현

이제 프로그램으로 넘어가겠습니다. 아래에 전체 코드를 추가하고 주석으로 코드를 설명했습니다.

**중요 사항**: 이 코드에서 `supabase_url`, `anon_key`를 본인의 자격 증명으로 변경해야 합니다. 또한 테이블 정의 부분에서, 본인의 `테이블`과 `컬럼`에 사용한 정확한 이름을 추가해야 합니다.

ESP32에 코드를 업로드하기 전에 **Wi-Fi 자격 증명**도 추가해야 합니다.

```cpp
// Import WiFi and ESPSupabase Library
#include <WiFi.h>
#include <ESPSupabase.h>

// Add you Wi-Fi credentials
const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

// Supabase credentials
const char* supabaseUrl = "YOUR SUPABASE URL";
const char* supabaseKey = "SUPABASE ANON KEY";

Supabase supabase;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Wi-Fi connected!");

  // Init Supabase
  supabase.begin(supabaseUrl, supabaseKey);

  // Add the table name here
  String tableName = "healthdata";

  // change the correct columns names you create in your table
  String jsonData = "{\"heartrate\": \"70\", \"bodytemp\": \"37\"}";

  // sending data to supabase
  int response = supabase.insert(tableName, jsonData, false);

  if (response == 200) {
    Serial.println("Data inserted successfully!");
  } else {
    Serial.print("Failed to insert data. HTTP response: ");
    Serial.println(response);
  }
}

void loop() {
}
```

### 4. 프로그램 검증 및 업로드

다음으로, 첫 번째 파란색 아이콘을 눌러 프로그램을 검증합니다. 프로그램이 성공적으로 컴파일될 것입니다.

![Arduino IDE 컴파일 성공](https://miro.medium.com/v2/resize:fit:1100/format:webp/1*5SqqlQKOI-pWctthmS08vQ.png)
_Arduino IDE에서 코드 컴파일 성공 화면_

마지막으로, ESP32를 노트북/PC에 연결한 다음 tools > PORT 섹션에서 올바른 포트를 선택하고 두 번째 파란색 아이콘을 사용하여 보드에 프로그램을 업로드합니다.

### 5. 결과 확인

완료되었습니다! 이제 Supabase 데이터베이스 테이블로 이동하면, 이 프로그램에서 추가한 모의 데이터가 컬럼에 표시되는 것을 볼 수 있습니다.

![Supabase 데이터 확인](https://miro.medium.com/v2/resize:fit:1100/format:webp/1*FIB7NUMoha27ygYdU2bPng.png)
_Supabase 테이블에 성공적으로 삽입된 ESP32 센서 데이터_

## 마무리

이제 ESP32에서 Supabase 데이터베이스로 데이터를 쉽게 전송하는 방법을 이해했을 것입니다.

한번 시도해보시고, Row Level Security와 같은 추가 기능으로 확장해보세요.

이에 대해 더 자세히 알고 싶다면 다음 문서들을 참고하세요.

## 참고 자료

- [GitHub - jhagas/ESPSupabase: Connect ESP32/8266 with Supabase](https://github.com/jhagas/ESPSupabase)
- [Supabase Documentation](https://supabase.com/docs)

---

# 프로젝트 파일들

## config.h - 설정 파일

**파일 위치**: `config.h`  
**용도**: WiFi 및 Supabase 연결 정보 설정

```cpp
// 여기에 config.h 내용을 넣어주세요
```

---

## supabase_insert.ino - 기본 데이터 삽입

**파일 위치**: `supabase_insert.ino`  
**용도**: ESP32에서 Supabase로 센서 데이터 삽입

```cpp
// 여기에 supabase_insert.ino 내용을 넣어주세요
```

---

## supabase_select.ino - 데이터 조회

**파일 위치**: `supabase_select.ino`  
**용도**: Supabase에서 저장된 데이터 조회 및 출력

```cpp
// 여기에 supabase_select.ino 내용을 넣어주세요
```

---

## supabase_realtime.ino - 실시간 데이터 구독

**파일 위치**: `supabase_realtime.ino`  
**용도**: Supabase 실시간 구독 기능을 이용한 데이터 모니터링

```cpp
// 여기에 supabase_realtime.ino 내용을 넣어주세요
```

---

## 태그

- Supabase
- ESP32
- Arduino

---
