//
// Created by william on 07/01/2026.
// 事件持久化实现 - 事件数据的文件存储和读取
//

#include "../include/write_event.h"
#include "../include/err_handle.h"
#include <string.h>

// 事件文件格式：二进制格式存储事件结构
// 文件头：版本号 + 事件数量
struct FileHeader {
    char magic[8];           // 魔数："CALENDAR"
    int version;            // 版本号：1
    int event_count;        // 事件数量
    time_t last_modified;   // 最后修改时间
};

// 保存所有事件到文件
int SaveEventsToFile(const char *filename, Event *events, int count) {
    if (!filename || !events || count <= 0) {
        return -1;
    }
    
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("无法打开文件保存事件");
        return -1;
    }
    
    // 写入文件头
    struct FileHeader header;
    strncpy(header.magic, "CALENDAR", 8);
    header.version = 1;
    header.event_count = count;
    header.last_modified = time(NULL);
    
    if (fwrite(&header, sizeof(struct FileHeader), 1, file) != 1) {
        perror("写入文件头失败");
        fclose(file);
        return -1;
    }
    
    // 写入所有事件
    size_t written = fwrite(events, sizeof(Event), count, file);
    if (written != count) {
        perror("写入事件数据失败");
        fclose(file);
        return -1;
    }
    
    fclose(file);
    return 0;
}

// 从文件加载事件
int LoadEventsFromFile(const char *filename, Event *events, int *count) {
    if (!filename || !events || !count) {
        return -1;
    }
    
    FILE *file = fopen(filename, "rb");
    if (!file) {
        // 文件不存在是正常情况（第一次运行）
        *count = 0;
        return 0;
    }
    
    // 读取文件头
    struct FileHeader header;
    if (fread(&header, sizeof(struct FileHeader), 1, file) != 1) {
        perror("读取文件头失败");
        fclose(file);
        return -1;
    }
    
    // 验证魔数
    if (strncmp(header.magic, "CALENDAR", 8) != 0) {
        fprintf(stderr, "无效的事件文件格式\n");
        fclose(file);
        return -1;
    }
    
    // 读取事件数据
    *count = header.event_count;
    size_t read = fread(events, sizeof(Event), *count, file);
    if (read != *count) {
        perror("读取事件数据失败");
        fclose(file);
        return -1;
    }
    
    fclose(file);
    return 0;
}

// 将单个事件写入文件流（用于导出）
size_t WriteEvent(FILE *stream, const Event *event) {
    if (!stream || !event) {
        return 0;
    }
    
    return fprintf(stream, "事件: %s\n"
                           "描述: %s\n"
                           "开始: %ld\n"
                           "结束: %ld\n"
                           "状态: %s\n"
                           "过期: %s\n\n",
                   event->Title,
                   event->Description,
                   event->StartTime,
                   event->EndTime,
                   event->within ? "进行中" : "已结束",
                   event->outofdate ? "是" : "否");
}

// 从文件流读取单个事件（用于导入）
size_t ReadEvent(FILE *stream, Event *event) {
    if (!stream || !event) {
        } else if (strstr(line, "描述: ")) {
            sscanf(line + 4, "%511[^\n]", event->Description);
            fields_read++;
        } else if (strstr(line, "开始: ")) {
            sscanf(line + 4, "%ld", &event->StartTime);
            fields_read++;
        } else if (strstr(line, "结束: ")) {
            sscanf(line + 4, "%ld", &event->EndTime);
            fields_read++;
        } else if (strstr(line, "状态: ")) {
            char status[20];
            sscanf(line + 4, "%19s", status);
            event->within = (strcmp(status, "进行中") == 0);
            fields_read++;
        } else if (strstr(line, "过期: ")) {
            char expired[10];
            sscanf(line + 4, "%9s", expired);
            event->outofdate = (strcmp(expired, "是") == 0);
            fields_read++;
        }
        
        if (fields_read >= 6) {
            break;
        }
    }
    
    return fields_read;
}