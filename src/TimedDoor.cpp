// Copyright 2021 FOM
#include "TimedDoor.h"
#include <iostream>
#include <string>
#include <time.h>


DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door_): door(door_) {}
void DoorTimerAdapter::Timeout() {
    door.DoorTimeOut();
}
TimedDoor::TimedDoor(int iTimeout_) : opened(false),
adapter(new DoorTimerAdapter(*this)),iTimeout(iTimeout_) {}

bool TimedDoor::isDoorOpened() {
    return opened;
}
void TimedDoor::unlock() {
    opened = true;
    Timer count;
    count.tregister(iTimeout, adapter);
}
void TimedDoor::lock() {
    opened = false;
}
void TimedDoor::DoorTimeOut() {
    throw std::string("close the door!");
}
void TimedDoor::throwState() {
    if (opened) {
	    throw std::string("the door is opened!");
    } else {
	    throw std::string("the door is closed!");
    }
}
void Timer::sleep(int iTimeout) {
    time_t start = time(nullptr);
    while (time(nullptr) - start < iTimeout) {
	    continue;
    }
}
void Timer::tregister(int iTimeout, TimerClient* client) {
    this->client = client;
    sleep(iTimeout);
    client->Timeout();
}
