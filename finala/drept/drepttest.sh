#!/bin/bash
g++ gen.cpp -o dreptgen
g++ drept.cpp -o drept
g++ dreptbrut.cpp -o dreptbrut
for i in {1..10}
do
    echo -n $i
 
    ./dreptgen
    echo -n "."

    ./drept
    echo -n "."

    ./dreptbrut
    echo -n "."

    if diff drept.out dreptbrut.out
    then
        echo "OK"
    else
        echo "FAIL"
        exit
    fi
done
