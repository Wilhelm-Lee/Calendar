//
// Created by william on 07/01/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char description[2048];
    char title[128];
    time_t start_in_seconds;
    time_t duration_in_seconds;
} _Event;

//                       title, start_in_seconds, duration_in_seconds, description
# define EVENT_FORMAT  "[%s] (%ld:%ld)\n\t\"%s\""

/* Returns total bytes written. */
size_t WriteEvent(FILE *const stream, const _Event *const event)
{
    if (!stream || !event) {
        return 0;
    }

    return fprintf(stream, EVENT_FORMAT,
        event->title, event->start_in_seconds,
        event->duration_in_seconds, event->description
    );
}

size_t ReadEvent(FILE *const stream, _Event *const event)
{
    if (!stream || !event) {
        return 0;
    }

    return fscanf(stream, EVENT_FORMAT,
        event->title, &event->start_in_seconds, &event->duration_in_seconds, event->description
    );
}
