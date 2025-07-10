/****************************************************************
 * ESP32 Firebase 실시간 데이터베이스 - 실시간 동기화 예제
 * 
 * 작성자: IoT Makerthon 강의자료
 * 기반: Random Nerd Tutorials (https://randomnerdtutorials.com)
 * 
 * 이 예제는 ESP32에서 Firebase 실시간 데이터베이스의 스트림 기능을 사용하여
 * 데이터 변경사항을 실시간으로 감지하고 반응하는 방법을 보여줍니다.
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

// LED 및 센서 핀 정의
#define LED_PIN 2        // 내장 LED
#define SENSOR_PIN A0    // 센서 핀 (예: 온도센서)

// 사용자 정의 함수 선언
void processData(AsyncResult &aResult);
void streamCallback(AsyncResult &aResult);

// Firebase 인증 설정
UserAuth user_auth(Web_API_KEY, USER_EMAIL, USER_PASS);

// Firebase 구성 요소들
FirebaseApp app;
WiFiClientSecure ssl_client;
using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);
RealtimeDatabase Database;

// 상태 변수들
bool streamConnected = false;
bool ledStatus = false;
float lastSensorValue = 0.0;

// 타이머 변수들
unsigned long lastSensorRead = 0;
const unsigned long sensorInterval = 5000; // 5초마다 센서 읽기

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== ESP32 Firebase 실시간 동기화 예제 ===");
  
  // 핀 설정
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
  
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
  Serial.println("실시간 스트림 연결을 기다리는 중...");
}

void loop() {
  // 인증 및 비동기 작업 유지
  app.loop();
  
  // 인증이 준비되었는지 확인
  if (app.ready()) {
    
    // 스트림이 아직 연결되지 않았다면 시작
    if (!streamConnected) {
      Serial.println("실시간 스트림 시작...");
      
      // LED 제어를 위한 스트림 시작
      Database.stream(aClient, "/control/led", streamCallback, "led_stream", true);
      
      // 원격 명령을 위한 스트림 시작
      Database.stream(aClient, "/control/command", streamCallback, "command_stream", true);
      
      streamConnected = true;
      Serial.println("✅ 실시간 스트림 연결 완료!");
      Serial.println("📱 Firebase 콘솔에서 /control/led 값을 변경해보세요!");
      Serial.println("📱 Firebase 콘솔에서 /control/command 값을 변경해보세요!");
    }
    
    // 주기적으로 센서 데이터 읽기 및 업로드
    unsigned long currentTime = millis();
    if (currentTime - lastSensorRead >= sensorInterval) {
      lastSensorRead = currentTime;
      
      // 센서 값 읽기 (예: 온도 센서 시뮬레이션)
      float sensorValue = random(200, 300) / 10.0; // 20.0 ~ 30.0 사이의 값
      
      // 값이 변경되었을 때만 업로드
      if (abs(sensorValue - lastSensorValue) > 0.1) {
        lastSensorValue = sensorValue;
        
        Serial.printf("📊 센서 값 업로드: %.1f\n", sensorValue);
        Database.set<float>(aClient, "/sensors/temperature", sensorValue, processData, "sensor_upload");
        
        // 타임스탬프도 함께 업로드
        Database.set<unsigned long>(aClient, "/sensors/timestamp", currentTime, processData, "timestamp_upload");
      }
    }
  }
}

/**
 * 스트림 콜백 함수 - 실시간 데이터 변경 감지
 */
