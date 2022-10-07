/*
 * Testing of the free operation.
*/

#include "common.h"



#include <stdio.h>
#include <assert.h>
#include <string.h>


#if defined(__ULTRIX__) || defined(__QuasiBSD__)
#   if !defined(CWUTILS_GENERIC)
#       define CWUTILS_GENERIC char *
#   endif
#   if !defined(CWUTILS_NULL)
#       define CWUTILS_NULL    ((char *) 0)
#   endif
#else
#   if !defined(CWUTILS_GENERIC)
#      define CWUTILS_GENERIC void *
#   endif
#   if !defined(CWUTILS_NULL)
#      define CWUTILS_NULL    ((void *) 0)
#   endif
#endif




























    struct IntQueue {
        int head;
        int length;
        int capacity;

        int *contents;
    }
;

    struct StringQueue {
        int head;
        int length;
        int capacity;

        char * *contents;
    }
;





/* This queue is used for testing memory reuse (hence
   the "RE" */










void test_free() {
    struct StringQueue *queue = (struct StringQueue *) CWUTILS_NULL;

    queue = 
	(struct StringQueue *) malloc(sizeof(*(queue)));

    LIBERROR_MALLOC_FAILURE((queue), "(queue)");

	(queue)->head = 0;
	(queue)->length = 0;
	(queue)->capacity = 3;
	(queue)->contents = (char * *) malloc(sizeof(char *) * 3);

    LIBERROR_MALLOC_FAILURE((queue)->contents, "(queue)->contents");
    LIBERROR_IS_NEGATIVE((queue)->capacity, "(queue)->capacity");
    LIBERROR_IS_NEGATIVE((queue)->head, "(queue)->head");
    LIBERROR_IS_NEGATIVE((queue)->length, "(queue)->length")
;

    
    
    LIBERROR_IS_NULL((queue), "(queue)");
    LIBERROR_IS_NULL((queue)->contents, "(queue)->contents");
    LIBERROR_IS_NEGATIVE((queue)->head, "(queue)->head");
    LIBERROR_IS_NEGATIVE((queue)->length, "(queue)->length");
    LIBERROR_IS_NEGATIVE((queue)->capacity, "(queue)->capacity")
;

	do {
        /* We start at the head of the queue because there might
           be items that were dequeued */
		int __M4_INDEX = (queue)->head;

		while(__M4_INDEX < ((queue)->length + (queue)->head)) {
            LIBERROR_IS_OOB(__M4_INDEX, ((queue)->length + (queue)->head));

			free((queue)->contents[__M4_INDEX]);

			__M4_INDEX++;
		}

        
    LIBERROR_IS_NULL((queue), "(queue)");
    LIBERROR_IS_NULL((queue)->contents, "(queue)->contents");
    LIBERROR_IS_NEGATIVE((queue)->head, "(queue)->head");
    LIBERROR_IS_NEGATIVE((queue)->length, "(queue)->length");
    LIBERROR_IS_NEGATIVE((queue)->capacity, "(queue)->capacity")
;

		free((queue)->contents);
		free((queue));
	} while(0)
;
}

int main() {
    test_free();

    return 0;
}
