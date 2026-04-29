#include "Student.h"
#include <iostream>
#include <algorithm>

Student::Student(const std::string& id, const std::string& name, const std::string& email, 
                 const std::string& phone, const std::string& rollNumber, const std::string& major)
    : Person(id, name, email, phone), rollNumber(rollNumber), major(major), gpa(0.0), residenceBlock("") {}

std::string Student::getRollNumber() const {
    return rollNumber;
}

std::string Student::getMajor() const {
    return major;
}

double Student::getGPA() const {
    return gpa;
}

std::string Student::getResidenceBlock() const {
    return residenceBlock;
}

std::vector<std::string> Student::getEnrolledCourses() const {
    return enrolledCourses;
}

void Student::setMajor(const std::string& major) {
    this->major = major;
}

void Student::setGPA(double gpa) {
    this->gpa = gpa;
}

void Student::setResidenceBlock(const std::string& block) {
    this->residenceBlock = block;
}

void Student::enrollCourse(const std::string& course) {
    enrolledCourses.push_back(course);
    std::cout << "Student " << name << " enrolled in course: " << course << "\n";
}

void Student::dropCourse(const std::string& course) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), course);
    if (it != enrolledCourses.end()) {
        enrolledCourses.erase(it);
        std::cout << "Student " << name << " dropped course: " << course << "\n";
    }
}

void Student::displayInfo() const {
    Person::displayInfo();
    std::cout << "Roll Number: " << rollNumber << "\n"
              << "Major: " << major << "\n"
              << "GPA: " << gpa << "\n"
              << "Residence Block: " << (residenceBlock.empty() ? "Not Assigned" : residenceBlock) << "\n";
    
    if (!enrolledCourses.empty()) {
        std::cout << "Enrolled Courses: ";
        for (const auto& course : enrolledCourses) {
            std::cout << course << " ";
        }
        std::cout << "\n";
    }
}
