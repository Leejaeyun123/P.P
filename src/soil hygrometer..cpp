// // ESP8266 클라이언트 코드 (토양 수분 측정기)

// #include <Arduino.h>               // Arduino 기본 함수 라이브러리
// #include <ESP8266WiFi.h>           // ESP8266의 WiFi 기능을 사용하기 위한 라이브러리
// #include <WiFiUdp.h>               // UDP 통신 기능을 사용하기 위한 라이브러리
// #include <Wire.h>                  // I2C 통신을 위한 라이브러리
// #include <LiquidCrystal_I2C.h>     // I2C LCD 제어를 위한 라이브러리

// // WiFi 정보
// const char* ssid = "";         // 연결할 WiFi 이름
// const char* password = ""; // WiFi 비밀번호

// // UDP 서버 정보
// const char* server_ip = "xxx.xxx.x.xx";    // 데이터를 받을 서버 IP (예: Ubuntu PC)
// const unsigned int server_port = 8889;     // 서버에서 데이터 수신을 위해 열어둔 포트 번호
// int moisture = 0;                          // 토양 수분값 저장 변수, 0으로 초기화

// WiFiUDP udp;                               // UDP 통신을 위한 WiFiUDP 객체 생성
// LiquidCrystal_I2C lcd(0x27, 16, 2);        // I2C LCD 객체 생성 (I2C 주소 0x27, 16글자 2줄 LCD)

// // 초기 설정
// void setup() {
//   Serial.begin(115200);           // 시리얼 통신 시작, 보드와 PC 간 통신속도 115200bps 설정
//   lcd.init();                     // LCD 초기화, I2C 통신 시작
//   lcd.backlight();                // LCD 백라이트 켜기

//   lcd.setCursor(0, 0);            // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("WiFi 연결 중...");    // LCD에 WiFi 연결 메시지 출력
//   Serial.println("WiFi 연결 중...");    // 시리얼 모니터에도 동일 메시지 출력

//   WiFi.begin(ssid, password);     // WiFi 연결 시도
//   while (WiFi.status() != WL_CONNECTED) {   // WiFi가 연결될 때까지 대기
//     delay(500);                   // 0.5초 대기
//     Serial.print(".");            // 연결 대기 상태를 점(.)으로 표시
//   }
//   Serial.print(".\n");            // 연결 완료 후 줄바꿈

//   lcd.clear();                    // LCD 화면 초기화 (지우기)
//   lcd.setCursor(0, 0);            // 첫 줄 첫 칸으로 커서 이동
//   lcd.setCursor(0, 1);            // 두 번째 줄 첫 칸으로 커서 이동
//   lcd.print(WiFi.localIP());      // LCD에 현재 ESP8266의 IP 주소 출력
//   delay(2000);                    // IP 주소 2초간 LCD에 표시
// }

// // 반복 실행
// void loop() {
//   moisture = analogRead(A0);  // 아날로그 입력 A0에서 토양 수분값 측정 (0~1023 범위)
 
//   // 시리얼 모니터에 토양 수분값 출력
//   Serial.print("토양 수분 값: ");
//   Serial.println(moisture);

//   // LCD에 토양 수분값 출력
//   lcd.clear();              // 이전 내용 삭제
//   lcd.setCursor(0, 0);      // 첫 줄 첫 칸으로 이동
//   lcd.print("Moisture:");   // 'Moisture:' 텍스트 출력
//   lcd.setCursor(0, 1);      // 두 번째 줄 첫 칸으로 이동
//   lcd.print(moisture);      // 측정된 토양 수분값 출력

//   String data = "토양 수분: " + String(moisture);   // UDP 전송할 데이터 문자열 생성
//   udp.beginPacket(server_ip, server_port);        // 지정 서버와 포트로 패킷 전송 준비
//   udp.write(data.c_str());                        // 문자열을 UDP 패킷에 쓰기 (C 문자열 형식으로 변환)
//   udp.endPacket();                                // 패킷 전송 완료

//   delay(5000);                                    // 5초 대기 후 반복 (수분값 5초마다 측정 및 전송)
// }
