#include <iostream>
#include <string>
#include <map>
using namespace std;

class resource {
private:
	string _name;
	string _who_borrow;
	int _borrow_date;

public:
	resource();
	void setName(string name);
	string getName();
	void insert_borrow_inf(string who, int date);
	string get_who_borrow();
	int get_borrow_date();
	void del_borrow_inf();
};

class book : public resource{
private:

public:
	book();
	book(string name);
};

class magazine : public resource{
private:
	int _year;
	int _month;
	bool usable;
public:
	magazine();
	magazine(string name, int month);
	magazine(string name, int month, int year);
	int get_month();
	void set_year(int year);
	int get_year();
	string getName();
	bool get_usable();
	void set_usable(bool b);
};

class e_book : public resource{
private:
	map<string, int> _borrow;
	int _size;
public:
	e_book();
	e_book(string e_b);
	int get_size();
	void insert_borrow_inf(string who, int date);
	int get_borrow_date(string who);
	void del_borrow_inf(string who);
};
