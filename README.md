# University Management System - C++ Project with Qt6 GUI
A comprehensive object-oriented C++ system for managing university operations including student registration, faculty management, academic administration, student residence management, and student sports activities, with a professional Qt6 graphical user interface.

## Overview

The University Management System is a feature-complete Qt6 application that provides an intuitive desktop interface for managing all aspects of university operations. The system includes:

- **Student Management**: Registration, search, deregistration, and profile management
- **Academic Management**: Mark assignment and tracking
- **Faculty Management**: Faculty administration and course assignments
- **Department Administration**: Department organization and payroll management
- **Residence Management**: Student housing assignments and occupancy tracking
- **Sports Management**: Student sports affiliation and participation tracking
- **Examination Management**: Exam scheduling and section enrollment

## Technology Stack

- **Language**: C++17
- **GUI Framework**: Qt6 (QtCore, QtGui, QtWidgets)
- **Build Systems**: CMake (primary) and Makefile (secondary)
- **Operating System**: Linux/Unix

## Building the Project

### Prerequisites

```bash
# Install Qt6 development libraries
sudo apt-get install qt6-base-dev qt6-tools-dev

# Install CMake
sudo apt-get install cmake make g++
```

### Build Instructions

**Using CMake (Recommended)**:
```bash
mkdir build
cd build
cmake ..
make
```

**Using Make**:
```bash
make clean
make
```

### Running the Application

After building successfully:
```bash
./build/university_system
```

Or if using Makefile:
```bash
./university_system
```

## Project Structure

### Classes Overview

```
Person (Base Class)
├── Student
└── Faculty

Department (Base Class)
├── ComputerScience
├── Electronics
├── Mathematics
├── Physics
├── Statistics
├── Engineering
├── InformationTechnology
└── Cybersecurity

Sports (Base Class)
├── Soccer
├── Tennis
├── Rugby
├── Volleyball
├── Karate
├── Swimming
├── Gymnastics
├── Jujitsu
├── Boxing
├── Basketball
├── Cricket
└── Chess

Exam (Base Class)
├── Midterm
├── Final
├── Quiz
└── Assignment

ExamSection
ExamSchedule

Administration
AcademicAdmin
Residence
SportsAffiliation

Qt6 Dialog Classes:
├── StudentRegistrationDialog
├── StudentSearchDialog
└── GenericListDialog
```

## Class Descriptions

### 1. **Person** (Base Class)
-> **Purpose**: Base class for all individuals in the university
-> **Attributes**: 
  -> `id`, `name`, `email`, `phone`
-> **Methods**:
  -> Getters/Setters for all attributes
  -> `displayInfo()` - Virtual method for displaying information

### 2. **Student** (Inherits from Person)
-> **Purpose**: Manages student information and enrollments
-> **Attributes**:
  -> `rollNumber`, `major`, `gpa`, `enrolledCourses`, `residenceBlock`
-> **Methods**:
  -> `enrollCourse()`, `dropCourse()`
  -> `setGPA()`, `setResidenceBlock()`
  -> Course management functions

### 3. **Faculty** (Inherits from Person)
-> **Purpose**: Manages faculty member information
-> **Attributes**:
  -> `employeeId`, `department`, `designation`, `coursesTaught`, `salary`
-> **Methods**:
  -> `assignCourse()`, `removeCourse()`
  -> Department and salary management functions

### 4. **Department** (Base Class)
-> **Purpose**: Manages academic departments
-> **Attributes**:
  -> `departmentId`, `departmentName`, `headOfDepartment`, `facultyMembers`, `totalStudents`
-> **Methods**:
  -> `addFaculty()`, `removeFaculty()`
  -> `setTotalStudents()`, `displayDepartmentInfo()`

### 5. **Department Subclasses**
Specific implementations for each department:
-> **ComputerScience**
-> **Electronics**
-> **Mathematics**
-> **Physics**
-> **Statistics**
-> **Engineering**
-> **InformationTechnology**
-> **Cybersecurity**

Each subclass inherits from Department and can be customized with specific features.

### 6. **Administration**
-> **Purpose**: Handles student registration and deregistration
-> **Attributes**:
  -> `adminId`, `adminName`, `registeredStudents`, `totalRegistrations`
-> **Methods**:
  -> `registerStudent()`, `deregisterStudent()`
  -> `searchStudent()`, `displayAllRegistrations()`

