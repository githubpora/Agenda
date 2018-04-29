#include "Date.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;

Date::Date() {}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) : m_year(t_year),
	m_month(t_month), m_day(t_day),m_minute(t_minute),m_hour(t_hour) {}

int Date::getYear(void) const {
	return m_year;
}
Date::Date(std::string datestring) {
	stringToDate(datestring);
}
void Date::setYear(const int t_year) {
	m_year = t_year;
}

int Date::getMonth(void) const {
	return m_month;
}

void Date::setMonth(const int t_month) {
	m_month = t_month;
}

int Date::getDay(void) const {
	return m_day;
}

void Date::setDay(const int t_day) {
	m_day = t_day;
}

int Date::getHour(void) const {
	return m_hour;
}

void Date::setHour(const int t_hour) {
	m_hour = t_hour;
}

int Date::getMinute(void) const {
	return m_minute;
}

void Date::setMinute(const int y_minute) {
	m_minute = y_minute;
}

bool Date::isValid(const Date t_date) {
	if (t_date.getYear() > 9999 || t_date.getYear() < 1000) {
		return false;
	}
	if (t_date.getMonth() > 12 || t_date.getMonth() < 1) return false;
	switch(t_date.getMonth()) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		    if (t_date.getDay() < 1 || t_date.getDay() > 31) return false;
		    break;
		case 4: case 6: case 9: case 11:
		    if (t_date.getDay() < 1 || t_date.getDay() > 30) {
		    	return false;
		    }
		    break;
		case 2:
		    if (t_date.getYear()%4 == 0 && t_date.getYear()%100 != 0 || t_date.getYear()%400 == 0) {
		    	if (t_date.getDay()< 1 || t_date.getDay() > 29) {
		    		return false;
		    	}
		    } else {
		    	if (t_date.getDay() < 1 || t_date.getDay()>28) {
		    		return false;
		    	}
		    }
		    break;
	}
	if (t_date.getHour() < 0 || t_date.getHour() > 23) return false;
	if (t_date.getMinute() < 0 || t_date.getMinute() > 59) return false;
	return true;
}

Date Date::stringToDate(const std::string datestring) {
	Date temp;
	stringstream t;
	char s;
	t.str(datestring);
	int y = 0, m = 0, d = 0, min = 0,h = 0;
	t >> y >> s;
	t >> m >> s;
	t >> d >> s;
	t >> h >> s >> min;
	temp.setYear(y);
	temp.setMonth(m);
	temp.setDay(d);
	temp.setMinute(min);
	temp.setHour(h);
	return temp;
}
std::string Date::dateToString(Date t_da) {
	string s;
	if(Date::isValid(t_da)) {
		stringstream t;
		t << t_da.getYear() << "-";
		t << setfill('0') << setw(2) << t_da.getMonth() << "-";
		t << setfill('0') << setw(2) << t_da.getDay() << "/";
		t << setfill('0') << setw(2) << t_da.getHour() << ":";
		t << setfill('0') << setw(2) << t_da.getMinute();
		s = t.str();
		return s;
	} else {
		s = "0000-00-00/00:00";
		return s;
	}
}

Date &Date::operator=(const Date &t_date) {
	m_year = t_date.getYear();
	m_month = t_date.getMonth();
	m_day = t_date.getDay();
	m_hour = t_date.getHour();
	m_minute = t_date.getMinute();
	return *this;
}

bool Date::operator==(const Date &t_date) const {
	if (m_year == t_date.getYear()) {
		if (m_month == t_date.getMonth()) {
			if (m_day == t_date.getDay()) {
				if (m_hour == t_date.getHour()) {
					if (m_minute == t_date.getMinute()) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Date::operator>(const Date &t_date) const{
	if (m_year > t_date.getYear()) {
		return true;
	} else if (m_year < t_date.getYear()) {
		return false;
	} else {
		if (m_month > t_date.getMonth()) {
			return true;
		} else if (m_month < t_date.getMonth()) {
			return false;
		} else {
			if (m_day > t_date.getDay()) {
				return true;
			} else if (m_day < t_date.getDay()) {
				return false;
			} else {
				if (m_hour > t_date.getHour()) {
					return true;
				} else if (m_day < t_date.getDay()) {
					return false;
				} else {
					if (m_minute > t_date.getMinute()) {
						return true;
					} else if (m_minute <= t_date.getMinute()) {
						return false;
					}
				}
			}
		}
	}
}

bool Date::operator<(const Date &t_date) const {
	if (m_year > t_date.getYear()) {
		return false;
	} else if (m_year < t_date.getYear()) {
		return true;
	} else {
		if (m_month > t_date.getMonth()) {
			return false;
		} else if (m_month < t_date.getMonth()) {
			return true;
		} else {
			if (m_day > t_date.getDay()) {
				return false;
			} else if (m_day < t_date.getDay()) {
				return true;
			} else {
				if (m_hour > t_date.getHour()) {
					return false;
				} else if (m_day < t_date.getDay()) {
					return true;
				} else {
					if (m_minute >= t_date.getMinute()) {
						return false;
					} else if (m_minute < t_date.getMinute()) {
						return true;
					}
				}
			}
		}
	}

}

bool Date::operator>=(const Date &t_date) const {
	if (*this < t_date) return false;
	return true;
}

bool Date::operator<=(const Date &t_date) const {
	if (*this > t_date) return false;
	return true;
}
