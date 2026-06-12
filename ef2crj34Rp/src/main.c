// 日历程序 - 命令行事件管理器
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "../include/struct.h"
#include "../include/err_handle.h"
#include "../include/event.h"
#include "../include/write_event.h"

// 全局事件存储
#define MAX_EVENTS 1000
Event event_store[MAX_EVENTS];
int event_count = 0;

// 链表状态（可选使用）
EventListPtr ListHead = NULL;
EventListPtr ListEnd = NULL;

// 事件查找函数
Event* FindEventByTitle(const char *title) {
    for (int i = 0; i < event_count; i++) {
        if (strcmp(event_store[i].Title, title) == 0) {
            return &event_store[i];
        }
    }
    return NULL;
}

// 移除事件
int RemoveEventByTitle(const char *title) {
    for (int i = 0; i < event_count; i++) {
        if (strcmp(event_store[i].Title, title) == 0) {
            // 将最后一个事件移到这个位置
            if (i < event_count - 1) {
                event_store[i] = event_store[event_count - 1];
            }
            event_count--;
            return 0; // 成功
        }
    }
    return -1; // 未找到
}

// 添加事件到数组
int AddEventToStore(const char *title, const char *desc, time_t start, time_t end) {
    if (event_count >= MAX_EVENTS) {
        fprintf(stderr, "错误: 事件存储已满（最大%d个事件）\n", MAX_EVENTS);
        return -1;
    }
    
    // 检查标题是否已存在
    if (FindEventByTitle(title) != NULL) {
        fprintf(stderr, "错误: 事件'%s'已存在\n", title);
        return -1;
    }
    
    Event *new_event = &event_store[event_count];
    strncpy(new_event->Title, title, sizeof(new_event->Title) - 1);
    new_event->Title[sizeof(new_event->Title) - 1] = '\0';
    
    strncpy(new_event->Description, desc, sizeof(new_event->Description) - 1);
    new_event->Description[sizeof(new_event->Description) - 1] = '\0';
    
    new_event->StartTime = start;
    new_event->EndTime = end;
    new_event->within = 0;
    new_event->outofdate = 0;
    
    event_count++;
    
    // 可选：也添加到链表
    Event *event_copy = malloc(sizeof(Event));
    if (event_copy) {
        *event_copy = *new_event;
        EventListPtr node = malloc(sizeof(EventList));
        if (node) {
            node->event_data = event_copy;
            node->occur_time = start;
            node->state = ADD;
            node->next = ListHead;
            ListHead = node;
        }
    }
    
    return 0;
}

// 更新所有事件的状态
void UpdateEventStates() {
    time_t now = time(NULL);
    
    for (int i = 0; i < event_count; i++) {
        if (event_store[i].EndTime < now) {
            event_store[i].outofdate = 1;
            event_store[i].within = 0;
        } else if (event_store[i].StartTime <= now && now <= event_store[i].EndTime) {
            event_store[i].within = 1;
            event_store[i].outofdate = 0;
        } else {
            event_store[i].within = 0;
            event_store[i].outofdate = 0;
        }
    }
}

// 打印单个事件的详细信息
void PrintEventDetailed(const Event *event) {
    if (!event) return;
    
    struct tm start_tm, end_tm;
    struct tm *tmp1 = localtime(&event->StartTime);
    struct tm *tmp2 = localtime(&event->EndTime);
    
    if (!tmp1 || !tmp2) return;
    
    memcpy(&start_tm, tmp1, sizeof(struct tm));
    memcpy(&end_tm, tmp2, sizeof(struct tm));
    
    time_t duration = event->EndTime - event->StartTime;
    
    printf("┌─────────────────────────────────────\n");
    printf("│ 标题:       %s\n", event->Title);
    printf("│ 描述:       %s\n", event->Description);
    printf("│ 开始时间:   %04d-%02d-%02d %02d:%02d:%02d\n",
           start_tm.tm_year + 1900, start_tm.tm_mon + 1, start_tm.tm_mday,
           start_tm.tm_hour, start_tm.tm_min, start_tm.tm_sec);
    printf("│ 结束时间:   %04d-%02d-%02d %02d:%02d:%02d\n",
           end_tm.tm_year + 1900, end_tm.tm_mon + 1, end_tm.tm_mday,
           end_tm.tm_hour, end_tm.tm_min, end_tm.tm_sec);
    printf("│ 持续时间:   %ld 秒", duration);
    if (duration >= 3600) {
        printf(" (约 %ld 小时 %ld 分钟)", duration / 3600, (duration % 3600) / 60);
    } else if (duration >= 60) {
        printf(" (约 %ld 分钟)", duration / 60);
    }
    printf("\n");
    printf("│ 状态:       %s\n", 
           event->outofdate ? "已过期" : (event->within ? "进行中" : "未开始"));
    printf("└─────────────────────────────────────\n");
}

