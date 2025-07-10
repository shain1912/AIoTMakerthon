/****************************************************************
 * ESP32 Firebase 실시간 데이터베이스 - 데이터 저장 예제
 * 
 * 작성자: IoT Makerthon 강의자료
 * 기반: Random Nerd Tutorials (https://randomnerdtutorials.com)
 * 
 * 이 예제는 ESP32에서 Firebase 실시간 데이터베이스로 
 * 다양한 데이터 타입(int, float, string)을 전송하는 방법을 보여줍니다.
 ****************************************************************/

#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

// 네트워크 및 Firebase 인증 정보
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define Web_API_KEY "YOUR_FIREBASE_PROJECT_API_KEY"
#define DATABASE_URL "YOUR_FIREBASE_DATABASE_URL"
#define USER_EMAIL "YOUR_FIREBASE_PROJECT_EMAIL_USER"
#define USER_PASS "YOUR_FIREBASE_PROJECT_USER_PASS"

// 사용자 정의 함수 선언
void processData(AsyncResult &aResult);

// Firebase 인증 설정
UserAuth user_auth(Web_API_KEY, USER_EMAIL, USER_PASS);

// Firebase 구성 요소들
FirebaseApp app;
WiFiClientSecure ssl_client;
using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);
RealtimeDatabase Database;

// 10초마다 데이터 전송을 위한 타이머 변수들
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 10000; // 10초 (밀리초 단위)

// 데이터베이스로 전송할 변수들
int intValue = 0;
float floatValue = 0.01;
String stringValue = "";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== ESP32 Firebase 데이터 저장 예제 ===");
  
  // Wi-Fi 연결
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Wi-Fi에 연결 중");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Wi-Fi 연결 완료! IP 주소: ");
  Serial.println(WiFi.localIP());
  
  // SSL 클라이언트 설정
  ssl_client.setInsecure();
  ssl_client.setConnectionTimeout(1000);
  ssl_client.setHandshakeTimeout(5);
  
  // Firebase 초기화
  Serial.println("Firebase 초기화 중...");
  initializeApp(aClient, app, getAuth(user_auth), processData, "🔐 authTask");
  
  // Firebase 앱에 데이터베이스 연결
  app.getApp<RealtimeDatabase>(Database);
  Database.url(DATABASE_URL);
  
  Serial.println("설정 완료!");
}

void loop() {
  // 인증 및 비동기 작업 유지
  app.loop();
  
  // 인증이 준비되었는지 확인
  if (app.ready()) {
    // 10초마다 주기적으로 데이터 전송
    unsigned long currentTime = millis();
    
    if (currentTime - lastSendTime >= sendInterval) {
      // 마지막 전송 시간 업데이트
      lastSendTime = currentTime;
      
      Serial.println("\n--- 데이터베이스에 데이터 전송 중 ---");
      
      // 문자열 전송
      stringValue = "value_" + String(currentTime);
      Serial.print("문자열 전송: ");
      Serial.println(stringValue);
      Database.set<String>(aClient, "/test/string", stringValue, processData, "RTDB_Send_String");
      
      // 정수 전송
      Serial.print("정수 전송: ");
      Serial.println(intValue);
      Database.set<int>(aClient, "/test/int", intValue, processData, "RTDB_Send_Int");
      intValue++; // 매 루프마다 intValue 증가
      
      // 부동소수점 전송
      floatValue = 0.01 + random(0, 100);
      Serial.print("실수 전송: ");
      Serial.println(floatValue);
      Database.set<float>(aClient, "/test/float", floatValue, processData, "RTDB_Send_Float");
      
      Serial.println("데이터 전송 완료!");
    }
  }
}

/**
 * Firebase 비동기 결과 처리 함수
 * 모든 Firebase 작업의 결과를 처리합니다.
 */
void processData(AsyncResult &aResult) {
  if (!aResult.isResult()) return;
  
  // 이벤트 로그 처리
  if (aResult.isEvent()) {
    Firebase.printf("이벤트 작업: %s, 메시지: %s, 코드: %d\n", 
                   aResult.uid().c_str(), 
                   aResult.eventLog().message().c_str(), 
                   aResult.eventLog().code());
  }
  
  // 디버그 로그 처리
  if (aResult.isDebug()) {
    Firebase.printf("디버그 작업: %s, 메시지: %s\n", 
                   aResult.uid().c_str(), 
                   aResult.debug().c_str());
  }
  
  // 에러 로그 처리
  if (aResult.isError()) {
    Firebase.printf("에러 작업: %s, 메시지: %s, 코드: %d\n", 
                   aResult.uid().c_str(), 
                   aResult.error().message().c_str(), 
                   aResult.error().code());
  }
  
  // 성공적인 응답 처리
  if (aResult.available()) {
    Firebase.printf("작업: %s, 응답: %s\n", 
                   aResult.uid().c_str(), 
                   aResult.c_str());
  }
}

/*
 * 사용 방법:
 * 1. 위의 설정 값들을 자신의 Firebase 프로젝트 정보로 변경
 * 2. 코드를 ESP32에 업로드
 * 3. 시리얼 모니터를 열어서 상태 확인 (115200 baud)
 * 4. Firebase 콘솔에서 실시간으로 데이터가 저장되는 것을 확인
 * 
 * 데이터베이스 구조:
 * /test/
 *   ├── string: "value_현재시간"
 *   ├── int: 0, 1, 2, 3... (증가하는 정수)
 *   └── float: 0.01 + 랜덤값 (0-100 사이)
 * 
 * 주의사항:
 * - Firebase 프로젝트가 미리 설정되어 있어야 함
 * - 실시간 데이터베이스가 생성되어 있어야 함
 * - 인증 방법이 이메일/패스워드로 설정되어 있어야 함
 * - 테스트 모드 또는 적절한 보안 규칙 설정 필요
 */
