#include "logging.h"

FILE* lfp = NULL;

void init_logger() {
    lfp = fopen(LOG_STREAM, "w");
    if (lfp == NULL) {
        printf("Failed to start logger!\n");
        exit(1);
    } 

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time_str[64];
    size_t ret = strftime(time_str, sizeof(time_str), "%c", tm);
    if (ret) {
        fprintf(lfp, "=== %s ===\n", time_str);
    }
}

void __log(int log_type, char* message, const char* func_name, int line_num) {
    if(lfp == NULL){
        printf("Logger not initialised!\n");
        exit(1);
    }
    
    switch(log_type){
        case Debug:
            fprintf(lfp, "[DEBUG:%s:%d] %s\n", func_name, line_num, message);
            break;
        case Info:
            fprintf(lfp, "[INFO:%s:%d] %s\n", func_name, line_num, message);
            break;
        case Warning:
            fprintf(lfp, "[WARN:%s:%d] %s\n", func_name, line_num, message);
            break;
        case Error:
            fprintf(lfp, "[ERROR:%s:%d] %s\n", func_name, line_num, message);
            break;
        case Fatal:
            fprintf(lfp, "[FATAL:%s:%d] %s\n", func_name, line_num, message);
            break;
    }
    fflush(lfp);
}

void close_logger() {
    fclose(lfp);
}
