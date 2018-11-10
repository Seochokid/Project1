#include <iostream>
#include <string>
#include "space.h"
using namespace std;

Space :: Space() {
    char state = 'N';
    string who_borrow = "";
    int when_borrow = 0;
}

void Space :: set_state(char in) {
    state = in;
}

void Space :: set_borrow(string who, int when) {
    who_borrow = who;
    when_borrow = when;
}

char Space :: get_state() {
    return state;
}

string Space :: get_who() {
    return who_borrow;
}

int Space :: get_when() {
    return when_borrow;
}

Study_room :: Study_room(int num, int many) {
    room_num = num;
    how_many = many;
}

void Study_room :: set_Sroom(char in, string who, int when, int num, int many) {
    set_state(in);
    set_borrow(who, when);
    room_num = num;
    how_many = many;
}

Seat :: Seat(int f) {
    floor = f;
}

void Seat :: set_Seat(char in, string who, int when, int f) {
    set_state(in);
    set_borrow(who, when);
    floor = f;
}

bool Seat :: isAble(int time) {
    switch(floor) {
        case 1: 
            return true;
        case 2:
            if(time>=9 && time<=21) return true;
            else return false;
        case 3:
            if(time>=9 && time<=18) return true;
            else return false;
        default:
            cout << "isAble error" << endl; 
            return false;
    }
}