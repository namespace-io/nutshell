#include "Echo_Handler.h"
#include "Reactor.h"
#include <iostream>
#include <string.h>
#include <unistd.h>

Echo_Handler::Echo_Handler(Handle sock_fd):fd(sock_fd), buf(new char[MAXSIZE])
{
    
}
Echo_Handler::~Echo_Handler()
{
    
}

void Echo_Handler::handle_event(Event_Type et){
    switch (et)
    {
        case Event_Type::READ_EVENT:
            {
                printf("Reading\n"); 
                auto p = buf.get();
                if(read(fd, p, MAXSIZE) > 0){
                    write(fd, p, strlen(p));
                }
            }
            
            break;
        default:
            break;
    }
}

Handle Echo_Handler::get_handle(){
    return fd;
}



