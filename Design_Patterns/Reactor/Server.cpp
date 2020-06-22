#include "Reactor.h"
#include "Acceptor_Handler.h"
#include <stdio.h>

int main(){

    

    Acceptor_Handler* h = new Acceptor_Handler();

    h->listen_on(10086);

    Reactor::singleton().register_handler(h, Event_Type::READ_EVENT);

    while(true){
        Reactor::singleton().event_loop(5000);
        printf("one loop\n");
    }

    return 0;
}