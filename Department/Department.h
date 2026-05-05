#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include "../Faculty/Faculty.h"
#include "../Exam/ExamSchedule.h"

// Forward declaration
class ExamSchedule;

// Base class for all departments
class Department {
protected:
    std::string departmentId;
    std::string departmentName;
    std::string headOfDepartment;
    std::vector<Faculty*> facultyMembers;
    int totalStudents;
    ExamSchedule* examSchedule;

public:
    Department(const std::string& deptId, const std::string& deptName, const std::string& head);
    virtual ~Department();

    // Getters
    std::string getDepartmentId() const;
    std::string getDepartmentName() const;
    std::string getHeadOfDepartment() const;
    int getTotalStudents() const;
    std::vector<Faculty*> getFacultyMembers() const;
    ExamSchedule* getExamSchedule() const;

    // Setters
    void setHeadOfDepartment(const std::string& head);
    void setTotalStudents(int count);

    // Faculty management
    void addFaculty(Faculty* faculty);
    void removeFaculty(const std::string& employeeId);

    // Exam schedule management
    void initializeExamSchedule(const std::string& semester);
    void displayExamSchedule() const;

    // Virtual method for department-specific information
    virtual void displayDepartmentInfo() const;
};

// Specific Department Subclasses
class ComputerScience : public Department {
public:
    ComputerScience(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

class Electronics : public Department {
public:
    Electronics(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

class Mathematics : public Department {
public:
    Mathematics(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

class Physics : public Department {
public:
    Physics(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

class Statistics : public Department {
public:
    Statistics(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

class Engineering : public Department {
public:
    Engineering(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

class InformationTechnology : public Department {
public:
    InformationTechnology(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

class Cybersecurity : public Department {
public:
    Cybersecurity(const std::string& deptId, const std::string& head);
    void displayDepartmentInfo() const override;
};

#endif // DEPARTMENT_H
