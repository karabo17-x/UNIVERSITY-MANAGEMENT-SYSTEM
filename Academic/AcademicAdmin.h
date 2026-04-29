#ifndef ACADEMICADMIN_H
#define ACADEMICADMIN_H

#include <string>
#include <map>
#include <vector>

class AcademicAdmin {
private:
    std::string adminId;
    std::string adminName;
    // Map to store student ID -> marks for different courses
    std::map<std::string, std::map<std::string, double>> studentMarks;
    // Map to store student ID -> grades
    std::map<std::string, std::map<std::string, char>> studentGrades;

public:
    AcademicAdmin(const std::string& adminId, const std::string& adminName);

    // Getters
    std::string getAdminId() const;
    std::string getAdminName() const;

    // Marks management
    void assignMarks(const std::string& studentId, const std::string& course, double marks);
    double getMarks(const std::string& studentId, const std::string& course) const;
    
    // Grade calculation and management
    void assignGrade(const std::string& studentId, const std::string& course, char grade);
    char getGrade(const std::string& studentId, const std::string& course) const;
    char calculateGrade(double marks) const;

    // Display functions
    void displayStudentMarks(const std::string& studentId) const;
    void displayStudentGrades(const std::string& studentId) const;
    void displayAllMarks() const;

    // Display information
    void displayAdminInfo() const;
};

#endif // ACADEMICADMIN_H
