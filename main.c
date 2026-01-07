#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
} Time;

/* 事件的结构体：
 *   1. 事件开始时间
 *   2. 事件时长
 *   3. 事件标题
 *   4. 事件描述
 */
typedef struct {
    char Title[50];
    char Description[200];
    time_t StartTime;
    time_t EndTime;
} Event;

enum err_state {
    NO_ENOUGH_MEMORY,

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
}

Event *Create_An_Event( char *Title , char *Description, time_t Start, time_t End ) {
    EventPtr p;
    p = malloc(sizeof(Event));
    if (p ==NULL) return NO_ENOUGH_MEMORY;
    strcpy(p->Title, Title);
    strcpy(p->Description, Description);
    p->StartTime = Start;
    p->EndTime = End;
    return p;
}



// Event *Copy_An_Event(Event *origion) {
//
//
// }

int main(void) {

    Event *event = Create_An_Event("this is a title","aabababa", time(NULL), time(NULL) + 36 * 60);

    return 0;
}
