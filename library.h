#include <iostream>
#include <vector>
#include "member.h"
#include "resource.h"
#include "space.h"
using namespace std;

class library {
private:
	vector<book*> B;
	vector<magazine*> M;
	vector<e_book*> E;
	vector<undergraduate*> U;
	vector<graduate*> G;
	vector<faculty*> F;

	vector<Study_room*> srooms;
	vector<Seat*> seats;

	int today;
public:
	library();
	void resource_data();
	string check(int cnt, int date, string r_type, string r_name, string op, string m_type, string m_name);
	string check2(int cnt, int s_date, string s_type, int s_num, string s_op, string sm_type, string sm_name, int sm_num, int s_time, int hour);
	void Update(int date, string m_type, string m_name, string r_type, string r_name, int op);
	bool is_registered(string name, string type);
	int DtoInt(string date);
	string DtoString(int date);
	int DtoHour(string date);
	void result();
	void print_resource();
	void print_member();
	void refresh(int day);
};