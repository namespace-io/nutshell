#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(){

    int sock_fd = -1;

    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) != -1){
        struct sockaddr_in sock;
        sock.sin_family = AF_INET;
        sock.sin_addr.s_addr = inet_addr("127.0.0.1");
        sock.sin_port = htons(10086);
        if((connect(sock_fd, (struct sockaddr*)&sock, sizeof(sock))) != -1){
            printf("connect ok!\n");
        } else {
            printf("connect error!\n");
            exit(-2);
        }
    }
    char wbuf[64] = {0}, rbuf[64] = {0};
    while(true){
        memset(wbuf, 0 , sizeof(wbuf));
        memset(rbuf, 0 , sizeof(rbuf));
        printf("press q to quit:\n");
        scanf("%s",wbuf);
        if(strcmp(wbuf, "q") == 0){
            return 0;
        } 

        write(sock_fd, wbuf, sizeof(wbuf));
        read(sock_fd, rbuf, sizeof(rbuf));
        printf("response: %s\n", rbuf); 
    }

    return 0;
}