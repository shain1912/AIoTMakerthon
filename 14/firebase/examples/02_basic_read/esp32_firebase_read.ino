/********* ESP32 Firebase 데이터 읽기 예제 *********
 * 작성자: AIoT Makerthon Team
 * 설명: Firebase 실시간 데이터베이스에서 데이터를 읽어오는 예제
 * 라이브러리: FirebaseClient by Mobitz (v2.0.3+)
 *********************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

// ========== 설정 부분 (여기를 수정하세요) ==========
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define WEB_API_KEY "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL "YOUR_DATABASE_URL"
#define USER_EMAIL "YOUR_USER_EMAIL"
#define USER_PASS "YOUR_USER_PASSWORD"
// ================================================

// 콜백 함수 선언
void processData(AsyncResult &aResult);

// Firebase 구성요소
UserAuth user_auth(WEB_API_KEY, USER_EMAIL, USER_PASS);
FirebaseApp app;
WiFiClientSecure ssl_client;
using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);
RealtimeDatabase Database;

// 타이머 변수 (5초마다 데이터 읽기)
unsigned long lastReadTime = 0;
const unsigned long readInterval = 5000; // 5초

// 읽어온 값을 저장할 변수들
int receivedInt = 0;
float receivedFloat = 0.0;
String receivedString = "";
unsigned long receivedTimestamp = 0;

// 데이터 구조체
struct DatabaseData {
    int intValue;
    float floatValue;
    String stringValue;
    unsigned long timestamp;
    bool isValid;
};

DatabaseData lastData;

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("ESP32 Firebase 데이터 읽기 예제 시작!");
    
    // 구조체 초기화
    lastData.isValid = false;
    
    // WiFi 연결
    connectToWiFi();
    
    // Firebase 초기화
    initializeFirebase();
    
    Serial.println("설정 완료! 데이터 읽기를 시작합니다...");
}

void loop() {
    app.loop();
    
    if (app.ready()) {
        unsigned long currentTime = millis();
        
        // 5초마다 데이터 읽기
        if (currentTime - lastReadTime >= readInterval) {
            lastReadTime = currentTime;
            readDatabaseData();
        }
    }
    
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
}

void initializeFirebase() {
    Serial.println("🔥 Firebase 초기화 중...");
    
    ssl_client.setInsecure();
    ssl_client.setConnectionTimeout(1000);
    ssl_client.setHandshakeTimeout(5);
    
    initializeApp(aClient, app, getAuth(user_auth), processData, "🔐인증작업");
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DATABASE_URL);
    
    Serial.println("✅ Firebase 초기화 완료!");
}

void readDatabaseData() {
    Serial.println("\n📥 데이터 읽기 중...");
    
    // 비동기 방식으로 각각의 데이터 읽기
    Database.get(aClient, "/test/int", processData, false, "정수_읽기");
    delay(100); // 요청 간격
    
    Database.get(aClient, "/test/float", processData, false, "실수_읽기");
    delay(100);
    
    Database.get(aClient, "/test/string", processData, false, "문자열_읽기");
    delay(100);
    
    Database.get(aClient, "/test/timestamp", processData, false, "시간_읽기");
    delay(100);
    
    // 전체 테스트 노드 읽기 (JSON 형태)
    Database.get(aClient, "/test", processData, false, "전체_읽기");
}

void processData(AsyncResult &aResult) {
    if (!aResult.isResult()) return;
    
    String taskId = aResult.uid().c_str();
    
    if (aResult.available()) {
        String value = aResult.c_str();
        Serial.printf("📦 받은 데이터 [%s]: %s\n", taskId.c_str(), value.c_str());
        
        // 작업 ID에 따라 적절한 변수에 저장
        if (taskId == "정수_읽기") {
            receivedInt = value.toInt();
            lastData.intValue = receivedInt;
            Serial.printf("🔢 정수 값: %d\n", receivedInt);
        }
        else if (taskId == "실수_읽기") {
            receivedFloat = value.toFloat();
            lastData.floatValue = receivedFloat;
            Serial.printf("🔢 실수 값: %.2f\n", receivedFloat);
        }
        else if (taskId == "문자열_읽기") {
            // JSON 문자열에서 실제 값 추출
            receivedString = extractStringValue(value);
            lastData.stringValue = receivedString;
            Serial.printf("📝 문자열 값: %s\n", receivedString.c_str());
        }
        else if (taskId == "시간_읽기") {
            receivedTimestamp = value.toInt();
            lastData.timestamp = receivedTimestamp;
            Serial.printf("⏰ 타임스탬프: %lu\n", receivedTimestamp);
        }
        else if (taskId == "전체_읽기") {
            Serial.printf("📋 전체 JSON 데이터:\n%s\n", value.c_str());
            parseJSONData(value);
        }
        
        lastData.isValid = true;
    }
    
    if (aResult.isError()) {
        Serial.printf("❌ 읽기 오류 [%s]: %s (코드: %d)\n", 
                     taskId.c_str(),
                     aResult.error().message().c_str(),
                     aResult.error().code());
    }
    
    if (aResult.isEvent()) {
        Serial.printf("✅ %s 완료\n", taskId.c_str());
    }
}

// JSON 문자열에서 실제 문자열 값 추출
String extractStringValue(String jsonValue) {
    // Firebase에서 문자열은 따옴표로 둘러싸여 옴
    if (jsonValue.startsWith("\"") && jsonValue.endsWith("\"")) {
        return jsonValue.substring(1, jsonValue.length() - 1);
    }
    return jsonValue;
}

// JSON 데이터 파싱 (간단한 예제)
void parseJSONData(String jsonData) {
    Serial.println("🔍 JSON 데이터 분석:");
    
    // 간단한 JSON 파싱 (실제 프로젝트에서는 ArduinoJson 라이브러리 사용 권장)
    if (jsonData.indexOf("\"int\":") != -1) {
        int intStart = jsonData.indexOf("\"int\":") + 6;
        int intEnd = jsonData.indexOf(",", intStart);
        if (intEnd == -1) intEnd = jsonData.indexOf("}", intStart);
        String intStr = jsonData.substring(intStart, intEnd);
        Serial.printf("  📊 정수: %s\n", intStr.c_str());
    }
    
    if (jsonData.indexOf("\"float\":") != -1) {
        int floatStart = jsonData.indexOf("\"float\":") + 8;
        int floatEnd = jsonData.indexOf(",", floatStart);
        if (floatEnd == -1) floatEnd = jsonData.indexOf("}", floatStart);
        String floatStr = jsonData.substring(floatStart, floatEnd);
        Serial.printf("  📊 실수: %s\n", floatStr.c_str());
    }
}

// 읽어온 데이터 요약 출력
void printDataSummary() {
    if (!lastData.isValid) {
        Serial.println("❌ 유효한 데이터가 없습니다.");
        return;
    }
    
    Serial.println("\n📊 데이터 요약:");
    Serial.printf("  🔢 정수: %d\n", lastData.intValue);
    Serial.printf("  🔢 실수: %.2f\n", lastData.floatValue);
    Serial.printf("  📝 문자열: %s\n", lastData.stringValue.c_str());
    Serial.printf("  ⏰ 타임스탬프: %lu\n", lastData.timestamp);
    
    // 타임스탬프를 시간으로 변환 (단순 계산)
    unsigned long seconds = lastData.timestamp / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    
    Serial.printf("  🕐 경과 시간: %lu시간 %lu분 %lu초\n", 
                 hours, minutes % 60, seconds % 60);
}

// 특정 경로의 데이터 모니터링 (수동 호출용)
void monitorSpecificPath(String path) {
    Serial.printf("👀 경로 모니터링: %s\n", path.c_str());
    Database.get(aClient, path, processData, false, "모니터링");
}
