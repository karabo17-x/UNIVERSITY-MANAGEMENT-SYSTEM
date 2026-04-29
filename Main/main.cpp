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
    cout << "\n--- SYSTEM INFO ---\n";
    cout << "17. View System Information\n";
    cout << "18. Exit\n";
    cout << "\nEnter your choice (1-18): ";
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
    
    // Initialize system components
    Administration admin("ADM001", "Mr. Karabo Mothapo");
    AcademicAdmin academicAdmin("AAM001", "Mrs. Petronella Mothapo");
    Residence hostelA("RES001", "Hostel A", "Block A", 10, "Dr. Phillip Mphahlele");
    
    cout << "\n System initialized successfully!\n";
    cout << " Administrator: " << admin.getAdminName() << "\n";
    cout << " Academic Admin: " << academicAdmin.getAdminName() << "\n";
    cout << " Residence: " << hostelA.getResidenceName() << " (Warden: Dr. Phillip Mphahlele)\n";
    
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
            
            case 18: {
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
                cout << "\n Invalid choice! Please enter a number between 1 and 18.\n";
                pause();
                clearScreen();
                break;
            }
        }
    }
    
    return 0;
}
