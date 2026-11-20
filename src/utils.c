#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void throw_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

File_S* readFile(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        throw_error("Error opening file!");
    }
    File_S* file = (File_S*) malloc(sizeof(File_S));
    if (!file) {
        fclose(f);
        throw_error("Error allocating memory!");
    }
    file->content = NULL;
    file->length = 0;

    int seek = fseek(f, 0, SEEK_END);
    if (seek != 0) {
        fclose(f);
        freeFile(file);
        throw_error("Error seeking file to the ending!");
    }
    const long size = ftell(f); // Seek to the end to determine bytes read from the file.
    if (size <= 0) {
        fclose(f);
        freeFile(file);
        throw_error("Error calculating file size!");
    }
    file->length = (size_t) size;
    seek = fseek(f, 0, SEEK_SET); // Seek to the beginning
    if (seek != 0) {
        fclose(f);
        freeFile(file);
        throw_error("Error seeking file to the beginning!");
    }
    file->content = (char*) malloc(file->length + 1);
    if (!file->content) {
        fclose(f);
        freeFile(file);
        throw_error("Error allocating memory for contents!");
    }

    const size_t bytes_read = fread(file->content, sizeof(char), file->length, f);
    if (bytes_read != file->length) {
        fclose(f);
        freeFile(file);
        throw_error("Error reading file!");
    }

    file->content[bytes_read] = '\0';
    fclose(f);

    return file;
}

void freeFile(File_S *file) {
    if (!file) {
        return;
    }
    if (file->content) {
        free(file->content);
    }
    free(file);
}