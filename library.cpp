#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "library.h"

using namespace std;

library :: library() {
	B.clear();
	M.clear();
	E.clear();
	U.clear();
	G.clear();
	F.clear();
	resource_data();
	result();
}

void library :: resource_data() {
	ifstream fin("resource.dat");
	string dummy, type, name;
	fin >> dummy;
	fin >> dummy;
	while(fin >> type) {
		if(type == "Book") {
			fin >> name;
			book input(name);
			B.push_back(input);
		} else if(type == "Magazine") {
			fin >> name;
			magazine input(name);
			M.push_back(input);
		} else {
			fin >> name;
			e_book input(name);
			E.push_back(input);
		}
	}
}

string library :: check(int cnt, int date, string r_type, string r_name, string op, string m_type, string m_name) {
	//return_code 1 : Non exist resource.
	string output;
	int flag = 0;
	for(auto s : B) {
		if(s.getName() == r_name) flag = 1;
	}
	if(flag == 0) {
		output = output + to_string(cnt) + "\t" + "1\t" + "Non exist resource." + "\n";
		return output;
	}

	//return_code 2 : Exceeds possible number of borrow
	if(op == "B") {
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				if(s.get_member() == m_name && s.get_borrow_num() > 0) {
					output = output + to_string(cnt) + "\t" + "2\t" + "Exceeds your possible number of borrow. Possible # of borrows: 1" + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s.get_member() == m_name && s.get_borrow_num() > 1) {
					cout << cnt << "\t" << "2\t" << "Exceeds your possible number of borrow. Possible # of borrows: ?" << "\n";
					output = output + to_string(cnt) + "\t" + "2\t" + "Exceeds your possible number of borrow. Possible # of borrows: ?" + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && s.get_borrow_num() > 2) {
					cout << cnt << "\t" << "2\t" << "Exceeds your possible number of borrow. Possible # of borrows: ?" << "\n";
					output = output + to_string(cnt) + "\t" + "2\t" + "Exceeds your possible number of borrow. Possible # of borrows: ?" + "\n";
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
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
					output = output + to_string(cnt) + "\t" + "3\t" + "You did not borrow this book." + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
					cout << cnt << "\t" << "3\t" << "You did not borrow this book" << "\n";
					output = output + to_string(cnt) + "\t" + "3\t" + "You did not borrow this book." + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
					cout << cnt << "\t" << "3\t" << "You did not borrow this book" << "\n";
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
				if(s.get_member() == m_name && s.get_borrow_fact(r_name)) {
					cout << cnt << "\t" << "4\t" << "You already borrowed this book at "<< DtoString(s.get_borrow_date(r_name)) << "\n";
					output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s.get_borrow_date(r_name)) + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
					cout << cnt << "\t" << "4\t" << "You already borrowed this book at "<< DtoString(s.get_borrow_date(r_name)) << "\n";
					output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s.get_borrow_date(r_name)) + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
					cout << cnt << "\t" << "4\t" << "You already borrowed this book at "<< DtoString(s.get_borrow_date(r_name)) << "\n";
					output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s.get_borrow_date(r_name)) + "\n";
					return output;
				}
			}
		}
	}

	//return_code 5 : Other member alread borrowed this book
	if(op == "B") {
		if(r_type == "Book") {
			for(auto s : B) {
				if(s.getName() == r_name && s.get_who_borrow() != "" && s.get_who_borrow() != m_name) {
					output = output + to_string(cnt) + "\t" + "5\t" + "Other member already borrowed this book. This book will be returned at "+ DtoString(s.get_borrow_date()+13) + "\n";
					return output;
				}
			}
		} else if(r_type == "Magazine") {
			for(auto s : M) {
				if(s.getName() == r_name && s.get_who_borrow() != m_name) {
					cout << cnt << "\t" << "5\t" << "Other member already borrowed this book. This book will be returned at  "<< DtoString(s.get_borrow_date()+13) << "\n";
					output = output + to_string(cnt) + "\t" + "5\t" + "Other member already borrowed this book. This book will be returned at "+ DtoString(s.get_borrow_date()+13) + "\n";
					return output;
				}
			}
		} else {
			for(auto s : E) {
				if(s.getName() == r_name && s.get_who_borrow() != m_name) {
					cout << cnt << "\t" << "5\t" << "Other member already borrowed this book. This book will be returned at  "<< DtoString(s.get_borrow_date()+13) << "\n";
					output = output + to_string(cnt) + "\t" + "5\t" + "Other member already borrowed this book. This book will be returned at "+ DtoString(s.get_borrow_date()+13) + "\n";
					return output;
				}
			}
		}
	}

	//return_code 6 : Restriced member
	if(op == "B") {
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				if(s.get_member() == m_name && s.get_restrict_date() >= date) {
					output = output + to_string(cnt) + "\t" + "6\t" + "Restricted member until "+ DtoString(s.get_restrict_date()) + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s.get_member() == m_name && s.get_restrict_date() >= date) {
					cout << cnt << "\t" << "6\t" << "Restricted member until "<< DtoString(s.get_restrict_date()) << "\n";
					output = output + to_string(cnt) + "\t" + "6\t" + "Restricted member until "+ DtoString(s.get_restrict_date()) + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && s.get_restrict_date() >= date) {
					cout << cnt << "\t" << "6\t" << "Restricted member until "<< DtoString(s.get_restrict_date()) << "\n";
					output = output + to_string(cnt) + "\t" + "6\t" + "Restricted member until "+ DtoString(s.get_restrict_date()) + "\n";
					return output;
				}
			}
		}
	}

	//return_code 7 : Delayed return
	if(op == "R") {
		for(auto s : U) {
			if(s.get_member() == m_name && s.get_borrow_date(r_name)+13 < date) {
				output = output + to_string(cnt) + "\t" + "7\t" + "Delayed return. You'll be restricted until "+ DtoString(2*date - (s.get_borrow_date(r_name)+13)) + "\n";
				Update(date, m_type, m_name, r_type, r_name, 1);
				return output;
			}
		}
		for(auto s : G) {
			if(s.get_member() == m_name && s.get_borrow_date(r_name)+13 < date) {
				cout << cnt << "\t" << "7\t" << "Delayed return. You'll be restricted until "<< DtoString(2*date - (s.get_borrow_date(r_name)+13)) << "\n";
				output = output + to_string(cnt) + "\t" + "7\t" + "Delayed return. You'll be restricted until "+ DtoString(2*date - (s.get_borrow_date(r_name)+13)) + "\n";
				s.set_restrict_date(2*date - (s.get_borrow_date(r_name)+13));
				Update(date, m_type, m_name, r_type, r_name, 1);
				return output;
			}
		}
		for(auto s : F) {
			if(s.get_member() == m_name && s.get_borrow_date(r_name)+13 < date) {
				cout << cnt << "\t" << "7\t" << "Delayed return. You'll be restricted until "<< DtoString(2*date - (s.get_borrow_date(r_name)+13)) << "\n";
				output = output + to_string(cnt) + "\t" + "7\t" + "Delayed return. You'll be restricted until "+ DtoString(2*date - (s.get_borrow_date(r_name)+13)) + "\n";
				s.set_restrict_date(2*date - (s.get_borrow_date(r_name)+13));
				Update(date, m_type, m_name, r_type, r_name, 1);
				return output;
			}
		}
	}

	//return_code 0 : Success
	if(op == "B") {
		Update(date, m_type, m_name, r_type, r_name, 0);
		//cout << cnt << "\t" << "0\t" << "Success." << "\n";
		output = output + to_string(cnt) + "\t" + "0\t" + "Success." + "\n";
	} else {
		Update(date, m_type, m_name, r_type, r_name, 1);
		//cout << cnt << "\t" << "0\t" << "Success." << "\n";
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
				undergraduate _mem(m_name, r_name, date);
				U.push_back(_mem);
			} else {
				for(auto s : U) {
					if(s.get_member() == m_name) {
						s.insert_borrow(r_name, date);
						s.set_restrict_date(0);
						auto iter = U.begin();
						while(iter != U.end()) {
							if(iter->get_member() == m_name) {
								iter = U.erase(iter);
								break;
							}
							else ++iter;
						}
						U.push_back(s);
						break;
					}
				}
			}
		} else if(m_type == "Graduate") {
			if(!is_registered(m_name, m_type)) {
				//Not registed member
				graduate _mem(m_name, r_name, date);
				G.push_back(_mem);
			} else {
				for(auto s : G) {
					if(s.get_member() == m_name) {
						s.insert_borrow(r_name, date);
						s.set_restrict_date(0);
						auto iter = G.begin();
						while(iter != G.end()) {
							if(iter->get_member() == m_name) {
								iter = G.erase(iter);
								break;
							}
							else ++iter;
						}
						G.push_back(s);
						break;
					}
				}
			}
		} else {
			if(!is_registered(m_name, m_type)) {
				//Not registed member
				faculty _mem(m_name, r_name, date);
				F.push_back(_mem);
			} else {
				for(auto s : F) {
					if(s.get_member() == m_name) {
						s.insert_borrow(r_name, date);
						s.set_restrict_date(0);
						auto iter = F.begin();
						while(iter != F.end()) {
							if(iter->get_member() == m_name) {
								iter = F.erase(iter);
								break;
							}
							else ++iter;
						}
						F.push_back(s);
						break;
					}
				}
			}
		}

		//borrow update resource
		if(r_type == "Book") {
			for(auto s : B) {
				if(s.getName() == r_name) {
					s.insert_borrow_inf(r_name, m_name, date);
					auto iter = B.begin();
					while(iter != B.end()) {
						if(iter->getName() == r_name) {
							iter = B.erase(iter);
							break;
						}
						else ++iter;
					}
					B.push_back(s);
					//cout << s.get_who_borrow() << endl;
					break;
				}
			}
		} else if(r_type == "Magazine") {
			for(auto s : M) {
				if(s.getName() == r_name) {
					s.insert_borrow_inf(r_name, m_name, date);
					auto iter = M.begin();
					while(iter != M.end()) {
						if(iter->getName() == r_name) {
							iter = M.erase(iter);
							break;
						}
						else ++iter;
					}
					M.push_back(s);
					break;
				}
			}
		} else {
			for(auto s : E) {
				if(s.getName() == r_name) {
					s.insert_borrow_inf(r_name, m_name, date);
					auto iter = E.begin();
					while(iter != E.end()) {
						if(iter->getName() == r_name) {
							iter = E.erase(iter);
							break;
						}
						else ++iter;
					}
					E.push_back(s);
					break;
				}
			}
		}

	} else { //op=1 : return update
		//return update member
		if(m_type == "Undergraduate") {
			for(auto s : U) {
				if(s.get_member() == m_name) {
					if(s.get_borrow_date(r_name)+13 < date) {
						s.set_restrict_date(2*date - (s.get_borrow_date(r_name)+13));
					} else {
						s.set_restrict_date(0);
					}
					s.delete_borrow(r_name);
					auto iter = U.begin();
					while(iter != U.end()) {
						if(iter->get_member() == m_name) {
							iter = U.erase(iter);
							break;
						}
						else ++iter;
					}
					U.push_back(s);
					break;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s.get_member() == m_name) {
					if(s.get_borrow_date(r_name)+13 < date) {
						s.set_restrict_date(2*date - (s.get_borrow_date(r_name)+13));
					} else {
						s.set_restrict_date(0);
					}
					s.delete_borrow(r_name);
					auto iter = G.begin();
					while(iter != G.end()) {
						if(iter->get_member() == m_name) {
							iter = G.erase(iter);
							break;
						}
						else ++iter;
					}
					G.push_back(s);
					break;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name) {
					if(s.get_borrow_date(r_name)+13 < date) {
						s.set_restrict_date(2*date - (s.get_borrow_date(r_name)+13));
					} else {
						s.set_restrict_date(0);
					}
					s.delete_borrow(r_name);
					auto iter = F.begin();
					while(iter != F.end()) {
						if(iter->get_member() == m_name) {
							iter = F.erase(iter);
							break;
						}
						else ++iter;
					}
					F.push_back(s);
					break;
				}
			}
		}

		//return update resource
		if(r_type == "Book") {
			for(auto s : B) {
				if(s.getName() == r_name) {
					s.del_borrow_inf();
					auto iter = B.begin();
					while(iter != B.end()) {
						if(iter->getName() == r_name) {
							iter = B.erase(iter);
							break;
						}
						else ++iter;
					}
					B.push_back(s);
					break;
				}
			}
		} else if(r_type == "Magazine") {
			for(auto s : M) {
				if(s.getName() == r_name) {
					s.del_borrow_inf();
					auto iter = M.begin();
					while(iter != M.end()) {
						if(iter->getName() == r_name) {
							iter = M.erase(iter);
							break;
						}
						else ++iter;
					}
					M.push_back(s);
					break;
				}
			}
		} else {
			for(auto s : E) {
				if(s.getName() == r_name) {
					s.del_borrow_inf();
					auto iter = E.begin();
					while(iter != E.end()) {
						if(iter->getName() == r_name) {
							iter = E.erase(iter);
							break;
						}
						else ++iter;
					}
					E.push_back(s);
					break;
				}
			}
		}
	}
}

bool library :: is_registered(string name, string type) {
	if(type == "Undergraduate") {
		for(auto s : U) {
			if(s.get_member() == name) {
				return true;
			}
		}
		return false;
	} else if(type == "Graduate") {
		for(auto s : G) {
			if(s.get_member() == name) {
				return true;
			}
		}
		return false;
	} else {
		for(auto s : F) {
			if(s.get_member() == name) {
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
	for(auto s : B) cout << s.getName() << endl;
	for(auto s : M) cout << s.getName() << endl;
	for(auto s : E) cout << s.getName() << endl;
}

void library :: print_member() {
	for(auto s : U) cout << s.get_member() << endl;
	for(auto s : G) cout << s.get_member() << endl;
	for(auto s : F) cout << s.get_member() << endl;
}