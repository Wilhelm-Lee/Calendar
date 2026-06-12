//
// Created by loogze on 2026/2/6.
//

#ifndef CALENDAR_ERR_HANDLE_H
#define CALENDAR_ERR_HANDLE_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

int error_handle(enum err_state error);

// 非致命错误处理函数
void error_message(const char *message);
void warning_message(const char *message);
void success_message(const char *message);

#endif //CALENDAR_ERR_HANDLE_H