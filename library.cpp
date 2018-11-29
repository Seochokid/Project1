#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "library.h"

using namespace std;

library :: library() {
	resource_data();
	result();
	int num = B.size();
	for(int i = 0; i < num; i++) {
		delete B.back();
		B.pop_back();
	}
	num = M.size();
	for(int i = 0; i < num; i++) {
		delete M.back();
		M.pop_back();
	}
	num = E.size();
	for(int i = 0; i < num; i++) {
		delete E.back();
		E.pop_back();
	}
}

void library :: resource_data() {
	ifstream fin("resource.dat");
	string dummy, type, name;
	fin >> dummy;
	fin >> dummy;
	while(fin >> type) {
		if(type == "Book") {
			fin >> name;
			book* input = new book(name);
			B.push_back(input);
		} else if(type == "Magazine") {
			fin >> name;
			for(int i = 1; i <= 12; i++) {
				magazine* input = new magazine(name, i);
				M.push_back(input);
			}
		} else if(type == "E-book") {
			fin >> name;
			e_book* input = new e_book(name);
			E.push_back(input);
		} else {
			cout << "Type not provided" << endl;
		}
	}
}

string library :: check(int cnt, int date, string r_type, string r_name, string op, string m_type, string m_name) {
	//Magazine update
	int y, m ,d;
	y = date/360;
	m = ((date%360)/30);
	if(((date%360)%30) == 0) d = 30;
	else d = ((date%360)%30);

	for(auto s : M) {
		if(s->get_year() == 0) {
			if(s->get_month()>m) {
				s->set_year(y-1);
				s->set_usable(true);
			} else {
				s->set_year(y);
				s->set_usable(true);
			}
		} else {
			if(s->get_usable()) {
				if(s->get_who_borrow() == "") {
					if(s->get_month()>m) {
						s->set_year(y-1);
						s->set_usable(true);
					} else {
						s->set_year(y);
						s->set_usable(true);
					}
				} else {
					if(s->get_year()<y && s->get_month()<=m) {
						s->set_usable(false);
						magazine* tmp = new magazine(s->resource::getName(), s->get_month(), y);
						M.push_back(tmp);
					} else if(s->get_year()<y-1) {
						s->set_usable(false);
						magazine* tmp = new magazine(s->resource::getName(), s->get_month(), y-1);
						M.push_back(tmp);
					}
				}

			}
			
		}
	}

	//e-book auto expire
	for(auto s : E){
		for(auto t : U){
			if(t->get_borrow_fact(s->getName()) && t->get_borrow_date(s->getName()) + 13 < date) {
				t->delete_borrow(s->getName());
				s->del_borrow_inf(t->get_member());
			}
		}
		for(auto t : G){
			if(t->get_borrow_fact(s->getName()) && t->get_borrow_date(s->getName()) + 29 < date) {
				t->delete_borrow(s->getName());
				s->del_borrow_inf(t->get_member());
			}
		}
		for(auto t : F){
			if(t->get_borrow_fact(s->getName()) && t->get_borrow_date(s->getName()) + 29 < date) {
				t->delete_borrow(s->getName());
				s->del_borrow_inf(t->get_member());
			}
		}
	}
	
	//return_code 1 : Non exist resource.
	string output;
	int flag = 0;
	if(r_type == "Book") {
		for(auto s : B) {
			if(s->getName() == r_name) flag = 1;
		}
	} else if(r_type == "Magazine") {
		for(auto s : M) {
			if(s->getName() == r_name) {
				if(op=="B" && s->get_usable()) flag = 1;
				else if(op == "R") flag = 1;
			} 
		}
	} else if(r_type == "E-book") {
		for(auto s : E) {
			if(s->getName() == r_name) flag = 1;
		}
	}
	if(flag == 0) {
		output = output + to_string(cnt) + "\t" + "1\t" + "Non exist resource." + "\n";
		return output;
	}

	//return_code 2 : Exceeds possible number of borrow
	if(op == "B") {
		int b_num = 0;
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				int cnt2 = 0;
				for(auto t : s->get_map()) {
					for(auto u : E) {
						if(u->getName() == t.first) cnt2++;
					}
				}
				b_num = s->get_borrow_num() - cnt2;
				if(s->get_member() == m_name && b_num == 1) {
					output = output + to_string(cnt) + "\t" + "2\t" + "Exceeds your possible number of borrow. Possible # of borrows: 1" + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				int cnt2 = 0;
				for(auto t : s->get_map()) {
					for(auto u : E) {
						if(u->getName() == t.first) cnt2++;
					}
				}
				b_num = s->get_borrow_num() - cnt2;
				if(s->get_member() == m_name && b_num == 5) {
					output = output + to_string(cnt) + "\t" + "2\t" + "Exceeds your possible number of borrow. Possible # of borrows: 5" + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				int cnt2 = 0;
				for(auto t : s->get_map()) {
					for(auto u : E) {
						if(u->getName() == t.first) cnt2++;
					}
				}
				b_num = s->get_borrow_num() - cnt2;
				if(s->get_member() == m_name && b_num == 10) {
					output = output + to_string(cnt) + "\t" + "2\t" + "Exceeds your possible number of borrow. Possible # of borrows: 10" + "\n";
					return output;
				}
			}
		}
		
	}

	//return_code 3 : You did not borrow this book
	if(op == "R") {
		if(!is_registered(m_name, m_type)) {
			output = output + to_string(cnt) + "\t" + "3\t" + "You did not borrow this book." + "\n";
			return output;
		}
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				if(s->get_member() == m_name && !(s->get_borrow_fact(r_name))) {
					output = output + to_string(cnt) + "\t" + "3\t" + "You did not borrow this book." + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s->get_member() == m_name && !(s->get_borrow_fact(r_name))) {
					output = output + to_string(cnt) + "\t" + "3\t" + "You did not borrow this book." + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s->get_member() == m_name && !(s->get_borrow_fact(r_name))) {
					output = output + to_string(cnt) + "\t" + "3\t" + "You did not borrow this book." + "\n";
					return output;
				}
			}
		}
	}

	//return_code 4 : You already borrow this book
	if(op == "B") {
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				if(s->get_member() == m_name && s->get_borrow_fact(r_name)) {
					if(r_type == "E-book" && s->get_borrow_date(r_name) + 13 < date) {
						s->delete_borrow(r_name);
					} else {
						output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s->get_borrow_date(r_name)) + "\n";
						return output;
					}
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s->get_member() == m_name && s->get_borrow_fact(r_name)) {
					if(r_type == "E-book" && s->get_borrow_date(r_name) + 29 < date) {
						s->delete_borrow(r_name);
					} else {
						output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s->get_borrow_date(r_name)) + "\n";
						return output;
					}
				}
			}
		} else {
			for(auto s : F) {
				if(s->get_member() == m_name && s->get_borrow_fact(r_name)) {
					if(r_type == "E-book" && s->get_borrow_date(r_name) + 29 < date) {
						s->delete_borrow(r_name);
					} else {
						output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s->get_borrow_date(r_name)) + "\n";
						return output;
					}
				}
			}
		}
	}

	//return_code 5 : Other member alread borrowed this book
	if(op == "B") {
		if(r_type == "Book") {
			for(auto s : B) {
				if(s->getName() == r_name && s->get_who_borrow() != "" && s->get_who_borrow() != m_name) {
					int num = 0;
					for(auto t : U) {
						if(t->get_member() == s->get_who_borrow()) num = 13;
					}
					if(num==0){
						for(auto t : G) {
							if(t->get_member() == s->get_who_borrow()) num = 29;
						}
					}
					if(num==0) {
						for(auto t : F) {
							if(t->get_member() == s->get_who_borrow()) num = 29;
						}
					}
					output = output + to_string(cnt) + "\t" + "5\t" + "Other member already borrowed this book. This book will be returned at "+ DtoString(s->get_borrow_date()+num) + "\n";
					return output;
				}
			}
		} else if(r_type == "Magazine") {
			for(auto s : M) {
				if(s->getName() == r_name && s->get_who_borrow() != "" && s->get_who_borrow() != m_name) {
					int num = 0;
					for(auto t : U) {
						if(t->get_member() == s->get_who_borrow()) num = 13;
					}
					if(num==0){
						for(auto t : G) {
							if(t->get_member() == s->get_who_borrow()) num = 29;
						}
					}
					if(num==0) {
						for(auto t : F) {
							if(t->get_member() == s->get_who_borrow()) num = 29;
						}
					}
					output = output + to_string(cnt) + "\t" + "5\t" + "Other member already borrowed this book. This book will be returned at "+ DtoString(s->get_borrow_date()+num) + "\n";
					return output;
				}
			}
		}
	}

	//return_code 6 : Restriced member
	if(op == "B") {
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				if(s->get_member() == m_name && s->get_restrict_date() >= date) {
					output = output + to_string(cnt) + "\t" + "6\t" + "Restricted member until "+ DtoString(s->get_restrict_date()) + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s->get_member() == m_name && s->get_restrict_date() >= date) {
					output = output + to_string(cnt) + "\t" + "6\t" + "Restricted member until "+ DtoString(s->get_restrict_date()) + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s->get_member() == m_name && s->get_restrict_date() >= date) {
					output = output + to_string(cnt) + "\t" + "6\t" + "Restricted member until "+ DtoString(s->get_restrict_date()) + "\n";
					return output;
				}
			}
		}
	}

	//return_code 7 : Delayed return
	if(op == "R") {
		for(auto s : U) {
			if(s->get_member() == m_name && s->get_borrow_date(r_name)+13 < date) {
				if(r_type == "E-book"){
					s->delete_borrow(r_name);
				} else {
					output = output + to_string(cnt) + "\t" + "7\t" + "Delayed return. You'll be restricted until "+ DtoString(2*date - (s->get_borrow_date(r_name)+13)) + "\n";
					Update(date, m_type, m_name, r_type, r_name, 1);
					return output;
				}
			}
		}
		for(auto s : G) {
			if(s->get_member() == m_name && s->get_borrow_date(r_name)+29 < date) {
				if(r_type == "E-book"){
					s->delete_borrow(r_name);
				} else {
					output = output + to_string(cnt) + "\t" + "7\t" + "Delayed return. You'll be restricted until "+ DtoString(2*date - (s->get_borrow_date(r_name)+13)) + "\n";
					Update(date, m_type, m_name, r_type, r_name, 1);
					return output;
				}
			}
		}
		for(auto s : F) {
			if(s->get_member() == m_name && s->get_borrow_date(r_name)+29 < date) {
				if(r_type == "E-book"){
					s->delete_borrow(r_name);
				} else {
					output = output + to_string(cnt) + "\t" + "7\t" + "Delayed return. You'll be restricted until "+ DtoString(2*date - (s->get_borrow_date(r_name)+13)) + "\n";
					Update(date, m_type, m_name, r_type, r_name, 1);
					return output;
				}
			}
		}
	}

	//return_code 15 : Exceed capacity
	if(op == "B" && r_type == "E-book") {
		int size;
		for(auto s : E) {
			if(s->getName() == r_name) {
				size = s->get_size();
				break;
			}
		}
		for(auto s : U) {
			if(s->get_member() == m_name && s->get_capacity() + size > 100) {
				output = output + to_string(cnt) + "\t" + "15\t" + "Exceeds your storage capacity." + "\n";
				return output;
			}
		}
		for(auto s : G) {
			if(s->get_member() == m_name && s->get_capacity() + size > 500) {
				output = output + to_string(cnt) + "\t" + "15\t" + "Exceeds your storage capacity." + "\n";
				return output;
			}
		}
		for(auto s : F) {
			if(s->get_member() == m_name && s->get_capacity() + size > 1000) {
				output = output + to_string(cnt) + "\t" + "15\t" + "Exceeds your storage capacity." + "\n";
				return output;
			}
		}
	}

	//return_code 0 : Success
	if(op == "B") {
		Update(date, m_type, m_name, r_type, r_name, 0);
		output = output + to_string(cnt) + "\t" + "0\t" + "Success." + "\n";
	} else {	//"R"
		Update(date, m_type, m_name, r_type, r_name, 1);
		output = output + to_string(cnt) + "\t" + "0\t" + "Success." + "\n";
	}
	return output;
}

