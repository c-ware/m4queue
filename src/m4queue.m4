dnl C-Ware License
dnl 
dnl Copyright (c) 2022, C-Ware
dnl All rights reserved.
dnl 
dnl Redistribution and use in source and binary forms, with or without
dnl modification, are permitted provided that the following conditions are met:
dnl 
dnl 1. Redistributions of source code must retain the above copyright notice, this
dnl    list of conditions and the following disclaimer.
dnl 
dnl 2. Redistributions in binary form must reproduce the above copyright notice,
dnl    this list of conditions and the following disclaimer in the documentation
dnl    and/or other materials provided with the distribution.
dnl 
dnl 3. Redistributions of modified source code must append a copyright notice in
dnl    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
dnl    copyright notice, and the standalone license file if one exists.
dnl 
dnl A "redistribution" can be constituted as any version of the source code
dnl that is intended to comprise some other derivative work of this code. A
dnl fork created for the purpose of contributing to any version of the source
dnl does not constitute a truly "derivative work" and does not require listing.
dnl 
dnl THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
dnl AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
dnl IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
dnl DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
dnl FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
dnl DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
dnl SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
dnl CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
dnl OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
dnl OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

dnl @docgen_start
dnl @type: project
dnl @name: m4queue
dnl @brief: an implementation of a queue in m4
dnl
dnl @include: m4queue/m4queue.m4
dnl
dnl @description
dnl @An implementation of a queue in m4. This is a rather basic queue
dnl @implementation with an important optimization applied, which is
dnl @the addition of a "head" pointer.
dnl @
dnl @The queue provides all basic operations one might expect from a
dnl @queue, like dequeueing, enqueueing, and peeking. It is type safe,
dnl @and highly portable. It has shown to compile on the following
dnl @operating systems, including those with K&R compilers!
dnl @   - FreeBSD 13.1
dnl @   - NetBSD 9.3
dnl @   - OpenBSD 7.1
dnl @   - OpenSolaris 10
dnl @   - ULTRIX 4.5
dnl @   - QuasijarusBSD 4.3
dnl @   - OS/2 4.52 Warp
dnl @   - DragonflyBSD 6.2.1
dnl @   - NeXTSTEP 4.2
dnl @   - UNIXWare 7.1.4
dnl @
dnl @Since this is an \Bm4\B(cware) implementation, it is recommended that
dnl @you \Ipreprocess\I your code with m4 \Bbefore\B shipping it, which will
dnl @also allow your code to be more portable, since not all operating systems
dnl @have an m4 implementation. For a larger introduction into how m4queue works,
dnl @and how to use it, please see \Bm4queue-intro\B.
dnl @
dnl @\BList of operations\B
dnl @\T
dnl @\S ;
dnl @\H Manual;Description
dnl @\E M4QUEUE_INIT(cware);initialize a new queue
dnl @\E M4QUEUE_ENQUEUE(cware);add to the queue
dnl @\E M4QUEUE_DEQUEUE(cware);remove the front element of the queue
dnl @\E M4QUEUE_IS_EMPTY(cware);determine if the queue is empty
dnl @\E M4QUEUE_LENGTH(cware);evaluate to the length of the queue
dnl @\E M4QUEUE_PEEK(cware);get the front element without removing it
dnl @\E M4QUEUE_DECLARE(cware);declare a new queue structure
dnl @\E M4QUEUE_FREE(cware);release the queue from memory
dnl @\T
dnl @description
dnl
dnl @examples
dnl @examples
dnl
dnl @reference: cware(cware)
dnl @reference: m4queue-intro(cware)
dnl
dnl @docgen_end

#include <stdio.h>
#include <assert.h>
#include <string.h>

dnl ==============================
dnl # M4queue portability macros #
dnl ==============================

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

dnl ========================================
dnl	# M4queue utility, and internal macros #
dnl ========================================

