#include "AgendaService.hpp"
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

AgendaService::AgendaService() {
	m_storage = Storage::getInstance();
}
AgendaService::~AgendaService() {}

bool AgendaService::userLogIn(const std::string userName, const std::string password) {
	list<User>::iterator it;
	list<User> t = listAllUsers();
	if (t.empty()) {
		return false;
	}
	for (it = t.begin(); it != t.end(); ++it) {
		if (password == it->getPassword()) {
			if (userName == it->getName()) {
				return true;
			}
		}
	}
	return false;
}

bool AgendaService::userRegister(const std::string userName, const std::string password,
                  const std::string email, const std::string phone) {
	list<User>::iterator iter;
	list<User> y = listAllUsers();
	for (iter = y.begin(); iter != y.end(); iter++) {
		if (userName == iter->getName()) {
			return false;
		}
	}
	User ty(userName, password, email, phone);
	m_storage->createUser(ty);
	return true;
}
bool AgendaService::changeuserpassword(std::string userName, const std::string password) {
	auto judge = [&userName, &password](const User & one)->bool {
		if (userName == one.getName()) {
			return true;
		}
		return false;
	};
	auto swither = [&userName, &password](User & one)->void {
		if (userName == one.getName()) {
			one.setPassword(password);
		}
	};
	if (m_storage->updateUser(judge, swither) != 0) {
		return true;
	} else {
		return false;
	}
}
bool AgendaService::deleteUser(const std::string userName, const std::string password) {
	auto judge = [&userName,&password](const User & one)->bool {
		if (userName == one.getName() && password == one.getPassword()) {
			return true;
		}
		return false;
	};
	if (m_storage->deleteUser(judge) == 0) {
		return false;
	}
	auto ju = [&userName](const Meeting& meeting)->bool {
		if (userName == meeting.getSponsor()) {
			return true;
		} else if (meeting.isParticipator(userName)) {
			return true;
		} else {
			return false;
		}
	};
	if (m_storage->deleteMeeting(ju) != 0) {
		return true;
	}
	return false;
}


list<User> AgendaService::listAllUsers(void) const {
	list<User> tep;
	auto judge = [](const User & th)->bool{return true;};
	tep = m_storage->queryUser(judge);
	return tep;
}

bool AgendaService::createMeeting(const std::string userName, const std::string title,
                   const std::string startDate, const std::string endDate,
                   const std::vector<std::string> participator) {
	list<User>::iterator it;
	int flag = 0;
	int count = participator.size();
	list<User> temp =  listAllUsers();

    list<Meeting>::iterator iter;
    list<Meeting> judge = listAllMeetings(userName);
    for (iter = judge.begin(); iter != judge.end(); iter++) {
    	if (title == iter->getTitle()) {
    		return false;
    	}
    }

	for (it = temp.begin(); it != temp.end(); it++) {
		if (it->getName() == userName) {
			flag = 1;
		}
	}
	if (!flag) {
		return false;
	}
	int k = 0;
	for (int i = 0; i < count; ++i) {
		for (it = temp.begin(); it != temp.end(); it++) {
			if (it->getName() == participator[i]) {
				k++;
			}
			if (userName == participator[i]) {
				return false;
			}
		}
	}
	if (k == count) {
		if (!Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate))) {
			return false;
		}
		for (iter = judge.begin(); iter != judge.end(); iter++) {
			if (Date::stringToDate(endDate) < iter->getStartDate()) {
				return false;
			} else if (Date::stringToDate(startDate) > iter->getEndDate()) {
				return false;
			}
		}
		if (Date::stringToDate(endDate) <= Date::stringToDate(startDate)) {
			return false;
		}

		Meeting meet(userName, participator,Date::stringToDate(startDate),Date::stringToDate(endDate),title);
		m_storage->createMeeting(meet);
		return true;
	} else {
		return false;
	}
}

//search meetings by username and title (user as sponsor or participator)
std::list<Meeting> AgendaService::meetingQuery(const std::string userName, const std::string title) const {
	auto judge = [&userName, &title](const Meeting & one)->bool {
		vector<string>::iterator fal;
		vector<string> peat = one.getParticipator();
		int flag = 0;
		for (fal = peat.begin(); fal != peat.end(); ++fal) {
			if (userName == *fal) {
				flag = 1;
			}
		}
		if (userName == one.getSponsor() || flag == 1) {
			if (title == one.getTitle()) {
				return true;
			}
		}
		return false;
	};
	list<Meeting> kep;
	kep = m_storage->queryMeeting(judge);
	return kep;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,const std::string startDate,
                                const std::string endDate) const {
	auto judge = [&userName, &startDate, &endDate](const Meeting & one)->bool {
		vector<string>::iterator fal;
		vector<string> peat = one.getParticipator();
		int flag = 0;
		for (fal = peat.begin(); fal != peat.end(); ++fal) {
			if (userName == *fal) {
				flag = 1;
			}
		}
		if (userName == one.getSponsor() || flag == 1) {
			if (endDate == Date::dateToString(one.getEndDate()) && startDate == Date::dateToString(one.getStartDate())) {
				return true;
			}
		}
		return false;
	};
	list<Meeting> keep;
	keep = m_storage->queryMeeting(judge);
	return keep;
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
	auto judge = [&userName](const Meeting & one)->bool {
		vector<string>::iterator fall;
		vector<string> peat = one.getParticipator();
		int flag = 0;
		for (fall = peat.begin(); fall != peat.end(); ++fall) {
			if (userName == *fall) {
				flag = 1;
			}
		}
		if (userName == one.getSponsor() || flag == 1) {
			return true;
		}
		return false;
	};
	list<Meeting> love;
	love = m_storage->queryMeeting(judge);
	return love;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
	auto judge = [&userName](const Meeting & one)->bool {
		if (userName == one.getSponsor()) {
			return true;
		}
		return false;
	};
	list<Meeting> l;
	l = m_storage->queryMeeting(judge);
	return l;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string userName) const {
	auto judge = [&userName](const Meeting & one)->bool {
		vector<string>::iterator fall;
		vector<string> peat = one.getParticipator();
		int flag = 0;
		for (fall = peat.begin(); fall != peat.end(); ++fall) {
			if (userName == *fall) {
				flag = 1;
			}
		}
		if (userName != one.getSponsor() || flag == 1) {
			return true;
		}
		return false;
	};
	list<Meeting> l;
	l = m_storage->queryMeeting(judge);
	return l;
}

bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
	auto judge = [&userName, &title](const Meeting & other)->bool {
		if (userName == other.getSponsor() && title == other.getTitle()) {
			return true;
		} else {
			return false;
		}
	};
	int flag = 0;
	flag = m_storage->deleteMeeting(judge);
	if (flag) return true;
	return false;
}

bool AgendaService::deleteAllMeetings(const std::string userName) {
	auto judge = [&userName](const Meeting & m)->bool {
		if (userName == m.getSponsor()) {
			return true;
		}
		return false;
	};
	int flag = 0;
	flag = m_storage->deleteMeeting(judge);
	if (flag) {
		return true;
	}
	return false;
}

void AgendaService::startAgenda(void) {
	m_storage->getInstance();
}

void AgendaService::quitAgenda(void) {
	m_storage->sync();
}


std::shared_ptr<Storage> m_storage = nullptr;