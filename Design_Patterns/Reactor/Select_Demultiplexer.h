#ifndef REACTOR_SELECT
#define REACTOR_SELECT

#include "Event_Demultiplexer.h"

class Select_Demultiplexer : public Event_Demultiplexer
{
private:
    fd_set read_set;
    fd_set write_set;
    fd_set err_set;

public:
    Select_Demultiplexer();
    virtual ~Select_Demultiplexer();
    virtual int wait_event(std::unordered_map<Handle, Event_Handler*>& handlers, int timeout);
    virtual int register_event(Event_Handler* handler, Event_Type et) ;
    virtual int remove_event(Event_Handler* handler, Event_Type et) ;
};

#endif
