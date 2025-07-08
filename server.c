// 리눅스에서 실행되는 TCP 수신 서버

#include <stdio.h>              // 표준 입출력 함수 사용 (예: printf)
#include <stdlib.h>             // 표준 라이브러리 함수 (예: exit)
#include <string.h>             // 문자열 처리 함수 사용 (예: memset, strcmp)
#include <unistd.h>             // close() 함수 포함 (POSIX 시스템용)
#include <arpa/inet.h>          // sockaddr_in 구조체 및 htons(), inet_ntoa() 함수 포함
#include <sys/socket.h>         // 소켓 관련 함수 및 자료형

#define PORT 8889               // ESP8266이 접속할 포트 번호
#define BUFFER_SIZE 1024        // 수신 데이터 버퍼 크기

int main() {
    int server_fd, client_fd;                      // 서버 소켓과 클라이언트 소켓 파일 디스크립터
    struct sockaddr_in server_addr, client_addr;   // 서버와 클라이언트 주소 정보
    socklen_t client_addr_len = sizeof(client_addr); // 클라이언트 주소 크기
    char buffer[BUFFER_SIZE];                      // 수신 데이터 저장 공간

    // 1. 소켓 생성 (IPv4, TCP 스트림)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("소켓 생성 실패");                      // 실패 시 에러 출력 후 종료
        exit(EXIT_FAILURE);
    }

    // 2. 서버 주소 구조체 초기화
    memset(&server_addr, 0, sizeof(server_addr));   // 서버 주소 초기화
    server_addr.sin_family = AF_INET;              // IPv4 주소 사용
    server_addr.sin_addr.s_addr = INADDR_ANY;      // 모든 IP로부터 수신 허용
    server_addr.sin_port = htons(PORT);            // 포트 번호를 네트워크 바이트 오더로 변환

    // 3. 소켓을 주소에 바인딩
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("바인딩 실패");  // 포트 바인딩 실패 시 메시지 출력 후 종료
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. 클라이언트 접속 대기 (최대 5개의 연결 대기)
    if (listen(server_fd, 5) == -1) {
        perror("리스닝 실패");  // 리스닝 실패 시 메시지 출력 후 종료
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("서버가 포트 %d에서 대기 중입니다...\n", PORT);  // 서버 상태 출력

    while (1) {
        // 5. 클라이언트 연결 수락
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);    // 클라이언트 연결 수락
        if (client_fd == -1) {
            perror("클라이언트 연결 수락 실패");
            continue; // 다음 연결 시도 계속
        }

        // 6. 데이터 수신
        memset(buffer, 0, BUFFER_SIZE);            // 버퍼 초기화
        int bytes_received = read(client_fd, buffer, BUFFER_SIZE - 1); // 데이터 수신
        if (bytes_received > 0) {
            printf("%s\n", buffer); // 수신된 온습도 데이터 출력
        }
            close(client_fd); // 클라이언트 연결 종료
    }

    // 이론적으로 도달 불가 (while 무한 루프)
    close(server_fd); // 서버 소켓 종료
    return 0;
}
