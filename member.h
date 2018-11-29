#include <iostream>
#include <string>
#include <map>
using namespace std;

class member {
private:
	string _name;
	map<string, int> _borrow;
	int _restrict_date;
	int _capacity;
public:
	member();
	void set_member(string name);
	string get_member();
	int get_borrow_num();
	int get_borrow_date(string res);
	int get_restrict_date();
	void set_restrict_date(int date);
	bool get_borrow_fact(string res);
	void insert_borrow(string res, int date);
	void delete_borrow(string res);
	void set_capacity(int cap);
	int get_capacity();
	map<string,int> get_map();
};

class undergraduate : public member{
private:

public:
	undergraduate();
	undergraduate(string name);
	undergraduate(string name, string res, int date);

};

class graduate : public member{
private:

public:
	graduate();
	graduate(string name);
	graduate(string name, string res, int date);
};

class faculty : public member{
private:

public:
	faculty();
	faculty(string name);
	faculty(string name, string res, int date);
};
