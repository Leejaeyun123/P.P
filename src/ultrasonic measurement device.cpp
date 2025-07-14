// ESP8266 클라이언트 코드 (초음파 측정기)

#include <Arduino.h>               // Arduino 기본 함수 라이브러리
#include <ESP8266WiFi.h>           // ESP8266의 WiFi 기능을 사용하기 위한 라이브러리
#include <WiFiUdp.h>               // UDP 통신 기능을 사용하기 위한 라이브러리
#include <Wire.h>                  // I2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>     // I2C LCD 제어를 위한 라이브러리

// WiFi 정보
const char* ssid = "";         // 연결할 WiFi 이름
const char* password = "";     // WiFi 비밀번호

// UDP 서버 정보
const char* server_ip = "xxx.xxx.x.xx";    // 데이터를 받을 서버 IP (예: Ubuntu PC)
const unsigned int server_port = 8889;     // 서버에서 데이터 수신을 위해 열어둔 포트 번호

WiFiUDP udp;                               // UDP 통신을 위한 WiFiUDP 객체 생성
LiquidCrystal_I2C lcd(0x27, 16, 2);        // I2C LCD 객체 생성 (I2C 주소 0x27, 16글자 2줄 LCD)

// 초음파 센서 핀 설정
const int trigPin = D5;                    // 초음파 송신 핀 (TRIG) → D5 (GPIO14)
const int echoPin = D6;                    // 초음파 수신 핀 (ECHO) → D6 (GPIO12)

// 초기 설정
void setup() {
  Serial.begin(115200);           // 시리얼 통신 시작, 보드와 PC 간 통신속도 115200bps 설정
  pinMode(trigPin, OUTPUT);       // TRIG 핀을 출력으로 설정
  pinMode(echoPin, INPUT);        // ECHO 핀을 입력으로 설정

  lcd.init();                     // LCD 초기화, I2C 통신 시작
  lcd.backlight();                // LCD 백라이트 켜기

  lcd.print("WiFi 연결 중...");    // LCD에 WiFi 연결 메시지 출력
  WiFi.begin(ssid, password);     // WiFi 연결 시도     
  while (WiFi.status() != WL_CONNECTED) {   // WiFi가 연결될 때까지 대기
    delay(500);                   // 0.5초 대기
    Serial.print(".");            // 연결 대기 상태를 점(.)으로 표시
  }
}

// 반복 실행
void loop() {
  // 거리 측정
  digitalWrite(trigPin, LOW);             // TRIG 핀 LOW → 초음파 트리거 초기화 (잔류 신호 제거)
  delayMicroseconds(2);                   // 2마이크로초 대기 (센서 안정화 시간)
  digitalWrite(trigPin, HIGH);            // TRIG 핀 HIGH → 초음파 발사 시작
  delayMicroseconds(10);                  // 10마이크로초 동안 HIGH 유지 → 초음파 8번 발사
  digitalWrite(trigPin, LOW);             // TRIG 핀 LOW → 초음파 신호 발사 종료
  long duration = pulseIn(echoPin, HIGH); // ECHO 핀 HIGH 지속시간 측정. 초음파가 목표물에 반사되어 돌아오는 시간 측정. pulseIn() : 왕복 시간
  float distance = duration * 0.034 / 2;  // 편도 거리(cm) = (음속 34cm/ms = 0.034cm/μs) × 왕복 시간 ÷ 2.   * 0.034 : 왕복 거리(cm) / /2 : 최종 결과 = 편도 거리

  // LCD 출력
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // UDP 전송
  String data = "거리: " + String(distance) + " cm";
  udp.beginPacket(server_ip, server_port);
  udp.write(data.c_str());
  udp.endPacket();

  Serial.println(data);
  delay(5000);
}
