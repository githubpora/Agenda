#include "AgendaUI.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <iomanip>

using namespace std;

AgendaUI::AgendaUI() {}

void AgendaUI::OperationLoop(void) {
	startAgenda();
}

void AgendaUI::startAgenda(void) {
	while(true) {
		cout << "                  Welcome to Agenda" << endl;
		cout << "-----------------------Agenda-------------------------" << endl;
		cout << "Action : " << endl;
		cout << "l    - log in Agenda by user name and password" << endl;
		cout << "r    - register an Agenda account" << endl;
		cout << "q    - quit Agenda" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << endl;
		cout << "Agenda : ~$ ";
		string input;
		cin >> input;
		executeOperation(input);
		if (input == "q") {
			break;
		}
	}
}

/**
 * catch user's operation
 * @return the operation
 */
std::string AgendaUI::getOperation() {
	cout << endl;
	cout << "-------------------------Agenda-----------------------" << endl;
	cout << "Action : "<< endl;
	cout << "o    - log out Agenda" << endl;
	cout << "dc   - delete Agenda account" << endl;
	cout << "lu   - list all Agenda user" << endl;
	cout << "cm   - create a meeting" << endl;
	cout << "la   - list all meetings" << endl;
	cout << "las  - list all sponsor meetings" << endl;
	cout << "qm   - query meeting by title" << endl;
	cout << "qt   - query meeting by time interval" << endl;
	cout << "dm   - delete meeting by title" << endl;
	cout << "da   - delete all meetings" << endl;
	cout << "ci   - change the user information" << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "Agenda@" << m_userName << " : # ";
	string operation;
	cin >> operation;
	cout << endl;
	return operation;
}

bool AgendaUI::executeOperation(std::string t_operation) {
	if (t_operation == "l") {
		userLogIn();
	} else if (t_operation == "r") {
		userRegister();
	} else if (t_operation == "o") {
		userLogOut();
	} else if (t_operation == "dc") {
		deleteUser();
	} else if (t_operation == "lu") {
		listAllUsers();
	} else if (t_operation == "cm") {
		createMeeting();
	} else if (t_operation == "la") {
		listAllMeetings();
	} else if (t_operation == "las") {
		listAllSponsorMeetings();
	} else if (t_operation == "lap") {
		listAllParticipateMeetings();
	} else if (t_operation == "qm") {
		queryMeetingByTitle();
	} else if (t_operation == "qt") {
		queryMeetingByTimeInterval();
	} else if(t_operation == "dm") {
		deleteMeetingByTitle();
	} else if (t_operation == "da") {
		deleteAllMeetings();
	} else if (t_operation == "ci") {
		changeuserpassword();
	}
	return 0;
}

void AgendaUI::userLogIn(void) {
	cout << endl;
	cout << "[log in] [user name] [password]" << endl;
	cout << "[log in] ";
	string operation;
	cin >> m_userName >> m_userPassword;

	if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
		cout << "[log in] succeed!" << endl;
		operation = getOperation();
		executeOperation(operation);
	} else {
		cout << "[error] log in fail!" << endl; 
	}

}
void AgendaUI::changeuserpassword() {
	cout << endl;
	cout << "[changeuserpassword] [user name] [old password] [new password]" << endl;
	cout << "[changeuserpassword] " << m_userName << " ";
	string old, newone;
	cin >> old >> newone;
	if (old == m_userPassword) {
		m_userPassword = newone;
		m_agendaService.changeuserpassword(m_userName, m_userPassword);
		cout << "[changeuserpassword] succeed!" << endl;
		userLogIn();
	} else {
		cout << "Error password" << endl;
	}
	cout << endl;

}
void AgendaUI::userRegister(void) {
	cout << endl;
	cout << "[register] [user name] [password] [email] [phone]" << endl;
	cout << "[register] ";
	string name, pass, email, phone;
	cin >> name >> pass >> email >> phone;
	m_userName = name;
	m_userPassword = pass;
	if (m_agendaService.userRegister(name,pass, email, phone)) {
		cout << "[register] succeed!" << endl;
	} else {
		cout << "[error] register fail!" << endl;
	}
}

void AgendaUI::quitAgenda(void) {
	cout << endl;
	cout << "Thanks for coming!See you!" << endl;
	cout << endl;
}


void AgendaUI::userLogOut(void) {
	cout << endl;
	cout << "Are you sure to log out?" << endl;
	cout << endl;
}

void AgendaUI::deleteUser(void) {
	if (m_agendaService.deleteUser(m_userName, m_userPassword)) {
		cout << "[delete agenda account] succeed!" << endl;
		cout << endl;
		m_userName = "";
		m_userPassword = "";
		startAgenda();
	} else {
		cout << "Error.Can't delete the user." << endl;
		cout << endl;
		string operation = getOperation();
		executeOperation(operation);
	}
}

