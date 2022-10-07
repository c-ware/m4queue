/*
 * Tests of both enqueuing and dequeueing
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










void test_mixed() {
    char *a = (char *) malloc(16);
    char *b = (char *) malloc(16);
    char *c = (char *) malloc(16);
    char *d = (char *) malloc(16);
    char *e = (char *) malloc(16);
    char *f = (char *) malloc(16);
    char *g = (char *) malloc(16);
    char *output = CWUTILS_NULL;
    struct StringQueue *my_queue = 
	(struct StringQueue *) malloc(sizeof(*(my_queue)));

    LIBERROR_MALLOC_FAILURE((my_queue), "(my_queue)");

	(my_queue)->head = 0;
	(my_queue)->length = 0;
	(my_queue)->capacity = 3;
	(my_queue)->contents = (char * *) malloc(sizeof(char *) * 3);

    LIBERROR_MALLOC_FAILURE((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length")
;

    strcpy(a, "foo");
    strcpy(b, "bar");
    strcpy(c, "baz");
    strcpy(d, "tuna");
    strcpy(e, "spam");
    strcpy(f, "thud");
    strcpy(g, "eggs");

    
    
do {
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

	if(((my_queue)->length) == ((my_queue)->capacity)) {
		(my_queue)->contents = (char * *) realloc((my_queue)->contents, sizeof(char *) * ((my_queue)->capacity * 2));
		(my_queue)->capacity = ((my_queue)->capacity * 2);

        LIBERROR_MALLOC_FAILURE((my_queue)->contents, "(my_queue)->contents");
        LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity");
	}
} while(0)
;

    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* If the head pointer of the queue is not at the start when we
       want to add something, we need to push everything to the
       start of the queue. */
    if((my_queue)->head != 0) {
        int __M4_INDEX = (my_queue)->head;
        int __M4_CURSOR = 0;

        while(__M4_INDEX < ((my_queue)->head + (my_queue)->length)) {
            (my_queue)->contents[__M4_CURSOR] = (my_queue)->contents[__M4_INDEX];

            __M4_INDEX++;
            __M4_CURSOR++;
        }
    }

    (my_queue)->contents[(my_queue)->length] = (a);
    (my_queue)->length = ((my_queue)->length + 1);
    (my_queue)->head = 0
;
    
    
do {
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

	if(((my_queue)->length) == ((my_queue)->capacity)) {
		(my_queue)->contents = (char * *) realloc((my_queue)->contents, sizeof(char *) * ((my_queue)->capacity * 2));
		(my_queue)->capacity = ((my_queue)->capacity * 2);

        LIBERROR_MALLOC_FAILURE((my_queue)->contents, "(my_queue)->contents");
        LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity");
	}
} while(0)
;

    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* If the head pointer of the queue is not at the start when we
       want to add something, we need to push everything to the
       start of the queue. */
    if((my_queue)->head != 0) {
        int __M4_INDEX = (my_queue)->head;
        int __M4_CURSOR = 0;

        while(__M4_INDEX < ((my_queue)->head + (my_queue)->length)) {
            (my_queue)->contents[__M4_CURSOR] = (my_queue)->contents[__M4_INDEX];

            __M4_INDEX++;
            __M4_CURSOR++;
        }
    }

    (my_queue)->contents[(my_queue)->length] = (b);
    (my_queue)->length = ((my_queue)->length + 1);
    (my_queue)->head = 0
