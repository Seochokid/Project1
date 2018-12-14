#include <iostream>
#include <string>
#include "resource.h"
using namespace std;

resource :: resource() {
	_name = "";
	_who_borrow = "";
	_borrow_date = 0;
}

void resource :: setName(string name) {
	_name = name;
}

string resource :: getName() {
	return _name;
}

void resource :: insert_borrow_inf(string who, int date) {
	_who_borrow = who;
	_borrow_date = date;
}

string resource :: get_who_borrow() {
	return _who_borrow;
}

int resource :: get_borrow_date() {
	return _borrow_date;
}

void resource :: del_borrow_inf() {
	_who_borrow = "";
	_borrow_date = 0;
}

book :: book() {
	setName("");
	del_borrow_inf();
}

book :: book(string name) {
	del_borrow_inf();
	setName(name);
}

magazine :: magazine() {
	setName("");
	del_borrow_inf();
}

magazine :: magazine(string name, int month) {
	setName(name);
	del_borrow_inf();
	_month = month;
	_year = 0;
	usable = false;
}

magazine :: magazine(string name, int month, int year) {
	setName(name);
	del_borrow_inf();
	_month = month;
	_year = year;
	usable = true;
}

int magazine :: get_month() {
	return _month;
}

void magazine :: set_year(int year) {
	_year = year;
}

int magazine :: get_year() {
	return _year;
}

string magazine :: getName() {
	string res = resource::getName();

	string year = "";
	if(to_string(_year).length() == 1) year = "0"+to_string(_year);
	else year = to_string(_year);

	string month = "";
	if(to_string(_month).length() == 1) month = "0"+to_string(_month);
	else month = to_string(_month);

	res+="["+year+"/"+month+"]";
	return res;
}

bool magazine :: get_usable() {
	return usable;
}

void magazine :: set_usable(bool b) {
	usable = b;
}

e_book :: e_book() {
	setName("");
}

e_book :: e_book(string e_b) {
	string name;
	int num = e_b.rfind('[');
	name.assign(e_b,0,num);
	setName(name);
	
	int size;
	int num1 = e_b.rfind('[');
	int num2 = e_b.rfind(']');
	string temp;
	temp.assign(e_b,num1+1,num2-num1+1);
	size = stoi(temp);
	_size = size;
}

int e_book :: get_size() {
	return _size;
}

void e_book :: insert_borrow_inf(string who, int date) {
	_borrow.insert(make_pair(who,date));
}

int e_book :: get_borrow_date(string who) {
	return _borrow.find(who)->second;
}

void e_book :: del_borrow_inf(string who) {
	_borrow.erase(who);
}
