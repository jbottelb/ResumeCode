#!/bin/bash

PROGRAM=thor.py
WORKSPACE=/tmp/$(basename $PROGRAM).$(id -u)

STATICFILE=http://student01.cse.nd.edu:9433/song.txt 
DIRECTORIES=http://student01.cse.nd.edu:9433/
CGI=http://student01.cse.nd.edu:9433/scripts/cowsay.sh

echo "Directory Tests: "
for i in {1..10}
do
	./$PROGRAM -h 4 -t 10 $DIRECTORIES | grep -E "TOTAL"
done

echo "Static File Tests: "
for j in {1..10}
do
	./$PROGRAM -h 4 -t 10 $STATICFILE | grep -E "TOTAL"
done

echo "CGI Tests: "
for k in {1..10}
do
	./$PROGRAM -h 4 -t 10 $CGI | grep -E "TOTAL"
done

echo "THROUGHPUT TESTS"
echo "1KB: "
for l in {1..10}
do
	./$PROGRAM -h 2 -t 10 http://student01.cse.nd.edu:9433/testing/test1K.img | grep -E "TOTAL"
done

echo "1MB: "
for m in {1..10}
do
	./$PROGRAM -h 2 -t 10 http://student01.cse.nd.edu:9433/testing/test1M.img | grep -E "TOTAL"
done

echo "\n1GB: "
for n in {1..10}
do
	./$PROGRAM -h 2 -t 10 http://student01.cse.nd.edu:9433/testing/test1G.img | grep -E "TOTAL"
done
