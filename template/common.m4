include(src/m4queue.m4)

M4QUEUE_DECLARE(IntQueue, int);
M4QUEUE_DECLARE(StringQueue, char *);

define(`STRING_QUEUE_TYPE', `char *')
define(`STRING_QUEUE_FREE', `free($1)')
define(`STRING_QUEUE_NAME', `struct StringQueue')

/* This queue is used for testing memory reuse (hence
   the "RE" */
define(`STRING_QUEUE_RE_TYPE', `char *')
define(`STRING_QUEUE_RE_FREE', `free($1)')
define(`STRING_QUEUE_RE_NAME', `struct StringQueue')
define(`STRING_QUEUE_RE_REUSE', `($1)[0] = 0x0; strcat($1, $2)')

define(`INT_QUEUE_TYPE', `int')
define(`INT_QUEUE_FREE', `')
define(`INT_QUEUE_NAME', `struct IntQueue')
