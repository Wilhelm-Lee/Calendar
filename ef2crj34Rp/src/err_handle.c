//
// Created by loogze on 2026/2/6.
//

#include "../include/err_handle.h"

int error_handle(enum err_state error){

    switch (error) {
        case NO_ENOUGH_MEMORY   : perror("Not enough memory");
                                  exit(-1);
        case EVENT_IS_EMPTY     : perror("Event is empty");
                                  exit(-2);
        case LIST_HEAD_IS_EMPTY : perror("List Head IS NULL!");
                                  exit(-3);
        default                 : perror("why you calling err,or you just forget???");
                                  exit(174);/* 114514 stars.*/
    }
}

// 显示错误信息但不退出程序
void error_message(const char *message) {
    fprintf(stderr, "错误: %s\n", message);
}

// 显示警告信息
void warning_message(const char *message) {
    fprintf(stderr, "警告: %s\n", message);
}

// 显示成功信息
void success_message(const char *message) {
    printf("成功: %s\n", message);
}