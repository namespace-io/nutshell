#ifndef REACTOR
#define REACTOR

#include <unordered_map>
#include "Event_Handler.h"
#include "Event_Demultiplexer.h"

class Reactor
{
private:

    std::unordered_map<Handle, Event_Handler*> handlers;
    Event_Demultiplexer* demultiplexer;
public:
    Reactor();
    ~Reactor();
    static Reactor& singleton();
    static Reactor reactor;
    int register_handler(Event_Handler* eh, Event_Type et);
    int remove_handler(Event_Handler* eh, Event_Type et);
    int event_loop(int timeout);
};

#endif
