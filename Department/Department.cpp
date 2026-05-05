#include "Department.h"
#include "../Exam/ExamSchedule.h"
#include <iostream>
#include <algorithm>

// Base Department class implementation
Department::Department(const std::string& deptId, const std::string& deptName, const std::string& head)
    : departmentId(deptId), departmentName(deptName), headOfDepartment(head), totalStudents(0), 
      examSchedule(nullptr) {}

Department::~Department() {
    if (examSchedule != nullptr) {
        delete examSchedule;
    }
}

std::string Department::getDepartmentId() const {
    return departmentId;
}

std::string Department::getDepartmentName() const {
    return departmentName;
}

std::string Department::getHeadOfDepartment() const {
    return headOfDepartment;
}

int Department::getTotalStudents() const {
    return totalStudents;
}

std::vector<Faculty*> Department::getFacultyMembers() const {
    return facultyMembers;
}

ExamSchedule* Department::getExamSchedule() const {
    return examSchedule;
}

void Department::setHeadOfDepartment(const std::string& head) {
    headOfDepartment = head;
}

void Department::setTotalStudents(int count) {
    totalStudents = count;
}

void Department::addFaculty(Faculty* faculty) {
    facultyMembers.push_back(faculty);
    std::cout << "Faculty member " << faculty->getName() << " added to department.\n";
}

void Department::removeFaculty(const std::string& employeeId) {
    auto it = std::find_if(facultyMembers.begin(), facultyMembers.end(),
        [&employeeId](Faculty* f) { return f->getEmployeeId() == employeeId; });
    
    if (it != facultyMembers.end()) {
        std::cout << "Faculty member removed from department.\n";
        facultyMembers.erase(it);
    }
}

void Department::initializeExamSchedule(const std::string& semester) {
    if (examSchedule == nullptr) {
        std::string scheduleId = departmentId + "_SCHEDULE_" + semester;
        examSchedule = new ExamSchedule(scheduleId, departmentName, semester);
        std::cout << "Exam schedule initialized for " << departmentName << " (" << semester << ").\n";
    } else {
        std::cout << "Exam schedule already exists for this department.\n";
    }
}

void Department::displayExamSchedule() const {
    if (examSchedule != nullptr) {
        examSchedule->displayScheduleInfo();
        examSchedule->displayAllSections();
    } else {
        std::cout << "No exam schedule available for " << departmentName << ".\n";
    }
}

void Department::displayDepartmentInfo() const {
    std::cout << "\n========== Department Information ==========\n"
              << "Department ID: " << departmentId << "\n"
              << "Department Name: " << departmentName << "\n"
              << "Head of Department: " << headOfDepartment << "\n"
              << "Total Students: " << totalStudents << "\n"
              << "Faculty Members: " << facultyMembers.size() << "\n"
              << "=========================================\n";
}

// Specific Department Implementations
ComputerScience::ComputerScience(const std::string& deptId, const std::string& head)
    : Department(deptId, "Computer Science", head) {}

void ComputerScience::displayDepartmentInfo() const {
    std::cout << "\n========== COMPUTER SCIENCE DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}

Electronics::Electronics(const std::string& deptId, const std::string& head)
    : Department(deptId, "Electronics", head) {}

void Electronics::displayDepartmentInfo() const {
    std::cout << "\n========== ELECTRONICS DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}

Mathematics::Mathematics(const std::string& deptId, const std::string& head)
    : Department(deptId, "Mathematics", head) {}

void Mathematics::displayDepartmentInfo() const {
    std::cout << "\n========== MATHEMATICS DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}

Physics::Physics(const std::string& deptId, const std::string& head)
    : Department(deptId, "Physics", head) {}

void Physics::displayDepartmentInfo() const {
    std::cout << "\n========== PHYSICS DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}

Statistics::Statistics(const std::string& deptId, const std::string& head)
    : Department(deptId, "Statistics", head) {}

void Statistics::displayDepartmentInfo() const {
    std::cout << "\n========== STATISTICS DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}

Engineering::Engineering(const std::string& deptId, const std::string& head)
    : Department(deptId, "Engineering", head) {}

void Engineering::displayDepartmentInfo() const {
    std::cout << "\n========== ENGINEERING DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}

InformationTechnology::InformationTechnology(const std::string& deptId, const std::string& head)
    : Department(deptId, "Information Technology", head) {}

void InformationTechnology::displayDepartmentInfo() const {
    std::cout << "\n========== INFORMATION TECHNOLOGY DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}

Cybersecurity::Cybersecurity(const std::string& deptId, const std::string& head)
    : Department(deptId, "Cybersecurity", head) {}

void Cybersecurity::displayDepartmentInfo() const {
    std::cout << "\n========== CYBERSECURITY DEPARTMENT ==========\n";
    Department::displayDepartmentInfo();
}
