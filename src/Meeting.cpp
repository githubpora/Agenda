#include "Meeting.hpp"
#include "Date.hpp"
#include <vector>
using namespace std;

Meeting::Meeting(string t_sponsor, vector<string> t_participator, Date t_startTime,
	Date t_endTime, string t_title):m_sponsor(t_sponsor), m_participators(t_participator),
    m_title(t_title) {
    if (t_startTime <= t_endTime) {
    	if (Date::isValid(t_startTime) && Date::isValid(t_endTime)) {
    		m_startDate = t_startTime;
    		m_endDate = t_endTime;
    	}
    }
}

Meeting::Meeting(const Meeting &t_meeting) {
	m_sponsor = t_meeting.getSponsor();
	m_participators = t_meeting.getParticipator();
	m_startDate = t_meeting.getStartDate();
	m_endDate = t_meeting.getEndDate();
	m_title = t_meeting.getTitle();
}

std::string Meeting::getSponsor(void) const {
	return m_sponsor;
}

void Meeting::setSponsor(const std::string t_sponsor) {
	m_sponsor = t_sponsor;
}

std::vector<std::string> Meeting::getParticipator(void) const {
	return m_participators;
}

void Meeting::setParticipator(const std::vector<std::string> t_participators) {
	int it = 0;
	for (it = 0; it < t_participators.size(); ++it) {
		m_participators[it] = t_participators[it];
	}
}

Date Meeting::getStartDate(void) const {
	return m_startDate;
}

void Meeting::setStartDate(const Date t_startTime) {
	m_startDate = t_startTime;
}
Date Meeting::getEndDate(void) const {
	return m_endDate;
}

void Meeting::setEndDate(const Date t_endTime) {
	m_endDate =  t_endTime;
}

std::string Meeting::getTitle(void) const {
	return m_title;
}

void Meeting::setTitle(const std::string t_title) {
	m_title = t_title;
}

bool Meeting::isParticipator(const std::string t_username) const {
	int i = 0;
	for (i = 0; i < m_participators.size(); i++) {
		if (m_participators[i] == t_username) {
			return true;
		}
	}
	return false;
}

