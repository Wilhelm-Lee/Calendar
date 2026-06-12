//
// Created by loogze on 2026/2/6.
//

#include "../include/event.h"

#include <string.h>
#include <stdlib.h>

#include "../include/err_handle.h"

inline EventPtr Create_An_Event(const char *Title, const char *Description,
                                const time_t Start, const time_t End ) {
    EventPtr p = malloc(sizeof(Event));
    if (p == NULL) error_handle(NO_ENOUGH_MEMORY);
    strcpy(p->Title, Title);
    strcpy(p->Description, Description);
    p->StartTime = Start;
    p->EndTime = End;
    return p;
}

inline void Delete_An_Event(Event *p) {
    if (p != NULL) {
        free(p);
    } else {
        error_handle(EVENT_IS_EMPTY);
    }
}
