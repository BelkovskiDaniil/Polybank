#include "include/person.h"

big_int person::id = 0;

person::person() {
  if (id == 0) {
    std::ifstream file("max_person_id.txt");
    std::string s;
    file >> s;
    id = big_int(s);
    if (id != 0) ++id;
    file.close();
  }
}

std::string person::get_login() const {
  return login_;
}

std::string person::get_password() const {
  return password_;
}

std::string person::get_first_name() const {
  return first_name_;
}

std::string person::get_second_name() const {
  return second_name_;
}

std::string person::get_address() const {
  return address_;
}

std::string person::get_passport_id() const {
  return passport_id_;
}

int person::get_money_limit() const {
  return money_limit_;
}

bool person::is_doubtful() const {
  return is_doubtful_;
}

big_int person::get_id() const {
  return id_;
}

void person::set_login(const std::string &login) {
  login_ = login;
}

void person::set_password(const std::string &password) {
  password_ = password;
}

void person::set_first_name(const std::string &first_name) {
  first_name_ = first_name;
}

void person::set_second_name(const std::string &second_name) {
  second_name_ = second_name;
}

void person::set_address(const std::string &address) {
  address_ = address;
}

void person::set_passport_id(const std::string &passport_id) {
  passport_id_ = passport_id;
}

void person::update() {
  is_doubtful_ = address_.empty() || passport_id_.empty();
  money_limit_ = (is_doubtful_ ? money_limit : 0);
}

void person::assign_id() {
  id_ = id++;
}

