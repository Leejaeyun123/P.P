// 리눅스에서 실행되는 UDP 수신 서버

#include <stdio.h>              // 표준 입출력 함수 사용 (예: printf)
#include <stdlib.h>             // 표준 라이브러리 함수 (예: exit)
#include <string.h>             // 문자열 처리 함수 사용 (예: memset, strcmp)
#include <unistd.h>             // close() 함수 포함 (POSIX 시스템용)
#include <arpa/inet.h>          // sockaddr_in 구조체 및 htons(), inet_ntoa() 함수 포함
#include <sys/socket.h>         // 소켓 관련 함수 및 자료형
#include <mysql/mysql.h>

#define PORT 8889               // ESP8266이 전송할 포트 번호 (UDP용)
#define BUFFER_SIZE 1024        // 수신 데이터 버퍼 크기

#define DB_HOST "192.168.0.97"
#define DB_USER "ljy"
#define DB_PASS "ljy"
#define DB_NAME "sensor"

int main() {
    int server_fd;                                 // UDP 소켓 디스크립터
    struct sockaddr_in server_addr, client_addr;   // 서버 및 클라이언트 주소 정보
    socklen_t client_addr_len = sizeof(client_addr); // 클라이언트 주소 길이
    char buffer[BUFFER_SIZE];                      // 수신 데이터를 저장할 버퍼

     // MySQL 초기화 및 연결
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL 초기화 실패\n");
        exit(EXIT_FAILURE);
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "MySQL 연결 실패: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    // 1. 소켓 생성 (IPv4, UDP 데이터그램)
    server_fd = socket(AF_INET, SOCK_DGRAM, 0); // TCP와 달리 SOCK_DGRAM 사용
    if (server_fd == -1) {
        perror("소켓 생성 실패");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // 2. 서버 주소 구조체 초기화
    memset(&server_addr, 0, sizeof(server_addr));   // 서버 주소 초기화
    server_addr.sin_family = AF_INET;              // IPv4 주소 체계 사용
    server_addr.sin_addr.s_addr = INADDR_ANY;      // 모든 IP에서의 수신 허용
    server_addr.sin_port = htons(PORT);            // 포트를 네트워크 바이트 오더로 변환

    // 3. 소켓을 주소에 바인딩
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("바인딩 실패");
        close(server_fd);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("UDP 서버가 포트 %d에서 대기 중입니다...\n", PORT);

    // 4. 수신 루프 (연결 없이 수신)
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);  // 수신 버퍼 초기화

        // 5. 클라이언트로부터 데이터 수신
        int bytes_received = recvfrom(server_fd, buffer, BUFFER_SIZE - 1, 0,
                                      (struct sockaddr*)&client_addr, &client_addr_len);
        if (bytes_received > 0) {
            char *ip = inet_ntoa(client_addr.sin_addr);
            printf("[%s] %s\n", ip,  buffer);  // 수신된 데이터 출력

            // INSERT 쿼리 생성
            char query[2048];
            snprintf(query, sizeof(query),
                     "INSERT INTO sensor_log (device_ip, message) VALUES ('%s', '%s')",
                     ip, buffer);

            if (mysql_query(conn, query)) {
                fprintf(stderr, "DB INSERT 실패: %s\n", mysql_error(conn));
        }
    }
}
    // 도달하지 않지만 명시적으로 소켓 닫기
    close(server_fd);
    mysql_close(conn);
    return 0;
}