void library :: Update(int date, string m_type, string m_name, string r_type, string r_name, int op) {
	if(op == 0) { //op=0 : borrow update
		//borrow update member
		if(m_type == "Undergraduate") {
			if(!is_registered(m_name, m_type)) {
				//Not registed member
				undergraduate* _mem = new undergraduate(m_name, r_name, date);
				if(r_type == "E-book") {
					for(auto s : E) {
						if(s->getName() == r_name) _mem->set_capacity(s->get_size());
					}
				}
				U.push_back(_mem);
			} else {
				for(auto s : U) {
					if(s->get_member() == m_name) {
						s->insert_borrow(r_name, date);
						s->set_restrict_date(0);
						if(r_type == "E-book") {
							for(auto t : E) {
								if(t->getName() == r_name) s->set_capacity(s->get_capacity()+t->get_size());
							}
						}
						break;
					}
				}
			}
		} else if(m_type == "Graduate") {
			if(!is_registered(m_name, m_type)) {
				//Not registed member
				graduate* _mem = new graduate(m_name, r_name, date);
				if(r_type == "E-book") {
					for(auto s : E) {
						if(s->getName() == r_name) _mem->set_capacity(s->get_size());
					}
				}
				G.push_back(_mem);
			} else {
				for(auto s : G) {
					if(s->get_member() == m_name) {
						s->insert_borrow(r_name, date);
						s->set_restrict_date(0);
						if(r_type == "E-book") {
							for(auto t : E) {
								if(t->getName() == r_name) s->set_capacity(s->get_capacity()+t->get_size());
							}
						}
						break;
					}
				}
			}
		} else {
			if(!is_registered(m_name, m_type)) {
				//Not registed member
				faculty* _mem = new faculty(m_name, r_name, date);
				if(r_type == "E-book") {
					for(auto s : E) {
						if(s->getName() == r_name) _mem->set_capacity(s->get_size());
					}
				}
				F.push_back(_mem);
			} else {
				for(auto s : F) {
					if(s->get_member() == m_name) {
						s->insert_borrow(r_name, date);
						s->set_restrict_date(0);
						if(r_type == "E-book") {
							for(auto t : E) {
								if(t->getName() == r_name) s->set_capacity(s->get_capacity()+t->get_size());
							}
						}
						break;
					}
				}
			}
		}

		//borrow update resource
		if(r_type == "Book") {
			for(auto s : B) {
				if(s->getName() == r_name) {
					s->insert_borrow_inf(m_name, date);
					break;
				}
			}
		} else if(r_type == "Magazine") {
			for(auto s : M) {
				if(s->getName() == r_name) {
					s->insert_borrow_inf(m_name, date);
					break;
				}
			}
		} else {
			for(auto s : E) {
				if(s->getName() == r_name) {
					s->insert_borrow_inf(m_name, date);
					break;
				}
			}
		}

	} else { //op=1 : return update
		//return update member
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				if(s->get_member() == m_name) {
					if(s->get_borrow_date(r_name)+13 < date && r_type != "E-book") {
						s->set_restrict_date(2*date - (s->get_borrow_date(r_name)+13));
					} else {
						s->set_restrict_date(0);
					}
					s->delete_borrow(r_name);
					if(r_type == "E-book") {
						for(auto t : E) {
							if(t->getName() == r_name) s->set_capacity(s->get_capacity()-t->get_size());
						}
					}
					break;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s->get_member() == m_name) {
					if(s->get_borrow_date(r_name)+29 < date && r_type != "E-book") {
						s->set_restrict_date(2*date - (s->get_borrow_date(r_name)+29));
					} else {
						s->set_restrict_date(0);
					}
					s->delete_borrow(r_name);
					if(r_type == "E-book") {
						for(auto t : E) {
							if(t->getName() == r_name) s->set_capacity(s->get_capacity()-t->get_size());
						}
					}
					break;
				}
			}
		} else {
			for(auto s : F) {
				if(s->get_member() == m_name) {
					if(s->get_borrow_date(r_name)+29 < date && r_type != "E-book") {
						s->set_restrict_date(2*date - (s->get_borrow_date(r_name)+29));
					} else {
						s->set_restrict_date(0);
					}
					s->delete_borrow(r_name);
					if(r_type == "E-book") {
						for(auto t : E) {
							if(t->getName() == r_name) s->set_capacity(s->get_capacity()-t->get_size());
						}
					}
					break;
				}
			}
		}

		//return update resource
		if(r_type == "Book") {
			for(auto s : B) {
				if(s->getName() == r_name) {
					s->del_borrow_inf();
					break;
				}
			}
		} else if(r_type == "Magazine") {
			for(auto s : M) {
				if(s->getName() == r_name) {
					s->del_borrow_inf();
					break;
				}
			}
		} else {
			for(auto s : E) {
				if(s->getName() == r_name) {
					s->del_borrow_inf(m_name);
					break;
				}
			}
		}
	}
}

