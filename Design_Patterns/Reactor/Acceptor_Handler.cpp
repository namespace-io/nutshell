#include "Acceptor_Handler.h"
#include "Echo_Handler.h"
#include "Reactor.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

Acceptor_Handler::Acceptor_Handler():listen_fd(-1){}
Acceptor_Handler::~Acceptor_Handler(){
    if(listen_fd != -1) close(listen_fd);
}

bool Acceptor_Handler::listen_on(int port){
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) != -1){
        struct sockaddr_in listen_socket;
        listen_socket.sin_family = AF_INET;
        listen_socket.sin_addr.s_addr = htonl(INADDR_ANY);
        listen_socket.sin_port = htons(port);

        if(bind(listen_fd, (struct sockaddr* )&listen_socket, sizeof(listen_socket)) != -1){
            if(listen(listen_fd, 5) != -1){
                return true;
            }
        }
    }
    printf("listen on error\n");
    return false;
}

void Acceptor_Handler::handle_event(Event_Type et){
    if(et == Event_Type::READ_EVENT){
        struct sockaddr_in client_sock;
        socklen_t len = sizeof(client_sock);
        char buf[INET_ADDRSTRLEN + 1];
        int fd = accept(listen_fd, (sockaddr* )&client_sock, (socklen_t*)&len);
        inet_ntop(AF_INET, &client_sock.sin_addr, buf, INET_ADDRSTRLEN);
        printf("connection from %s : %d", buf, ntohs(client_sock.sin_port));
        
        Echo_Handler* echo = new Echo_Handler(fd);
        Reactor::singleton().register_handler(echo, Event_Type::READ_EVENT);
    }
}

Handle Acceptor_Handler::get_handle(){
    return listen_fd;
}