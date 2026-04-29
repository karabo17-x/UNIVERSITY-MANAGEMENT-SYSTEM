#include "Person.h"
#include <iostream>

Person::Person(const std::string& id, const std::string& name, 
               const std::string& email, const std::string& phone)
    : id(id), name(name), email(email), phone(phone) {}

Person::~Person() {}

std::string Person::getId() const {
    return id;
}

std::string Person::getName() const {
    return name;
}

std::string Person::getEmail() const {
    return email;
}

std::string Person::getPhone() const {
    return phone;
}

void Person::setName(const std::string& name) {
    this->name = name;
}

void Person::setEmail(const std::string& email) {
    this->email = email;
}

void Person::setPhone(const std::string& phone) {
    this->phone = phone;
}

void Person::displayInfo() const {
    std::cout << "ID: " << id << "\n"
              << "Name: " << name << "\n"
              << "Email: " << email << "\n"
              << "Phone: " << phone << "\n";
}
