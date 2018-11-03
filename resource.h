#include <iostream>
#include <string>
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
	void insert_borrow_inf(string name, string who, int date);
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

public:
	magazine();
	magazine(string name);
};

class e_book : public resource{
private:

public:
	e_book();
	e_book(string name);
};
