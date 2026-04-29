#ifndef FACULTY_H
#define FACULTY_H

#include "../Person/Person.h"
#include <vector>

class Faculty : public Person {
protected:
    std::string employeeId;
    std::string department;
    std::string designation;
    std::vector<std::string> coursesTaught;
    double salary;

public:
    Faculty(const std::string& id, const std::string& name, const std::string& email, 
            const std::string& phone, const std::string& employeeId, const std::string& department,
            const std::string& designation, double salary);
    
    virtual ~Faculty();

    // Getters
    std::string getEmployeeId() const;
    std::string getDepartment() const;
    std::string getDesignation() const;
    double getSalary() const;
    std::vector<std::string> getCoursesTaught() const;

    // Setters
    void setDepartment(const std::string& department);
    void setDesignation(const std::string& designation);
    void setSalary(double salary);

    // Course management
    void assignCourse(const std::string& course);
    void removeCourse(const std::string& course);

    // Display information
    void displayInfo() const override;
};

#endif // FACULTY_H
