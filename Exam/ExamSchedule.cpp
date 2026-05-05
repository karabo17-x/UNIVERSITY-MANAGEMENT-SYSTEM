#include "ExamSchedule.h"
#include <iostream>
#include <algorithm>

ExamSchedule::ExamSchedule(const std::string& id, const std::string& dept, const std::string& semester)
    : scheduleId(id), department(dept), semester(semester), startDate(""), 
      endDate(""), isPublished(false) {}

ExamSchedule::~ExamSchedule() {
    for (auto section : examSections) {
        delete section;
    }
    examSections.clear();
}

std::string ExamSchedule::getScheduleId() const {
    return scheduleId;
}

std::string ExamSchedule::getDepartment() const {
    return department;
}

std::string ExamSchedule::getSemester() const {
    return semester;
}

std::string ExamSchedule::getStartDate() const {
    return startDate;
}

std::string ExamSchedule::getEndDate() const {
    return endDate;
}

bool ExamSchedule::getIsPublished() const {
    return isPublished;
}

std::vector<ExamSection*> ExamSchedule::getExamSections() const {
    return examSections;
}

void ExamSchedule::setStartDate(const std::string& date) {
    startDate = date;
}

void ExamSchedule::setEndDate(const std::string& date) {
    endDate = date;
}

void ExamSchedule::setIsPublished(bool published) {
    isPublished = published;
    if (published) {
        std::cout << "Exam schedule published for " << department << "!\n";
    } else {
        std::cout << "Exam schedule unpublished for " << department << ".\n";
    }
}

void ExamSchedule::addExamSection(ExamSection* section) {
    examSections.push_back(section);
    std::cout << "Exam section " << section->getSectionName() << " added to schedule.\n";
}

void ExamSchedule::removeExamSection(const std::string& sectionId) {
    auto it = std::find_if(examSections.begin(), examSections.end(),
        [&sectionId](ExamSection* s) { return s->getSectionId() == sectionId; });
    
    if (it != examSections.end()) {
        delete *it;
        examSections.erase(it);
        std::cout << "Exam section removed from schedule.\n";
    } else {
        std::cout << "Section not found in this schedule.\n";
    }
}

ExamSection* ExamSchedule::getExamSectionById(const std::string& sectionId) const {
    auto it = std::find_if(examSections.begin(), examSections.end(),
        [&sectionId](ExamSection* s) { return s->getSectionId() == sectionId; });
    
    if (it != examSections.end()) {
        return *it;
    }
    return nullptr;
}

int ExamSchedule::getTotalSections() const {
    return examSections.size();
}

int ExamSchedule::getTotalEnrolledStudents() const {
    int total = 0;
    for (auto section : examSections) {
        total += section->getEnrolledCount();
    }
    return total;
}

void ExamSchedule::displayScheduleInfo() const {
    std::cout << "\n========== Exam Schedule Information ==========\n"
              << "Schedule ID: " << scheduleId << "\n"
              << "Department: " << department << "\n"
              << "Semester: " << semester << "\n"
              << "Start Date: " << (startDate.empty() ? "Not Set" : startDate) << "\n"
              << "End Date: " << (endDate.empty() ? "Not Set" : endDate) << "\n"
              << "Status: " << (isPublished ? "Published" : "Not Published") << "\n"
              << "Total Exam Sections: " << getTotalSections() << "\n"
              << "Total Enrolled Students: " << getTotalEnrolledStudents() << "\n"
              << "=============================================\n";
}

void ExamSchedule::displayAllSections() const {
    std::cout << "\n========== All Exam Sections for " << department << " ==========\n";
    if (examSections.empty()) {
        std::cout << "No exam sections found.\n";
    } else {
        for (int i = 0; i < examSections.size(); i++) {
            std::cout << "\n[" << (i + 1) << "] " << examSections[i]->getSectionName()
                      << " (ID: " << examSections[i]->getSectionId() << ")\n"
                      << "    Invigilator: " << examSections[i]->getInvigilator() << "\n"
                      << "    Room: " << examSections[i]->getRoomNumber() << "\n"
                      << "    Capacity: " << examSections[i]->getCapacity() << "\n"
                      << "    Enrolled: " << examSections[i]->getEnrolledCount() << "\n"
                      << "    Status: " << (examSections[i]->getIsActive() ? "Active" : "Inactive") << "\n";
        }
    }
    std::cout << "==========================================================\n";
}

void ExamSchedule::displaySectionDetails(const std::string& sectionId) const {
    ExamSection* section = getExamSectionById(sectionId);
    if (section != nullptr) {
        section->displaySectionInfo();
        section->displayExamSchedule();
        section->displayEnrolledStudents();
    } else {
        std::cout << "Section not found!\n";
    }
}