// 打印事件的简短信息
void PrintEventSummary(const Event *event) {
    if (!event) return;
    
    struct tm tm_result;
    struct tm *start_tm = localtime(&event->StartTime);
    if (!start_tm) return;
    
    memcpy(&tm_result, start_tm, sizeof(struct tm));
    
    char time_str[20];
    if (strftime(time_str, sizeof(time_str), "%m-%d %H:%M", &tm_result) == 0) {
        time_str[0] = '\0';
    }
    
    printf("[%s] %s - %s\n", 
           event->outofdate ? "X" : (event->within ? "*" : " "),
           time_str, event->Title);
}

// 获取今天的开始时间戳（00:00:00）
time_t GetTodayStart() {
    time_t now = time(NULL);
    struct tm today_result;
    struct tm *today = localtime(&now);
    if (!today) return now;
    
    memcpy(&today_result, today, sizeof(struct tm));
    today_result.tm_hour = 0;
    today_result.tm_min = 0;
    today_result.tm_sec = 0;
    
    return mktime(&today_result);
}

// 判断某个时间戳是否在指定日期
int IsSameDay(time_t timestamp, int year, int month, int day) {
    struct tm tm_result;
    struct tm *tm_info = localtime(&timestamp);
    if (!tm_info) return 0;
    
    memcpy(&tm_result, tm_info, sizeof(struct tm));
    return (tm_result.tm_year + 1900 == year &&
            tm_result.tm_mon + 1 == month &&
            tm_result.tm_mday == day);
}

// 事件排序函数（按开始时间）
int CompareEventsByTime(const void *a, const void *b) {
    const Event *event_a = (const Event *)a;
    const Event *event_b = (const Event *)b;
    return (event_a->StartTime > event_b->StartTime) - (event_a->StartTime < event_b->StartTime);
}

// 显示帮助信息
void PrintUsage(const char *program_name) {
    printf("\n日历事件管理器 v1.0\n");
    printf("使用方法: %s <命令> [参数...]\n\n", program_name);
    printf("可用命令:\n");
    printf("  add    <标题> <描述> <开始时间戳> <持续时间秒>  添加新事件\n");
    printf("  del    <标题>                                  删除指定事件\n");
    printf("  list                                          列出所有事件\n");
    printf("  today                                         列出今天的事件\n");
    printf("  date   <年> <月> <日>                         列出指定日期的事件\n");
    printf("  ongoing                                       列出当前进行中的事件\n");
    printf("  remain <标题>                                 查看事件剩余时间\n");
    printf("  export [文件名]                               导出事件为文本文件\n");
    printf("  import <文件名>                               从文本文件导入事件\n");
    printf("  help                                          显示此帮助信息\n");
    printf("  version                                       显示版本信息\n\n");
    printf("示例:\n");
    printf("  %s add \"会议\" \"项目讨论\" %ld 3600\n", program_name, time(NULL));
    printf("  %s list\n", program_name);
    printf("  %s remain \"会议\"\n", program_name);
    printf("  %s today\n", program_name);
    printf("\n时间戳说明: 从1970年1月1日开始的秒数，使用 date +%%s 可获取当前时间戳\n");
}

// 显示版本信息
void PrintVersion() {
    printf("日历事件管理器 v1.0\n");
    printf("基于GPL-2.0许可证发布\n");
    printf("构建时间: %s %s\n", __DATE__, __TIME__);
}

// 导出事件为文本文件
void ExportEvents(const char *filename) {
    if (!filename || strlen(filename) == 0) {
        filename = EXPORT_TEXT_FILE;
    }
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("无法创建导出文件");
        return;
    }
    
    fprintf(file, "# 日历事件导出文件\n");
    fprintf(file, "# 导出时间: %ld\n", time(NULL));
    fprintf(file, "# 事件总数: %d\n\n", event_count);
    
    for (int i = 0; i < event_count; i++) {
        WriteEvent(file, &event_store[i]);
    }
    
    fclose(file);
    printf("已导出 %d 个事件到文件: %s\n", event_count, filename);
}

