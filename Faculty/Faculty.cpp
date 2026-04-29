#include "Faculty.h"
#include <iostream>
#include <algorithm>

Faculty::Faculty(const std::string& id, const std::string& name, const std::string& email, 
                 const std::string& phone, const std::string& employeeId, const std::string& department,
                 const std::string& designation, double salary)
    : Person(id, name, email, phone), employeeId(employeeId), department(department), 
      designation(designation), salary(salary) {}

Faculty::~Faculty() {}

std::string Faculty::getEmployeeId() const {
    return employeeId;
}

std::string Faculty::getDepartment() const {
    return department;
}

std::string Faculty::getDesignation() const {
    return designation;
}

double Faculty::getSalary() const {
    return salary;
}

std::vector<std::string> Faculty::getCoursesTaught() const {
    return coursesTaught;
}

void Faculty::setDepartment(const std::string& department) {
    this->department = department;
}

void Faculty::setDesignation(const std::string& designation) {
    this->designation = designation;
}

void Faculty::setSalary(double salary) {
    this->salary = salary;
}

void Faculty::assignCourse(const std::string& course) {
    coursesTaught.push_back(course);
    std::cout << "Faculty member " << name << " assigned to course: " << course << "\n";
}

void Faculty::removeCourse(const std::string& course) {
    auto it = std::find(coursesTaught.begin(), coursesTaught.end(), course);
    if (it != coursesTaught.end()) {
        coursesTaught.erase(it);
        std::cout << "Faculty member " << name << " removed from course: " << course << "\n";
    }
}

void Faculty::displayInfo() const {
    Person::displayInfo();
    std::cout << "Employee ID: " << employeeId << "\n"
              << "Department: " << department << "\n"
              << "Designation: " << designation << "\n"
              << "Salary: R" << salary << "\n";
    
    if (!coursesTaught.empty()) {
        std::cout << "Courses Taught: ";
        for (const auto& course : coursesTaught) {
            std::cout << course << " ";
        }
        std::cout << "\n";
    }
}
