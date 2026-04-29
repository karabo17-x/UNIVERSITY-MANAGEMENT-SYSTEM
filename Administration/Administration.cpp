#include "Administration.h"
#include <iostream>
#include <algorithm>
#include <sstream>

Administration::Administration(const std::string& adminId, const std::string& adminName)
    : adminId(adminId), adminName(adminName), totalRegistrations(0) {}

Administration::~Administration() {}

std::string Administration::getAdminId() const {
    return adminId;
}

std::string Administration::getAdminName() const {
    return adminName;
}

int Administration::getTotalRegistrations() const {
    return totalRegistrations;
}

std::vector<Student*> Administration::getRegisteredStudents() const {
    return registeredStudents;
}

std::vector<Faculty*> Administration::getFacultyList() const {
    return facultyList;
}

std::vector<Department*> Administration::getDepartments() const {
    return departments;
}

bool Administration::studentIdExists(const std::string& studentId) {
    auto it = std::find_if(registeredStudents.begin(), registeredStudents.end(),
        [&studentId](Student* s) { return s->getId() == studentId; });
    return it != registeredStudents.end();
}

std::string Administration::validateEmail(const std::string& email) {
    // Check if email contains '@' symbol
    if (email.find('@') == std::string::npos) {
        return "Invalid email format! Email must contain '@' symbol.";
    }
    if (email.find('.') == std::string::npos) {
        return "Invalid email format! Email must contain a domain.";
    }
    return ""; // Empty string means valid
}

std::string Administration::validatePhone(const std::string& phone) {
    // Check if phone contains at least 10 characters (digits and hyphens)
    int digitCount = 0;
    for (char c : phone) {
        if (isdigit(c)) digitCount++;
    }
    if (digitCount < 10) {
        return "Invalid phone number! Must contain at least 10 digits.";
    }
    return ""; // Empty string means valid
}

void Administration::registerStudent(Student* student) {
    if (studentIdExists(student->getId())) {
        std::cout << "\n ERROR: Student with ID " << student->getId() << " is already registered!\n";
        return;
    }
    registeredStudents.push_back(student);
    totalRegistrations++;
    std::cout << "\n Student " << student->getName() << " (Roll: " << student->getRollNumber() 
              << ") registered successfully!\n";
}

void Administration::deregisterStudent(const std::string& studentId) {
    auto it = std::find_if(registeredStudents.begin(), registeredStudents.end(),
        [&studentId](Student* s) { return s->getId() == studentId; });
    
    if (it != registeredStudents.end()) {
        std::cout << "Student " << (*it)->getName() << " deregistered.\n";
        registeredStudents.erase(it);
        totalRegistrations--;
    } else {
        std::cout << "Student not found.\n";
    }
}

Student* Administration::searchStudent(const std::string& studentId) {
    auto it = std::find_if(registeredStudents.begin(), registeredStudents.end(),
        [&studentId](Student* s) { return s->getId() == studentId; });
    
    if (it != registeredStudents.end()) {
        return *it;
    }
    return nullptr;
}

void Administration::displayAllRegistrations() const {
    std::cout << "\n========== All Student Registrations ==========\n";
    std::cout << "Total Registered Students: " << totalRegistrations << "\n\n";
    
    if (totalRegistrations == 0) {
        std::cout << "No students registered yet.\n";
    } else {
        for (const auto& student : registeredStudents) {
            std::cout << "Name: " << student->getName() 
                      << " | Roll: " << student->getRollNumber() 
                      << " | Major: " << student->getMajor() << "\n";
        }
    }
    std::cout << "==============================================\n";
}

