//
// Created by loogze on 2026/2/6.
//

#include "../include/event.h"

#include <string.h>
#include <stdlib.h>

#include "../include/err_handle.h"

EventPtr Create_An_Event(const char *Title, const char *Description,
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


EventListPtr ListHead = NULL;
EventListPtr ListEnd = NULL; // position

FullEventList Create_Event_Node(EventPtr event_p) {
    const EventListPtr start = malloc(sizeof(EventList));
    if (start == NULL) error_handle(NO_ENOUGH_MEMORY);
    const EventListPtr end = malloc(sizeof(EventList));
    if (end == NULL) {
        free(start);
        error_handle(NO_ENOUGH_MEMORY);
    }
    start->state = ADD;
    start->event_data = event_p;
    start->occur_time = event_p->StartTime;
    end->state = REMOVE;
    end->event_data = event_p;
    end->occur_time = event_p->EndTime;

    FullEventList end_and_start ;
    end_and_start.start = start;
    end_and_start.end = end;
    end_and_start.NEEDTOFREE = &end_and_start;
    return end_and_start;
}



inline void JoinIntoEventlist(EventListPtr NeedToJoinPtr) {
    EventListPtr p = ListHead;
    while (NeedToJoinPtr->event_data < p->event_data) {
        p = p->next;
    }
    NeedToJoinPtr->next = p->next;
    p->next = NeedToJoinPtr;
}

void Add_event_to_list(EventPtr event_p) {
    const FullEventList startAndEndNode = Create_Event_Node(event_p);
    const EventListPtr StartNode = startAndEndNode.start;
    const EventListPtr EndNode = startAndEndNode.end;
    free(startAndEndNode.NEEDTOFREE);

    if (!ListHead && !ListEnd) { //若第一次创建
        ListHead = StartNode;
        ListEnd = EndNode;
    }else {
        if (ListEnd->occur_time <= event_p->StartTime) {
            // 事件在最后
            ListEnd->next = StartNode;
            StartNode->next = EndNode;
            ListEnd = EndNode;
            return;
        }
        if (ListHead->occur_time > event_p->EndTime) {
            // 事件在最前
            EndNode->next = ListHead;
            StartNode->next = EndNode;
            ListHead = StartNode;
            return;
        } // "Warning: the condition is always true."  -- CLion (Mon 12 Jan 16:50:21 CST 2026)
          //进行普通插入
        JoinIntoEventlist(EndNode);
        JoinIntoEventlist(StartNode);
    }
    return;
}

void Delete_event_in_list(const time_t timing) {
    EventListPtr needToDelete_p = ListHead;
    int howManyEventNodeDeleted = 0;
    while (howManyEventNodeDeleted < 2) {
        if (needToDelete_p->next != NULL && needToDelete_p->next->event_data->StartTime == timing) {
            EventListPtr tmp = needToDelete_p->next;
            needToDelete_p->next = needToDelete_p->next->next;
            free(tmp->event_data);
            free(tmp);
            howManyEventNodeDeleted++;
        }

        needToDelete_p = needToDelete_p->next;

        if (needToDelete_p == NULL) break;
    }
}


static time_t time_yet;

void CheckList(void) {
    const time_t now = time(NULL);
    if (time_yet == now) return;
    time_yet = now;
    if (ListHead == NULL || ListHead->occur_time != now) return;
    const EventListPtr needToDelete = ListHead;
    if (ListHead->next != NULL)
        ListHead = ListHead->next;
    Delete_An_Event(needToDelete->event_data);
    free(needToDelete);
}



// void ADD_EventList(EventPtr event_p) {
//     if (ListHead == NULL) {
//         FullEventListPtr F_event = Init_Eventlist(event_p);
//         EventListPtr start = F_event->start;
//         EventListPtr end = F_event->end;
//         ListHead = start;
//         start->next = end;
//         ListEnd = end;
//         ListEnd->next = NULL;
//     } else {
//         // "就是要自己删"  -- 什么澈 (Mon 12 Jan 16:26:25 CST 2026)
//
//         /*                     -----[-------------{}------]-----------{-}----------*--------[--]--                */
//         /*                             ^                            ^  ^                                          */
//         /*                ListEnd->occur_time          >?             event->StartTime                            */
//         /*                                       ->                                                               */
//         const EventListPtr start = malloc(sizeof(EventList));
//         if (start == NULL) error_handle(NO_ENOUGH_MEMORY);
//         const EventListPtr end = malloc(sizeof(EventList));
//         if (end == NULL) {
//             free(start);
//             error_handle(NO_ENOUGH_MEMORY);
//         }
//         if (ListEnd->occur_time <= event_p->StartTime) {
//             // 事件在最后
//             ListEnd->next = start;
//             start->next = end;
//             ListEnd = end;
//             return;
//         }
//         if (ListHead->occur_time > event_p->EndTime) {
//             // 事件在最前
//             end->next = ListHead;
//             start->next = end;
//             ListHead = start;
//         } // "Warning: the condition is always true."  -- CLion (Mon 12 Jan 16:50:21 CST 2026)
//         JoinIntoEventlist(end);
//         JoinIntoEventlist(start);
//     }
// }