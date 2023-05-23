#include "adt_queue.h"
#include "logger.h"
#include <stdio.h>
#include "EDK_MemoryManager/edk_memory_manager.h"



void main(){
    printf("*** Init Logger Test ***\n");

    Logger *log = NULL;
    log = LOGGER_Create();

    if(log != NULL){
        printf("Logger created correctly\n");
    }

    log->ops_->print(log,"Print normal data");
    log->ops_->print(log,"Print normal data con numero: %d", 90);
    log->ops_->printSucces(log,"Print Succes data");
    log->ops_->printSucces(log,"Print Succes data con numero %d",91);
    log->ops_->printWarning(log,"Print Warning data");
    log->ops_->printWarning(log,"Print Warning data con numero %d", 92);
    log->ops_->printError(log,"Print Error data");
    log->ops_->printError(log,"Print Error data con numero %d", 93);
    

    FILE *f;

    f = fopen("log.txt","w");
    if(f != NULL){
        log->ops_->printWarning(log,"Flushing msgs...");
        s8 result = log->ops_->flush(log,f);

        if(result == 0){
            log->ops_->printSucces(log,"Messages flushed correctly");
        }else{
            log->ops_->printError(log,"Error flushing");
        }
    }

    log->ops_->destroy(log);


    MM->status();

    return 0;
}