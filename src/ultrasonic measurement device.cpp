// // ESP8266 클라이언트 코드 (초음파 측정기)

// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <WiFiUdp.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// // WiFi 정보
// const char* ssid = "turtle";
// const char* password = "turtlebot3";
// const char* server_ip = "192.168.0.97"; // Ubuntu 서버 IP
// const unsigned int server_port = 8889;

// // I2C LCD 설정
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// // 초음파 센서 핀 설정
// const int trigPin = D5;
// const int echoPin = D6;

// WiFiUDP udp;

// void setup() {
//   Serial.begin(115200);
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);

//   lcd.init();
//   lcd.backlight();

//   lcd.print("WiFi 연결 중...");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//   }

//   lcd.clear();
//   lcd.println("WiFi 연결 완료");
//   delay(1000);
// }

// void loop() {
//   // 거리 측정
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   long duration = pulseIn(echoPin, HIGH);
//   float distance = duration * 0.034 / 2;

//   // LCD 출력
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Distance:");
//   lcd.setCursor(0, 1);
//   lcd.print(distance);
//   lcd.print(" cm");

//   // UDP 전송
//   String data = "거리: " + String(distance) + " cm";
//   udp.beginPacket(server_ip, server_port);
//   udp.write(data.c_str());
//   udp.endPacket();

//   Serial.println(data);
//   delay(5000);
// }
