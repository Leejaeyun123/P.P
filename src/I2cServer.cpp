// // I2C 주소값 코드

// #include <Wire.h>
// #include <Arduino.h>

// void setup() {
//   Wire.begin();
//   Serial.begin(115200);
//   Serial.println("I2C 스캔 시작");

//   for (byte address = 1; address < 127; address++) {
//     Wire.beginTransmission(address);
//     if (Wire.endTransmission() == 0) {
//       Serial.print("I2C 장치 발견: 0x");
//       Serial.println(address, HEX);
//     }
//   }

//   Serial.println("I2C 스캔 완료");
// }

// void loop() {}