//
// Created by wppuq on 2026/2/6.
//

#ifndef CALENDAR_EVENT_H
#define CALENDAR_EVENT_H

#include "../include/struct.h"

EventPtr Create_An_Event(const char *Title, const char *Description, time_t Start, time_t End);

void Add_event_to_list(EventPtr event_p);

void CheckList(void);

void Delete_event_in_list(time_t timing);

void Delete_An_Event(Event *p);

#endif //CALENDAR_EVENT_H


