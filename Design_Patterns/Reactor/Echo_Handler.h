#ifndef REACTOR_ECHO
#define REACTOR_ECHO

#include "Event_Handler.h"
#include <memory>



class Echo_Handler : public Event_Handler
{
private:
    Handle fd;
    std::shared_ptr<char> buf;
    static const int MAXSIZE = 64;

public:
    Echo_Handler(Handle sock_fd);
    virtual ~Echo_Handler();
    virtual void handle_event(Event_Type et);
    virtual Handle get_handle() ;
 
};

#endif
