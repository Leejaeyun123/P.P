// // ESP8266 클라이언트 코드 (온습도계)

// // tcp 코드

// #include <Arduino.h>              // 아두이노 프레임워크 기본 함수 사용을 위한 헤더
// #include <DHT.h>                  // 온습도 센서 DHT11을 제어하기 위한 라이브러리
// #include <Wire.h>                 // I2C 통신용 기본 라이브러리
// #include <LiquidCrystal_I2C.h>    // I2C 방식 LCD 제어를 위한 라이브러리
// #include <ESP8266WiFi.h>          // ESP8266 WiFi 연결을 위한 라이브러리
// #include <WiFiClient.h>           // TCP 클라이언트 소켓 통신을 위한 라이브러리

// #define DHTPIN D4                 // DHT11의 데이터 핀을 D4(GPIO2)에 연결
// #define DHTTYPE DHT11             // 사용할 DHT 센서 타입을 DHT11로 지정

// DHT dht(DHTPIN, DHTTYPE);         // DHT 객체 생성
// LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 객체 생성 (주소 0x27, 16문자 x 2줄 LCD)

// const char* ssid = "turtle";         // 연결할 WiFi SSID
// const char* password = "turtlebot3"; // 연결할 WiFi 비밀번호

// const char* server_ip = "192.168.0.97"; // TCP 서버의 IP 주소 (리눅스 PC)
// const uint16_t server_port = 8889;       // TCP 서버에서 열어둔 포트 번호

// WiFiClient client;                 // TCP 연결을 위한 클라이언트 객체 생성

// void setup() {
//   Serial.begin(115200);           // 시리얼 통신 시작 (디버깅용)
//   dht.begin();                    // DHT11 센서 초기화
//   lcd.init();                     // I2C LCD 초기화
//   lcd.backlight();                // LCD 백라이트 켜기

//   lcd.setCursor(0, 0);            // LCD 첫 줄 첫 번째 칸으로 커서 이동
//   lcd.print("WiFi 연결 중...");    // LCD에 WiFi 연결 메시지 출력

//   WiFi.begin(ssid, password);     // WiFi 연결 시도

//   // WiFi 연결될 때까지 반복 확인
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);                   // 0.5초 대기
//     Serial.print(".");            // 시리얼로 진행 상황 출력
//   }

//   lcd.clear();                    // LCD 화면 초기화
//   lcd.setCursor(0, 0);            // LCD 첫 줄 첫 번째 칸으로 커서 이동
//   lcd.print("WiFi 연결 완료");      // 연결 완료 메시지 출력
//   lcd.setCursor(0, 1);            // LCD 두 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print(WiFi.localIP());      // 현재 보드의 IP 주소 표시
//   delay(2000);                    // 2초 대기 후 본 동작 시작
// }

// void loop() {
//   float temp = dht.readTemperature();  // 온도 측정
//   float humi = dht.readHumidity();     // 습도 측정

//   // 센서 오류일 경우 LCD에 에러 출력 후 5초 대기
//   if (isnan(temp) || isnan(humi)) {
//     lcd.clear();                  // LCD 화면 초기화
//     lcd.setCursor(0, 0);          // LCD 첫 줄 첫 번째 칸으로 커서 이동
//     lcd.print("센서 오류");
//     delay(5000);                  // 5초 대기 후 재시도
//     return; // loop 재시작
//   }

//   lcd.clear();                   // LCD 화면 초기화
//   lcd.setCursor(0, 0);           // LCD 첫 줄 첫 번째 칸으로 커서 이동
//   lcd.print("Temp: ");           // 온도 표시 시작
//   lcd.print(temp, 1);            // 소수점 1자리 온도 표시
//   lcd.print(" C");

//   lcd.setCursor(0, 1);           // LCD 두 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("Humi: ");           // 습도 표시 시작
//   lcd.print(humi, 1);            // 습도 출력 (소수점 1자리)
//   lcd.print(" %");

//   // TCP 서버에 연결 시도
//   if (client.connect(server_ip, server_port)) {
//     String msg = "온도: " + String(temp, 2) + " C / 습도: " + String(humi, 2) + " %";  // 전송 문자열 생성
//     client.print(msg);          // 서버로 온습도 데이터 전송
//     client.stop();              // 전송 후 연결 종료
//   } else {
//     Serial.println("서버 연결 실패"); // 연결 실패 시 시리얼에 메시지 출력
//   }

//   delay(5000);                  // 5초 후 재측정 및 재전송
// }




// // udp 코드

// #include <Arduino.h>
// #include <DHT.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <ESP8266WiFi.h>
// #include <WiFiUdp.h>  // UDP 통신용 라이브러리

// #define DHTPIN D4
// #define DHTTYPE DHT11

// DHT dht(DHTPIN, DHTTYPE);
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// const char* ssid = "turtle";
// const char* password = "turtlebot3";

// const char* server_ip = "192.168.0.97"; // 리눅스 서버 IP
// const uint16_t server_port = 8889;      // UDP 서버 포트

// WiFiUDP udp;  // UDP 통신 객체

// void setup() {
//   Serial.begin(115200);
//   dht.begin();
//   lcd.init();
//   lcd.backlight();

//   lcd.setCursor(0, 0);
//   lcd.print("WiFi 연결 중...");
//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("WiFi 연결 완료");
//   lcd.setCursor(0, 1);
//   lcd.print(WiFi.localIP());
//   delay(2000);

//   udp.begin(12345);  // 클라이언트 UDP 포트 (임의 값)
// }

// void loop() {
//   float temp = dht.readTemperature();
//   float humi = dht.readHumidity();

//   if (isnan(temp) || isnan(humi)) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("센서 오류");
//     delay(5000);
//     return;
//   }

//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Temp: ");
//   lcd.print(temp, 1);
//   lcd.print(" C");

//   lcd.setCursor(0, 1);
//   lcd.print("Humi: ");
//   lcd.print(humi, 1);
//   lcd.print(" %");

//   String msg = "온도: " + String(temp, 2) + " C / 습도: " + String(humi, 2) + " %";
//   udp.beginPacket(server_ip, server_port);
//   udp.print(msg);
//   udp.endPacket();

//   delay(5000);  // 5초마다 측정 및 전송
// }

