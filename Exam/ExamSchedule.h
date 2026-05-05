#ifndef EXAM_SCHEDULE_H
#define EXAM_SCHEDULE_H

#include <string>
#include <vector>
#include "ExamSection.h"

// ExamSchedule class - manages all exam sections for a department
class ExamSchedule {
private:
    std::string scheduleId;
    std::string department;
    std::string semester;      
    std::vector<ExamSection*> examSections;
    std::string startDate;
    std::string endDate;
    bool isPublished;

public:
    ExamSchedule(const std::string& id, const std::string& dept, const std::string& semester);
    virtual ~ExamSchedule();

    // Getters
    std::string getScheduleId() const;
    std::string getDepartment() const;
    std::string getSemester() const;
    std::string getStartDate() const;
    std::string getEndDate() const;
    bool getIsPublished() const;
    std::vector<ExamSection*> getExamSections() const;

    // Setters
    void setStartDate(const std::string& date);
    void setEndDate(const std::string& date);
    void setIsPublished(bool published);

    // Section management
    void addExamSection(ExamSection* section);
    void removeExamSection(const std::string& sectionId);
    ExamSection* getExamSectionById(const std::string& sectionId) const;
    int getTotalSections() const;
    int getTotalEnrolledStudents() const;

    // Display information
    void displayScheduleInfo() const;
    void displayAllSections() const;
    void displaySectionDetails(const std::string& sectionId) const;
};

#endif // EXAM_SCHEDULE_H