;
    
    
do {
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

	if(((my_queue)->length) == ((my_queue)->capacity)) {
		(my_queue)->contents = (char * *) realloc((my_queue)->contents, sizeof(char *) * ((my_queue)->capacity * 2));
		(my_queue)->capacity = ((my_queue)->capacity * 2);

        LIBERROR_MALLOC_FAILURE((my_queue)->contents, "(my_queue)->contents");
        LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity");
	}
} while(0)
;

    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* If the head pointer of the queue is not at the start when we
       want to add something, we need to push everything to the
       start of the queue. */
    if((my_queue)->head != 0) {
        int __M4_INDEX = (my_queue)->head;
        int __M4_CURSOR = 0;

        while(__M4_INDEX < ((my_queue)->head + (my_queue)->length)) {
            (my_queue)->contents[__M4_CURSOR] = (my_queue)->contents[__M4_INDEX];

            __M4_INDEX++;
            __M4_CURSOR++;
        }
    }

    (my_queue)->contents[(my_queue)->length] = (c);
    (my_queue)->length = ((my_queue)->length + 1);
    (my_queue)->head = 0
;

    ASSERT_NUMEQ(my_queue->length, 3);
    ASSERT_NUMEQ(my_queue->head, 0);
    ASSERT_NUMEQ(my_queue->capacity, 3);
    ASSERT_STREQ(my_queue->contents[0], "foo");
    ASSERT_STREQ(my_queue->contents[1], "bar");
    ASSERT_STREQ(my_queue->contents[2], "baz");

    
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* Cannot dequeue from an empty array */
#if defined(LIBERROR_ENABLED)
    if((my_queue)->length == 0) {
       fprintf(LIBERROR_STREAM, "attempt to dequeue from an empty queue (%s:%i)\n", __FILE__, __LINE__);
        abort();
    }
#endif

    (output) = (my_queue)->contents[(my_queue)->head];
    (my_queue)->head++;    
    (my_queue)->length--;
;

    ASSERT_NUMEQ(my_queue->length, 2);
    ASSERT_NUMEQ(my_queue->head, 1);
    ASSERT_NUMEQ(my_queue->capacity, 3);
    ASSERT_STREQ(my_queue->contents[0], "foo");
    ASSERT_STREQ(my_queue->contents[1], "bar");

    
    
do {
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

	if(((my_queue)->length) == ((my_queue)->capacity)) {
		(my_queue)->contents = (char * *) realloc((my_queue)->contents, sizeof(char *) * ((my_queue)->capacity * 2));
		(my_queue)->capacity = ((my_queue)->capacity * 2);

        LIBERROR_MALLOC_FAILURE((my_queue)->contents, "(my_queue)->contents");
        LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity");
	}
} while(0)
;

    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* If the head pointer of the queue is not at the start when we
       want to add something, we need to push everything to the
       start of the queue. */
    if((my_queue)->head != 0) {
        int __M4_INDEX = (my_queue)->head;
        int __M4_CURSOR = 0;

        while(__M4_INDEX < ((my_queue)->head + (my_queue)->length)) {
            (my_queue)->contents[__M4_CURSOR] = (my_queue)->contents[__M4_INDEX];

            __M4_INDEX++;
            __M4_CURSOR++;
        }
    }

    (my_queue)->contents[(my_queue)->length] = (d);
    (my_queue)->length = ((my_queue)->length + 1);
    (my_queue)->head = 0
;

    ASSERT_NUMEQ(my_queue->length, 3);
    ASSERT_NUMEQ(my_queue->head, 0);
    ASSERT_NUMEQ(my_queue->capacity, 3);
    ASSERT_STREQ(my_queue->contents[0], "bar");
    ASSERT_STREQ(my_queue->contents[1], "baz");
    ASSERT_STREQ(my_queue->contents[2], "tuna");

    
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* Cannot dequeue from an empty array */
#if defined(LIBERROR_ENABLED)
    if((my_queue)->length == 0) {
       fprintf(LIBERROR_STREAM, "attempt to dequeue from an empty queue (%s:%i)\n", __FILE__, __LINE__);
        abort();
    }
#endif

    (output) = (my_queue)->contents[(my_queue)->head];
    (my_queue)->head++;    
    (my_queue)->length--;
;
    
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* Cannot dequeue from an empty array */
#if defined(LIBERROR_ENABLED)
    if((my_queue)->length == 0) {
       fprintf(LIBERROR_STREAM, "attempt to dequeue from an empty queue (%s:%i)\n", __FILE__, __LINE__);
        abort();
    }
