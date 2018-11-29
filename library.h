#include <iostream>
#include <vector>
#include "member.h"
#include "resource.h"
using namespace std;

class library {
private:
	vector<book*> B;
	vector<magazine*> M;
	vector<e_book*> E;
	vector<undergraduate*> U;
	vector<graduate*> G;
	vector<faculty*> F;
public:
	library();
	void resource_data();
	string check(int cnt, int date, string r_type, string r_name, string op, string m_type, string m_name);
	void Update(int date, string m_type, string m_name, string r_type, string r_name, int op);
	bool is_registered(string name, string type);
	int DtoInt(string date);
	string DtoString(int date);
	void result();
	void print_resource();
	void print_member();
};