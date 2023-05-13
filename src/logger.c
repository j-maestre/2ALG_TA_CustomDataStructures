#include "EDK_MemoryManager/edk_memory_manager.h"
#include "logger.h"
#include "adt_queue.h"
#include "common_def.h"
#include "string.h"

static void LOGGER_Print(Logger *log, const char *msg);
static void LOGGER_PrintSucces(Logger *log, const char *msg);
static void LOGGER_PrintWarning(Logger *log, const char *msg);
static void LOGGER_PrintError(Logger *log, const char *msg);
static s8 LOGGER_Flush(Logger *log, FILE *f);
static void LOGGER_Destroy(Logger *log);
static void LOGGER_Reset(Logger *log);

struct Callbacks callbacks = {
    .print = LOGGER_Print,
    .printSucces = LOGGER_PrintSucces,
    .printWarning = LOGGER_PrintWarning,
    .printError = LOGGER_PrintError,
    .flush = LOGGER_Flush,
    .destroy = LOGGER_Destroy,
    .reset = LOGGER_Reset
};



Logger* LOGGER_Create(){

    Logger *log = MM->malloc(sizeof(Logger));
    
    if(NULL == log){
        return NULL;
    }

    log->queue = QUEUE_create(1);

    if( NULL == log->queue){
        MM->free(log);
        return NULL;
    }

    log->ops_ = &callbacks;

    return log;
} 


void LOGGER_Print(Logger *log, const char *msg){
    if( NULL == log ){
        return NULL;
    }
    if(NULL == msg){
        return NULL;
    }

    printf("\n------------------------\n");
    printf("\n [LOGGER] TEXT: \n");
    printf(" %s \n",msg);
    printf("\n------------------------\n");

    char *msg_copy = (char*) MM->malloc(strlen(msg)+1);
    strcpy(msg_copy,msg);

    log->queue->ops_->enqueue(log->queue, msg_copy, strlen(msg_copy)+1);
    log->queue->ops_->resize(log->queue, log->queue->ops_->length(log->queue)+1);

}

void LOGGER_PrintSucces(Logger *log, const char *msg){
    printf("\033[1;32m");
    LOGGER_Print(log, msg);
    printf("\033[0m");
}

void LOGGER_PrintWarning(Logger *log, const char *msg){
    printf("\033[1;33m");
    LOGGER_Print(log, msg);
    printf("\033[0m");
}

void LOGGER_PrintError(Logger *log, const char *msg){
    printf("\033[1;31m");
    LOGGER_Print(log, msg);
    printf("\033[0m");
}


s8 LOGGER_Flush(Logger *log, FILE *f){

    if(NULL == log){
        return kErrorCode_LoggerNULL;
    }
    
    if(NULL == f){
        return kErrorCode_FileNULL;
    }

    u16 size = log->queue->ops_->length(log->queue);
    for(u16 i = 0; i < size; i++){
        char *msg = (char*) log->queue->ops_->dequeue(log->queue);
        fwrite(msg,1,strlen(msg)+1,f);
        fwrite("\n",1,1,f);
        MM->free(msg);
    }

    log->queue->ops_->resize(log->queue,1);


    return kErrorCode_Ok;
}

void LOGGER_Destroy(Logger *l){
    if(NULL != l){
        if(l->queue != NULL){
            l->queue->ops_->reset(l->queue);
            l->queue->ops_->destroy(l->queue);
        }
        MM->free(l);
    }
}


void LOGGER_Reset(Logger *l){
    if(NULL != l){
        l->queue->ops_->reset(l->queue);
        l->queue->ops_->resize(l->queue,1);
    }
}









