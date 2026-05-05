#ifndef EXAM_SECTION_H
#define EXAM_SECTION_H

#include <string>
#include <vector>
#include "Exam.h"

// ExamSection class - manages exam sections for each department
class ExamSection {
private:
    std::string sectionId;
    std::string sectionName;
    std::string department;
    std::string invigilator;           // Faculty member supervising
    int capacity;                      // Number of students in section
    std::vector<std::string> enrolledStudents;  // Student IDs
    std::vector<Exam*> exams;
    std::string roomNumber;
    bool isActive;

public:
    ExamSection(const std::string& id, const std::string& name, const std::string& dept,
                const std::string& invigilator, int capacity, const std::string& room);
    
    virtual ~ExamSection();

    // Getters
    std::string getSectionId() const;
    std::string getSectionName() const;
    std::string getDepartment() const;
    std::string getInvigilator() const;
    int getCapacity() const;
    int getEnrolledCount() const;
    std::string getRoomNumber() const;
    bool getIsActive() const;
    std::vector<std::string> getEnrolledStudents() const;
    std::vector<Exam*> getExams() const;

    // Setters
    void setInvigilator(const std::string& invigilator);
    void setCapacity(int capacity);
    void setRoomNumber(const std::string& room);
    void setIsActive(bool active);

    // Student management
    void enrollStudent(const std::string& studentId);
    void removeStudent(const std::string& studentId);
    bool isStudentEnrolled(const std::string& studentId) const;

    // Exam management
    void addExam(Exam* exam);
    void removeExam(const std::string& examId);
    Exam* getExamById(const std::string& examId) const;

    // Display information
    void displaySectionInfo() const;
    void displayExamSchedule() const;
    void displayEnrolledStudents() const;
};

#endif // EXAM_SECTION_H
