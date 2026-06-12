#include <stdio.h>
#include <time.h>

int main() {
    // 测试 time_t 和 struct tm 的兼容性
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    printf("编译测试:\n");
    printf("当前时间: %04d-%02d-%02d %02d:%02d:%02d\n",
           tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    
    // 测试 snprintf 的使用
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "测试格式化: %ld", now);
    printf("%s\n", buffer);
    
    // 测试字符串函数
    char str1[50] = "Hello";
    char str2[50] = "World";
    if (strcmp(str1, "Hello") == 0) {
        printf("字符串比较正确\n");
    }
    
    return 0;
}