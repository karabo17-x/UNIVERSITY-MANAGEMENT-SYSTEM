#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <string>
#include <vector>
#include "../Student/Student.h"
#include "../Faculty/Faculty.h"
#include "../Department/Department.h"

class Administration {
private:
    std::string adminId;
    std::string adminName;
    std::vector<Student*> registeredStudents;
    std::vector<Faculty*> facultyList;
    std::vector<Department*> departments;
    int totalRegistrations;
    
    // Helper methods for validation
    std::string validateEmail(const std::string& email);
    std::string validatePhone(const std::string& phone);
    bool studentIdExists(const std::string& studentId);
    bool facultyIdExists(const std::string& employeeId);

public:
    Administration(const std::string& adminId, const std::string& adminName);
    ~Administration();

    // Getters
    std::string getAdminId() const;
    std::string getAdminName() const;
    int getTotalRegistrations() const;
    std::vector<Student*> getRegisteredStudents() const;
    std::vector<Faculty*> getFacultyList() const;
    std::vector<Department*> getDepartments() const;

    // Student registration management
    void registerStudent(Student* student);
    void deregisterStudent(const std::string& studentId);
    Student* searchStudent(const std::string& studentId);
    void displayAllRegistrations() const;

    // Faculty management
    void addFaculty(Faculty* faculty);
    void removeFaculty(const std::string& employeeId);
    Faculty* searchFaculty(const std::string& employeeId);
    void displayAllFaculty() const;
    void displayFacultyByDepartment(const std::string& department) const;
    Faculty* interactiveAddFaculty();

    // Department management
    void addDepartment(Department* department);
    void displayAllDepartments() const;
    void displayDepartmentFaculty(const std::string& deptName) const;

    // Course management
    void assignFacultyToCourse(const std::string& employeeId, const std::string& courseName);
    void displayCourseFacultyMapping() const;

    // Interactive registration (prompts user for input)
    Student* interactiveStudentRegistration();
    
    // Display information
    void displayAdminInfo() const;
};

#endif // ADMINISTRATION_H
