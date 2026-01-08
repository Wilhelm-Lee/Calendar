//
// Created by william on 07/01/2026.
//

#ifndef CALENDAR_WRITE_EVENT_H
# define CALENDAR_WRITE_EVENT_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// typedef struct _Event _Event;
typedef struct Event Event;

size_t ReadEvent(FILE *stream, Event *event);

size_t WriteEvent(FILE *stream, const Event *event);

#endif //CALENDAR_WRITE_EVENT_H