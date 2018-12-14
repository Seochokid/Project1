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
    when_return = when;
}

char Space :: get_state() {
    return state;
}

string Space :: get_who() {
    return who_borrow;
}

int Space :: get_when() {
    return when_return;
}

Study_room :: Study_room(int num, int many) {
    set_state('N');
    set_borrow("", 0);
    room_num = num;
    how_many = many;
}

void Study_room :: set_Sroom(char in, string who, int when, int many) {
    set_state(in);
    set_borrow(who, when);
    how_many = many;
}

int Study_room :: get_roomNum() {
    return room_num;
}

Seat :: Seat(int f, int num, int come) {
    set_state('N');
    set_borrow("", 0);
    floor = f;
    seat_num = num;
    when_come = come;
}

void Seat :: set_Seat(char in, string who, int when, int come) {
    set_state(in);
    set_borrow(who, when);
    when_come = come;
}

void Seat :: set_come(int come) {
    when_come = come;
}
int Seat :: get_come() {
    return when_come;
}

int Seat :: get_floor() {
    return floor;
}