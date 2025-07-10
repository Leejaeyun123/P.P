// // ESP8266 클라이언트 코드 (토양 수분 측정기)

// #include <Arduino.h>
// #include <ESP8266WiFi.h>           // WiFi 기능 사용
// #include <WiFiUdp.h>               // UDP 전송 기능
// #include <Wire.h>                  // I2C 통신
// #include <LiquidCrystal_I2C.h>     // I2C LCD 제어

// // WiFi 정보
// const char* ssid = "turtle";         // WiFi SSID
// const char* password = "turtlebot3"; // WiFi 비밀번호

// // UDP 서버 정보
// const char* server_ip = "192.168.0.97";    // 수신할 서버 IP (예: Ubuntu PC)
// const unsigned int server_port = 8889;     // 수신할 포트
// int moisture = 0; //초기화

// WiFiUDP udp;                               // UDP 객체
// LiquidCrystal_I2C lcd(0x27, 16, 2);        // LCD 객체 생성 (주소 0x27, 16x2)

// // 초기 설정
// void setup() {
//   Serial.begin(115200);           // 시리얼 통신 시작
//   lcd.init();                     // LCD 초기화
//   lcd.backlight();                // 백라이트 켜기

//   lcd.setCursor(0, 0);
//   lcd.print("WiFi 연결 중...");
//   Serial.println("WiFi 연결 중...");

//   WiFi.begin(ssid, password);     // WiFi 연결 시도
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.print(".\n");

//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.setCursor(0, 1);
//   lcd.print(WiFi.localIP());
//   delay(2000); // 연결 메시지 잠시 보여줌
// }

// // 주 반복 동작
// void loop() {
//   moisture = analogRead(A0);  // 토양 수분 측정
//   int soilper = map(moisture, 170, 1023, 100, 0);

//   // 시리얼 출력
//   Serial.print("토양 수분 값: ");
//   Serial.print(moisture);
//   Serial.print(", test: ");
//   Serial.println(soilper);

//   // LCD 출력
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Moisture:");
//   lcd.setCursor(0, 1);
//   lcd.print(moisture);

//   // UDP 데이터 전송
//   String data = "토양 수분: " + String(moisture);
//   udp.beginPacket(server_ip, server_port);
//   udp.write(data.c_str());
//   udp.endPacket();

//   delay(5000); // 5초마다 측정
// }
