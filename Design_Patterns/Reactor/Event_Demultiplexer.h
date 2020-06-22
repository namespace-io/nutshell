#ifndef REACTOR_DEMULTIPLEXER
#define REACTOR_DEMULTIPLEXER

#include "Event_Handler.h"
#include <unordered_map>
class Event_Demultiplexer
{
public:
    Event_Demultiplexer(){};
    virtual ~Event_Demultiplexer() {};
    virtual int wait_event(std::unordered_map<Handle, Event_Handler*>& handlers, int timeout) = 0;
    virtual int register_event( Event_Handler* handler, Event_Type et) = 0;
    virtual int remove_event( Event_Handler* handler, Event_Type et) = 0;
};

#endif