### 7. **AcademicAdmin**
-> **Purpose**: Manages student grades and marks
-> **Attributes**:
  -> `studentMarks`, `studentGrades` (using Maps)
-> **Methods**:
  -> `assignMarks()`, `getMarks()`
  -> `assignGrade()`, `calculateGrade()`
  -> Display methods for marks and grades

### 8. **Residence**
-> **Purpose**: Manages student accommodation
-> **Attributes**:
  -> `residenceId`, `residenceName`, `blockName`, `totalRooms`, `occupiedRooms`, `warden`, `roomAssignments`
-> **Methods**:
  -> `assignRoom()`, `vacateRoom()`
  -> `getRoomOccupant()`, `displayRoomOccupancy()`

### 9. **Sports** (Base Class)
-> **Purpose**: Manages student sports activities and affiliations
-> **Attributes**:
  -> `sportId`, `sportName`, `coordinator`, `affiliatedStudents`, `affiliationFee`
-> **Methods**:
  -> `addStudent()`, `removeStudent()`
  -> `isStudentAffiliated()`, `getAffiliatedStudents()`
  -> Getters/Setters for sport properties

### 10. **Sports Subclasses**
Specific implementations for each sport:
-> **Soccer** - Fee: R150.00
-> **Tennis** - Fee: R120.00
-> **Rugby** - Fee: R140.00
-> **Volleyball** - Fee: R100.00
-> **Karate** - Fee: R175.00
-> **Swimming** - Fee: R130.00
-> **Gymnastics** - Fee: R160.00
-> **Jujitsu** - Fee: R180.00
-> **Boxing** - Fee: R165.00
-> **Basketball** - Fee: R135.00
-> **Cricket** - Fee: R145.00
-> **Chess** - Fee: R110.00

Each sport subclass inherits from Sports and represents a student activity with unique affiliation fees.

### 11. **SportsAffiliation**
-> **Purpose**: Manages student sports affiliations and payments
-> **Attributes**:
  -> `allSports` (map of sports), `studentAffiliations`, `studentPayments`
-> **Methods**:
  -> `affiliateStudentWithSport()`, `removeStudentFromSport()`
  -> `getStudentAffiliations()`, `recordPayment()`
  -> `displayAllSports()`, `displayStudentSportInfo()`, `displaySportParticipants()`

### 12. **Exam** (Base Class)
-> **Purpose**: Manages examination records and schedules
-> **Attributes**:
  -> `examId`, `examName`, `examType`, `department`, `date`, `time`, `duration`, `maxMarks`, `venue`
-> **Methods**:
  -> Getters/Setters for all exam attributes
  -> `displayExamInfo()` - Virtual method for displaying exam details

### 13. **Exam Subclasses**
Specific implementations for each exam type:
-> **Midterm** - Mid-semester examinations
-> **Final** - End-semester final examinations
-> **Quiz** - Quick assessments
-> **Assignment** - Coursework assignments

Each exam type inherits from Exam and represents a specific assessment category.

### 14. **ExamSection**
-> **Purpose**: Manages exam sections within departments
-> **Attributes**:
  -> `sectionId`, `sectionName`, `department`, `invigilator`, `capacity`, `enrolledStudents`, `exams`, `roomNumber`, `isActive`
-> **Methods**:
  -> `enrollStudent()`, `removeStudent()`, `isStudentEnrolled()`
  -> `addExam()`, `removeExam()`, `getExamById()`
  -> `displaySectionInfo()`, `displayExamSchedule()`, `displayEnrolledStudents()`

### 15. **ExamSchedule**
-> **Purpose**: Manages all exam sections for a department in a given semester
-> **Attributes**:
  -> `scheduleId`, `department`, `semester`, `examSections`, `startDate`, `endDate`, `isPublished`
-> **Methods**:
  -> `addExamSection()`, `removeExamSection()`, `getExamSectionById()`
  -> `getTotalSections()`, `getTotalEnrolledStudents()`
  -> `displayScheduleInfo()`, `displayAllSections()`, `displaySectionDetails()`

## Building the Project

### Option 1: Using Makefile

```bash
# Build the project
make

# Run the program
make run

# Clean build files
make clean
```