// 从文本文件导入事件
void ImportEvents(const char *filename) {
    if (!filename) {
        fprintf(stderr, "错误: 需要指定导入文件名\n");
        return;
    }
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("无法打开导入文件");
        return;
    }
    
    int imported = 0;
    char line[1024];
    
    // 跳过文件头部
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#') {
            fseek(file, -strlen(line), SEEK_CUR);
            break;
        }
    }
    
    while (!feof(file) && event_count < MAX_EVENTS) {
        Event new_event;
        memset(&new_event, 0, sizeof(Event));
        
        if (ReadEvent(file, &new_event) >= 4) { // 至少需要读取标题、描述、开始、结束时间
            if (FindEventByTitle(new_event.Title) == NULL) {
                event_store[event_count++] = new_event;
                imported++;
            } else {
                printf("警告: 事件'%s'已存在，跳过\n", new_event.Title);
            }
        }
    }
    
    fclose(file);
    printf("已导入 %d 个事件\n", imported);
}

// 主命令处理函数
int ProcessCommand(int argc, char *argv[]) {
    if (argc < 2) {
        PrintUsage(argv[0]);
        return 0;
    }
    
    const char *command = argv[1];
    
    if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0 || strcmp(command, "-h") == 0) {
        PrintUsage(argv[0]);
    } 
    else if (strcmp(command, "version") == 0 || strcmp(command, "--version") == 0 || strcmp(command, "-v") == 0) {
        PrintVersion();
    }
    else if (strcmp(command, "add") == 0) {
        if (argc < 6) {
            printf("错误: add命令需要4个参数\n");
            printf("使用方法: %s add <标题> <描述> <开始时间戳> <持续时间秒>\n", argv[0]);
            return 1;
        }
        
        const char *title = argv[2];
        const char *description = argv[3];
        time_t start_time = atol(argv[4]);
        int duration = atoi(argv[5]);
        
        if (duration <= 0) {
            printf("错误: 持续时间必须是正数\n");
            return 1;
        }
        
        time_t end_time = start_time + duration;
        
        if (AddEventToStore(title, description, start_time, end_time) == 0) {
            printf("成功添加事件: %s\n", title);
            // 保存到文件
            SaveEventsToFile(EVENT_DATA_FILE, event_store, event_count);
        } else {
            printf("添加事件失败\n");
            return 1;
        }
    }
    else if (strcmp(command, "del") == 0 || strcmp(command, "remove") == 0) {
        if (argc < 3) {
            printf("错误: del命令需要1个参数\n");
            printf("使用方法: %s del <标题>\n", argv[0]);
            return 1;
        }
        
        const char *title = argv[2];
        
        if (RemoveEventByTitle(title) == 0) {
            printf("成功删除事件: %s\n", title);
            SaveEventsToFile(EVENT_DATA_FILE, event_store, event_count);
        } else {
            printf("错误: 未找到事件 '%s'\n", title);
            return 1;
        }
    }
    else if (strcmp(command, "list") == 0) {
        UpdateEventStates();
        
        if (event_count == 0) {
            printf("当前没有事件\n");
            return 0;
        }
        
        // 排序
        qsort(event_store, event_count, sizeof(Event), CompareEventsByTime);
        
        printf("事件总数: %d\n\n", event_count);
        
        for (int i = 0; i < event_count; i++) {
            PrintEventSummary(&event_store[i]);
        }
        
        // 统计信息
        int ongoing_count = 0, expired_count = 0;
        for (int i = 0; i < event_count; i++) {
            if (event_store[i].within) ongoing_count++;
            if (event_store[i].outofdate) expired_count++;
        }
        
        printf("\n统计: %d 个进行中, %d 个已过期, %d 个未开始\n",
               ongoing_count, expired_count, event_count - ongoing_count - expired_count);
    }
    else if (strcmp(command, "today") == 0) {
        UpdateEventStates();
        time_t today_start = GetTodayStart();
        time_t tomorrow_start = today_start + 24 * 3600;
        
        printf("今天的事件列表:\n");
        int count = 0;
        
        for (int i = 0; i < event_count; i++) {
            if (event_store[i].StartTime >= today_start && event_store[i].StartTime < tomorrow_start) {
                PrintEventSummary(&event_store[i]);
                count++;
            }
        }
        
        if (count == 0) {
            printf("今天没有事件\n");
        } else {
            printf("\n总计: %d 个事件\n", count);
        }
    }
    else if (strcmp(command, "date") == 0) {
        if (argc < 5) {
            printf("错误: date命令需要3个参数\n");
            printf("使用方法: %s date <年> <月> <日>\n", argv[0]);
            return 1;
        }
        
        int year = atoi(argv[2]);
        int month = atoi(argv[3]);
        int day = atoi(argv[4]);
        
        UpdateEventStates();
        printf("%04d年%02d月%02d日的事件列表:\n", year, month, day);
        int count = 0;
        
        for (int i = 0; i < event_count; i++) {
            if (IsSameDay(event_store[i].StartTime, year, month, day)) {
                PrintEventSummary(&event_store[i]);
                count++;
            }
        }
        
        if (count == 0) {
            printf("没有找到该日期的事件\n");
        } else {
            printf("\n总计: %d 个事件\n", count);
        }
    }
    else if (strcmp(command, "ongoing") == 0) {
        UpdateEventStates();
        
        printf("当前进行中的事件:\n");
        int count = 0;
        
        for (int i = 0; i < event_count; i++) {
            if (event_store[i].within) {
                PrintEventDetailed(&event_store[i]);
                count++;
            }
        }
        
        if (count == 0) {
            printf("当前没有进行中的事件\n");
        }
    }
    else if (strcmp(command, "remain") == 0) {
        if (argc < 3) {
            printf("错误: remain命令需要1个参数\n");
            printf("使用方法: %s remain <标题>\n", argv[0]);
            return 1;
        }
        
        const char *title = argv[2];
        Event *event = FindEventByTitle(title);
        
        if (!event) {
            printf("错误: 未找到事件 '%s'\n", title);
            return 1;
        }
        
        UpdateEventStates();
        
        time_t now = time(NULL);
        
        if (event->outofdate) {
            printf("事件 '%s' 已过期\n", title);
            time_t ago = now - event->EndTime;
            printf("结束于 %ld 秒前\n", ago);
        } else if (event->within) {
            printf("事件 '%s' 进行中\n", title);
            time_t remaining = event->EndTime - now;
            printf("剩余时间: %ld 秒", remaining);
            if (remaining >= 3600) {
                printf(" (约 %ld 小时 %ld 分钟)", remaining / 3600, (remaining % 3600) / 60);
            } else if (remaining >= 60) {
                printf(" (约 %ld 分钟)", remaining / 60);
            }
            printf("\n");
        } else {
            printf("事件 '%s' 尚未开始\n", title);
            time_t until = event->StartTime - now;
            printf("将在 %ld 秒后开始", until);
            if (until >= 3600) {
                printf(" (约 %ld 小时 %ld 分钟)", until / 3600, (until % 3600) / 60);
            } else if (until >= 60) {
                printf(" (约 %ld 分钟)", until / 60);
            }
            printf("\n");
        }
    }
    else if (strcmp(command, "export") == 0) {
        const char *filename = (argc >= 3) ? argv[2] : NULL;
        ExportEvents(filename);
    }
    else if (strcmp(command, "import") == 0) {
        if (argc < 3) {
            printf("错误: import命令需要1个参数\n");
            printf("使用方法: %s import <文件名>\n", argv[0]);
            return 1;
        }
        
        const char *filename = argv[2];
        ImportEvents(filename);
    }
    else {
        printf("未知命令: %s\n", command);
        printf("使用 '%s help' 查看可用命令\n", argv[0]);
        return 1;
    }
    
    return 0;
}

// 主函数
int main(int argc, char *argv[]) {
    printf("日历事件管理器 - 加载中...\n");
    
    // 从文件加载事件
    int loaded_count = 0;
    if (LoadEventsFromFile(EVENT_DATA_FILE, event_store, &loaded_count) == 0) {
        event_count = loaded_count;
        printf("已加载 %d 个事件\n", event_count);
    } else {
        printf("警告: 无法加载事件数据文件，从空事件列表开始\n");
    }
    
    // 更新事件状态
    UpdateEventStates();
    
    // 处理用户命令
    int result = ProcessCommand(argc, argv);
    
    // 程序退出前保存事件
    SaveEventsToFile(EVENT_DATA_FILE, event_store, event_count);
    
    return result;
}