#include "Storage.hpp"
#include "User.hpp"
#include "Path.hpp"
#include "Meeting.hpp"
#include <functional>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

Storage::Storage() {
	m_dirty = 0;
	readFromFile();
}

bool Storage::readFromFile(void) {
	ifstream file_meeting;
	ifstream file_user;
	file_meeting.open(Path::meetingPath, ios::out);
	file_user.open(Path::userPath, ios::out);

	if ((!file_meeting) || (!file_user)) {
		return false;
	}
	string one, name1,password1,email1,phone1;
	int sign = 0;
	int point = 1;
	while (getline(file_user, one)) {
		string two = one;
		int n = two.length();
		for (int j = 0;j < n; j++) {
			if (two[j] == ',' && two[j+1] == '"' && two[j-1] == '"') {
				sign++;
				if (sign == 1) {
					name1 = two.substr(1, j-2);
					point = j+1;
				} else if (sign == 2) {
					password1 = two.substr(point+1, j-2-point);
					point = j+1;
				} else if (sign == 3) {
					email1 = two.substr(point+1, j-2-point);
					point = j +1;
				}
			} else if (two[j] == '"' && j == two.length()-1) {
				phone1 = two.substr(point +1, j - point -1);
			}
		}
		sign = point = 0;
		User out(name1,password1,email1, phone1);
		m_userList.push_back(out);
		one = two = name1 = password1 = email1 = phone1 = "";
	}

	string three,sponsor1,title1;
	vector<string> another;
	string participator1;
	Date startdate1,enddate1;
	string c, d;
	int sign2 = 0;
	int point2 = 0;
	while (getline(file_meeting, three)) {
		string two2 = three;
		int n2 = two2.length();
		for (int j = 0;j < n2; j++) {
			if (two2[j] == ',' && two2[j+1] == '"' && two2[j-1] == '"') {
				sign2++;
				if (sign2 == 1) {
					sponsor1 = two2.substr(point2+1, j-2);
					point2 = j+1;
				} else if (sign2 == 2) {
					participator1 = two2.substr(point2+1, j-2-point2);
					point2 = j+1;
				} else if (sign2 == 3) {
					c = two2.substr(point2+1, j-2-point2);
					point2 = j+1;
				} else if (sign2 == 4) {
					d = two2.substr(point2+1, j-2-point2);
					point2 = j+1;
				}
			} else if (two2[j] == '"' && j == two2.length()-1) {
				title1 = two2.substr(point2 +1, j-point2-1);
			}
		}
	    string k = "";
		for (int i = 0; i < participator1.length(); i++) {
			k += participator1[i];
			if (participator1[i+1] == '&') {
				another.push_back(k);
				k = "";
				i++;
			}
		}
		sign2 = point2 = 0;
		startdate1 = Date::stringToDate(c);
		enddate1 = Date::stringToDate(d);
		Meeting str(sponsor1,another,startdate1, enddate1, title1);
		m_meetingList.push_back(str);
		three = two2 = sponsor1 = title1 = "";
		another.clear();
		participator1 = c = d = "";
		Date start;
		startdate1 = enddate1 = start;
	}


	file_meeting.close();
	file_user.close();
	return true;
}
bool Storage::writeToFile(void) {
	ofstream file_meeting;
	ofstream file_user;
	file_meeting.open(Path::meetingPath,ios::in);
	file_user.open(Path::userPath, ios::in);

	if (!file_user) {
		return false;
	}
	list<User>::iterator iter;
	for (iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		string name2 = iter->getName();
		string password2 = iter->getPassword();
		string email2 = iter->getEmail();
		string phone2 = iter->getPhone();
		file_user << "\"" << name2 <<"\",\"" << password2 << "\",\"" << email2 << "\",\"" << phone2 << "\""<< endl;
	}
	file_user.close();

	list<Meeting>::iterator itera;
	for (itera = m_meetingList.begin(); itera != m_meetingList.end(); itera++) {
		string sponsor2,title2;
		vector<string> participators2;
		string a, b;
		Date startDate2,endDate2;

		sponsor2 = itera->getSponsor();
		participators2 = itera->getParticipator();
		startDate2 = itera->getStartDate();
		endDate2 = itera->getEndDate();
		title2 = itera->getTitle();
		a = Date::dateToString(startDate2);
		b = Date::dateToString(endDate2);
		

		string str = "";
		str += "\""+sponsor2+"\",\"";
		vector<string>::iterator it;
		for (it = participators2.begin(); it != participators2.end(); it++) {
			str += (*it);
			if (it != participators2.end()-1) {
				str += "&";
			}
		}
		str += "\",\""+a+"\",\""+b+"\",\""+title2 + "\"";

		file_meeting << str << endl;
	}

	file_meeting.close();
}

std::shared_ptr<Storage> Storage::getInstance(void) {
	if (m_instance == NULL) {
		m_instance = shared_ptr<Storage>(new Storage());
	}
	return m_instance;
}	

Storage::~Storage() {
	writeToFile();
	m_instance = NULL;
	sync();
}
void Storage::createUser(const User & t_user) {
	m_userList.push_back(t_user);
}
list<User> Storage::queryUser(function<bool(const User &)> filter) const {

	list<User>::const_iterator iter = m_userList.begin();
	list<User> temp;
	for (; iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			temp.push_back(*iter);
		}
	}
	return temp;
}
int Storage::updateUser(std::function<bool(const User &)> filter, std::function<void(User &)> switcher) {
	int number = 0;
	list<User>::iterator iter;
	for (iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			number++;
			switcher(*iter);
		}
	}
	return number;
}
int Storage::deleteUser(std::function<bool(const User &)> filter) {
	int number = 0;
	list<User>::iterator iter; 
	for(iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			number++;
			iter = m_userList.erase(iter);
		}
	}
	return number;
}
void Storage::createMeeting(const Meeting & t_meeting) {
	m_meetingList.push_back(t_meeting);
}
list<Meeting> Storage::queryMeeting(function<bool(const Meeting &)> filter) const {
	list<Meeting> temp;
	list<Meeting>::const_iterator iter = m_meetingList.begin();
	for (iter; iter != m_meetingList.end(); iter++) {
		if (filter(*iter)) {
			temp.push_back(*iter);
		}
	}
	return temp;
}
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter, std::function<void(Meeting &)> switcher) {
	int number = 0;
	list<Meeting>::iterator iter;
	for (iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		if (filter(*iter)) {
			number++;
			switcher(*iter);
		}
	}
	return number;
}
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
	int number = 0;
	list<Meeting>::iterator iter = m_meetingList.begin(); 
	while(iter != m_meetingList.end()) {
		if (filter(*iter)) {
			number++;
			iter = m_meetingList.erase(iter);
		} else {
			iter++;
		}
	}
	return number;
}
bool Storage::sync(void) {
	if (m_dirty) writeToFile();
	if (writeToFile()) return true;
	return false;
}

std::shared_ptr<Storage> Storage::m_instance = NULL;