Student* Administration::interactiveStudentRegistration() {
    std::cout << "\n========== STUDENT REGISTRATION FORM ==========\n";
    
    std::string id, name, email, phone, rollNumber, major;
    std::string errorMsg;
    
    // Get Student ID
    std::cout << "\nEnter Student ID (unique identifier): ";
    std::getline(std::cin, id);
    
    // Trim whitespace
    id.erase(0, id.find_first_not_of(" \t\n\r"));
    id.erase(id.find_last_not_of(" \t\n\r") + 1);
    
    if (id.empty()) {
        std::cout << " Student ID cannot be empty!\n";
        return nullptr;
    }
    
    if (studentIdExists(id)) {
        std::cout << " Student with ID " << id << " is already registered!\n";
        return nullptr;
    }
    
    // Get Full Name
    std::cout << "Enter Full Name: ";
    std::getline(std::cin, name);
    name.erase(0, name.find_first_not_of(" \t\n\r"));
    name.erase(name.find_last_not_of(" \t\n\r") + 1);
    
    if (name.empty()) {
        std::cout << " Name cannot be empty!\n";
        return nullptr;
    }
    
    // Get Email with validation
    while (true) {
        std::cout << "Enter Email Address: ";
        std::getline(std::cin, email);
        email.erase(0, email.find_first_not_of(" \t\n\r"));
        email.erase(email.find_last_not_of(" \t\n\r") + 1);
        
        errorMsg = validateEmail(email);
        if (errorMsg.empty()) {
            break;
        } else {
            std::cout << " " << errorMsg << " Please try again.\n";
        }
    }
    
    // Get Phone with validation
    while (true) {
        std::cout << "Enter Phone Number: ";
        std::getline(std::cin, phone);
        phone.erase(0, phone.find_first_not_of(" \t\n\r"));
        phone.erase(phone.find_last_not_of(" \t\n\r") + 1);
        
        errorMsg = validatePhone(phone);
        if (errorMsg.empty()) {
            break;
        } else {
            std::cout << " " << errorMsg << " Please try again.\n";
        }
    }
    
    // Get Roll Number
    std::cout << "Enter Roll Number (e.g., CS2024001): ";
    std::getline(std::cin, rollNumber);
    rollNumber.erase(0, rollNumber.find_first_not_of(" \t\n\r"));
    rollNumber.erase(rollNumber.find_last_not_of(" \t\n\r") + 1);
    
    if (rollNumber.empty()) {
        std::cout << " Roll number cannot be empty!\n";
        return nullptr;
    }
    
    // Get Major with options
    std::cout << "\nSelect Major:\n";
    std::cout << "1. Computer Science\n";
    std::cout << "2. Electronics\n";
    std::cout << "3. Mathematics\n";
    std::cout << "4. Physics\n";
    std::cout << "5. Statistics\n";
    std::cout << "6. Engineering Field\n";
    std::cout << "7. Information Technology\n";
    std::cout << "8. Cybersecurity\n";
    std::cout << "Enter choice (1-8): ";
    
    std::string choice;
    std::getline(std::cin, choice);
    
    switch (std::stoi(choice)) {
        case 1: major = "Computer Science"; break;
        case 2: major = "Electronics"; break;
        case 3: major = "Mathematics"; break;
        case 4: major = "Physics"; break;
        case 5: major = "Statistics"; break;
        case 6: major = "Engineering Field"; break;
        case 7: major = "Information Technology"; break;
        case 8: major = "Cybersecurity"; break;
        default: 
            std::cout << " Invalid choice!\n";
            return nullptr;
    }
    
    
    Student* newStudent = new Student(id, name, email, phone, rollNumber, major);
    
    std::cout << "\n Student details validated successfully!\n";
    std::cout << "============================================\n";
    
    return newStudent;
}

void Administration::displayAdminInfo() const {
    std::cout << "\n========== Administration Information ==========\n"
              << "Admin ID: " << adminId << "\n"
              << "Admin Name: " << adminName << "\n"
              << "Total Registrations: " << totalRegistrations << "\n"
              << "Total Faculty: " << facultyList.size() << "\n"
              << "Total Departments: " << departments.size() << "\n"
              << "================================================\n";
}

// Faculty Management Methods
bool Administration::facultyIdExists(const std::string& employeeId) {
    auto it = std::find_if(facultyList.begin(), facultyList.end(),
        [&employeeId](Faculty* f) { return f->getEmployeeId() == employeeId; });
    return it != facultyList.end();
}

void Administration::addFaculty(Faculty* faculty) {
    if (facultyIdExists(faculty->getEmployeeId())) {
        std::cout << "\n ERROR: Faculty with ID " << faculty->getEmployeeId() << " already exists!\n";
        return;
    }
    facultyList.push_back(faculty);
    std::cout << "\n Faculty " << faculty->getName() << " (ID: " << faculty->getEmployeeId() 
              << ") added successfully!\n";
}

void Administration::removeFaculty(const std::string& employeeId) {
    auto it = std::find_if(facultyList.begin(), facultyList.end(),
        [&employeeId](Faculty* f) { return f->getEmployeeId() == employeeId; });
    
    if (it != facultyList.end()) {
        std::cout << "\n Faculty " << (*it)->getName() << " removed from system.\n";
        facultyList.erase(it);
    } else {
        std::cout << "\n ERROR: Faculty not found.\n";
    }
}

Faculty* Administration::searchFaculty(const std::string& employeeId) {
    auto it = std::find_if(facultyList.begin(), facultyList.end(),
        [&employeeId](Faculty* f) { return f->getEmployeeId() == employeeId; });
    
    if (it != facultyList.end()) {
        return *it;
    }
    return nullptr;
}