### Option 2: Using CMake

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run the executable
./university_system
```

### Option 3: Manual Compilation

```bash
# Compile all source files
g++ -std=c++11 -Wall -Wextra -c Person.cpp
g++ -std=c++11 -Wall -Wextra -c Student.cpp
g++ -std=c++11 -Wall -Wextra -c Faculty.cpp
g++ -std=c++11 -Wall -Wextra -c Department.cpp
g++ -std=c++11 -Wall -Wextra -c Administration.cpp
g++ -std=c++11 -Wall -Wextra -c AcademicAdmin.cpp
g++ -std=c++11 -Wall -Wextra -c Residence.cpp
g++ -std=c++11 -Wall -Wextra -c main.cpp

# Link object files
g++ -std=c++11 -o university_system Person.o Student.o Faculty.o Department.o Administration.o AcademicAdmin.o Residence.o main.o

# Run the program
./university_system
```

## File Structure

```
University Management System/
├── Person.h / Person.cpp
├── Student.h / Student.cpp
├── Faculty.h / Faculty.cpp
├── Department.h / Department.cpp
├── Administration.h / Administration.cpp
├── AcademicAdmin.h / AcademicAdmin.cpp
├── Residence.h / Residence.cpp
├── main.cpp
├── Makefile
├── CMakeLists.txt
└── README.md
```

## Usage Example

```cpp
// Create departments
ComputerScience csDepart("DEPT001", "Dr. John Smith");

// Create faculty
Faculty prof1("F001", "Dr. John Smith", "smith@university.edu", "555-1001", 
              "EMP001", "Computer Science", "Professor", 85000);

// Create students
Student student1("S001", "John Doe", "johndoe@student.edu", "555-2001", 
                 "CS2024001", "Computer Science");

// Enroll student
student1.enrollCourse("Data Structures");

// Register student
Administration admin("ADM001", "Mr. David White");
admin.registerStudent(&student1);

// Assign marks
AcademicAdmin academicAdmin("AAM001", "Mrs. Patricia Lee");
academicAdmin.assignMarks("S001", "Data Structures", 92);

// Manage residence
Residence hostelA("RES001", "Hostel A", "Block A", 10, "Dr. George Martin");
hostelA.assignRoom(1, &student1);
```

## Key Features

**Qt6 Graphical User Interface**:
 - Professional welcome screen with system introduction
 - Organized main menu with grid-based navigation (29 menu options)
 - Dialog-based data input with validation
 - Real-time list display of students, faculty, and system data
 - Functional transitions between screens using QStackedWidget
 - Dark-themed styling with consistent color scheme

**Object-Oriented Design**: Uses inheritance and polymorphism  
**Encapsulation**: Private attributes with public getters/setters  
**Multiple Classes**: 8 different department types, 12 sports types, 4 exam types  
**Course Management**: Students can enroll/drop courses  
**Marks & Grades**: Automatic grade calculation system  
**Residence Management**: Room assignment and tracking with occupancy management
**Sports Management**: Complete student sports affiliation and payment tracking
**Search Functionality**: Search for students by ID with detailed profile display
**Dialog-Based Operations**:
 - Student registration with input validation
 - Student search by ID
 - Generic list display for any data (students, faculty, sports, etc.)
 - Add/remove operations through interactive dialogs

## User Interface Workflow

1. **Welcome Screen**: Shows system overview and provides entry point
2. **Main Menu**: Grid-based navigation with 29 menu options organized by category
3. **Dialogs**: 
   - StudentRegistrationDialog for adding new students
   - StudentSearchDialog for viewing student details
   - GenericListDialog for displaying lists of data
4. **Back Navigation**: Quick return to previous screen or welcome screen

## Functional Menu Options

**Student Management (4 options)**:
  - Register New Student (with validation)
  - View All Students (list display)
  - Search Student by ID (detailed profile)
  - Deregister Student

**Academic Management (2 options)**:
  - Assign Marks to Student
  - View Student Marks

**Faculty Management (5 options)**:
  - Add Faculty Member
  - View All Faculty Members
  - View Faculty by Department
  - Assign Course to Faculty
  - View Course-Faculty Mapping

**Department Management (3 options)**:
  - View All Departments
  - View Faculty by Department
  - View Payroll Information

**Residence Management (2 options)**:
  - Assign Residence Room
  - View Residence Occupancy

**Sports Management (5 options)**:
  - View All Available Sports
  - Affiliate Student with Sport
  - View Student Sports Profile
  - View Sport Participants
  - Remove Student from Sport

**Exam Management (6 options)**:
  - Initialize Department Exam Schedule
  - Create Exam Section
  - Add Exam to Section
  - Enroll Student in Exam Section
  - View Department Exam Schedule
  - View Exam Section Details

**System Info (1 option)**:
  - View System Information

## Building the Project

### Option 1: Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Generate build files with Qt6 support
cmake ..

# Build the project
make

# Run the application
./university_system
```

