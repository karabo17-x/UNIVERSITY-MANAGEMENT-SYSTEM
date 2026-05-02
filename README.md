# University Management System - C++ Project
A comprehensive object-oriented C++ system for managing university operations including student registration, faculty management, academic administration, student residence management, and student sports activities.


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

Administration
AcademicAdmin
Residence
SportsAffiliation
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

 **Object-Oriented Design**: Uses inheritance and polymorphism  
 **Encapsulation**: Private attributes with public getters/setters  
 **Multiple Classes**: 8 different department types  
 **Course Management**: Students can enroll/drop courses  
 **Marks & Grades**: Automatic grade calculation system  
 **Residence Management**: Room assignment and tracking  
 **Search Functionality**: Search for students by ID  
 **Display Functions**: Comprehensive information display methods  

## Future Enhancements

-> Database integration for persistent storage
-> File I/O for importing/exporting student data
-> Advanced reporting and analytics
-> Notification system for grades/schedules
-> Transcript generation
-> Fee management system
-> Library management integration
-> Attendance tracking

## Requirements

-> C++ compiler supporting C++11 or higher
-> Linux/Mac: g++, clang++
-> Windows: Visual Studio, MinGW, or g++
-> CMake (optional, for CMake builds)

## Author Notes

-> Inheritance and polymorphism
-> File organization (header/implementation separation)
-> Object composition
-> Vector and Map STL containers
-> User-defined data types
-> Memory management with pointers


---

**Happy Coding! **
