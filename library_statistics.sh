#!/bin/bash

main() {
    if [ $1 = "resource" ]
    then
        resource $2
    elif [ $1 = "input" ]
    then
        cp space.dat space.bak
        cp input.dat input.bak
        rm space.dat
        input $2 $3 $4
        cp space.bak space.dat
        rm space.bak
        rm input.bak
        ./library
    elif [ $1 = "space" ]
    then
        cp space.dat space.bak
        cp input.dat input.bak
        rm input.dat
        space $2 $3 $4
        cp input.bak input.dat
        rm space.bak
        rm input.bak
        ./library
    elif [ $1 = "output" ]
    then
        ./library
        output $2
    elif [ $1 = "all" ]
    then
        main resource all
        main input all
        main space all
        main output stat_table
    else
        echo "parameter 1 error"
    fi
}

resource() {

}

input() {

}

space() {  

}

output() {

}

mkdir -p result
make
main $1 $2 $3 $4
make clean