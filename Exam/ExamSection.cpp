#include "ExamSection.h"
#include <iostream>
#include <algorithm>

ExamSection::ExamSection(const std::string& id, const std::string& name, const std::string& dept,
                         const std::string& invigilator, int capacity, const std::string& room)
    : sectionId(id), sectionName(name), department(dept), invigilator(invigilator),
      capacity(capacity), roomNumber(room), isActive(true) {}

ExamSection::~ExamSection() {
    for (auto exam : exams) {
        delete exam;
    }
    exams.clear();
}

std::string ExamSection::getSectionId() const {
    return sectionId;
}

std::string ExamSection::getSectionName() const {
    return sectionName;
}

std::string ExamSection::getDepartment() const {
    return department;
}

std::string ExamSection::getInvigilator() const {
    return invigilator;
}

int ExamSection::getCapacity() const {
    return capacity;
}

int ExamSection::getEnrolledCount() const {
    return enrolledStudents.size();
}

std::string ExamSection::getRoomNumber() const {
    return roomNumber;
}

bool ExamSection::getIsActive() const {
    return isActive;
}

std::vector<std::string> ExamSection::getEnrolledStudents() const {
    return enrolledStudents;
}

std::vector<Exam*> ExamSection::getExams() const {
    return exams;
}

void ExamSection::setInvigilator(const std::string& invigilator) {
    this->invigilator = invigilator;
}

void ExamSection::setCapacity(int capacity) {
    this->capacity = capacity;
}

void ExamSection::setRoomNumber(const std::string& room) {
    roomNumber = room;
}

void ExamSection::setIsActive(bool active) {
    isActive = active;
}

void ExamSection::enrollStudent(const std::string& studentId) {
    if (getEnrolledCount() >= capacity) {
        std::cout << "Section is full! Cannot enroll more students.\n";
        return;
    }
    
    if (!isStudentEnrolled(studentId)) {
        enrolledStudents.push_back(studentId);
        std::cout << "Student " << studentId << " enrolled in exam section " << sectionName << ".\n";
    } else {
        std::cout << "Student is already enrolled in this section.\n";
    }
}

void ExamSection::removeStudent(const std::string& studentId) {
    auto it = std::find(enrolledStudents.begin(), enrolledStudents.end(), studentId);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);
        std::cout << "Student " << studentId << " removed from exam section.\n";
    } else {
        std::cout << "Student not found in this section.\n";
    }
}

bool ExamSection::isStudentEnrolled(const std::string& studentId) const {
    return std::find(enrolledStudents.begin(), enrolledStudents.end(), studentId) 
           != enrolledStudents.end();
}

void ExamSection::addExam(Exam* exam) {
    exams.push_back(exam);
    std::cout << "Exam " << exam->getExamName() << " added to section " << sectionName << ".\n";
}

void ExamSection::removeExam(const std::string& examId) {
    auto it = std::find_if(exams.begin(), exams.end(),
        [&examId](Exam* e) { return e->getExamId() == examId; });
    
    if (it != exams.end()) {
        delete *it;
        exams.erase(it);
        std::cout << "Exam removed from section.\n";
    } else {
        std::cout << "Exam not found in this section.\n";
    }
}

Exam* ExamSection::getExamById(const std::string& examId) const {
    auto it = std::find_if(exams.begin(), exams.end(),
        [&examId](Exam* e) { return e->getExamId() == examId; });
    
    if (it != exams.end()) {
        return *it;
    }
    return nullptr;
}

void ExamSection::displaySectionInfo() const {
    std::cout << "\n========== Exam Section Information ==========\n"
              << "Section ID: " << sectionId << "\n"
              << "Section Name: " << sectionName << "\n"
              << "Department: " << department << "\n"
              << "Invigilator: " << invigilator << "\n"
              << "Room Number: " << roomNumber << "\n"
              << "Capacity: " << capacity << "\n"
              << "Enrolled Students: " << getEnrolledCount() << "\n"
              << "Status: " << (isActive ? "Active" : "Inactive") << "\n"
              << "Total Exams: " << exams.size() << "\n"
              << "============================================\n";
}

void ExamSection::displayExamSchedule() const {
    std::cout << "\n========== Exam Schedule for " << sectionName << " ==========\n";
    if (exams.empty()) {
        std::cout << "No exams scheduled for this section.\n";
    } else {
        for (int i = 0; i < exams.size(); i++) {
            std::cout << "\n[" << (i + 1) << "] " << exams[i]->getExamName()
                      << " (" << exams[i]->getExamType() << ")\n"
                      << "    Date: " << exams[i]->getDate() << "\n"
                      << "    Time: " << exams[i]->getTime() << "\n"
                      << "    Duration: " << exams[i]->getDuration() << " minutes\n"
                      << "    Max Marks: " << exams[i]->getMaxMarks() << "\n";
        }
    }
    std::cout << "===============================================\n";
}

void ExamSection::displayEnrolledStudents() const {
    std::cout << "\n========== Enrolled Students in " << sectionName << " ==========\n";
    if (enrolledStudents.empty()) {
        std::cout << "No students enrolled in this section.\n";
    } else {
        for (int i = 0; i < enrolledStudents.size(); i++) {
            std::cout << (i + 1) << ". " << enrolledStudents[i] << "\n";
        }
    }
    std::cout << "======================================================\n";
}
