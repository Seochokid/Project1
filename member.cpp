#include <iostream>
#include <string>
#include <map>
#include "member.h"
using namespace std;

member :: member() {
	_name = "";
	_restrict_date = 0;
	_borrow.clear();
	_capacity = 0;
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

void member :: set_capacity(int cap) {
	_capacity = cap;
}

int member :: get_capacity() {
	return _capacity;
}

map<string,int> member :: get_map() {
	return _borrow;
}

void member :: del_bor_map(){
	_borrow.clear();
}

undergraduate :: undergraduate() {
	set_member("");
	set_restrict_date(0);
	del_bor_map();
	set_capacity(0);
}

undergraduate :: undergraduate(string name) {
	set_member(name);
	set_restrict_date(0);
	del_bor_map();
	set_capacity(0);
}

undergraduate :: undergraduate(string name, string res, int date) {
	set_member(name);
	del_bor_map();
	insert_borrow(res, date);
	set_restrict_date(0);
	set_capacity(0);
}

graduate :: graduate() {
	set_member("");
	set_restrict_date(0);
	del_bor_map();
	set_capacity(0);
}

graduate :: graduate(string name) {
	set_member(name);
	set_restrict_date(0);
	del_bor_map();
	set_capacity(0);
}

graduate :: graduate(string name, string res, int date) {
	set_member(name);
	del_bor_map();
	insert_borrow(res, date);
	set_restrict_date(0);
	set_capacity(0);
}

faculty :: faculty() {
	set_member("");
	set_restrict_date(0);
	del_bor_map();
	set_capacity(0);
}

faculty :: faculty(string name) {
	set_member(name);
	set_restrict_date(0);
	del_bor_map();
	set_capacity(0);
}

faculty :: faculty(string name, string res, int date) {
	set_member(name);
	del_bor_map();
	insert_borrow(res, date);
	set_restrict_date(0);
	set_capacity(0);
}
