/**
 * @file logger.h
 * @author Jose Maria Maestre <maestrequi@esat-alumni.com>
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__ 1

#include "EDK_MemoryManager/edk_platform_types.h"
#include "adt_queue.h"
#include <stdio.h>
#include <stdarg.h>

typedef struct Logger{
    struct adt_queue_s* queue;
    struct Callbacks* ops_;
} Logger;

struct Callbacks{
    /**
     * \brief Print the message recived in a normal format and enqueue the message
     * 
     * \param logger Logger to enqueue the message
     * \param msg Message to be printed and enqueued
     * \param ... Arguments to be printed
     * 
     * \return NULL when the logger is NULL
     * \return NULL when the message is NULL
    */
    void (*print)(Logger *logger, const char *msg, ...);



    /**
     * \brief Print the message recived in Green format and enqueue the message
     * 
     * \param logger Logger to enqueue the message
     * \param msg Message to be printed and enqueued
     * \param ... Arguments to be printed
     * 
     * \return NULL when the logger is NULL
     * \return NULL when the message is NULL
    */
    void (*printSucces)(Logger *logger, const char *msg, ...);



    /**
     * \brief Print the message recived in Yellow format and enqueue the message
     * 
     * \param logger Logger to enqueue the message
     * \param msg Message to be printed and enqueued
     * \param ... Arguments to be printed
     * 
     * \return NULL when the logger is NULL
     * \return NULL when the message is NULL
    */
    void (*printWarning)(Logger *logger, const char *msg, ...);

    /**
     * \brief Print the message recived in Red format and enqueue the message
     * 
     * \param logger Logger to enqueue the message
     * \param msg Message to be printed and enqueued
     * \param ... Arguments to be printed
     * 
     * \return NULL when the logger is NULL
     * \return NULL when the message is NULL
    */
    void (*printError)(Logger *logger, const char *msg, ...);

    /**
     * \brief Write all the messages enqueued previously on a txt file
     * 
     * \param logger Logger to dequeued the messages to be written on txt file
     * \param f File to write the messages in
     * 
     * \return kErrorCode_LoggerNULL when the logger is NULL
     * \return kErrorCode_FileNULL when the file is NULL
     * \return kErrorCode_Ok when the file is written succesfully
    */
    s8 (*flush)(Logger *logger, FILE *f);

    /**
     * \brief Destroy the enqueued messages and the logger itselfs
     * 
     * \param logger Logger to be destroyed
     *
     * \return kErrorCode_LoggerNULL when the logger to be destroyed is NULL
     * \return kErrorCode_Ok when the logger is successfully destroyed
    */
    s8 (*destroy)(Logger *logger);


    /**
     * \brief Delete the messages enqueued
     * 
     * \param logger Logger to be reseted
     *
     * \return kErrorCode_LoggerNULL when the logger to be reseted is NULL
     * \return kErrorCode_Ok when the logger is successfully reseted
    */    
    s8 (*reset)(Logger *logger);
};


/**
 * \brief Creates a new logger 
 * 
 * \return Logger* NULL when there is no memory to alloc the logger
 * \return Logger* NULL when there is no memory to alloc the queue
 * \return pointer to the created Logger when the function has done his job
 */
Logger* LOGGER_Create();


#endif