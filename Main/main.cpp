#include <iostream>
#include <vector>
#include <cstdlib>
#include "../Person/Person.h"
#include "../Student/Student.h"
#include "../Faculty/Faculty.h"
#include "../Department/Department.h"
#include "../Administration/Administration.h"
#include "../Academic/AcademicAdmin.h"
#include "../Residence/Residence.h"
#include "../Sports/Sports.h"
#include "../Sports/SportsAffiliation.h"
#include "../Exam/Exam.h"
#include "../Exam/ExamSection.h"
#include "../Exam/ExamSchedule.h"

using namespace std;

// Function to clear screen
void clearScreen() {
    system("clear");
}

// Function to display main menu
void displayMainMenu() {
    cout << "\n===================================================\n";
    cout << "     UNIVERSITY MANAGEMENT SYSTEM - MAIN MENU       \n";
    cout << "=====================================================\n";
    cout << "\n--- STUDENT MANAGEMENT ---\n";
    cout << "1. Register New Student\n";
    cout << "2. View All Registered Students\n";
    cout << "3. Search Student by ID\n";
    cout << "4. Deregister Student\n";
    cout << "\n--- ACADEMIC MANAGEMENT ---\n";
    cout << "5. Assign Marks to Student\n";
    cout << "6. View Student Marks\n";
    cout << "\n--- FACULTY MANAGEMENT ---\n";
    cout << "7. Add Faculty Member\n";
    cout << "8. View All Faculty Members\n";
    cout << "9. View Faculty by Department\n";
    cout << "10. Assign Course to Faculty\n";
    cout << "11. View Course-Faculty Mapping\n";
    cout << "\n--- DEPARTMENT MANAGEMENT ---\n";
    cout << "12. View All Departments\n";
    cout << "13. View Department Faculty\n";
    cout << "14. Faculty Payroll (Salary Info)\n";
    cout << "\n--- RESIDENCE MANAGEMENT ---\n";
    cout << "15. Assign Residence Room\n";
    cout << "16. View Residence Occupancy\n";
    cout << "\n--- SPORTS MANAGEMENT ---\n";
    cout << "17. View All Available Sports\n";
    cout << "18. Affiliate Student with Sport\n";
    cout << "19. View Student Sports Profile\n";
    cout << "20. View Sport Participants\n";
    cout << "21. Remove Student from Sport\n";
    cout << "\n--- EXAM MANAGEMENT ---\n";
    cout << "22. Initialize Department Exam Schedule\n";
    cout << "23. Create Exam Section\n";
    cout << "24. Add Exam to Section\n";
    cout << "25. Enroll Student in Exam Section\n";
    cout << "26. View Department Exam Schedule\n";
    cout << "27. View Exam Section Details\n";
    cout << "\n--- SYSTEM INFO ---\n";
    cout << "28. View System Information\n";
    cout << "29. Exit\n";
    cout << "\nEnter your choice (1-29): ";
}

// Function to pause execution
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}


