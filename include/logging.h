#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LOG_STREAM "./logfile.txt"

enum LogType {
    Debug, Info, Warning, Error, Fatal
};

void init_logger();
void __log(int log_type, char* message, const char* func_name, int line_num);
void close_logger();

#define log(log_type, message) __log(log_type, message, __func__, __LINE__)
