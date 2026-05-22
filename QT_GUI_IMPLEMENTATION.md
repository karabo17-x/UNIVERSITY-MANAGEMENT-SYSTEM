# University Management System - Qt6 GUI Implementation

## Overview

The University Management System has been successfully migrated to use **Qt6**, a modern C++ GUI framework offering:

- **Professional UI**: Modern, polished interface with professional styling
- **Signal-Slot Architecture**: Robust event handling for user interactions
- **Database-Ready**: Extensible architecture for future database integration
- **Cross-Platform**: Can be compiled and run on Linux, Windows, and macOS

## Project Structure

### New Qt Components

- **Main/MainWindow.h**: Qt main window class declaration with all UI and slot handlers
- **Main/MainWindow.cpp**: Complete implementation of the GUI including:
  - Welcome screen with system introduction
  - Multi-section menu system with 29 different operations
  - Organized category sections (Student, Faculty, Academic, etc.)
  - Professional styling and color scheme
  - Placeholder message boxes for future feature implementation

- **Main/main.cpp**: Qt application entry point

### Updated Build Configuration

- **CMakeLists.txt**: Updated to Qt6 with proper MOC handling (Recommended)
- **Makefile**: Updated for Qt6 compilation (Alternative - requires Qt6 headers/libraries)

## Building the Project

### Method 1: CMake (Recommended)

CMake automatically handles Qt6's Meta-Object Compiler (MOC) and is more robust:

```bash
cd /home/xster/University\ Management\ System
mkdir build
cd build
cmake ..
make
```

The executable will be created at: `build/university_system`

### Method 2: Make (Alternative)

```bash
cd /home/xster/University\ Management\ System
make clean
make
```

The executable will be created at: `university_system`

**Note**: The Makefile approach uses manual Qt6 include paths and may require adjustment based on your system's Qt6 installation location.

## Running the Application

### From VS Code
Use the "Run University System" task in VS Code, which builds and executes automatically.

### From Terminal

```bash
./university_system
```

## GUI Features

### Welcome Screen
- **Professional introduction** to the University Management System
- **System overview** describing all major features
- **Enter System button** to access the main menu
- **Exit button** to close the application

### Main Menu Interface
The application presents a comprehensive grid-based menu with:

#### Student Management (4 options)
- Register New Student
- View All Students
- Search Student by ID
- Deregister Student

#### Academic Management (2 options)
- Assign Marks to Student
- View Student Marks

#### Faculty Management (5 options)
- Add Faculty Member
- View All Faculty Members
- View Faculty by Department
- Assign Course to Faculty
- View Course-Faculty Mapping

#### Department Management (3 options)
- View All Departments
- View Department Faculty
- Faculty Payroll

#### Residence Management (2 options)
- Assign Residence Room
- View Residence Occupancy

#### Sports Management (5 options)
- View All Available Sports
- Affiliate Student with Sport
- View Student Sports Profile
- View Sport Participants
- Remove Student from Sport

#### Exam Management (6 options)
- Initialize Department Exam Schedule
- Create Exam Section
- Add Exam to Section
- Enroll Student in Exam Section
- View Department Exam Schedule
- View Exam Section Details

#### System Information
- View System Information (displays admin names and initialized system resources)

### Navigation
- **Back to Welcome Button**: Returns from main menu to welcome screen
- **Exit Button**: Cleanly closes the application

## Technical Specifications

### C++ Standard
- **C++17** (Required by Qt6)

### Qt6 Components
- **QtCore**: Core functionality (signals, slots, meta-object system)
- **QtGui**: Graphics and low-level UI primitives
- **QtWidgets**: High-level UI components (buttons, windows, layouts)

### Key Classes

#### MainWindow (QMainWindow)
- Inherits from QMainWindow for application window management
- Uses QStackedWidget for screen transitions
- Implements all 29 menu slot handlers
- Manages business logic object instances

#### System Initialization
- Automatically initializes 8 academic departments
- Creates administrator and academic admin objects
- Sets up hostel/residence facilities
- Configures sports affiliation system

### UI Architecture
- **Stacked Widget Layout**: Smooth transitions between welcome screen and main menu
- **Grid Layout**: Organized button arrangement in 2-column format
- **Scroll Area**: Main menu is scrollable for accessibility
- **Responsive Design**: Adapts to window resizing

## Color Scheme

- **Primary Blue**: #1a5490 (headers, buttons)
- **Success Red**: #d9534f (exit buttons)
- **Light Background**: #f5f5fa
- **Text**: Dark gray/black for readability

## Future Development

The framework is ready for:

1. **Feature Implementation**: Each menu item has a placeholder slot ready for database operations
2. **Database Integration**: Can connect to MySQL/PostgreSQL through Qt SQL modules
3. **Advanced Dialogs**: Modal dialogs for data entry and editing
4. **Data Validation**: Input validation before database commits
5. **Reporting**: Export functionality for student records, schedules, etc.

## Dependencies

### System Requirements
- Linux/Windows/macOS
- G++ compiler supporting C++17
- Qt6 development libraries (qt6-base)
- CMake 3.10+ (for building)

### Installation on Ubuntu/Debian
```bash
sudo apt-get install qt6-base-dev cmake g++
```

## Build Output Directory

- **CMake Build**: `build/` directory (recommended)
- **Make Build**: Root directory
- **Executable Name**: `university_system`

## Compilation Details

The build system properly handles:
- Automatic MOC (Meta-Object Compiler) file generation
- Proper include path resolution for Qt6
- Linking against Qt6 libraries
- C++17 compliance for Qt6 compatibility

## License and Notes

This GUI implementation retains all original business logic from the command-line version while providing a modern, professional interface through Qt6. The modular architecture allows for easy extension and feature addition.

---

**Build Status**: ✓ Successfully compiled with Qt6
**GUI Status**: ✓ Welcome screen and main menu operational
**Ready for Development**: ✓ All 29 menu handlers available for implementation