#endif

    (output) = (my_queue)->contents[(my_queue)->head];
    (my_queue)->head++;    
    (my_queue)->length--;
;
    
    
do {
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

	if(((my_queue)->length) == ((my_queue)->capacity)) {
		(my_queue)->contents = (char * *) realloc((my_queue)->contents, sizeof(char *) * ((my_queue)->capacity * 2));
		(my_queue)->capacity = ((my_queue)->capacity * 2);

        LIBERROR_MALLOC_FAILURE((my_queue)->contents, "(my_queue)->contents");
        LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity");
	}
} while(0)
;

    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* If the head pointer of the queue is not at the start when we
       want to add something, we need to push everything to the
       start of the queue. */
    if((my_queue)->head != 0) {
        int __M4_INDEX = (my_queue)->head;
        int __M4_CURSOR = 0;

        while(__M4_INDEX < ((my_queue)->head + (my_queue)->length)) {
            (my_queue)->contents[__M4_CURSOR] = (my_queue)->contents[__M4_INDEX];

            __M4_INDEX++;
            __M4_CURSOR++;
        }
    }

    (my_queue)->contents[(my_queue)->length] = (a);
    (my_queue)->length = ((my_queue)->length + 1);
    (my_queue)->head = 0
;
    
    
do {
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

	if(((my_queue)->length) == ((my_queue)->capacity)) {
		(my_queue)->contents = (char * *) realloc((my_queue)->contents, sizeof(char *) * ((my_queue)->capacity * 2));
		(my_queue)->capacity = ((my_queue)->capacity * 2);

        LIBERROR_MALLOC_FAILURE((my_queue)->contents, "(my_queue)->contents");
        LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity");
	}
} while(0)
;

    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

    /* If the head pointer of the queue is not at the start when we
       want to add something, we need to push everything to the
       start of the queue. */
    if((my_queue)->head != 0) {
        int __M4_INDEX = (my_queue)->head;
        int __M4_CURSOR = 0;

        while(__M4_INDEX < ((my_queue)->head + (my_queue)->length)) {
            (my_queue)->contents[__M4_CURSOR] = (my_queue)->contents[__M4_INDEX];

            __M4_INDEX++;
            __M4_CURSOR++;
        }
    }

    (my_queue)->contents[(my_queue)->length] = (b);
    (my_queue)->length = ((my_queue)->length + 1);
    (my_queue)->head = 0
;

    ASSERT_NUMEQ(my_queue->length, 3);
    ASSERT_NUMEQ(my_queue->head, 0);
    ASSERT_NUMEQ(my_queue->capacity, 3);
    ASSERT_STREQ(my_queue->contents[0], "tuna");
    ASSERT_STREQ(my_queue->contents[1], "foo");
    ASSERT_STREQ(my_queue->contents[2], "bar");

    
    
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

	do {
        /* We start at the head of the queue because there might
           be items that were dequeued */
		int __M4_INDEX = (my_queue)->head;

		while(__M4_INDEX < ((my_queue)->length + (my_queue)->head)) {
            LIBERROR_IS_OOB(__M4_INDEX, ((my_queue)->length + (my_queue)->head));

			free((my_queue)->contents[__M4_INDEX]);

			__M4_INDEX++;
		}

        
    LIBERROR_IS_NULL((my_queue), "(my_queue)");
    LIBERROR_IS_NULL((my_queue)->contents, "(my_queue)->contents");
    LIBERROR_IS_NEGATIVE((my_queue)->head, "(my_queue)->head");
    LIBERROR_IS_NEGATIVE((my_queue)->length, "(my_queue)->length");
    LIBERROR_IS_NEGATIVE((my_queue)->capacity, "(my_queue)->capacity")
;

		free((my_queue)->contents);
		free((my_queue));
	} while(0)
;
}

int main() {
    test_mixed();

    return 0;
}
