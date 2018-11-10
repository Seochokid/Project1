#include <iostream>
#include <string>
using namespace std;

class Space {
private:
    char state;     //U:use, A:away, N:notuse
    string who_borrow;
    int when_borrow;
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
    void set_Sroom(char in, string who, int when, int num, int many);
};

class Seat : public Space{
private:
    int floor;
public:
	Seat(int f);
    void set_Seat(char in, string who, int when, int f);
    bool isAble(int time);
};