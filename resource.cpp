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

void resource :: insert_borrow_inf(string name, string who, int date) {
	_name = name;
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

}

book :: book(string name) {
	setName(name);
}

magazine :: magazine() {

}

magazine :: magazine(string name) {
	setName(name);
}

e_book :: e_book() {

}

e_book :: e_book(string name) {
	setName(name);
}