bool library :: is_registered(string name, string type) {
	if(type == "Undergraduate") {
		for(auto s : U) {
			if(s->get_member() == name) {
				return true;
			}
		}
		return false;
	} else if(type == "Graduate") {
		for(auto s : G) {
			if(s->get_member() == name) {
				return true;
			}
		}
		return false;
	} else {
		for(auto s : F) {
			if(s->get_member() == name) {
				return true;
			}
		}
		return false;
	}
}

int library :: DtoInt(string date) {
	int year, month, day;
	string y, m, d;
	char *str_buff = new char[10];
	strcpy(str_buff, date.c_str());

	char *tok = strtok(str_buff,"/");
	y = tok;
	year = stoi(y);

	tok = strtok(nullptr,"/");
	m = tok;
	month = stoi(m);

	tok = strtok(nullptr,"/");
	d = tok;
	day = stoi(d);

	return year*360 + month*30 + day;
}

string library :: DtoString(int date) {
	string str, year, month, day;
	int y, m ,d;

	y = date/360;
	year = to_string(y);
	if(year.length()<2) year = "0" + year;

	date %= 360;
	m = (date/30);
	month = to_string(m);
	if(month.length()<2) month = "0" + month;
	
	date %= 30;
	if(date == 0) d = 30;
	else d = date;
	day = to_string(d);
	if(day.length()<2) day = "0" + day;
	
	str = year + "/" + month + "/" + day;
	return str;
}

void library :: result() {
	ifstream fin("input.dat");
	ofstream fout("output.dat");
	string dummy, date, r_type, r_name, op, m_type, m_name;
	for(int i = 0; i < 6; i ++) {
		fin >> dummy;
	}
	int cnt = 0;
	fout << "Op_#\tReturn_code\tDescription\n"; 
	string res;
	while(fin >> date) {
		cnt ++;
		int day = DtoInt(date);
		fin >> r_type;
		fin >> r_name;
		fin >> op;
		fin >> m_type;
		fin >> m_name;
		res += check(cnt, day, r_type, r_name, op, m_type, m_name);
	}
	fout << res;
}

void library :: print_resource() {
	for(auto s : B) cout << s->getName() << endl;
	for(auto s : M) cout << s->getName() << endl;
	for(auto s : E) cout << s->getName() << endl;
}

void library :: print_member() {
	for(auto s : U) cout << s->get_member() << endl;
	for(auto s : G) cout << s->get_member() << endl;
	for(auto s : F) cout << s->get_member() << endl;
}