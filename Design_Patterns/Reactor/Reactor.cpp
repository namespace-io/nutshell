#include "Reactor.h"
#include "Select_Demultiplexer.h"

Reactor Reactor::reactor;
Reactor::Reactor(){
    demultiplexer = new Select_Demultiplexer();
}

Reactor::~Reactor(){
    delete demultiplexer;
}

Reactor& Reactor::singleton(){ 
    return reactor;
}

int Reactor::register_handler(Event_Handler* eh, Event_Type et){
    demultiplexer->register_event(eh, et);
    handlers.insert({eh->get_handle(), eh});
    return 0;
}

int Reactor::remove_handler(Event_Handler* eh, Event_Type et){
    demultiplexer->remove_event(eh, et);
    return 0;
}

int Reactor::event_loop(int timeout){
    demultiplexer->wait_event(handlers, timeout);
    return 0;
}