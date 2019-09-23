#! /bin/bash

DIR=output/
if [ ! -d "$DIR" ]; then
    mkdir $DIR
fi
for i in 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16;
do
    echo Completing test $i
    ./sdriver.pl -t trace$i.txt -s ./tshref -a "-p" > $DIR/reftest$1
    ./sdriver.pl -t trace$i.txt -s ./tsh -a "-p" > $DIR/test$1
    diff $DIR/reftest$1 $DIR/test$1
done
