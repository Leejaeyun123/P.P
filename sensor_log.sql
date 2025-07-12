CREATE TABLE IF NOT EXISTS sensor_log (
    id INT AUTO_INCREMENT PRIMARY KEY,       -- 고유 ID
    device_ip VARCHAR(45) NOT NULL,          -- ESP8266의 IP 주소
    message TEXT NOT NULL,                   -- ESP8266에서 전송한 문자열 전체
    received_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- 수신 시간 자동 기록
);
