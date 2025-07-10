/********* ESP32 Firebase 기본 데이터 전송 예제 *********
 * 작성자: AIoT Makerthon Team
 * 설명: ESP32에서 Firebase 실시간 데이터베이스로 기본 데이터를 전송하는 예제
 * 라이브러리: FirebaseClient by Mobitz (v2.0.3+)
 *********************************************************/

#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

// ========== 설정 부분 (여기를 수정하세요) ==========
#define WIFI_SSID "YOUR_WIFI_SSID"           // WiFi SSID
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"   // WiFi 비밀번호
#define WEB_API_KEY "YOUR_FIREBASE_API_KEY"  // Firebase 프로젝트 API 키
#define DATABASE_URL "YOUR_DATABASE_URL"     // Firebase 데이터베이스 URL
#define USER_EMAIL "YOUR_USER_EMAIL"         // Firebase 사용자 이메일
#define USER_PASS "YOUR_USER_PASSWORD"       // Firebase 사용자 비밀번호
// ================================================

// 콜백 함수 선언
void processData(AsyncResult &aResult);

// Firebase 인증 및 구성요소
UserAuth user_auth(WEB_API_KEY, USER_EMAIL, USER_PASS);
FirebaseApp app;
WiFiClientSecure ssl_client;
using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);
RealtimeDatabase Database;

// 타이머 변수 (10초마다 데이터 전송)
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 10000; // 10초

// 전송할 변수들
int intValue = 0;
float floatValue = 0.01;
String stringValue = "";

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("ESP32 Firebase 기본 예제 시작!");
    
    // WiFi 연결
    connectToWiFi();
    
    // Firebase 초기화
    initializeFirebase();
    
    Serial.println("설정 완료! 데이터 전송을 시작합니다...");
}

void loop() {
    // Firebase 앱 루프 유지 (중요!)
    app.loop();
    
    // 인증이 완료되었는지 확인
    if (app.ready()) {
        unsigned long currentTime = millis();
        
        // 10초마다 데이터 전송
        if (currentTime - lastSendTime >= sendInterval) {
            lastSendTime = currentTime;
            sendSampleData();
        }
    }
    
    // 다른 작업들...
    delay(100);
}

void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("WiFi 연결 중");
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    
    Serial.println();
    Serial.println("✅ WiFi 연결 완료!");
    Serial.printf("📶 IP 주소: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("📶 신호 강도: %d dBm\n", WiFi.RSSI());
}

void initializeFirebase() {
    Serial.println("🔥 Firebase 초기화 중...");
    
    // SSL 클라이언트 설정
    ssl_client.setInsecure();
    ssl_client.setConnectionTimeout(1000);
    ssl_client.setHandshakeTimeout(5);
    
    // Firebase 초기화
    initializeApp(aClient, app, getAuth(user_auth), processData, "🔐 인증작업");
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DATABASE_URL);
    
    Serial.println("✅ Firebase 초기화 완료!");
}

void sendSampleData() {
    Serial.println("\n📤 데이터 전송 중...");
    
    // 문자열 데이터 생성 및 전송
    stringValue = "값_" + String(millis());
    Database.set<String>(aClient, "/test/string", stringValue, processData, "문자열_전송");
    
    // 정수 데이터 전송
    Database.set<int>(aClient, "/test/int", intValue, processData, "정수_전송");
    intValue++; // 값 증가
    
    // 실수 데이터 생성 및 전송
    floatValue = 20.0 + random(0, 200) / 10.0; // 20.0 ~ 40.0 사이의 랜덤 값
    Database.set<float>(aClient, "/test/float", floatValue, processData, "실수_전송");
    
    // 타임스탬프 전송
    Database.set<unsigned long>(aClient, "/test/timestamp", millis(), processData, "시간_전송");
    
    Serial.printf("📊 전송 데이터 - 정수: %d, 실수: %.2f, 문자열: %s\n", 
                 intValue-1, floatValue, stringValue.c_str());
}

// Firebase 결과 처리 함수
void processData(AsyncResult &aResult) {
    if (!aResult.isResult()) return;
    
    String taskId = aResult.uid().c_str();
    
    // 이벤트 처리
    if (aResult.isEvent()) {
        Serial.printf("✅ %s 성공\n", taskId.c_str());
    }
    
    // 디버그 정보
    if (aResult.isDebug()) {
        Serial.printf("🔧 디버그 [%s]: %s\n", taskId.c_str(), aResult.debug().c_str());
    }
    
    // 오류 처리
    if (aResult.isError()) {
        Serial.printf("❌ %s 오류: %s (코드: %d)\n", 
                     taskId.c_str(), 
                     aResult.error().message().c_str(),
                     aResult.error().code());
    }
    
    // 결과 데이터
    if (aResult.available()) {
        Serial.printf("📦 %s 결과: %s\n", taskId.c_str(), aResult.c_str());
    }
}

// 메모리 정보 출력 (디버깅용)
void printMemoryInfo() {
    Serial.printf("🧠 여유 힙 메모리: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("⏱️ 가동 시간: %lu초\n", millis() / 1000);
}
