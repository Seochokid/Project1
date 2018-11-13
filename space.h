#include <iostream>
#include <string>
using namespace std;

class Space {
private:
    char state;     //U:use, A:away, N:notuse
    string who_borrow;
    int when_return;
public:
	Space();
    void set_state(char in);
    void set_borrow(string who, int when);
    char get_state();
    string get_who();
    int get_when();
};

class Study_room : public Space{
private:
    int room_num;
    int how_many;
public:
	Study_room(int num, int many);
    void set_Sroom(char in, string who, int when, int many);
    int get_roomNum();
};

class Seat : public Space{
private:
    int floor;
    int seat_num;
    int when_come;
public:
	Seat(int f, int num, int come);
    void set_Seat(char in, string who, int when, int come);
    void set_come(int come);
    int get_come();
    int get_floor();
};