void Administration::displayAllFaculty() const {
    std::cout << "\n================= ALL FACULTY MEMBERS =================\n";
    std::cout << "Total Faculty: " << facultyList.size() << "\n\n";
    
    if (facultyList.empty()) {
        std::cout << "No faculty members registered yet.\n";
    } else {
        int count = 1;
        for (const auto& faculty : facultyList) {
            std::cout << count << ". Name: " << faculty->getName()
                      << " | Employee ID: " << faculty->getEmployeeId()
                      << " | Department: " << faculty->getDepartment()
                      << " | Designation: " << faculty->getDesignation()
                      << " | Salary: R" << faculty->getSalary() << "\n";
            if (count > 0 && count % 3 == 0) std::cout << "\n";
            count++;
        }
    }
    std::cout << "======================================================\n";
}

void Administration::displayFacultyByDepartment(const std::string& department) const {
    std::cout << "\n=============== FACULTY IN " << department << " ===============\n";
    
    std::vector<Faculty*> deptFaculty;
    for (const auto& faculty : facultyList) {
        if (faculty->getDepartment() == department) {
            deptFaculty.push_back(faculty);
        }
    }
    
    if (deptFaculty.empty()) {
        std::cout << "No faculty members in " << department << ".\n";
    } else {
        for (const auto& faculty : deptFaculty) {
            std::cout << "\nName: " << faculty->getName()
                      << "\nEmployee ID: " << faculty->getEmployeeId()
                      << "\nDesignation: " << faculty->getDesignation()
                      << "\nSalary: R" << faculty->getSalary()
                      << "\nCourses Taught: ";
            
            auto courses = faculty->getCoursesTaught();
            if (courses.empty()) {
                std::cout << "None assigned";
            } else {
                for (const auto& course : courses) {
                    std::cout << course << " ";
                }
            }
            std::cout << "\n";
        }
    }
    std::cout << "=========================================================\n";
}

Faculty* Administration::interactiveAddFaculty() {
    std::cout << "\n========== FACULTY REGISTRATION FORM ==========\n";
    
    std::string id, name, email, phone, employeeId, department, designation;
    double salary;
    std::string errorMsg;
    
    // Get Faculty ID
    std::cout << "\nEnter Faculty ID (unique identifier): ";
    std::getline(std::cin, id);
    id.erase(0, id.find_first_not_of(" \t\n\r"));
    id.erase(id.find_last_not_of(" \t\n\r") + 1);
    
    if (id.empty()) {
        std::cout << " Faculty ID cannot be empty!\n";
        return nullptr;
    }
    
    // Get Full Name
    std::cout << "Enter Full Name: ";
    std::getline(std::cin, name);
    name.erase(0, name.find_first_not_of(" \t\n\r"));
    name.erase(name.find_last_not_of(" \t\n\r") + 1);
    
    if (name.empty()) {
        std::cout << " Name cannot be empty!\n";
        return nullptr;
    }
    
    // Get Email with validation
    while (true) {
        std::cout << "Enter Email Address: ";
        std::getline(std::cin, email);
        email.erase(0, email.find_first_not_of(" \t\n\r"));
        email.erase(email.find_last_not_of(" \t\n\r") + 1);
        errorMsg = validateEmail(email);
        if (errorMsg.empty()) break;
        std::cout << " " << errorMsg << " Please try again.\n";
    }
    
    // Get Phone with validation
    while (true) {
        std::cout << "Enter Phone Number: ";
        std::getline(std::cin, phone);
        phone.erase(0, phone.find_first_not_of(" \t\n\r"));
        phone.erase(phone.find_last_not_of(" \t\n\r") + 1);
        errorMsg = validatePhone(phone);
        if (errorMsg.empty()) break;
        std::cout << " " << errorMsg << " Please try again.\n";
    }
    
    // Get Employee ID
    std::cout << "Enter Employee ID: ";
    std::getline(std::cin, employeeId);
    employeeId.erase(0, employeeId.find_first_not_of(" \t\n\r"));
    employeeId.erase(employeeId.find_last_not_of(" \t\n\r") + 1);
    
    if (employeeId.empty()) {
        std::cout << " Employee ID cannot be empty!\n";
        return nullptr;
    }
    
    // Select Department
    std::cout << "\nSelect Department:\n";
    std::cout << "1. Computer Science\n";
    std::cout << "2. Electronics\n";
    std::cout << "3. Mathematics\n";
    std::cout << "4. Physics\n";
    std::cout << "5. Statistics\n";
    std::cout << "6. Engineering Field\n";
    std::cout << "Enter choice (1-6): ";
    
    std::string deptChoice;
    std::getline(std::cin, deptChoice);
    
    switch (std::stoi(deptChoice)) {
        case 1: department = "Computer Science"; break;
        case 2: department = "Electronics"; break;
        case 3: department = "Mathematics"; break;
        case 4: department = "Physics"; break;
        case 5: department = "Statistics"; break;
        case 6: department = "Engineering Field"; break;
        default:
            std::cout << " Invalid choice!\n";
            return nullptr;
    }
    
    // Select Designation
    std::cout << "\nSelect Designation:\n";
    std::cout << "1. Professor\n";
    std::cout << "2. Associate Professor\n";
    std::cout << "3. Assistant Professor\n";
    std::cout << "4. Lecturer\n";
    std::cout << "5. Teaching Assistant\n";
    std::cout << "Enter choice (1-5): ";
    
    std::string desgnChoice;
    std::getline(std::cin, desgnChoice);
    
    switch (std::stoi(desgnChoice)) {
        case 1: designation = "Professor"; break;
        case 2: designation = "Associate Professor"; break;
        case 3: designation = "Assistant Professor"; break;
        case 4: designation = "Lecturer"; break;
        case 5: designation = "Teaching Assistant"; break;
        default:
            std::cout << " Invalid choice!\n";
            return nullptr;
    }
    
    // Get Salary
    std::cout << "Enter Monthly Salary (R): ";
    std::cin >> salary;
    std::cin.ignore();
    
    if (salary <= 0) {
        std::cout << " Salary must be positive!\n";
        return nullptr;
    }
    
    Faculty* newFaculty = new Faculty(id, name, email, phone, employeeId, department, designation, salary);
    std::cout << "\n Faculty details validated successfully!\n";
    std::cout << "===========================================\n";
    
    return newFaculty;
}