int main() {
    clearScreen();
    
    cout << "\n===================================================\n";
    cout << "     WELCOME TO UNIVERSITY MANAGEMENT SYSTEM          \n";
    cout << "     Initializing System...                           \n";
    cout << "=====================================================\n";
    
    Administration admin("ADM001", "Mr. Karabo Mothapo");
    AcademicAdmin academicAdmin("AAM001", "Mrs. Petronella Mothapo");
    Residence hostelA("RES001", "Hostel A", "Block A", 10, "Dr. Phillip Mphahlele");
    SportsAffiliation sportsAffiliation;
    
    // Initialize Departments
    vector<Department*> departments;
    departments.push_back(new ComputerScience("DEPT001", "Dr. Ahmed Hassan"));
    departments.push_back(new Electronics("DEPT002", "Prof. Sarah Johnson"));
    departments.push_back(new Mathematics("DEPT003", "Dr. Michael Smith"));
    departments.push_back(new Physics("DEPT004", "Dr. Emily Brown"));
    departments.push_back(new Statistics("DEPT005", "Prof. James Wilson"));
    departments.push_back(new Engineering("DEPT006", "Dr. Robert Davis"));
    departments.push_back(new InformationTechnology("DEPT007", "Dr. Lisa Anderson"));
    departments.push_back(new Cybersecurity("DEPT008", "Prof. David Martinez"));
    
    cout << "\n System initialized successfully!\n";
    cout << " Administrator: " << admin.getAdminName() << "\n";
    cout << " Academic Admin: " << academicAdmin.getAdminName() << "\n";
    cout << " Residence: " << hostelA.getResidenceName() << " (Warden: Dr. Phillip Mphahlele)\n";
    cout << " Sports Department: 12 Sports Initialized\n";
    cout << " Departments: 8 Academic Departments Initialized\n";
    
    // Main application loop
    bool running = true;
    int choice;
    
    while (running) {
        displayMainMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1: {
                // Register New Student
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     NEW STUDENT REGISTRATION                    \n";
                cout << "=====================================================\n";
                
                Student* newStudent = admin.interactiveStudentRegistration();
                
                if (newStudent != nullptr) {
                    cout << "\nRegistering student in system...\n";
                    admin.registerStudent(newStudent);
                    
                    // Display the registered student's information
                    cout << "\n--- Student Registration Summary ---\n";
                    newStudent->displayInfo();
                } else {
                    cout << "\nStudent registration failed!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 2: {
                // View All Registered Students
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     REGISTERED STUDENTS LIST                       \n";
                cout << "=====================================================\n";
                admin.displayAllRegistrations();
                pause();
                clearScreen();
                break;
            }
            
            case 3: {
                // Search Student
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     SEARCH STUDENT                              \n";
                cout << "=====================================================\n";
                
                string searchId;
                cout << "\nEnter Student ID to search: ";
                getline(cin, searchId);
                
                Student* found = admin.searchStudent(searchId);
                if (found != nullptr) {
                    cout << "\n Student found!\n\n";
                    found->displayInfo();
                } else {
                    cout << "\n Student with ID '" << searchId << "' not found!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 4: {
                // Deregister Student
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     DEREGISTER STUDENT                          \n";
                cout << "=====================================================\n";
                
                string studentId;
                cout << "\nEnter Student ID to deregister: ";
                getline(cin, studentId);
                
                Student* student = admin.searchStudent(studentId);
                if (student != nullptr) {
                    cout << "\nStudent Details:\n";
                    student->displayInfo();
                    
                    cout << "\nAre you sure you want to deregister this student? (yes/no): ";
                    string confirm;
                    getline(cin, confirm);
                    
                    if (confirm == "yes" || confirm == "YES") {
                        admin.deregisterStudent(studentId);
                        cout << "\n Student deregistered successfully!\n";
                    } else {
                        cout << "\n Operation cancelled.\n";
                    }
                } else {
                    cout << "\n ERROR: Student not found!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 5: {
                // Assign Marks
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ASSIGN MARKS TO STUDENT                     \n";
                cout << "=====================================================\n";
                
                string studentId, courseName;
                double marks;
                
                cout << "\nEnter Student ID: ";
                getline(cin, studentId);
                
                cout << "Enter Course Name: ";
                getline(cin, courseName);
                
                cout << "Enter Marks (0-100): ";
                cin >> marks;
                cin.ignore();
                
                if (marks < 0 || marks > 100) {
                    cout << "\n Invalid marks! Please enter marks between 0 and 100.\n";
                } else {
                    academicAdmin.assignMarks(studentId, courseName, marks);
                    cout << "\n Marks assigned successfully!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 6: {
                // View Student Marks
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     VIEW STUDENT MARKS                          \n";
                cout << "=====================================================\n";
                
                string studentId;
                cout << "\nEnter Student ID: ";
                getline(cin, studentId);
                
                academicAdmin.displayStudentMarks(studentId);
                academicAdmin.displayStudentGrades(studentId);
                pause();
                clearScreen();
                break;
            }
            
            case 7: {
                // Add Faculty Member
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ADD FACULTY MEMBER                          \n";
                cout << "=====================================================\n";
                
                Faculty* newFaculty = admin.interactiveAddFaculty();
                
                if (newFaculty != nullptr) {
                    cout << "\nAdding faculty to system...\n";
                    admin.addFaculty(newFaculty);
                    
                    cout << "\n--- Faculty Registration Summary ---\n";
                    newFaculty->displayInfo();
                } else {
                    cout << "\nFaculty registration failed!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 8: {
                // View All Faculty Members
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ALL FACULTY MEMBERS                         \n";
                cout << "=====================================================\n";
                admin.displayAllFaculty();
                pause();
                clearScreen();
                break;
            }
            
            case 9: {
                // View Faculty by Department
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     FACULTY BY DEPARTMENT                      \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                cout << "1. Computer Science\n";
                cout << "2. Electronics\n";
                cout << "3. Mathematics\n";
                cout << "4. Physics\n";
                cout << "5. Statistics\n";
                cout << "6. Engineering Field\n";
                cout << "Enter choice (1-6): ";
                
                int deptChoice;
                cin >> deptChoice;
                cin.ignore();
                
                string dept;
                switch (deptChoice) {
                    case 1: dept = "Computer Science"; break;
                    case 2: dept = "Electronics"; break;
                    case 3: dept = "Mathematics"; break;
                    case 4: dept = "Physics"; break;
                    case 5: dept = "Statistics"; break;
                    case 6: dept = "Engineering Field"; break;
                    default:
                        cout << "\n Invalid choice!\n";
                        pause();
                        clearScreen();
                        break;
                }
                
                if (!dept.empty()) {
                    admin.displayFacultyByDepartment(dept);
                    pause();
                    clearScreen();
                }
                break;
            }
            
            case 10: {
                // Assign Course to Faculty
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ASSIGN COURSE TO FACULTY                   \n";
                cout << "=====================================================\n";
                
                string employeeId, courseName;
                
                cout << "\nEnter Faculty Employee ID: ";
                getline(cin, employeeId);
                
                cout << "Enter Course Name: ";
                getline(cin, courseName);
                
                admin.assignFacultyToCourse(employeeId, courseName);
                cout << "\n Course assigned successfully!\n";
                
                pause();
                clearScreen();
                break;
            }
            
            case 11: {
                // View Course-Faculty Mapping
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     COURSE-FACULTY MAPPING                     \n";
                cout << "=====================================================\n";
                admin.displayCourseFacultyMapping();
                pause();
                clearScreen();
                break;
            }
            
            case 12: {
                // View All Departments
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ALL DEPARTMENTS                            \n";
                cout << "=====================================================\n";
                admin.displayAllDepartments();
                pause();
                clearScreen();
                break;
            }
            
            case 13: {
                // View Department Faculty
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     DEPARTMENT FACULTY DETAILS                 \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                cout << "1. Computer Science\n";
                cout << "2. Electronics\n";
                cout << "3. Mathematics\n";
                cout << "4. Physics\n";
                cout << "5. Statistics\n";
                cout << "6. Engineering Field\n";
                cout << "Enter choice (1-6): ";
                
                int deptChoice2;
                cin >> deptChoice2;
                cin.ignore();
                
                string dept2;
                switch (deptChoice2) {
                    case 1: dept2 = "Computer Science"; break;
                    case 2: dept2 = "Electronics"; break;
                    case 3: dept2 = "Mathematics"; break;
                    case 4: dept2 = "Physics"; break;
                    case 5: dept2 = "Statistics"; break;
                    case 6: dept2 = "Engineering Field"; break;
                    default:
                        cout << "\n Invalid choice!\n";
                        pause();
                        clearScreen();
                        break;
                }
                
                if (!dept2.empty()) {
                    admin.displayDepartmentFaculty(dept2);
                    pause();
                    clearScreen();
                }
                break;
            }
            
            case 14: {
                // Faculty Payroll (Salary Info)
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     FACULTY PAYROLL - SALARY INFORMATION        \n";
                cout << "=====================================================\n";
                
                auto facultyList = admin.getFacultyList();
                if (facultyList.empty()) {
                    cout << "\nNo faculty members in the system.\n";
                } else {
                    double totalPayroll = 0;
                    cout << "\n========== Monthly Payroll Report ==========\n\n";
                    
                    cout << "Employee ID | Name | Designation | Department | Salary\n";
                    cout << "========================================================\n";
                    
                    for (const auto& faculty : facultyList) {
                        cout << faculty->getEmployeeId() << " | "
                             << faculty->getName() << " | "
                             << faculty->getDesignation() << " | "
                             << faculty->getDepartment() << " | R"
                             << faculty->getSalary() << "\n";
                        totalPayroll += faculty->getSalary();
                    }
                    
                    cout << "\n========== PAYROLL SUMMARY ==========\n";
                    cout << "Total Faculty Members: " << facultyList.size() << "\n";
                    cout << "Total Monthly Payroll: R" << totalPayroll << "\n";
                    cout << "Average Salary: R" << (totalPayroll / facultyList.size()) << "\n";
                    cout << "=====================================\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 15: {
                // Assign Hostel Room
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ASSIGN RESIDENCE ROOM                         \n";
                cout << "=====================================================\n";
                
                string studentId;
                int roomNumber;
                
                cout << "\nEnter Student ID: ";
                getline(cin, studentId);
                
                cout << "Enter Room Number (1-10): ";
                cin >> roomNumber;
                cin.ignore();
                
                Student* student = admin.searchStudent(studentId);
                if (student != nullptr) {
                    hostelA.assignRoom(roomNumber, student);
                    cout << "\n Room assigned successfully!\n";
                } else {
                    cout << "\n Student not found!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 16: {
                // View Hostel Occupancy
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     RESIDENCE OCCUPANCY                            \n";
                cout << "=====================================================\n";
                hostelA.displayResidenceInfo();
                hostelA.displayRoomOccupancy();
                hostelA.displayAllOccupants();
                pause();
                clearScreen();
                break;
            }
            
            case 17: {
                // View All Available Sports
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     AVAILABLE SPORTS                             \n";
                cout << "=====================================================\n";
                sportsAffiliation.displayAllSports();
                pause();
                clearScreen();
                break;
            }
            
            case 18: {
                // Affiliate Student with Sport
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     AFFILIATE STUDENT WITH SPORT                 \n";
                cout << "=====================================================\n";
                
                sportsAffiliation.displayAllSports();
                
                string studentId, sportId;
                cout << "\nEnter Student ID: ";
                getline(cin, studentId);
                
                cout << "Enter Sport ID (e.g., S001 for Soccer): ";
                getline(cin, sportId);
                
                Student* student = admin.searchStudent(studentId);
                if (student != nullptr) {
                    sportsAffiliation.affiliateStudentWithSport(studentId, sportId);
                    cout << "\nAffiliation successful!\n";
                } else {
                    cout << "\nStudent not found!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 19: {
                // View Student Sports Profile
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     STUDENT SPORTS PROFILE                      \n";
                cout << "=====================================================\n";
                
                string studentId;
                cout << "\nEnter Student ID: ";
                getline(cin, studentId);
                
                Student* student = admin.searchStudent(studentId);
                if (student != nullptr) {
                    sportsAffiliation.displayStudentSportInfo(studentId);
                } else {
                    cout << "\nStudent not found!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 20: {
                // View Sport Participants
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     SPORT PARTICIPANTS                          \n";
                cout << "=====================================================\n";
                
                sportsAffiliation.displayAllSports();
                
                string sportId;
                cout << "\nEnter Sport ID: ";
                getline(cin, sportId);
                
                sportsAffiliation.displaySportParticipants(sportId);
                pause();
                clearScreen();
                break;
            }
            
            case 21: {
                // Remove Student from Sport
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     REMOVE STUDENT FROM SPORT                   \n";
                cout << "=====================================================\n";
                
                string studentId, sportId;
                cout << "\nEnter Student ID: ";
                getline(cin, studentId);
                
                cout << "Enter Sport ID: ";
                getline(cin, sportId);
                
                Student* student = admin.searchStudent(studentId);
                if (student != nullptr) {
                    sportsAffiliation.removeStudentFromSport(studentId, sportId);
                    cout << "\nStudent removed from sport!\n";
                } else {
                    cout << "\nStudent not found!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 22: {
                // Initialize Department Exam Schedule
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     INITIALIZE DEPARTMENT EXAM SCHEDULE         \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                for (int i = 0; i < departments.size(); i++) {
                    cout << (i + 1) << ". " << departments[i]->getDepartmentName() << "\n";
                }
                
                int deptChoice;
                cout << "\nEnter department number: ";
                cin >> deptChoice;
                cin.ignore();
                
                if (deptChoice > 0 && deptChoice <= departments.size()) {
                    string semester;
                    cout << "Enter semester: ";
                    getline(cin, semester);
                    
                    departments[deptChoice - 1]->initializeExamSchedule(semester);
                    cout << "\nExam schedule initialized successfully!\n";
                } else {
                    cout << "\nInvalid choice!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 23: {
                // Create Exam Section
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     CREATE EXAM SECTION                          \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                for (int i = 0; i < departments.size(); i++) {
                    cout << (i + 1) << ". " << departments[i]->getDepartmentName() << "\n";
                }
                
                int deptChoice;
                cout << "\nEnter department number: ";
                cin >> deptChoice;
                cin.ignore();
                
                if (deptChoice > 0 && deptChoice <= departments.size()) {
                    ExamSchedule* schedule = departments[deptChoice - 1]->getExamSchedule();
                    if (schedule != nullptr) {
                        string sectionId, sectionName, invigilator, roomNumber;
                        int capacity;
                        
                        cout << "Enter Section ID: ";
                        getline(cin, sectionId);
                        
                        cout << "Enter Section Name: ";
                        getline(cin, sectionName);
                        
                        cout << "Enter Invigilator Name: ";
                        getline(cin, invigilator);
                        
                        cout << "Enter Room Number: ";
                        getline(cin, roomNumber);
                        
                        cout << "Enter Section Capacity: ";
                        cin >> capacity;
                        
                        ExamSection* newSection = new ExamSection(sectionId, sectionName, 
                                                                  departments[deptChoice - 1]->getDepartmentName(),
                                                                  invigilator, capacity, roomNumber);
                        schedule->addExamSection(newSection);
                    } else {
                        cout << "\nNo exam schedule found for this department. Initialize first!\n";
                    }
                } else {
                    cout << "\nInvalid choice!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 24: {
                // Add Exam to Section
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ADD EXAM TO SECTION                         \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                for (int i = 0; i < departments.size(); i++) {
                    cout << (i + 1) << ". " << departments[i]->getDepartmentName() << "\n";
                }
                
                int deptChoice;
                cout << "\nEnter department number: ";
                cin >> deptChoice;
                cin.ignore();
                
                if (deptChoice > 0 && deptChoice <= departments.size()) {
                    ExamSchedule* schedule = departments[deptChoice - 1]->getExamSchedule();
                    if (schedule != nullptr && schedule->getTotalSections() > 0) {
                        string sectionId;
                        cout << "\nEnter Section ID: ";
                        getline(cin, sectionId);
                        
                        ExamSection* section = schedule->getExamSectionById(sectionId);
                        if (section != nullptr) {
                            string examId, examName, examType, date, time, venue;
                            int duration, maxMarks;
                            
                            cout << "Enter Exam ID: ";
                            getline(cin, examId);
                            
                            cout << "Enter Exam Name: ";
                            getline(cin, examName);
                            
                            cout << "Enter Exam Type (Midterm/Final/Quiz/Assignment): ";
                            getline(cin, examType);
                            
                            cout << "Enter Date (DD/MM/YYYY): ";
                            getline(cin, date);
                            
                            cout << "Enter Time (HH:MM): ";
                            getline(cin, time);
                            
                            cout << "Enter Duration (minutes): ";
                            cin >> duration;
                            
                            cout << "Enter Max Marks: ";
                            cin >> maxMarks;
                            cin.ignore();
                            
                            cout << "Enter Venue: ";
                            getline(cin, venue);
                            
                            Exam* newExam = nullptr;
                            if (examType == "Midterm" || examType == "midterm") {
                                newExam = new Midterm(examId, examName, departments[deptChoice - 1]->getDepartmentName(),
                                                     date, time, duration, maxMarks, venue);
                            } else if (examType == "Final" || examType == "final") {
                                newExam = new Final(examId, examName, departments[deptChoice - 1]->getDepartmentName(),
                                                   date, time, duration, maxMarks, venue);
                            } else if (examType == "Quiz" || examType == "quiz") {
                                newExam = new Quiz(examId, examName, departments[deptChoice - 1]->getDepartmentName(),
                                                  date, time, duration, maxMarks, venue);
                            } else if (examType == "Assignment" || examType == "assignment") {
                                newExam = new Assignment(examId, examName, departments[deptChoice - 1]->getDepartmentName(),
                                                        date, time, duration, maxMarks, venue);
                            } else {
                                newExam = new Exam(examId, examName, examType, departments[deptChoice - 1]->getDepartmentName(),
                                                  date, time, duration, maxMarks, venue);
                            }
                            
                            section->addExam(newExam);
                        } else {
                            cout << "\nSection not found!\n";
                        }
                    } else {
                        cout << "\nNo exam schedule or sections found for this department!\n";
                    }
                } else {
                    cout << "\nInvalid choice!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 25: {
                // Enroll Student in Exam Section
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     ENROLL STUDENT IN EXAM SECTION             \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                for (int i = 0; i < departments.size(); i++) {
                    cout << (i + 1) << ". " << departments[i]->getDepartmentName() << "\n";
                }
                
                int deptChoice;
                cout << "\nEnter department number: ";
                cin >> deptChoice;
                cin.ignore();
                
                if (deptChoice > 0 && deptChoice <= departments.size()) {
                    ExamSchedule* schedule = departments[deptChoice - 1]->getExamSchedule();
                    if (schedule != nullptr && schedule->getTotalSections() > 0) {
                        string sectionId, studentId;
                        cout << "\nEnter Section ID: ";
                        getline(cin, sectionId);
                        
                        cout << "Enter Student ID: ";
                        getline(cin, studentId);
                        
                        ExamSection* section = schedule->getExamSectionById(sectionId);
                        if (section != nullptr) {
                            Student* student = admin.searchStudent(studentId);
                            if (student != nullptr) {
                                section->enrollStudent(studentId);
                            } else {
                                cout << "\nStudent not found!\n";
                            }
                        } else {
                            cout << "\nSection not found!\n";
                        }
                    } else {
                        cout << "\nNo exam schedule or sections found for this department!\n";
                    }
                } else {
                    cout << "\nInvalid choice!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 26: {
                // View Department Exam Schedule
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     DEPARTMENT EXAM SCHEDULE                    \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                for (int i = 0; i < departments.size(); i++) {
                    cout << (i + 1) << ". " << departments[i]->getDepartmentName() << "\n";
                }
                
                int deptChoice;
                cout << "\nEnter department number: ";
                cin >> deptChoice;
                cin.ignore();
                
                if (deptChoice > 0 && deptChoice <= departments.size()) {
                    departments[deptChoice - 1]->displayExamSchedule();
                } else {
                    cout << "\nInvalid choice!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 27: {
                // View Exam Section Details
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     EXAM SECTION DETAILS                        \n";
                cout << "=====================================================\n";
                
                cout << "\nSelect Department:\n";
                for (int i = 0; i < departments.size(); i++) {
                    cout << (i + 1) << ". " << departments[i]->getDepartmentName() << "\n";
                }
                
                int deptChoice;
                cout << "\nEnter department number: ";
                cin >> deptChoice;
                cin.ignore();
                
                if (deptChoice > 0 && deptChoice <= departments.size()) {
                    ExamSchedule* schedule = departments[deptChoice - 1]->getExamSchedule();
                    if (schedule != nullptr) {
                        string sectionId;
                        cout << "\nEnter Section ID: ";
                        getline(cin, sectionId);
                        schedule->displaySectionDetails(sectionId);
                    } else {
                        cout << "\nNo exam schedule found for this department!\n";
                    }
                } else {
                    cout << "\nInvalid choice!\n";
                }
                pause();
                clearScreen();
                break;
            }
            
            case 28: {
                // View System Information
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     SYSTEM INFORMATION                          \n";
                cout << "=====================================================\n";
                admin.displayAdminInfo();
                academicAdmin.displayAdminInfo();
                hostelA.displayResidenceInfo();
                pause();
                clearScreen(); 
                break;
            }
            
            case 29: {
                // Exit
                clearScreen();
                cout << "\n===================================================\n";
                cout << "     THANK YOU FOR USING UNIVERSITY MANAGEMENT SYSTEM  \n";
                cout << "                        GOODBYE!                        \n";
                cout << "=====================================================\n\n";
                running = false;
                break;
            }
            
            default: {
                cout << "\n Invalid choice! Please enter a number between 1 and 29.\n";
                pause();
                clearScreen();
                break;
            }
        }
    }
    
    // Cleanup departments
    for (auto dept : departments) {
        delete dept;
    }
    departments.clear();
    
    return 0;
}
