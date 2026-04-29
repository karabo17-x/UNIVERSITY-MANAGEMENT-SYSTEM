#include "AcademicAdmin.h"
#include "../Student/Student.h"
#include <iostream>
#include <iomanip>

AcademicAdmin::AcademicAdmin(const std::string& adminId, const std::string& adminName)
    : adminId(adminId), adminName(adminName) {}

std::string AcademicAdmin::getAdminId() const {
    return adminId;
}

std::string AcademicAdmin::getAdminName() const {
    return adminName;
}

void AcademicAdmin::assignMarks(const std::string& studentId, const std::string& course, double marks) {
    if (marks < 0 || marks > 100) {
        std::cout << "Invalid marks! Please enter marks between 0 and 100.\n";
        return;
    }
    studentMarks[studentId][course] = marks;
    
    // Automatically calculate and assign grade
    char grade = calculateGrade(marks);
    studentGrades[studentId][course] = grade;
    
    std::cout << "Marks assigned: Student " << studentId << " - Course: " << course 
              << " - Marks: " << marks << " - Grade: " << grade << "\n";
}

double AcademicAdmin::getMarks(const std::string& studentId, const std::string& course) const {
    auto studentIt = studentMarks.find(studentId);
    if (studentIt != studentMarks.end()) {
        auto courseIt = studentIt->second.find(course);
        if (courseIt != studentIt->second.end()) {
            return courseIt->second;
        }
    }
    return -1.0; // Return -1 if not found
}

void AcademicAdmin::assignGrade(const std::string& studentId, const std::string& course, char grade) {
    studentGrades[studentId][course] = grade;
    std::cout << "Grade assigned: Student " << studentId << " - Course: " << course 
              << " - Grade: " << grade << "\n";
}

char AcademicAdmin::getGrade(const std::string& studentId, const std::string& course) const {
    auto studentIt = studentGrades.find(studentId);
    if (studentIt != studentGrades.end()) {
        auto courseIt = studentIt->second.find(course);
        if (courseIt != studentIt->second.end()) {
            return courseIt->second;
        }
    }
    return 'N'; // Return 'N' for not found
}

char AcademicAdmin::calculateGrade(double marks) const {
    if (marks >= 90) return 'A';
    else if (marks >= 80) return 'B';
    else if (marks >= 70) return 'C';
    else if (marks >= 60) return 'D';
    else return 'F';
}

void AcademicAdmin::displayStudentMarks(const std::string& studentId) const {
    auto studentIt = studentMarks.find(studentId);
    if (studentIt != studentMarks.end()) {
        std::cout << "\n========== Marks for Student " << studentId << " ==========\n";
        for (const auto& course : studentIt->second) {
            std::cout << "Course: " << course.first << " | Marks: " << course.second << "\n";
        }
        std::cout << "======================================================\n";
    } else {
        std::cout << "No marks found for student " << studentId << ".\n";
    }
}

void AcademicAdmin::displayStudentGrades(const std::string& studentId) const {
    auto studentIt = studentGrades.find(studentId);
    if (studentIt != studentGrades.end()) {
        std::cout << "\n========== Grades for Student " << studentId << " ==========\n";
        for (const auto& course : studentIt->second) {
            std::cout << "Course: " << course.first << " | Grade: " << course.second << "\n";
        }
        std::cout << "======================================================\n";
    } else {
        std::cout << "No grades found for student " << studentId << ".\n";
    }
}

void AcademicAdmin::displayAllMarks() const {
    std::cout << "\n========== All Student Marks ==========\n";
    for (const auto& student : studentMarks) {
        std::cout << "\nStudent ID: " << student.first << "\n";
        for (const auto& course : student.second) {
            std::cout << "  Course: " << course.first << " | Marks: " << course.second << "\n";
        }
    }
    std::cout << "=====================================\n";
}

void AcademicAdmin::displayAdminInfo() const {
    std::cout << "\n========== Academic Administration Information ==========\n"
              << "Admin ID: " << adminId << "\n"
              << "Admin Name: " << adminName << "\n"
              << "====================================================\n";
}