// Department Management Methods
void Administration::addDepartment(Department* department) {
    departments.push_back(department);
    std::cout << "\n Department " << department->getDepartmentName() << " added successfully!\n";
}

void Administration::displayAllDepartments() const {
    std::cout << "\n================= ALL DEPARTMENTS =================\n";
    std::cout << "Total Departments: " << departments.size() << "\n\n";
    
    if (departments.empty()) {
        std::cout << "No departments registered yet.\n";
    } else {
        for (const auto& dept : departments) {
            dept->displayDepartmentInfo();
        }
    }
    std::cout << "==================================================\n";
}

void Administration::displayDepartmentFaculty(const std::string& deptName) const {
    for (const auto& dept : departments) {
        if (dept->getDepartmentName() == deptName) {
            std::cout << "\n=============== " << deptName << " FACULTY ===============\n";
            std::cout << "Head of Department: " << dept->getHeadOfDepartment() << "\n";
            std::cout << "Total Faculty Members: " << dept->getFacultyMembers().size() << "\n\n";
            
            if (dept->getFacultyMembers().empty()) {
                std::cout << "No faculty members assigned to this department.\n";
            } else {
                int count = 1;
                for (const auto& faculty : dept->getFacultyMembers()) {
                    std::cout << count << ". " << faculty->getName()
                              << " | " << faculty->getDesignation()
                              << " | Salary: R" << faculty->getSalary() << "\n";
                    count++;
                }
            }
            std::cout << "=================================================\n";
            return;
        }
    }
    std::cout << "\n ERROR: Department '" << deptName << "' not found.\n";
}

// Course Management Methods
void Administration::assignFacultyToCourse(const std::string& employeeId, const std::string& courseName) {
    Faculty* faculty = searchFaculty(employeeId);
    if (faculty != nullptr) {
        faculty->assignCourse(courseName);
        std::cout << " Course assigned to faculty member.\n";
    } else {
        std::cout << " ERROR: Faculty not found.\n";
    }
}

void Administration::displayCourseFacultyMapping() const {
    std::cout << "\n============= COURSE-FACULTY MAPPING =============\n";
    
    bool hasCourses = false;
    for (const auto& faculty : facultyList) {
        auto courses = faculty->getCoursesTaught();
        if (!courses.empty()) {
            hasCourses = true;
            std::cout << "\n" << faculty->getName() << " (" << faculty->getEmployeeId() << ")\n";
            std::cout << "  Department: " << faculty->getDepartment() << "\n";
            std::cout << "  Designation: " << faculty->getDesignation() << "\n";
            std::cout << "  Courses Teaching:\n";
            for (const auto& course : courses) {
                std::cout << "    - " << course << "\n";
            }
        }
    }
    
    if (!hasCourses) {
        std::cout << "No faculty members assigned to courses yet.\n";
    }
    std::cout << "=================================================\n";
}