void streamCallback(AsyncResult &aResult) {
  if (aResult.isStream()) {
    String streamPath = aResult.dataPath().c_str();
    String streamData = aResult.c_str();
    String streamUID = aResult.uid().c_str();
    
    Serial.println("\n🔔 실시간 데이터 변경 감지!");
    Serial.printf("스트림 UID: %s\n", streamUID.c_str());
    Serial.printf("변경된 경로: %s\n", streamPath.c_str());
    Serial.printf("새로운 값: %s\n", streamData.c_str());
    
    // LED 제어 스트림 처리
    if (streamUID == "led_stream") {
      if (streamData == "true" || streamData == "1") {
        digitalWrite(LED_PIN, HIGH);
        ledStatus = true;
        Serial.println("💡 LED 켜짐");
      } else if (streamData == "false" || streamData == "0") {
        digitalWrite(LED_PIN, LOW);
        ledStatus = false;
        Serial.println("💡 LED 꺼짐");
      }
    }
    
    // 명령 스트림 처리
    else if (streamUID == "command_stream") {
      // JSON에서 문자열 값 추출
      String command = streamData;
      if (command.startsWith("\"") && command.endsWith("\"")) {
        command = command.substring(1, command.length() - 1);
      }
      
      Serial.printf("🎮 명령 수신: %s\n", command.c_str());
      
      if (command == "blink") {
        Serial.println("LED 깜빡임 실행");
        for (int i = 0; i < 5; i++) {
          digitalWrite(LED_PIN, HIGH);
          delay(200);
          digitalWrite(LED_PIN, LOW);
          delay(200);
        }
        // 원래 상태로 복원
        digitalWrite(LED_PIN, ledStatus ? HIGH : LOW);
        
      } else if (command == "status") {
        Serial.println("상태 정보 업로드");
        Database.set<bool>(aClient, "/status/led", ledStatus, processData, "status_update");
        Database.set<float>(aClient, "/status/temperature", lastSensorValue, processData, "status_update");
        Database.set<unsigned long>(aClient, "/status/uptime", millis(), processData, "status_update");
        
      } else if (command == "reset") {
        Serial.println("시스템 재시작");
        Database.set<String>(aClient, "/control/command", "acknowledged", processData, "command_ack");
        delay(1000);
        ESP.restart();
      }
    }
    
    Serial.println("------------------------");
  }
}

/**
 * Firebase 비동기 결과 처리 함수
 */
void processData(AsyncResult &aResult) {
  if (!aResult.isResult()) return;
  
  // 에러 로그 처리
  if (aResult.isError()) {
    Firebase.printf("❌ 에러: %s, 메시지: %s, 코드: %d\n", 
                   aResult.uid().c_str(), 
                   aResult.error().message().c_str(), 
                   aResult.error().code());
  }
  
  // 성공적인 응답 처리
  if (aResult.available()) {
    String uid = aResult.uid().c_str();
    
    if (uid == "sensor_upload") {
      Serial.println("✅ 센서 데이터 업로드 완료");
    } else if (uid == "timestamp_upload") {
      Serial.println("✅ 타임스탬프 업로드 완료");
    } else if (uid == "status_update") {
      Serial.println("✅ 상태 정보 업로드 완료");
    } else if (uid == "command_ack") {
      Serial.println("✅ 명령 응답 완료");
    }
  }
}

/*
 * 사용 방법:
 * 1. 위의 설정 값들을 자신의 Firebase 프로젝트 정보로 변경
 * 2. 코드를 ESP32에 업로드
 * 3. 시리얼 모니터를 열어서 상태 확인 (115200 baud)
 * 4. Firebase 콘솔에서 실시간으로 값을 변경해보세요:
 *    - /control/led : true 또는 false (LED 제어)
 *    - /control/command : "blink", "status", "reset" (명령 실행)
 * 5. /sensors/ 경로에서 실시간 센서 데이터 확인
 * 
 * 실시간 기능:
 * 📡 데이터 스트림: Firebase의 변경사항을 실시간으로 감지
 * 💡 원격 LED 제어: 웹에서 LED를 실시간으로 켜고 끄기
 * 🎮 원격 명령: blink, status, reset 명령 실행
 * 📊 센서 데이터: 5초마다 자동으로 센서 값 업로드
 * 
 * 데이터베이스 구조:
 * /control/
 *   ├── led: true/false (LED 상태 제어)
 *   └── command: "blink"/"status"/"reset" (명령)
 * /sensors/
 *   ├── temperature: 실시간 온도 값
 *   └── timestamp: 마지막 업데이트 시간
 * /status/
 *   ├── led: 현재 LED 상태
 *   ├── temperature: 현재 온도
 *   └── uptime: 시스템 가동 시간
 * 
 * 주의사항:
 * - Firebase 보안 규칙에서 읽기/쓰기 권한 설정 필요
 * - 실시간 스트림은 네트워크 연결이 끊어지면 자동으로 재연결됨
 * - ESP32 내장 LED는 핀 2번에 연결되어 있음
 * - 명령 실행 후에는 응답을 보내어 상태를 확인할 수 있음
 * 
 * 테스트 방법:
 * 1. Firebase 콘솔 열기
 * 2. 실시간 데이터베이스로 이동
 * 3. /control/led 값을 true/false로 변경 → LED가 켜지고 꺼짐
 * 4. /control/command 값을 "blink"로 변경 → LED가 5번 깜빡임
 * 5. /control/command 값을 "status"로 변경 → 현재 상태가 /status/에 업로드됨
 */
