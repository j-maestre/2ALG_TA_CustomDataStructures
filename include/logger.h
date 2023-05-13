
#ifndef __LOGGER_H__
#define __LOGGER_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"
#include "adt_queue.h"
#include <stdio.h>

typedef struct Logger{
    struct adt_queue_s* queue;
    struct Callbacks* call;
} Logger;

struct Callbacks{
    void (*print)(Logger *logger, const char *msg);
    void (*printWarning)(Logger *logger, const char *msg);
    void (*printError)(Logger *logger, const char *msg);
    s8 (*flush)(Logger *logger, FILE *f);
    void (*destroy)(Logger *logger);
    void (*reset)(Logger *logger);
};


Logger* LOGGER_Create();




#endif