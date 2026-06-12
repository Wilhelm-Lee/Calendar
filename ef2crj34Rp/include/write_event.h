//
// Created by william on 07/01/2026.
// 事件持久化接口
//

#ifndef CALENDAR_WRITE_EVENT_H
# define CALENDAR_WRITE_EVENT_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "struct.h"

// 事件文件操作接口
int SaveEventsToFile(const char *filename, Event *events, int count);
int LoadEventsFromFile(const char *filename, Event *events, int *count);

// 单个事件文本格式读写
size_t ReadEvent(FILE *stream, Event *event);
size_t WriteEvent(FILE *stream, const Event *event);

// 事件文件路径常量
#define EVENT_DATA_FILE "calendar_events.dat"

// 导出/导入格式常量
#define EXPORT_TEXT_FILE "calendar_export.txt"

#endif //CALENDAR_WRITE_EVENT_H