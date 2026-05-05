#include "Exam.h"
#include <iostream>

// Base Exam class implementation
Exam::Exam(const std::string& id, const std::string& name, const std::string& type,
           const std::string& dept, const std::string& date, const std::string& time,
           int duration, int maxMarks, const std::string& venue)
    : examId(id), examName(name), examType(type), department(dept), date(date),
      time(time), duration(duration), maxMarks(maxMarks), venue(venue) {}

Exam::~Exam() {}

std::string Exam::getExamId() const {
    return examId;
}

std::string Exam::getExamName() const {
    return examName;
}

std::string Exam::getExamType() const {
    return examType;
}

std::string Exam::getDepartment() const {
    return department;
}

std::string Exam::getDate() const {
    return date;
}

std::string Exam::getTime() const {
    return time;
}

int Exam::getDuration() const {
    return duration;
}

int Exam::getMaxMarks() const {
    return maxMarks;
}

std::string Exam::getVenue() const {
    return venue;
}

void Exam::setDate(const std::string& date) {
    this->date = date;
}

void Exam::setTime(const std::string& time) {
    this->time = time;
}

void Exam::setVenue(const std::string& venue) {
    this->venue = venue;
}

void Exam::setMaxMarks(int marks) {
    maxMarks = marks;
}

void Exam::displayExamInfo() const {
    std::cout << "\n========== Exam Information ==========\n"
              << "Exam ID: " << examId << "\n"
              << "Exam Name: " << examName << "\n"
              << "Exam Type: " << examType << "\n"
              << "Department: " << department << "\n"
              << "Date: " << date << "\n"
              << "Time: " << time << "\n"
              << "Duration: " << duration << " minutes\n"
              << "Max Marks: " << maxMarks << "\n"
              << "Venue: " << venue << "\n"
              << "======================================\n";
}

// Midterm Exam
Midterm::Midterm(const std::string& id, const std::string& name, const std::string& dept,
                 const std::string& date, const std::string& time, int duration,
                 int maxMarks, const std::string& venue)
    : Exam(id, name, "Midterm", dept, date, time, duration, maxMarks, venue) {}

void Midterm::displayExamInfo() const {
    std::cout << "\n========== MIDTERM EXAM ==========\n";
    Exam::displayExamInfo();
}

// Final Exam
Final::Final(const std::string& id, const std::string& name, const std::string& dept,
             const std::string& date, const std::string& time, int duration,
             int maxMarks, const std::string& venue)
    : Exam(id, name, "Final", dept, date, time, duration, maxMarks, venue) {}

void Final::displayExamInfo() const {
    std::cout << "\n========== FINAL EXAM ==========\n";
    Exam::displayExamInfo();
}

// Quiz Exam
Quiz::Quiz(const std::string& id, const std::string& name, const std::string& dept,
           const std::string& date, const std::string& time, int duration,
           int maxMarks, const std::string& venue)
    : Exam(id, name, "Quiz", dept, date, time, duration, maxMarks, venue) {}

void Quiz::displayExamInfo() const {
    std::cout << "\n========== QUIZ ==========\n";
    Exam::displayExamInfo();
}

// Assignment Exam
Assignment::Assignment(const std::string& id, const std::string& name, const std::string& dept,
                       const std::string& date, const std::string& time, int duration,
                       int maxMarks, const std::string& venue)
    : Exam(id, name, "Assignment", dept, date, time, duration, maxMarks, venue) {}

void Assignment::displayExamInfo() const {
    std::cout << "\n========== ASSIGNMENT ==========\n";
    Exam::displayExamInfo();
}