define(`M4QUEUE_INITIAL_LENGTH', `3')
define(`M4QUEUE_NEXT_SIZE', `(($1)->capacity * 2)')

dnl Verify that a queue object is not in an
dnl invalid state.
define(`M4QUEUE_VERIFY', `
    LIBERROR_IS_NULL(($1), "($1)");
    LIBERROR_IS_NULL(($1)->contents, "($1)->contents");
    LIBERROR_IS_NEGATIVE(($1)->head, "($1)->head");
    LIBERROR_IS_NEGATIVE(($1)->length, "($1)->length");
    LIBERROR_IS_NEGATIVE(($1)->capacity, "($1)->capacity")
')

define(`__M4QUEUE_RESIZE', `
do {
    M4QUEUE_VERIFY($1);

	if((($1)->length) == (($1)->capacity)) {
		($1)->contents = ($2_TYPE *) realloc(($1)->contents, sizeof($2_TYPE) * M4QUEUE_NEXT_SIZE($1));
		($1)->capacity = M4QUEUE_NEXT_SIZE($1);

        LIBERROR_MALLOC_FAILURE(($1)->contents, "($1)->contents");
        LIBERROR_IS_NEGATIVE(($1)->capacity, "($1)->capacity");
	}
} while(0)
')

dnl ======================
dnl	# M4queue operations #
dnl ======================

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_DECLARE
dnl @brief: declare a new queue structure
dnl
dnl @include: m4queue/m4queue.m4
dnl 
dnl @description
dnl @This will declare a new queue structure of a certain name.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4queue\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: the name of the structure
dnl
dnl @param: 2
dnl @brief: the type of the queue
dnl
dnl @reference: m4queue(cware)
dnl
dnl @docgen_end
define(`M4QUEUE_DECLARE', `
    struct $1 {
        int head;
        int length;
        int capacity;

        $2 *contents;
    }
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_INIT
dnl @brief: initialize a new queue
dnl
dnl @include: m4queue/m4queue.m4
dnl 
dnl @description
dnl @This will initialize a new queue on the heap. The initial length will be judged
dnl @by M4QUEUE_INITIAL_LENGTH, and must be released from memory using \BM4QUEUE_FREE\B(cware)
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4queue\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the queue to initialize
dnl
dnl @param: 2
dnl @brief: namespace of the queue
dnl
dnl @reference: m4queue(cware)
dnl
dnl @docgen_end
define(`M4QUEUE_INIT', `
	($2_NAME *) malloc(sizeof(*($1)));

    LIBERROR_MALLOC_FAILURE(($1), "($1)");

	($1)->head = 0;
	($1)->length = 0;
	($1)->capacity = M4QUEUE_INITIAL_LENGTH;
	($1)->contents = ($2_TYPE *) malloc(sizeof($2_TYPE) * M4QUEUE_INITIAL_LENGTH);

    LIBERROR_MALLOC_FAILURE(($1)->contents, "($1)->contents");
    LIBERROR_IS_NEGATIVE(($1)->capacity, "($1)->capacity");
    LIBERROR_IS_NEGATIVE(($1)->head, "($1)->head");
    LIBERROR_IS_NEGATIVE(($1)->length, "($1)->length")
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_ENQUEUE
dnl @brief: add a new item to the queue
dnl
dnl @include: m4queue/m4queue.m4
dnl
dnl @description
dnl @This will add a new item to the back of the queue. It
dnl @description
dnl
dnl @param: 1
dnl @brief: pointer to the queue to enqueue into
dnl
dnl @param: 2
dnl @brief: value to enqueue
dnl
dnl @param: 3
dnl @brief: namespace of the queue
dnl
dnl @docgen_end
define(`M4QUEUE_ENQUEUE', `
    __M4QUEUE_RESIZE($1, $3);

    M4QUEUE_VERIFY($1);

    /* If the head pointer of the queue is not at the start when we
       want to add something, we need to push everything to the
       start of the queue. */
    if(($1)->head != 0) {
        int __M4_INDEX = ($1)->head;
        int __M4_CURSOR = 0;

        while(__M4_INDEX < (($1)->head + ($1)->length)) {
            ($1)->contents[__M4_CURSOR] = ($1)->contents[__M4_INDEX];

            __M4_INDEX++;
            __M4_CURSOR++;
        }
    }

    ($1)->contents[($1)->length] = ($2);
    ($1)->length = (($1)->length + 1);
    ($1)->head = 0
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_DEQUEUE
dnl @brief: add a new item to the queue
dnl
dnl @include: m4queue/m4queue.m4
dnl
dnl @description
dnl @Dequeue a value from the front of the queue, and write it into
dnl @a variable.
dnl @description
dnl
dnl @param: 1
dnl @brief: the queue to dequeue from
dnl
dnl @param: 2
dnl @brief: the variable to put the value in
dnl
dnl @param: 3
dnl @brief: the namespace of the queue
dnl 
dnl @docgen_end
define(`M4QUEUE_DEQUEUE', `
    M4QUEUE_VERIFY($1);

    /* Cannot dequeue from an empty array */
#if defined(LIBERROR_ENABLED)
    if(($1)->length == 0) {
       fprintf(LIBERROR_STREAM, "attempt to dequeue from an empty queue (%s:%i)\n", __FILE__, __LINE__);
        abort();
    }
#endif

    ($2) = ($1)->contents[($1)->head];
    ($1)->head++;    
    ($1)->length--;
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_FREE
dnl @brief: release a queue and its contents from memory
dnl 
dnl @include: m4queue/m4queue.m4
dnl
dnl @description
dnl @This macro will apply a free-macro for each element of the queue, and 
dnl @release the queue itself. The macro that will be called has the suffix
dnl @_FREE.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4queue\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the queue to release
dnl
dnl @param: 2
dnl @brief: the namespace of the queue
dnl
dnl @reference: m4queue(cware)
dnl
dnl @docgen_end
define(`M4QUEUE_FREE', `
    M4QUEUE_VERIFY($1);

	do {
        /* We start at the head of the queue because there might
           be items that were dequeued */
		int __M4_INDEX = ($1)->head;

		while(__M4_INDEX < (($1)->length + ($1)->head)) {
            LIBERROR_IS_OOB(__M4_INDEX, (($1)->length + ($1)->head));

			$2_FREE(($1)->contents[__M4_INDEX]);

			__M4_INDEX++;
		}

        M4QUEUE_VERIFY($1);

		free(($1)->contents);
		free(($1));
	} while(0)
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_PEEK
dnl @brief: get the value at the front of the queue
dnl 
dnl @include: m4queue/m4queue.m4
dnl
dnl @description
dnl @This macro will retrieve the value vat the front of the queue, writing
dnl @it into a variable.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4queue\B(cware)
dnl @examples
dnl
dnl @param: 1
dnl @brief: pointer to the queue to release
dnl
dnl @param: 2
dnl @brief: the variable to put the value into
dnl
dnl @reference: m4queue(cware)
dnl
dnl @docgen_end
define(`M4QUEUE_PEEK', `
    M4QUEUE_VERIFY($1);

    /* Cannot peek from an empty array */
#if defined(LIBERROR_ENABLED)
    if(($1)->length == 0) {
       fprintf(LIBERROR_STREAM, "attempt to peek from an empty queue (%s:%i)\n", __FILE__, __LINE__);
        abort();
    }
#endif

    ($2) = ($1)->contents[($1)->head]
')

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_IS_EMPTY
dnl @brief: determine whether or not the array is empty
dnl 
dnl @include: m4queue/m4queue.m4
dnl
dnl @description
dnl @This macro will evaluate to \B1\B if the queue is empty, and evaluates
dnl @to \B0\B if the queue is not empty.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4queue\B(cware)
dnl @examples
dnl
dnl @notes
dnl @This operation does NOT perform safety checks, even if they are enabled.
dnl @Make sure you perform them yourself.
dnl @notes
dnl
dnl @param: 1
dnl @brief: pointer to the queue to release
dnl
dnl @param: 2
dnl @brief: the variable to put the value into
dnl
dnl @reference: m4queue(cware)
dnl
dnl @docgen_end
define(`M4QUEUE_IS_EMPTY', `((($1)->length) == 0)')

dnl @docgen_start
dnl @type: macro
dnl @name: M4QUEUE_LENGTH
dnl @brief: determine the length of the queue
dnl 
dnl @include: m4queue/m4queue.m4
dnl
dnl @description
dnl @This macro will evaluate the length of the queue.
dnl @description
dnl
dnl @examples
dnl @For examples, please see the examples section in \Bm4queue\B(cware)
dnl @examples
dnl
dnl @notes
dnl @This operation does NOT perform safety checks, even if they are enabled.
dnl @Make sure you perform them yourself.
dnl @notes
dnl
dnl @param: 1
dnl @brief: pointer to the queue to release
dnl
dnl @param: 2
dnl @brief: the variable to put the value into
dnl
dnl @reference: m4queue(cware)
dnl
dnl @docgen_end
define(`M4QUEUE_LENGTH', `(($1)->length)')
