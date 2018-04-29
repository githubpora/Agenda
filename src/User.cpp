#include "User.hpp"

using namespace std;

User::User(const User & t_user) {
	m_name = t_user.m_name;
	m_password = t_user.m_password;
	m_email = t_user.m_email;
	m_phone = t_user.m_phone;
}

User::User(std::string username, std::string userpassword, std::string useremail, std::string userphone) {
	m_name = username;
	m_password = userpassword;
	m_email = useremail;
	m_phone = userphone;
}

std::string User::getName() const {
	return m_name;
}

void User::setName(std::string name) {
	m_name = name;
}

std::string User::getPassword() const {
	return m_password;
}

void User::setPassword(std::string password) {
	m_password = password;
}

std::string User::getEmail() const {
	return m_email;
}

void User::setEmail(std::string email) {
	m_email = email;
}

std::string User::getPhone() const {
	return m_phone;
}

void User::setPhone(std::string phone) {
	m_phone = phone;
}
