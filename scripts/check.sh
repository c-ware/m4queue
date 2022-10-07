#!/bin/sh
# Run checks

echo Running test tests/init
$1 tests/init
echo Ran test tests/init

echo Running test tests/free
$1 tests/free
echo Ran test tests/free

echo Running test tests/enqueue
$1 tests/enqueue
echo Ran test tests/enqueue

echo Running test tests/dequeue
$1 tests/dequeue
echo Ran test tests/dequeue

echo Running test tests/peek
$1 tests/peek
echo Ran test tests/peek

echo Running test tests/is_empty
$1 tests/is_empty
echo Ran test tests/is_empty

echo Running test tests/length
$1 tests/length
echo Ran test tests/length

echo Running test tests/addremov
$1 tests/addremov
echo Ran test tests/addremov
