#include "Select_Demultiplexer.h"
#include <sys/select.h>
#include <time.h>
#include <string.h>
#include <errno.h>

Select_Demultiplexer::Select_Demultiplexer(){
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    FD_ZERO(&err_set);
}


Select_Demultiplexer::~Select_Demultiplexer(){

}

int Select_Demultiplexer::register_event(Event_Handler* handler, Event_Type et){
    auto fd = handler->get_handle();
    if(et | Event_Type::READ_EVENT) FD_SET(fd, &read_set);
    if(et | Event_Type::WRITE_EVENT) FD_SET(fd, &write_set);
    FD_SET(fd, &err_set);
    return 0;
}

int Select_Demultiplexer::remove_event(Event_Handler* handler, Event_Type et){
    auto fd = handler->get_handle();
    if(et | Event_Type::READ_EVENT) FD_CLR(fd, &read_set);
    if(et | Event_Type::WRITE_EVENT) FD_CLR(fd, &write_set);
    FD_CLR(fd, &err_set);
   
    return 0;
}

int Select_Demultiplexer::wait_event(std::unordered_map<Handle, Event_Handler*>& handlers, int timeout){
    struct timeval tv;
    struct timeval* ptv;
    if(timeout > 0){
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = timeout % 1000 * 1000;
        ptv = &tv;
    } else {
        ptv = NULL;
    }

    auto r_set = read_set;
    auto w_set = write_set;
    auto e_set = err_set;
    int num = select(1024, &r_set, &w_set, &e_set, ptv);

    if(num < 0){
        printf("select error: %s", strerror(errno));
        return -1; 
    }

    if(num == 0) return 0;
    for(auto& p : handlers){
        if(FD_ISSET(p.first, &r_set)){
            p.second->handle_event(Event_Type::READ_EVENT);
        }
        if(FD_ISSET(p.first, &w_set)){
            p.second->handle_event(Event_Type::WRITE_EVENT);
        }
    }

    return num;
}
