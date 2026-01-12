#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "write_event.h"

typedef struct Time {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
} tm;

/* 事件的结构体：
 *   1. 事件开始时间
 *   2. 事件时长
 *   3. 事件标题
 *   4. 事件描述
 */
typedef struct Event {
    char Title[50];
    char Description[200];
    time_t StartTime;
    time_t EndTime;
    bool within;
    bool outofdate;
} Event;

enum err_state {
    NO_ENOUGH_MEMORY,
    EVENT_IS_EMPTY,
};

typedef Event*  EventPtr;

/* 事件对象的:
 *   1. 创建
 *   2. 复制
 *   3. 销毁。 */

int error_handle(enum err_state error){
    if (error == NO_ENOUGH_MEMORY ) {
        puts("Not enough memory");
        exit(-1);
    }
    if (error == EVENT_IS_EMPTY) {
        puts("Event is empty");
        exit(-2);
    }
    puts("why you calling err,or you just forget???");  // 5 stars.
    exit(174);
}

EventPtr Create_An_Event(const char *Title , const char *Description, const time_t Start, const time_t End ) {
    EventPtr p;
    p = malloc(sizeof(Event));
    if (p ==NULL) return NO_ENOUGH_MEMORY;
    strcpy(p->Title, Title);
    strcpy(p->Description, Description);
    p->StartTime = Start;
    p->EndTime = End;
    return p;
}

int Delete_An_Event( Event *p ) {
    if (p != NULL) {
        free(p);
    }
    else {
        error_handle(EVENT_IS_EMPTY);
    }
}

enum EVENT_STATE {
    ADD,REMOVE,
};

// 链表的定义
typedef struct EventLink { // 起始/ 终止
    EventPtr event_data;
    time_t occur_time;
    enum EVENT_STATE state;// 类型：增加/ 删除
    struct EventLink *next;
} EventList,*EventListPtr;
EventListPtr ListHead =  NULL;
EventListPtr ListEnd = NULL;  // position

typedef struct StartAndEnd { // 为了一碟醋包了一盘饺子（？）
    EventListPtr start;
    EventListPtr end;
}StartAndEnd;

StartAndEnd Init_Eventlist(const EventPtr eventptr) {
    EventListPtr start,end;
    start= malloc(sizeof(EventList));
    if (start == NULL) error_handle(NO_ENOUGH_MEMORY);
    end  = malloc(sizeof(EventList));
    if (end == NULL ) {
        free(start);
        error_handle(NO_ENOUGH_MEMORY);
    }
    start->state = ADD;
    start->event_data = eventptr;
    start->occur_time = eventptr->StartTime;
    end->state = REMOVE;
    end->event_data = eventptr;
    end->occur_time = eventptr->EndTime;
    StartAndEnd _return ;
    _return.start = start;
    _return.end = end;
    return _return;
}

void JoinIntoEventlist(EventListPtr NeedToJoinPtr) {

}

int ADD_EventList(const EventPtr event){
    StartAndEnd _return = Init_Eventlist(event);
    EventListPtr start = _return.start;
    EventListPtr end = _return.end;
    if (ListEnd == NULL) {  // 第一次创建的处理
        ListHead = start;
        start->next = end;
        ListEnd = end;
        ListEnd->next = NULL;
    }
    else {  // "就是要自己删"  -- 什么澈 (Mon 12 Jan 16:26:25 CST 2026)

        /*                     -----[-------------{}------]-----------{-}----------*--------[--]--                */
        /*                             ^                            ^  ^                                          */
        /*                ListEnd->occur_time          >?             event->StartTime                            */
        /*                                       ->                                                               */

        if (ListEnd->occur_time <= event->StartTime) { // 事件在最后
            ListEnd->next = start;
            start->next = end;
            ListEnd = end;
            return 0;
        }
        if (ListHead->occur_time > event->EndTime) { // 事件在最前
            end->next = ListHead;
            start->next = end;
            ListHead = start;
            return 0;
        }  // "Warning: the condition is always true."  -- CLion (Mon 12 Jan 16:50:21 CST 2026)

    }
    return 0;
}

void PrintEventList(EventList *const list) {
    if (!list) {
        return;
    }

    EventList *current_list = list;
    Event *current = current_list->event_data;
    do {
        printf("[%d] %ld %s\n", list->state, current->StartTime, current->Title);

        current_list = current_list->next;

        current = current_list->event_data;
    } while (current);
}

// typedef struct StampNode {
//     time_t stamp;
//     struct EventNode *next;
// } stamp_node,*stamp_node_ptr;
//
// struct StampNode StampChain[1024] = {0};
//

// int _main(void) {
//
//     Event *event1 = Create_An_Event("this is a title","aabababa", time(NULL), time(NULL) + 36 * 60);
//     Delete_An_Event(event1);
//
//     return 0;
// }

int main(void)
{
    Event *event1 = Create_An_Event("Go shopping", "Buy some apples.", time(NULL), time(NULL) + 36 * 60);
    Event *event2 = Create_An_Event("aadadada","adawdawdad",time(NULL),time(NULL)+24*60);
    ADD_EventList(event1);
    PrintEventList(HEAD);
    ADD_EventList(event1);
    PrintEventList(HEAD);
    ADD_EventList(event2);
    PrintEventList(HEAD);
    Delete_An_Event(event1);
    Delete_An_Event(event2);

    return 0;
}

/*  1       2         3   4       5  6   */
/* [...]   [.....]   [...[...]..] ｛  [  } ]*/
/* [<--]---[<----]---[<--[...]..]<｛<-[<-}-]*/
/* [...]   [.....]   [...[...]..] ｛  [  } ]*/
/*                             |           */
/* 1   0   1     0   1   2   1  0 1  2  1 0*/
/* 1   1   1     1   1   1   1  1 1  1  1 1*/

// Event TIMETABLE[1024] = {0};  // 栈
//
// inline bool Within(const time_t moment, const time_t start, const time_t end)
// {
//     if (end < start) {
//         return false;
//     }
//
//     return (moment >= start && moment <= end);
// }
//
// void Mark(Event *const timetable, const size_t length, const time_t moment)
// {
//     if (!timetable || !length) {
//         return;
//     }
//
//     for (register size_t i = 0; i < length; i++) {
//         if (timetable[i].outofdate) {
//             continue;
//         }
//
//         if (timetable[i].StartTime < moment && timetable[i].EndTime < moment) {
//             timetable[i].outofdate = true;
//
//             continue;
//         }
//
//         timetable[i].within = Within(moment, timetable[i].StartTime, timetable[i].EndTime);
//     }
// }
//
// //                       Title, StartTime, EndTime, Description
// # define EVENT_FORMAT  "[%s] (%ld-%ld)\n\t\"%s\""
//
// void PrintEvent(const Event *const event)
// {
//     printf(EVENT_FORMAT, event->Title, event->StartTime, event->EndTime, event->Description);
// }
//
// void PrintOnGoingEvents(Event *const timetable, const size_t length)
// {
//     if (!timetable || !length) {
//         return;
//     }
//
//     for (register size_t i = 0; i < length; i++) {
//         if (timetable[i].within) {
//             PrintEvent(&timetable[i]);
//         }
//     }
// }