void AgendaUI::listAllUsers(void) {
	cout << endl;
	cout << "[list all users]" << endl;
	list<User> temp = m_agendaService.listAllUsers();
	list<User>::iterator it;
	if (temp.empty()) {
		cout << "Error!" << endl;
		return;
	}
	cout << "name" <<"\t" <<"email" << "\t" << "phone"<<endl;
	for (it = temp.begin(); it != temp.end(); it++) {
		cout << it->getName() << "\t" << it->getEmail() << "\t"<<it->getPhone() << endl;
	}
	string operation = getOperation();
	executeOperation(operation);
}

void AgendaUI::createMeeting(void) {
	int number;
	vector<string> participators;
	string title, starttime, endtime;	
	cout << "[create meeting] [the number of participators]" << endl;
	cout << "[create meeting] ";
	cin >> number;
	for (int i = 0; i < number; i++) {
		string t = "";
		cout << "[create meeting] [please enter the participator " << i+1 << " ]" << endl;
		cout << "[create meeting] ";
		cin >> t;
		participators.push_back(t);
	}
	cout << "[create meeting} [title][start time(yyyy-mm-dd/hh:mm)][end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[create meeting] ";
	cin >> title >> starttime >> endtime;
	if (m_agendaService.createMeeting(m_userName,title,starttime,endtime,participators)) {
		cout << "[create meeting] succeed!" << endl;
	} else {
		cout << "[create meeting] error!" << endl;
	}
	string operation = getOperation();
	executeOperation(operation);
}

void AgendaUI::listAllMeetings(void) {
	cout << "[list all meetings]" << endl;
	list<Meeting> temp = m_agendaService.listAllMeetings(m_userName);
	if (temp.empty()) {
		cout << "Error!" << endl;
	} else {
		printMeetings(temp);
	}
	string operation = getOperation();
	executeOperation(operation);
}

/**
 * list all meetings that this user sponsored
 */
void AgendaUI::listAllSponsorMeetings(void) {
	cout << "[list all sponsor meetings]" << endl;
	list<Meeting> temp = m_agendaService.listAllSponsorMeetings(m_userName);
	if (temp.empty()) {
		cout << "Error!" << endl;
	} else {
		printMeetings(temp);
	}
	string operation = getOperation();
	executeOperation(operation);
}

/**
 * list all meetings that this user take part in
 */
void AgendaUI::listAllParticipateMeetings(void) {
	cout << "[list all participate meetings]" << endl;
	list<Meeting> temp = m_agendaService.listAllParticipateMeetings(m_userName);
	if (temp.empty()) {
		cout << "Error!" << endl;
	} else {
		printMeetings(temp);
	}
	string operation = getOperation();
	executeOperation(operation);
}

/**
 * search meetings by title from storage
 */
void AgendaUI::queryMeetingByTitle(void) {
	cout << "[query meeting] [title]" <<endl;
	cout << "[query meeting] ";
	string title;
	cin >> title;
	list<Meeting> temp = m_agendaService.meetingQuery(m_userName,title);
	if (temp.empty()) {
		cout << "Error!" << endl;
	} else {
		printMeetings(temp);
	}
	string operation = getOperation();
	executeOperation(operation);
}

/**
 * search meetings by timeinterval from storage
 */
void AgendaUI::queryMeetingByTimeInterval(void) {
	cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" <<endl;
	cout << "[query meetings] ";
	string starttime,endtime;
	cin >> starttime >> endtime;
	list<Meeting> temp = m_agendaService.meetingQuery(m_userName,starttime,endtime);
	if (temp.empty()) {
		cout << "Error!" << endl;
	} else {
		printMeetings(temp);
	}
	string operation = getOperation();
	executeOperation(operation);
}
/**
 * delete meetings by title from storage
 */
void AgendaUI::deleteMeetingByTitle(void) {
	cout << "[delete meeting] [title]" << endl;
	string title;
	cout << "[delete meeting] ";
	cin >> title;
	cout << endl;
	if (m_agendaService.deleteMeeting(m_userName,title)) {
		cout << "[delete meeting by title] succeed!" << endl;
	} else {
		cout << "[error] delete meeting fail!" << endl;
	}
	string operation = getOperation();
	executeOperation(operation);
}

/**
 * delete all meetings that this user sponsored
 */
void AgendaUI::deleteAllMeetings(void) {
	cout << endl;
	if (m_agendaService.deleteAllMeetings(m_userName)) {
		cout << "[delete all meetings] succeed!" << endl;
	} else {
		cout << "[error] delete meeting fail!" << endl;
	}
	string operation = getOperation();
	executeOperation(operation);
}

/**
 * show the meetings in the screen
 */
void AgendaUI::printMeetings(std::list<Meeting> temp) {
	list<Meeting>::iterator it;
	cout << "title" <<"\t" <<"sponsor" << "\t" << "start time"<< "\t"  << "\t"<< "end time" << "\t" << "\t"<< "participators" << endl;
	for (it = temp.begin(); it != temp.end(); it++) {
		cout << it->getTitle() << "\t" << it->getSponsor() << "\t"<< Date::dateToString(it->getStartDate()) << "\t" << Date::dateToString(it->getEndDate()) << "\t";
		vector<string> re = it->getParticipator();
		cout << re[0];
		if (re.size() > 1) {
			for (int j = 1; j < re.size(); j++) {
				cout << "," << re[j];
			}
		}
		cout << endl;
	}
}

