/*
 * @docgen_start
 * @type: project
 * @name: m4queue-example-tree
 * @brief: tree command implemented with m4queue
 *
 * @description
 * @This is an basic example of a tree command, which recursively lists
 * @directories and files. Since its using m4queue, which is a queue
 * @implementation, it is performed using breadth-first search.
 * @description
 *
 * @examples
 * @#include <stdio.h>\N
 * @#include <stdlib.h>\N
 * @#include <dirent.h>\N
 * @#include <string.h>\N
 * @#include <sys/stat.h>\N
 * @
 * @#include "m4queue/liberror.h"
 * @
 * @
 * @// M4 related junk, like getting m4queue included and\N
 * @// defining data structure properties.\N
 * @define(PATH_TYPE, char *)\N
 * @define(PATH_NAME, struct PathQueue)\N
 * @define(PATH_FREE, free($1))\N
 * @
 * @M4QUEUE_DECLARE(PathQueue, char *);
 * @
 * @char *copy_string(const char *string) {
 * @    char *new_string = CWUTILS_NULL;
 * @
 * @    LIBERROR_IS_NULL(string, "string");
 * @
 * @    new_string = malloc(sizeof(char) * strlen(string) + 1);
 * @
 * @    LIBERROR_MALLOC_FAILURE(new_string, "new_string");
 * @
 * @    strncpy(new_string, string, strlen(string) + 1);
 * @
 * @    return new_string;\N
 * @}
 * @
 * @int is_direc(const char *path) {
 * @    struct stat stat_buffer;
 * @    int response = 0;
 * @
 * @    if((response = stat(path, &stat_buffer)) == -1)
 * @        return 0;
 * @
 * @    if((stat_buffer.st_mode & S_IFMT) != S_IFDIR)
 * @        return 0;
 * @
 * @    return 1;\N
 * @}
 * @
 * @int main() {
 * @    int path_buffer_capacity = 128 + 1;
 * @    char *path_buffer = CWUTILS_NULL;
 * @    struct PathQueue *directories = CWUTILS_NULL;
 * @
 * @    directories = M4QUEUE_INIT(directories, PATH);
 * @    path_buffer = malloc(sizeof(char) * 128 + 1);
 * @
 * @    M4QUEUE_VERIFY(directories);
 * @    LIBERROR_MALLOC_FAILURE(path_buffer, "path_buffer");
 * @    M4QUEUE_ENQUEUE(directories, copy_string("."), PATH);
 * @
 * @    // Exhaust directories until there are no more
 * @    while(M4QUEUE_IS_EMPTY(directories) == 0) {
 * @        DIR *directory_ptr = CWUTILS_NULL;
 * @        char *next_directory = CWUTILS_NULL;
 * @        struct dirent *entry = CWUTILS_NULL;
 * @
 * @        // Dequeue the next directory, load it, and scan its contents.
 * @        // This will separate files, which will be printed to the
 * @        // stdout, and directories, which will be enqueued to continue
 * @        // the cycle.
 * @        M4QUEUE_DEQUEUE(directories, next_directory, PATH);
 * @        LIBERROR_IS_NULL(next_directory, "next_directory");
 * @        
 * @        // Load the file path into the reused memory buffer, then read
 * @        // it through dirent. This buffer will be reused when making
 * @        // the full paths to new directories to enqueue. But, if the
 * @        // length of the directory name is too big, resize the buffer.
 * @        if(strlen(next_directory) > (path_buffer_capacity - 1)) {
 * @            path_buffer = realloc(path_buffer,
 * @                          sizeof(char) * (strlen(next_directory) + 1));
 * @            path_buffer_capacity = strlen(next_directory) + 1;
 * @
 * @            LIBERROR_MALLOC_FAILURE(path_buffer, "path_buffer");
 * @        }
 * @
 * @        strncpy(path_buffer, next_directory,
 * @                strlen(next_directory) + 1);
 * @
 * @        // Scan the directory, enqueueing new directories, and
 * @        // displaying files.
 * @        directory_ptr = opendir(next_directory);
 * @
 * @        LIBERROR_IS_NULL(directory_ptr, "directory_ptr");
 * @
 * @        // For each directory entry, build the full path to it.
 * @        while((entry = readdir(directory_ptr)) != NULL) {
 * @            if(strcmp(entry->d_name, ".") == 0 ||
 * @               strcmp(entry->d_name, "..") == 0)
 * @                continue;
 * @
 * @            if((strlen(entry->d_name) + strlen(next_directory) + 1) >
 * @                (path_buffer_capacity - 1)) {
 * @                path_buffer = realloc(path_buffer, sizeof(char) *
 * @                                      (strlen(entry->d_name) +
 * @                                       strlen(next_directory) + 2));
 * @                path_buffer_capacity = strlen(entry->d_name) +
 * @                                       strlen(next_directory) + 1 + 1;
 * @
 * @                LIBERROR_MALLOC_FAILURE(path_buffer, "path_buffer");
 * @            }
 * @
 * @            sprintf(path_buffer, "%s/%s", next_directory,
 * @                                          entry->d_name);
 * @
 * @            // Enqueue directories
 * @            if(is_direc(path_buffer) == 1) {
 * @                M4QUEUE_ENQUEUE(directories, copy_string(path_buffer),
 * @                                PATH);
 * @            }
 * @
 * @            printf("%s\\\\n", path_buffer);
 * @        }
 * @
 * @        free(next_directory);
 * @        closedir(directory_ptr);
 * @    }
 * @
 * @    M4QUEUE_FREE(directories, PATH);
 * @    free(path_buffer);
 * @
 * @    return 0;\N
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: m4queue(cware)
 *
 * @docgen_end
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <sys/stat.h>

#include "m4queue/liberror.h"


/* M4 related junk, like getting m4queue included and
 * defining data structure properties. */
