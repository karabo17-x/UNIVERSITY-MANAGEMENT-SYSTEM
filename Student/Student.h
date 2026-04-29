#ifndef STUDENT_H
#define STUDENT_H

#include "../Person/Person.h"
#include <vector>

class Student : public Person {
private:
    std::string rollNumber;
    std::string major;
    double gpa;
    std::vector<std::string> enrolledCourses;
    std::string residenceBlock;

public:
    Student(const std::string& id, const std::string& name, const std::string& email, 
            const std::string& phone, const std::string& rollNumber, const std::string& major);
    
    // Getters
    std::string getRollNumber() const;
    std::string getMajor() const;
    double getGPA() const;
    std::string getResidenceBlock() const;
    std::vector<std::string> getEnrolledCourses() const;

    // Setters
    void setMajor(const std::string& major);
    void setGPA(double gpa);
    void setResidenceBlock(const std::string& block);

    // Course management
    void enrollCourse(const std::string& course);
    void dropCourse(const std::string& course);

    // Display information
    void displayInfo() const override;
};

#endif // STUDENT_H
