#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "library.h"

using namespace std;

library :: library() {
	today = "";
	B.clear();
	M.clear();
	E.clear();
	U.clear();
	G.clear();
	F.clear();
	for(int i = 1; i < 11; i++) {
		Study_room* tmp = new Study_room(i, 0);
		srooms.push_back(tmp);
	}
	for(int i = 1; i < 4; i++) {
		for(int j = 0; j < 50; j++) {
			Seat* tmp = new Seat(i, j, 0);
			seats.push_back(tmp);
		}
	}
	resource_data();
	result();
	for(int i = 1; i < 11; i++) {
		delete srooms.back();
		srooms.pop_back();
	}
	for(int i = 1; i < 4; i++) {
		for(int j = 0; j < 50; j++) {
			delete seats.back();
			seats.pop_back();
		}
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

string library :: check(int cnt, string dateS, string r_type, string r_name, string op, string m_type, string m_name) {
	int date = DtoInt(dateS);
	refresh(dateS);
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
					output = output + to_string(cnt) + "\t" + "2\t" + "Exceeds your possible number of borrow. Possible # of borrows: ?" + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && s.get_borrow_num() > 2) {
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
					output = output + to_string(cnt) + "\t" + "3\t" + "You did not borrow this book." + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
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
					output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s.get_borrow_date(r_name)) + "\n";
					return output;
				}
			}
		} else if(m_type == "Graduate") {
			for(auto s : G) {
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
					output = output + to_string(cnt) + "\t" + "4\t" + "You already borrowed this book at "+ DtoString(s.get_borrow_date(r_name)) + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && !(s.get_borrow_fact(r_name))) {
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
					output = output + to_string(cnt) + "\t" + "5\t" + "Other member already borrowed this book. This book will be returned at "+ DtoString(s.get_borrow_date()+13) + "\n";
					return output;
				}
			}
		} else {
			for(auto s : E) {
				if(s.getName() == r_name && s.get_who_borrow() != m_name) {
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
					output = output + to_string(cnt) + "\t" + "6\t" + "Restricted member until "+ DtoString(s.get_restrict_date()) + "\n";
					return output;
				}
			}
		} else {
			for(auto s : F) {
				if(s.get_member() == m_name && s.get_restrict_date() >= date) {
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
				output = output + to_string(cnt) + "\t" + "7\t" + "Delayed return. You'll be restricted until "+ DtoString(2*date - (s.get_borrow_date(r_name)+13)) + "\n";
				s.set_restrict_date(2*date - (s.get_borrow_date(r_name)+13));
				Update(date, m_type, m_name, r_type, r_name, 1);
				return output;
			}
		}
		for(auto s : F) {
			if(s.get_member() == m_name && s.get_borrow_date(r_name)+13 < date) {
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
		output = output + to_string(cnt) + "\t" + "0\t" + "Success." + "\n";
	} else {
		Update(date, m_type, m_name, r_type, r_name, 1);
		output = output + to_string(cnt) + "\t" + "0\t" + "Success." + "\n";
	}
	return output;
}

string library :: check2(int cnt, string s_dateS, string s_type, int s_num, string s_op, string sm_type, string sm_name, int sm_num, int s_time, int hour) {
	refresh(s_dateS);
	int s_date = DtoInt(s_dateS);
	string output;
	//return_code 8 : Invalid space id
	if((s_type == "StudyRoom" && (s_num > 10 || s_num < 1)) || (s_type == "Seat" && (s_num > 3 || s_num < 1))) {
		output = output + to_string(cnt) + "\t" + "8\t" + "Invalid space id.\n";
		return output;
	}

	//return_code 9 : This space is not available now
	if(s_op == "B") {
		if(s_type == "StudyRoom" && (hour < 9 || hour >= 18)) {
			output = output + to_string(cnt) + "\t" + "9\t" + "This space is not available now. Available from 09 to 18.\n";
			return output;
		} else if(s_type == "Seat" && s_num == 2 && (hour < 9 || hour >= 21)) {
			output = output + to_string(cnt) + "\t" + "9\t" + "This space is not available now. Available from 09 to 21.\n";
			return output;
		} else if(s_type == "Seat" && s_num == 3 && (hour < 9 || hour >= 18)) {
			output = output + to_string(cnt) + "\t" + "9\t" + "This space is not available now. Available from 09 to 21.\n";
			return output;
		} else return "Error\n";
	}

	//return_code 10 : You did not borrow this space
	if(s_op != "B") {
		if(s_type == "StudyRoom") {
			for(auto s : srooms) {
				if(s->get_roomNum() == s_num && s->get_who() != sm_name) {
					output = output + to_string(cnt) + "\t" + "10\t" + "You did not borrow this space\n";
					return output;
				}
			}
		} else if(s_type == "Seat") {
			int flag = 0;
			for(auto s : seats) {
				if(s->get_floor() == s_num && s->get_who() == sm_name) {
					flag = 1;
				}
			}
			if(flag == 0) {
				output = output + to_string(cnt) + "\t" + "10\t" + "You did not borrow this space\n";
				return output;
			}
		} else {
			return "Error on return_code_10\n";
		}
	}

	//return_code 11 : You already borrow this kind of space
	if(s_op == "B") {
		if(s_type == "StudyRoom") {
			for(auto s : srooms) {
				if(s->get_who() == sm_name) {
					output = output + to_string(cnt) + "\t" + "11\t" + "You already borrow this kind of space\n";
					return output;
				}
			}
		} else if(s_type == "Seat") {
			for(auto s : seats) {
				if(s->get_who() == sm_name) {
					output = output + to_string(cnt) + "\t" + "11\t" + "You already borrow this kind of space\n";
					return output;
				}
			}
		} else {
			return "Error on return_code_11\n";
		}
	}

	//return_code 12 : Exceed available number
	if(s_op == "B") {
		if(s_type == "StudyRoom") {
			if(sm_num > 6) {
				output = output + to_string(cnt) + "\t" + "12\t" + "Exceed available number.\n";
				return output;
			}
		} else if(s_type == "Seat") {
			if(sm_num > 1) {
				output = output + to_string(cnt) + "\t" + "12\t" + "Exceed available number.\n";
				return output;
			}
		} else {
			return "Error on return_code_12\n";
		}
	}

	//return_code 13 : Exceed available time
	if(s_op == "B") {
		if(s_type == "StudyRoom") {
			if(s_time > 3) {
				output = output + to_string(cnt) + "\t" + "13\t" + "Exceed available time.\n";
				return output;
			}
		} else if(s_type == "Seat") {
			if(sm_type == "Undergraduate" && s_time > 3) {
				output = output + to_string(cnt) + "\t" + "13\t" + "Exceed available time.\n";
				return output;
			}
		} else {
			return "Error on return_code_13\n";
		}
	}

	//return_code 14 : There is no remain space
	if(s_op == "B") {
		string next_time;
		if(s_type == "StudyRoom") {
			for(auto s : srooms) {
				if(s->get_roomNum() == s_num && s->get_state() != 'N') {
					if(s->get_when() >= 18) {
						next_time = "09";
					} else {
						next_time = HtoString(s->get_when());
					}
					output = output + to_string(cnt) + "\t" + "14\t" + "There is no remain space. This space is available after " + next_time + ".\n";
					return output;
				}
			}
		} else if(s_type == "Seat") {
			int min = 0;
			int flag = 0;
			for(auto s : seats) {
				if(s->get_floor() == s_num) {
					if(s->get_state() == 'N') {
						flag = 1;
					} else {
						if(min > s->get_when()) min = s->get_when();
					}
				}
			}
			if(flag == 0) {
				if(s_num == 1) {
					if(min >= 24) {
						next_time = "00";
					} else {
						next_time = HtoString(min);
					}
				} else if((s_num == 2 && min >= 21) || (s_num == 3 && min >= 18)) {
					next_time = "09";
				} else {
					next_time = HtoString(min);
				}
				output = output + to_string(cnt) + "\t" + "14\t" + "There is no remain space. This space is available after " + next_time + ".\n";
				return output;
			}
		} else {
			return "Error on return_code_14\n";
		}
	}

	//return_code 0 : Success
	if(s_op == "B") {
		//update member
		if(!is_registered(sm_name, sm_type)) {
			//Not registed member
			if(sm_type == "Undergraduate") {
				undergraduate _mem(sm_name);
				U.push_back(_mem);
			} else if(sm_type == "Graduate") {
				graduate _mem(sm_name);
				G.push_back(_mem);
			} else {
				faculty _mem(sm_name);
				F.push_back(_mem);
			}
		}
		if(s_type == "StudyRoom") {
			for(auto s : srooms) {
				if(s->get_roomNum() == s_num && s->get_state() == 'N') {
					s->set_Sroom('U', sm_name, hour+s_time, sm_num);
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else if(s_type == "Seat") {
			for(auto s : seats) {
				if(s->get_floor() == s_num && s->get_state() == 'N') {
					s->set_Seat('U', sm_name, hour+s_time, 0);
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else {
			return "Error_code_0_s_type\n";
		}
	} else if(s_op == "R") {
		if(s_type == "StudyRoom") {
			for(auto s : srooms) {
				if(s->get_roomNum() == s_num && s->get_state() != 'N') {
					s->set_Sroom('N', "", 0, 0);
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else if(s_type == "Seat") {
			for(auto s : seats) {
				if(s->get_floor() == s_num && s->get_who() == sm_name && s->get_state() != 'N') {
					s->set_Seat('N', "", 0, 0);
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else {
			return "Error_code_0_s_type\n";
		}
	} else if(s_op == "E") {
		if(s_type == "StudyRoom") {
			for(auto s : srooms) {
				if(s->get_roomNum() == s_num && s->get_state() == 'U') {
					s->set_state('A');
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else if(s_type == "Seat") {
			for(auto s : seats) {
				if(s->get_floor() == s_num && s->get_who() == sm_name && s->get_state() == 'U') {
					s->set_state('A');
					s->set_come(hour+1);
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else {
			return "Error_code_0_s_type\n";
		}
	} else if(s_op == "C") {
		if(s_type == "StudyRoom") {
			for(auto s : srooms) {
				if(s->get_roomNum() == s_num && s->get_state() == 'A') {
					s->set_state('U');
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else if(s_type == "Seat") {
			for(auto s : seats) {
				if(s->get_floor() == s_num && s->get_who() == sm_name && s->get_state() == 'A') {
					s->set_state('U');
					s->set_come(0);
					output = output + to_string(cnt) + "\t" + "0\t" + "Success.\n";
					return output;
				}
			}
		} else {
			return "Error_code_0_s_type\n";
		}
	} else {
		return "Error_code_0_s_op\n";
	}
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
    if(date.length() == 8) year = stoi(y);
    else year = stoi(y)-2000;

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

int library :: DtoHour(string date) {
    int hour;
    string h;
    char *str_buff = new char[14];
    strcpy(str_buff, date.c_str());
    char *tok = strtok(str_buff,"/");
    tok = strtok(nullptr,"/");
    tok = strtok(nullptr,"/");
    tok = strtok(nullptr,"/");
    h = tok;
    hour = stoi(h);
    return hour;
}

void library :: result() {
	ifstream fin("input.dat");
	ifstream fin2("space.dat");
	ofstream fout("output.dat");
	string dummy, date, r_type, r_name, op, m_type, m_name;
	string s_date, s_type, s_num, s_op, sm_type, sm_name, sm_num, s_time;
	for(int i = 0; i < 6; i ++) {
		fin >> dummy;
	}
    for(int i = 0; i < 8; i++) {
        fin2 >> dummy;
    }
	int cnt = 0;
    int flag = 0;
    int flag2 = 0;
	fout << "Op_#\tReturn_code\tDescription\n"; 
	string res;

    while(true) {
        if(flag2 == 0 || flag2 == 1) {
            if(!(fin >> date)) {
                flag = 0;
                break;
            }
        }
        if(flag2 == 0 || flag2 == 2) {
            if(!(fin2 >> s_date)) {
                flag = 1;
                break;
            }
        }

        if(DtoInt(date) <= DtoInt(s_date)) {
            flag2 = 1;
            fin >> r_type;
            fin >> r_name;
            fin >> op;
            fin >> m_type;
            fin >> m_name;
            res += check(cnt++, date, r_type, r_name, op, m_type, m_name);
        } else if(DtoInt(date) > DtoInt(s_date)) {
            flag2 = 2;
            fin2 >> s_type;
            fin2 >> s_num;
            fin2 >> s_op;
            fin2 >> sm_type;
            fin2 >> sm_name;
			if(s_op == "B") {
				fin2 >> sm_num;
				fin2 >> s_time;		
			} else {
				sm_num = "0";
				s_time = "0";
			}
            res += check2(cnt++, s_date, s_type, stoi(s_num), s_op, sm_type, sm_name, stoi(sm_num), stoi(s_time), DtoHour(s_date));
        }
    }
    if(flag == 0) {
        while(fin2 >> s_type) {
            fin2 >> s_num;
            fin2 >> s_op;
            fin2 >> sm_type;
            fin2 >> sm_name;
			if(s_op == "B") {
				fin2 >> sm_num;
				fin2 >> s_time;		
			} else {
				sm_num = "0";
				s_time = "0";
			}
            res += check2(cnt++, s_date, s_type, stoi(s_num), s_op, sm_type, sm_name, stoi(sm_num), stoi(s_time), DtoHour(s_date));
            fin2 >> s_date;
        }
    } else if(flag == 1) {
        while(fin >> r_type) {
            fin >> r_name;
            fin >> op;
            fin >> m_type;
            fin >> m_name;
            res += check(cnt++, date, r_type, r_name, op, m_type, m_name);
            fin >> date;
        }
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

void library :: refresh(string date) {
	if(DtoInt(today) != DtoInt(date)) {
		today = date;
		for(auto s : srooms) {
			s->set_Sroom('N', "", 0, 0);
		}
		for(auto s : seats) {
			s->set_Seat('N', "", 0, 0);
		}
	} else {
		if(date.length() == 13) {
			today = date;
			int currentH = DtoHour(date);
			if(currentH > 18) {
				for(auto s : srooms) {
					s->set_Sroom('N', "", 0, 0);
				}
				for(auto s : seats) {
					if(s->get_floor() == 3) {
						s->set_Seat('N', "", 0, 0);
					}
				}
			} else if(currentH > 21) {
				for(auto s : seats) {
					if(s->get_floor() == 2) {
						s->set_Seat('N', "", 0, 0);
					}
				}
			}
			for(auto s : srooms) {
				if(s->get_state() != 'N' && currentH >= s->get_when()) {
					s->set_Sroom('N', "", 0, 0);
				}
			}
			for(auto s : seats) {
				if(s->get_state() == 'U' && currentH >= s->get_when()) {
					s->set_Seat('N', "", 0, 0);
				} else if(s->get_state() == 'A' && currentH >= s->get_come()) {
					s->set_Seat('N', "", 0, 0);
				}
			}
		}
	}
}

string library :: get_type(string name) {
	for(auto s : U) {
		if(s.get_member() == name) {
			return "Undergraduate";
		}
	}
	for(auto s : G) {
		if(s.get_member() == name) {
			return "Graduate";
		}
	}
	for(auto s : F) {
		if(s.get_member() == name) {
			return "Faculty";
		}
	}
	return "Error_get_type";
}

string library :: HtoString(int hour) {
	string str;
	if(hour<10) str = "0" + to_string(hour);
	else str = to_string(hour);
	return str;
}