### Option 2: Using Makefile

```bash
# Clean and build
make clean && make

# Run the application
./university_system
```

## File Structure

```
University Management System/
├── Person/
│   ├── Person.h / Person.cpp
├── Student/
│   ├── Student.h / Student.cpp
├── Faculty/
│   ├── Faculty.h / Faculty.cpp
├── Department/
│   ├── Department.h / Department.cpp
├── Administration/
│   ├── Administration.h / Administration.cpp
├── Academic/
│   ├── AcademicAdmin.h / AcademicAdmin.cpp
├── Residence/
│   ├── Residence.h / Residence.cpp
├── Sports/
│   ├── Sports.h / Sports.cpp
│   ├── SportsAffiliation.h / SportsAffiliation.cpp
├── Exam/
│   ├── Exam.h / Exam.cpp
│   ├── ExamSection.h / ExamSection.cpp
│   ├── ExamSchedule.h / ExamSchedule.cpp
├── Main/
│   ├── main.cpp
│   ├── MainWindow.h / MainWindow.cpp
│   ├── StudentRegistrationDialog.h / StudentRegistrationDialog.cpp
│   ├── StudentSearchDialog.h / StudentSearchDialog.cpp
│   ├── GenericListDialog.h / GenericListDialog.cpp
├── Makefile
├── CMakeLists.txt
└── README.md
```

## Usage Example

```cpp
// Create departments
ComputerScience csDepart("DEPT001", "Dr. John Smith");

// Create faculty
Faculty prof1("F001", "Dr. John Smith", "smith@university.edu", "555-1001", 
              "EMP001", "Computer Science", "Professor", 85000);

// Create students
Student student1("S001", "John Doe", "johndoe@student.edu", "555-2001", 
                 "CS2024001", "Computer Science");

// Enroll student
student1.enrollCourse("Data Structures");

// Register student
Administration admin("ADM001", "Mr. David White");
admin.registerStudent(&student1);

// Assign marks
AcademicAdmin academicAdmin("AAM001", "Mrs. Patricia Lee");
academicAdmin.assignMarks("S001", "Data Structures", 92);

// Manage residence
Residence hostelA("RES001", "Hostel A", "Block A", 10, "Dr. George Martin");
Student* foundStudent = admin.searchStudent("S001");
if (foundStudent) {
    hostelA.assignRoom(1, foundStudent);
}
```

## Key Architectural Features

**Object-Oriented Design**: 
 - Inheritance hierarchies (Person, Department, Sports, Exam)
 - Polymorphic behavior for department and sport types
 - Abstract base classes with virtual methods

**Encapsulation**: 
 - Private member variables with public accessors
 - Data validation in setter methods
 - Controlled access to internal data structures

**Qt6 Integration**:
 - Automatic MOC (Meta-Object Compiler) for signal/slot processing
 - Modal dialogs for data collection
 - Layout-based UI management
 - Custom stylesheets for theming

**Memory Management**:
 - Proper allocation and deallocation in constructors/destructors
 - Resource cleanup in MainWindow destructor
 - Vector and map containers for collection management

## Requirements

**System Requirements**:
 - Linux/Unix operating system
 - g++ compiler supporting C++17
 - CMake 3.16 or higher
 - Qt6 development libraries

**Library Dependencies**:
 - Qt6Core
 - Qt6Gui
 - Qt6Widgets

**Installation on Ubuntu/Debian**:
 ```bash
 sudo apt-get install qt6-base-dev qt6-tools-dev cmake g++
 ```

## Troubleshooting

**Build Issues**:
 - Ensure Qt6 is properly installed: `dpkg -l | grep qt6`
 - Check CMake version: `cmake --version` (requires 3.16+)
 - Verify C++ compiler: `g++ --version` (requires C++17 support)

**Runtime Issues**:
 - Verify all Business Logic classes are instantiated in MainWindow
 - Check dialog pointers are properly initialized
 - Ensure all signal/slot connections use correct syntax

---

Built with Qt6 and C++17 | Professional University Management Solution

