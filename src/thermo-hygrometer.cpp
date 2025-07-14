// // ESP8266 클라이언트 코드 (온습도계)

// // tcp 코드

// #include <Arduino.h>              // Arduino 기본 함수 라이브러리
// #include <ESP8266WiFi.h>          // ESP8266의 WiFi 기능을 사용하기 위한 라이브러리
// #include <DHT.h>                  // 온습도 센서 DHT11을 제어하기 위한 라이브러리
// #include <Wire.h>                 // I2C 통신을 위한 라이브러리
// #include <LiquidCrystal_I2C.h>    // I2C LCD 제어를 위한 라이브러리
// #include <WiFiClient.h>           // TCP 클라이언트 소켓 통신을 위한 라이브러리

// #define DHTPIN D4                 // DHT11의 데이터 핀을 D4(GPIO2)에 연결
// #define DHTTYPE DHT11             // 사용할 DHT 센서 타입을 DHT11로 지정

// DHT dht(DHTPIN, DHTTYPE);         // DHT 객체 생성 (지정 핀과 센서 타입으로 초기화)
// LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD 객체 생성 (I2C 주소 0x27, 16글자 2줄 LCD)

// const char* ssid = "";         // 연결할 WiFi SSID
// const char* password = ""; // 연결할 WiFi 비밀번호

// const char* server_ip = "xxx.xxx.x.xx"; // 데이터를 받을 서버 IP (예: Ubuntu PC)
// const uint16_t server_port = 8889;      // 서버에서 데이터 수신을 위해 열어둔 포트 번호

// WiFiClient client;                 // TCP 통신을 위한 WiFiClient 객체 생성

// // 초기 설정
// void setup() {
//   Serial.begin(115200);           // 시리얼 통신 시작, 보드와 PC 간 통신속도 115200bps 설정
//   dht.begin();                    // DHT11 센서 초기화
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

//   lcd.clear();                    // LCD 화면 초기화
//   lcd.setCursor(0, 0);            // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("WiFi 연결 완료");      // 연결 완료 메시지 출력
//   lcd.setCursor(0, 1);            // 두 번째 줄 첫 칸으로 커서 이동
//   lcd.print(WiFi.localIP());      // LCD에 현재 ESP8266의 IP 주소 출력
//   delay(2000);                    // IP 주소 2초간 LCD에 표시
// }

// // 반복 실행
// void loop() {
//   float temp = dht.readTemperature();  // DHT11 센서로 온도 측정
//   float humi = dht.readHumidity();     // DHT11 센서로 습도 측정

//   // 측정 오류 발생 시 LCD 오류 출력 후 루프 재시작
//   if (isnan(temp) || isnan(humi)) { // 측정 실패시 NaN 값 반환됨
//     lcd.clear();                  // LCD 화면 초기화
//     lcd.setCursor(0, 0);          // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//     lcd.print("센서 오류");         
//     delay(5000);                  // 5초 대기 후 loop 재실행
//     return;                       // loop 함수 종료 후 재시작
//   }

//   lcd.clear();                   // 측정 성공 시 LCD 초기화
//   lcd.setCursor(0, 0);           // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("Temp: ");           // 온도 표시 시작
//   lcd.print(temp, 1);            // 소수점 한 자리까지 온도 표시
//   lcd.print(" C");

//   lcd.setCursor(0, 1);           // LCD 두 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("Humi: ");           // 습도 표시 시작
//   lcd.print(humi, 1);            // 소수점 한 자리까지 습도 표시
//   lcd.print(" %");

//   // TCP 서버 연결 시도 후 데이터 전송
//   if (client.connect(server_ip, server_port)) { // 서버와 연결 성공 시
//     String msg = "온도: " + String(temp, 2) + " C / 습도: " + String(humi, 2) + " %"; // 전송할 데이터 문자열 생성 (소수점 두 자리)
//     client.print(msg);          // 서버로 온습도 데이터 전송
//     client.stop();              // 데이터 전송 후 연결 종료 (TCP 연결 끊기)
//   } else {
//     Serial.println("서버 연결 실패"); // 연결 실패 시 시리얼에 메시지 출력
//   }

//   delay(5000);                  // 5초 후 재측정 및 재전송
// }




// // udp 코드

