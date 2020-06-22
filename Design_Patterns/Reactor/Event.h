#ifndef REACTOR_EVENT
#define REACTOR_EVENT

enum Event_Type{
    ACCEPT_EVENT = 01,
    READ_EVENT = 02,
    WRITE_EVENT = 04,
    TIMEOUT_EVENT = 010,
    SIGNAL_EVENT = 020,
    CLOSE_EVENT = 040
};

#endif