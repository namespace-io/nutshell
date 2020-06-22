#ifndef REACTOR_HANDLER
#define REACTOR_HANDLER

#include "Event.h"

typedef int Handle;

class Event_Handler
{
public:
    Event_Handler(){};
    virtual ~Event_Handler() {};

    virtual void handle_event(Event_Type et) = 0;
    virtual Handle get_handle() = 0;
};

#endif