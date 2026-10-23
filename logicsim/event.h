#ifndef EVENT_H
#define EVENT_H
#include "wire.h"

struct Event
{
    uint64_t time;
    Wire* wire;
    char state;
};

typedef struct EventLess {
        //write the operator() required to make this a functor that compares Events by time
        bool operator()(const Event* a, const Event* b) const
    {
        return a->time < b->time;   // earlier time has priority -> min-heap
    }
} EventLess;
	
#endif
