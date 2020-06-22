#ifndef REACTOR_ACCEPTOR
#define REACTOR_ACCEPTOR

#include "Event_Handler.h"

class Acceptor_Handler : public Event_Handler
{
private:
    Handle listen_fd;
public:
    Acceptor_Handler();
    virtual ~Acceptor_Handler();
    virtual void handle_event(Event_Type et);
    virtual Handle get_handle();
    bool listen_on(int port);
};

#endif