include(m4queue/m4queue.m4)
define(PATH_TYPE, char *)
define(PATH_NAME, struct PathQueue)
define(PATH_FREE, free($1))

M4QUEUE_DECLARE(PathQueue, char *);

char *copy_string(const char *string) {
    char *new_string = CWUTILS_NULL;

    LIBERROR_IS_NULL(string, "string");

    new_string = malloc(sizeof(char) * strlen(string) + 1);

    LIBERROR_MALLOC_FAILURE(new_string, "new_string");

    strncpy(new_string, string, strlen(string) + 1);

    return new_string;
}

int is_direc(const char *path) {
    struct stat stat_buffer;
    int response = 0;

    if((response = stat(path, &stat_buffer)) == -1)
        return 0;

    if((stat_buffer.st_mode & S_IFMT) != S_IFDIR)
        return 0;

    return 1;
}

int main() {
    int path_buffer_capacity = 128 + 1;
    char *path_buffer = CWUTILS_NULL;
    struct PathQueue *directories = CWUTILS_NULL;

    directories = M4QUEUE_INIT(directories, PATH);
    path_buffer = malloc(sizeof(char) * 128 + 1);

    M4QUEUE_VERIFY(directories);
    LIBERROR_MALLOC_FAILURE(path_buffer, "path_buffer");
    M4QUEUE_ENQUEUE(directories, copy_string("."), PATH);

    /* Exhaust directories until there are no more */
    while(M4QUEUE_IS_EMPTY(directories) == 0) {
        DIR *directory_ptr = CWUTILS_NULL;
        char *next_directory = CWUTILS_NULL;
        struct dirent *entry = CWUTILS_NULL;

        /* Dequeue the next directory, load it, and scan its contents.
         * This will separate files, which will be printed to the stdout,
         * and directories, which will be enqueued to continue the cycle. */
        M4QUEUE_DEQUEUE(directories, next_directory, PATH);
        LIBERROR_IS_NULL(next_directory, "next_directory");
        
        /* Load the file path into the reused memory buffer, then read it
         * through dirent. This buffer will be reused when making the full
         * paths to new directories to enqueue. But, if the length of the
         * directory name is too big, resize the buffer. */
        if(strlen(next_directory) > (path_buffer_capacity - 1)) {
            path_buffer = realloc(path_buffer, sizeof(char) * (strlen(next_directory) + 1));
            path_buffer_capacity = strlen(next_directory) + 1;

            LIBERROR_MALLOC_FAILURE(path_buffer, "path_buffer");
        }

        strncpy(path_buffer, next_directory, strlen(next_directory) + 1);

        /* Scan the directory, enqueueing new directories, and displaying
         * files. */
        directory_ptr = opendir(next_directory);

        LIBERROR_IS_NULL(directory_ptr, "directory_ptr");

        /* For each directory entry, build the full path to it. */
        while((entry = readdir(directory_ptr)) != NULL) {
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if((strlen(entry->d_name) + strlen(next_directory) + 1) > (path_buffer_capacity - 1)) {
                path_buffer = realloc(path_buffer, sizeof(char) * (strlen(entry->d_name) + strlen(next_directory) + 1 + 1));
                path_buffer_capacity = strlen(entry->d_name) + strlen(next_directory) + 1 + 1;

                LIBERROR_MALLOC_FAILURE(path_buffer, "path_buffer");
            }

            sprintf(path_buffer, "%s/%s", next_directory, entry->d_name);

            /* Enqueue directories */
            if(is_direc(path_buffer) == 1) {
                M4QUEUE_ENQUEUE(directories, copy_string(path_buffer), PATH);
            }

            printf("%s\n", path_buffer);
        }

        free(next_directory);
        closedir(directory_ptr);
    }

    M4QUEUE_FREE(directories, PATH);
    free(path_buffer);

    return 0;
}
