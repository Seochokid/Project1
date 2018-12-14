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
    mkdir -p ./result/space
    if [ $1 = "date" ]
    then
        from_year=`echo $2 | cut -d'/' -f1`
        from_month=`echo $2 | cut -d'/' -f2`
        from_day=`echo $2 | cut -d'/' -f3`
        from_hour=`echo $2 | cut -d'/' -f4`
        to_year=`echo $3 | cut -d'/' -f1`
        to_month=`echo $3 | cut -d'/' -f2`
        to_day=`echo $3 | cut -d'/' -f3`
        to_hour=`echo $3 | cut -d'/' -f4`
        read line < space.dat;
        echo "$line" > new_space.dat
        one=0
        while read A B C D E F G H || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            else
                input_year=`echo $A | cut -d'/' -f1`
                ((input_year-=2000))
                input_month=`echo $A | cut -d'/' -f2`
                input_day=`echo $A | cut -d'/' -f3`
                input_hour=`echo $A | cut -d'/' -f4`

                if [ $from_year -lt $input_year -a $input_year -lt $to_year ]
                then
                    echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                elif [ $from_year = $input_year -a $input_year -lt $to_year ]
                then
                    if [ $from_month -lt $input_month ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                    elif [ $from_month = $input_month ]
                    then
                        if [ $from_day -lt $input_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                        elif [ $from_day = $input_day ]
                        then
                            if [ $from_hour -le $input_hour ]
                            then
                                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                            fi
                        fi
                    fi
                elif [ $from_year -lt $input_year -a $input_year = $to_year ]
                then
                    if [ $input_month -lt $to_month ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                    elif [ $input_month = $to_month ]
                    then
                        if [ $input_day -lt $to_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                        elif [ $input_day = $to_day ]
                        then
                            if [ $input_hour -le $to_hour ]
                            then
                                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                            fi
                        fi
                    fi
                elif [ $from_year = $input_year -a $input_year = $to_year ]
                then
                    if [ $from_month -lt $input_month -a $input_month -lt $to_month ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                    elif [ $from_month = $input_month -a $input_month -lt $to_month ]
                    then
                        if [ $from_day -lt $input_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                        elif [ $from_day = $input_day ]
                        then
                            if [ $from_hour -le $input_hour ]
                            then
                                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                            fi
                        fi
                    elif [ $from_month -lt $input_month -a $input_month = $to_month ]
                    then
                        if [ $input_day -lt $to_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                        elif [ $input_day = $to_day ]
                        then
                            if [ $input_hour -le $to_hour ]
                            then
                                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                            fi
                        fi
                    elif [ $from_month = $input_month -a $input_month = $to_month ]
                    then
                        if [ $from_day -lt $input_day -a $input_day -lt $to_day ]
                        then
                            echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                        elif [ $from_day = $input_day -a $input_day -lt $to_day ]
                        then
                            if [ $from_hour -le $input_hour ]
                            then
                                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                            fi
                        elif [ $from_day -lt $input_day -a $input_day = $to_day ]
                        then
                            if [ $input_hour -le $to_hour ]
                            then
                                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                            fi
                        elif [ $from_day = $input_day -a $input_day = $to_day ]
                        then
                            if [ $from_hour -le $input_hour -a $input_hour -le $to_hour ]
                            then
                                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                            fi
                        fi
                    fi
                fi
            fi
        done < space.dat
        rm space.dat
        cp new_space.dat space.dat
        ./library
        cp output.dat ./result/space/date.dat
        rm new_space.dat
        rm output.dat
        cp space.bak space.dat
    elif [ $1 = "studyroom" ]
    then
        read line < space.dat;
        echo "$line" > new_space.dat
        one=0
        while read A B C D E F G H || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $B = "StudyRoom" ]
            then
                if [ $2 = "all" ]
                then
                    echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                elif [ 1 -le $2 -a $2 -le 10 ]
                then
                    if [ $C = $2 ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                    fi
                else
                    echo "parameter 3 error"
                fi
            fi
        done < space.dat
        rm space.dat
        cp new_space.dat space.dat
        ./library
        cp output.dat ./result/space/studyroom.dat
        rm new_space.dat
        rm output.dat
        cp space.bak space.dat
    elif [ $1 = "seat" ]
    then
        read line < space.dat;
        echo "$line" > new_space.dat
        one=0
        while read A B C D E F G H || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $B = "Seat" ]
            then
                if [ $2 = "all" ]
                then
                    echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                elif [ 1 -le $2 -a $2 -le 3 ]
                then
                    if [ $C = $2 ]
                    then
                        echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
                    fi
                else
                    echo "parameter 3 error"
                fi
            fi
        done < space.dat
        rm space.dat
        cp new_space.dat space.dat
        ./library
        cp output.dat ./result/space/seat.dat
        rm new_space.dat
        rm output.dat
        cp space.bak space.dat
    elif [ $1 = "undergraduate" ]
    then
        read line < space.dat;
        echo "$line" > new_space.dat
        one=0
        while read A B C D E F G H || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $E = "Undergraduate" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
            fi
        done < space.dat
        rm space.dat
        cp new_space.dat space.dat
        ./library
        cp output.dat ./result/space/undergraduate.dat
        rm new_space.dat
        rm output.dat
        cp space.bak space.dat
    elif [ $1 = "graduate" ]
    then
        read line < space.dat;
        echo "$line" > new_space.dat
        one=0
        while read A B C D E F G H || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $E = "Graduate" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
            fi
        done < space.dat
        rm space.dat
        cp new_space.dat space.dat
        ./library
        cp output.dat ./result/space/graduate.dat
        rm new_space.dat
        rm output.dat
        cp space.bak space.dat
    elif [ $1 = "faculty" ]
    then
        read line < space.dat;
        echo "$line" > new_space.dat
        one=0
        while read A B C D E F G H || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            elif [ $E = "Faculty" ]
            then
                echo -e "$A\t$B\t$C\t$D\t$E\t$F\t$G\t$H" >> new_space.dat
            fi
        done < space.dat
        rm space.dat
        cp new_space.dat space.dat
        ./library
        cp output.dat ./result/space/faculty.dat
        rm new_space.dat
        rm output.dat
        cp space.bak space.dat
    elif [ $1 = "all" ]
    then
        space studyroom all
        space seat all
        space undergraduate
        space graduate
        space faculty
    else
        echo "parameter 2 error"
    fi
}

output() {
    mkdir -p ./result/output
    if [ $1 = "stat_table" ]
    then
        read line < output.dat;
        echo -e "Return_code\tNumber" > ./result/output/stat_table.dat
        r_code=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)

        one=0
        while read A B C || [ -n "$A" ];
        do
            if [ $one = 0 ]
            then
                ((one++))
            else
                if [ $B = -1 ]
                then
                    ((r_code[17]++))
                else
                    ((r_code[$B]++))
                fi
            fi
        done < output.dat
        one=-1
        for (( i = 0 ; i < ${#r_code[@]} ; i++ )); do
            if [ $i = 17 ]
            then
                echo -e "-1\t${r_code[$i]}" >> ./result/output/stat_table.dat
            else echo -e "$i\t${r_code[$i]}" >> ./result/output/stat_table.dat
            fi
        done
    else
        echo "parameter 2 error"
    fi
}

mkdir -p result
make
main $1 $2 $3 $4
make clean