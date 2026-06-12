//
// Created by wppuq on 2026/2/6.
//

#ifndef CALENDAR_EVENT_H
#define CALENDAR_EVENT_H

#include <time.h>
#include "struct.h"

EventPtr Create_An_Event(const char *Title, const char *Description, time_t Start, time_t End);

void Delete_An_Event(Event *p);

#endif //CALENDAR_EVENT_H
