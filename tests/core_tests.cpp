#include "Academic/AcademicAdmin.h"
#include "Administration/Administration.h"
#include "Sports/SportsAffiliation.h"
#include "Student/Student.h"

#include <cassert>
#include <memory>

int main() {
    Administration administration("ADM001", "Test Administrator");

    auto firstStudent = std::make_unique<Student>(
        "STU001", "John Doe", "john@example.com", "5551234567", "2024001", "Computer Science");
    assert(administration.registerStudent(std::move(firstStudent)));
    assert(administration.getTotalRegistrations() == 1);
    assert(administration.searchStudent("STU001") != nullptr);

    auto duplicateStudent = std::make_unique<Student>(
        "STU001", "Jane Doe", "jane@example.com", "5559876543", "2024002", "Mathematics");
    assert(!administration.registerStudent(std::move(duplicateStudent)));
    assert(administration.getTotalRegistrations() == 1);

    administration.deregisterStudent("STU001");
    assert(administration.getTotalRegistrations() == 0);
    assert(administration.searchStudent("STU001") == nullptr);

    AcademicAdmin academicAdmin("ACA001", "Academic Administrator");
    academicAdmin.assignMarks("STU001", "Algorithms", 85.0);
    assert(academicAdmin.getMarks("STU001", "Algorithms") == 85.0);
    assert(academicAdmin.getGrade("STU001", "Algorithms") == 'B');
    academicAdmin.assignMarks("STU001", "Invalid", 101.0);
    assert(academicAdmin.getMarks("STU001", "Invalid") == -1.0);

    SportsAffiliation sports;
    sports.affiliateStudentWithSport("STU001", "S001");
    sports.affiliateStudentWithSport("STU001", "S001");
    assert(sports.getStudentAffiliations("STU001").size() == 1);
    assert(sports.getStudentPaymentTotal("STU001") == 150.0);

    return 0;
}
