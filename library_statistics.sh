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
    mkdir -p ./result/resource
    if [ $1 = "book" ]
    then
        read line < resource.dat;
        echo "$line" > ./result/resource/book.dat
        one=0
        while read T N || [ -n "$T" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $T = "Book" ]
            then
                echo -e "$T\t$N" >> ./result/resource/book.dat
            fi
        done < resource.dat
    elif [ $1 = "e-book" ]
    then
        read line < resource.dat;
        echo "$line" > ./result/resource/e-book.dat
        one=0
        while read T N || [ -n "$T" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $T = "E-book" ]
            then
                echo -e "$T\t$N" >> ./result/resource/e-book.dat
            fi
        done < resource.dat
    elif [ $1 = "magazine" ]
    then
        read line < resource.dat;
        echo "$line" > ./result/resource/magazine.dat
        one=0
        while read T N || [ -n "$T" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $T = "Magazine" ]
            then
                echo -e "$T\t$N" >> ./result/resource/magazine.dat
            fi
        done < resource.dat
    elif [ $1 = "all" ]
    then
        resource book
        resource e-book
        resource magazine
    else
        echo "parameter 2 error"
    fi
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