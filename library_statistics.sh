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
    mkdir -p ./result/input
    if [ $1 = "date" ]
    then
        from_year=`echo $2 | cut -d'/' -f1`
        from_month=`echo $2 | cut -d'/' -f2`
        from_day=`echo $2 | cut -d'/' -f3`
        to_year=`echo $3 | cut -d'/' -f1`
        to_month=`echo $3 | cut -d'/' -f2`
        to_day=`echo $3 | cut -d'/' -f3`
        read line < input.dat;
        echo "$line" > new_input.dat
        one=0
        while read A B C D E F || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            else
                input_year=`echo $A | cut -d'/' -f1`
                input_month=`echo $A | cut -d'/' -f2`
                input_day=`echo $A | cut -d'/' -f3`

                if [ $from_year -lt $input_year -a $input_year -lt $to_year ]
                then
                    echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                elif [ $from_year = $input_year -a $input_year -lt $to_year ]
                then
                    if [ $from_month -lt $input_month ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                    elif [ $from_month = $input_month ]
                    then
                        if [ $from_day -le $input_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                        fi
                    fi
                elif [ $from_year -lt $input_year -a $input_year = $to_year ]
                then
                    if [ $input_month -lt $to_month ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                    elif [ $input_month = $to_month ]
                    then
                        if [ $input_day -le $to_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                        fi
                    fi
                elif [ $from_year = $input_year -a $input_year = $to_year ]
                then
                    if [ $from_month -lt $input_month -a $input_month -lt $to_month ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                    elif [ $from_month = $input_month -a $input_month -lt $to_month ]
                    then
                        if [ $from_day -le $input_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                        fi
                    elif [ $from_month -lt $input_month -a $input_month = $to_month ]
                    then
                        if [ $input_day -le $to_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                        fi
                    elif [ $from_month = $input_month -a $input_month = $to_month ]
                    then
                        if [ $from_day -le $input_day -a $input_day -le $to_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
                        fi
                    fi
                fi
            fi
        done < input.dat
        rm input.dat
        cp new_input.dat input.dat
        ./library
        cp output.dat ./result/input/date.dat
        rm new_input.dat
        rm output.dat
        cp input.bak input.dat
    elif [ $1 = "book" ]
    then
        read line < input.dat;
        echo "$line" > new_input.dat
        one=0
        while read A B C D E F || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $B = "Book" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
            fi
        done < input.dat
        rm input.dat
        cp new_input.dat input.dat
        ./library
        cp output.dat ./result/input/book.dat
        rm new_input.dat
        rm output.dat
        cp input.bak input.dat
    elif [ $1 = "e-book" ]
    then
        read line < input.dat;
        echo "$line" > new_input.dat
        one=0
        while read A B C D E F || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $B = "E-book" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
            fi
        done < input.dat
        rm input.dat
        cp new_input.dat input.dat
        ./library
        cp output.dat ./result/input/e-book.dat
        rm new_input.dat
        rm output.dat
        cp input.bak input.dat
    elif [ $1 = "magazine" ]
    then
        read line < input.dat;
        echo "$line" > new_input.dat
        one=0
        while read A B C D E F || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $B = "Magazine" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
            fi
        done < input.dat
        rm input.dat
        cp new_input.dat input.dat
        ./library
        cp output.dat ./result/input/magazine.dat
        rm new_input.dat
        rm output.dat
        cp input.bak input.dat
    elif [ $1 = "undergraduate" ]
    then
        read line < input.dat;
        echo "$line" > new_input.dat
        one=0
        while read A B C D E F || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $E = "Undergraduate" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
            fi
        done < input.dat
        rm input.dat
        cp new_input.dat input.dat
        ./library
        cp output.dat ./result/input/undergraduate.dat
        rm new_input.dat
        rm output.dat
        cp input.bak input.dat
    elif [ $1 = "graduate" ]
    then
        read line < input.dat;
        echo "$line" > new_input.dat
        one=0
        while read A B C D E F || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $E = "Graduate" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
            fi
        done < input.dat
        rm input.dat
        cp new_input.dat input.dat
        ./library
        cp output.dat ./result/input/graduate.dat
        rm new_input.dat
        rm output.dat
        cp input.bak input.dat
    elif [ $1 = "faculty" ]
    then
        read line < input.dat;
        echo "$line" > new_input.dat
        one=0
        while read A B C D E F || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $E = "Faculty" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F" >> new_input.dat
            fi
        done < input.dat
        rm input.dat
        cp new_input.dat input.dat
        ./library
        cp output.dat ./result/input/faculty.dat
        rm new_input.dat
        rm output.dat
        cp input.bak input.dat
    elif [ $1 = "all" ]
    then
        input book
        input e-book
        input magazine
        input undergraduate
        input graduate
        input faculty
    else
        echo "parameter 2 error"
    fi
}

space() {  

}

output() {

}

mkdir -p result
make
main $1 $2 $3 $4
make clean