#!/bin/sh
echo "Building starter"
gcc -o starter starter.c
echo "Building test program"
gcc -shared -o test.so test.c
echo "Running test program:\n"
./starter ./test.so
echo "\nDone!"
echo "Run ./starter -h for additional info"