// #include <Arduino.h>            // 아두이노 프레임워크 기본 함수 사용을 위한 헤더
// #include <DHT.h>                // 온습도 센서 DHT11을 제어하기 위한 라이브러리
// #include <Wire.h>               // I2C 통신용 기본 라이브러리
// #include <LiquidCrystal_I2C.h>  // I2C 방식 LCD 제어를 위한 라이브러리
// #include <ESP8266WiFi.h>        // ESP8266 WiFi 연결을 위한 라이브러리
// #include <WiFiUdp.h>            // UDP 통신 기능을 사용하기 위한 라이브러리

// #define DHTPIN D4               // DHT11의 데이터 핀을 D4(GPIO2)에 연결
// #define DHTTYPE DHT11           // 사용할 DHT 센서 타입을 DHT11로 지정

// DHT dht(DHTPIN, DHTTYPE);       // DHT 객체 생성
// LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 객체 생성 (주소 0x27, 16문자 x 2줄 LCD)

// const char* ssid = "";          // 연결할 WiFi SSID
// const char* password = "";      // 연결할 WiFi 비밀번호

// const char* server_ip = "xxx.xxx.x.xx"; // 데이터를 받을 서버 IP (예: Ubuntu PC)
// const uint16_t server_port = 8889;      // 서버에서 데이터 수신을 위해 열어둔 포트 번호

// WiFiUDP udp;                    // UDP 통신을 위한 WiFiUDP 객체 생성

// // 초기 설정
// void setup() {
//   Serial.begin(115200);           // 시리얼 통신 시작, 보드와 PC 간 통신속도 115200bps 설정
//   dht.begin();                    // DHT11 센서 초기화
//   lcd.init();                     // LCD 초기화, I2C 통신 시작
//   lcd.backlight();                // LCD 백라이트 켜기

//   lcd.setCursor(0, 0);            // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("WiFi 연결 중...");     // LCD에 WiFi 연결 메시지 출력
//   Serial.println("WiFi 연결 중...");    // 시리얼 모니터에도 동일 메시지 출력
  
//   WiFi.begin(ssid, password);     // WiFi 연결 시도
//   while (WiFi.status() != WL_CONNECTED) {   // WiFi가 연결될 때까지 대기
//     delay(500);                   // 0.5초 대기
//     Serial.print(".");            // 연결 대기 상태를 점(.)으로 표시
//   }

//   lcd.clear();                    // LCD 화면 초기화
//   lcd.setCursor(0, 0);            // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("WiFi 연결 완료");      // 연결 완료 메시지 출력
//   lcd.setCursor(0, 1);            // 두 번째 줄 첫 칸으로 커서 이동
//   lcd.print(WiFi.localIP());      // LCD에 현재 ESP8266의 IP 주소 출력
//   delay(2000);                    // IP 주소 2초간 LCD에 표시

//   udp.begin(12345);               // UDP 통신 시작 (클라이언트 송신용 포트 번호 지정, 임의값)
// }

// // 반복 실행
// void loop() {
//   float temp = dht.readTemperature();  // DHT11 센서로 온도 측정
//   float humi = dht.readHumidity();     // DHT11 센서로 습도 측정

//   // 측정 오류 발생 시 LCD 오류 출력 후 루프 재시작
//   if (isnan(temp) || isnan(humi)) { // 측정 실패시 NaN 값 반환됨
//     lcd.clear();                  // LCD 화면 초기화
//     lcd.setCursor(0, 0);          // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//     lcd.print("센서 오류");         
//     delay(5000);                  // 5초 대기 후 loop 재실행
//     return;                       // loop 함수 종료 후 재시작
//   }

//   lcd.clear();                   // 측정 성공 시 LCD 초기화
//   lcd.setCursor(0, 0);           // LCD 첫 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("Temp: ");           // 온도 표시 시작
//   lcd.print(temp, 1);            // 소수점 한 자리까지 온도 표시
//   lcd.print(" C");

//   lcd.setCursor(0, 1);           // LCD 두 번째 줄 첫 번째 칸으로 커서 이동
//   lcd.print("Humi: ");           // 습도 표시 시작
//   lcd.print(humi, 1);            // 소수점 한 자리까지 습도 표시
//   lcd.print(" %");

//   String msg = "온도: " + String(temp, 2) + " C / 습도: " + String(humi, 2) + " %"; // UDP로 전송할 문자열 생성 (온도와 습도 각각 소수점 두 자리)
//   udp.beginPacket(server_ip, server_port);                                        // 지정 서버와 포트로 패킷 전송 준비
//   udp.print(msg);                                                                 // 준비된 메시지를 UDP 패킷에 쓰기
//   udp.endPacket();                                                                // 패킷 전송 완료

//   delay(5000);  // 5초 대기 후 반복
// }

