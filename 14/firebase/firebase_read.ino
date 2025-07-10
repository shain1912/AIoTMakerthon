/****************************************************************
 * ESP32 Firebase 실시간 데이터베이스 - 데이터 읽기 예제
 * 
 * 작성자: IoT Makerthon 강의자료
 * 기반: Random Nerd Tutorials (https://randomnerdtutorials.com)
 * 
 * 이 예제는 ESP32에서 Firebase 실시간 데이터베이스로부터
 * 다양한 데이터 타입(int, float, string)을 읽어오는 방법을 보여줍니다.
 ****************************************************************/

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

// 10초마다 데이터 읽기를 위한 타이머 변수들
unsigned long lastReadTime = 0;
const unsigned long readInterval = 10000; // 10초 (밀리초 단위)

// 데이터베이스에서 읽어온 값을 저장할 변수들
int intValue = 0;
float floatValue = 0.0;
String stringValue = "";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== ESP32 Firebase 데이터 읽기 예제 ===");
  
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
  Serial.println();
  
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
  Serial.println("10초마다 데이터베이스에서 데이터를 읽어옵니다...");
}

void loop() {
  // 인증 및 비동기 작업 유지
  app.loop();
  
  // 인증이 준비되었는지 확인
  if (app.ready()) {
    // 10초마다 주기적으로 데이터 읽기
    unsigned long currentTime = millis();
    
    if (currentTime - lastReadTime >= readInterval) {
      // 마지막 읽기 시간 업데이트
      lastReadTime = currentTime;
      
      Serial.println("\n--- 데이터베이스에서 데이터 읽기 중 ---");
      
      // 문자열 읽기
      Serial.println("문자열 데이터 요청 중...");
      Database.get(aClient, "/test/string", processData, false, "RTDB_Get_String");
      
      // 정수 읽기
      Serial.println("정수 데이터 요청 중...");
      Database.get(aClient, "/test/int", processData, false, "RTDB_Get_Int");
      
      // 부동소수점 읽기
      Serial.println("실수 데이터 요청 중...");
      Database.get(aClient, "/test/float", processData, false, "RTDB_Get_Float");
      
      Serial.println("데이터 읽기 요청 완료!");
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
    String uid = aResult.uid().c_str();
    String data = aResult.c_str();
    
    Serial.println("--- 데이터 수신 완료 ---");
    Serial.printf("작업 ID: %s\n", uid.c_str());
    
    // 작업 유형에 따라 데이터 파싱
    if (uid == "RTDB_Get_String") {
      stringValue = data;
      // JSON 형태에서 실제 문자열 값 추출
      if (stringValue.startsWith("\"") && stringValue.endsWith("\"")) {
        stringValue = stringValue.substring(1, stringValue.length() - 1);
      }
      Serial.printf("📝 문자열 값: %s\n", stringValue.c_str());
      
    } else if (uid == "RTDB_Get_Int") {
      intValue = data.toInt();
      Serial.printf("🔢 정수 값: %d\n", intValue);
      
    } else if (uid == "RTDB_Get_Float") {
      floatValue = data.toFloat();
      Serial.printf("📊 실수 값: %.2f\n", floatValue);
    }
    
    Serial.println("------------------------");
  }
}

/*
 * 사용 방법:
 * 1. 위의 설정 값들을 자신의 Firebase 프로젝트 정보로 변경
 * 2. firebase_write.ino를 먼저 실행하여 데이터를 저장
 * 3. 이 코드를 ESP32에 업로드
 * 4. 시리얼 모니터를 열어서 상태 확인 (115200 baud)
 * 5. 10초마다 데이터베이스에서 값을 읽어오는 것을 확인
 * 
 * 읽어오는 데이터:
 * - /test/string: 문자열 데이터
 * - /test/int: 정수 데이터  
 * - /test/float: 실수 데이터
 * 
 * 주의사항:
 * - Firebase 프로젝트가 미리 설정되어 있어야 함
 * - 실시간 데이터베이스에 데이터가 저장되어 있어야 함
 * - 인증 방법이 이메일/패스워드로 설정되어 있어야 함
 * - 적절한 보안 규칙 설정 필요 (읽기 권한)
 * 
 * 비동기 vs 동기:
 * - 이 예제는 비동기 방식을 사용합니다
 * - 데이터 요청 후 결과는 processData() 함수에서 처리됩니다
 * - 여러 개의 읽기 요청을 동시에 보낼 수 있습니다
 */
