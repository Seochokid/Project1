#include <iostream>
#include <string>
#include <map>
#include "member.h"
using namespace std;

member :: member() {
	_name = "";
	_restrict_date = 0;
	_borrow.clear();
}

void member :: set_member(string name) {
	_name = name;
}

string member :: get_member() {
	return _name;
}

int member :: get_borrow_num() {
	return _borrow.size();
}

int member :: get_borrow_date(string res) {
	return _borrow.find(res)->second;
}

int member :: get_restrict_date() {
	return _restrict_date;
}

void member :: set_restrict_date(int date) {
	_restrict_date = date;
}

bool member :: get_borrow_fact(string res) {
	if(_borrow.find(res) == _borrow.end()) return false;
	else return true;
}

void member :: insert_borrow(string res, int date) {
	_borrow.insert(make_pair(res,date));
}

void member :: delete_borrow(string res) {
	_borrow.erase(res);
}

undergraduate :: undergraduate() {

}

undergraduate :: undergraduate(string name) {
	set_member(name);
}

undergraduate :: undergraduate(string name, string res, int date) {
	set_member(name);
	insert_borrow(res, date);
}

graduate :: graduate() {

}

graduate :: graduate(string name) {
	set_member(name);
}

graduate :: graduate(string name, string res, int date) {
	set_member(name);
	insert_borrow(res, date);
}

faculty :: faculty() {

}

faculty :: faculty(string name) {
	set_member(name);
}

faculty :: faculty(string name, string res, int date) {
	set_member(name);
	insert_borrow(res, date);
}