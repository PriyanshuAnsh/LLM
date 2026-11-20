#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

/**
 * This is a helper function that'll print the message
 * to Standard Error and force-exit the program on encounter an error
 * with an error code
 * @param message The message to print to stderr.
 */
void throw_error(const char *message);


/**
 * A helper struct for keeping a track of contents read from a file
 * and length of the file.
 */
typedef struct {
    char *content;
    size_t length;
} File_S;


/**
 * This is a helper function to read from the file.
 * Must call freeFile to free the memory.
 * @param filename The path of the file to read from.
 * @return The memory address of the data-structure of the file content and length.
 */
File_S* readFile(const char *filename);

/**
 * This function is responsible for freeing the File_S struct.
 * @param file The allocated File_S struct
 */
void freeFile(File_S *file);

#endif

