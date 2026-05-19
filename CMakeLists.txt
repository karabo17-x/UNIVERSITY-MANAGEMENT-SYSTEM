cmake_minimum_required(VERSION 3.10)
project(UniversityManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(SOURCES
    Person/Person.cpp
    Student/Student.cpp
    Faculty/Faculty.cpp
    Department/Department.cpp
    Administration/Administration.cpp
    Academic/AcademicAdmin.cpp
    Residence/Residence.cpp
    Sports/Sports.cpp
    Sports/SportsAffiliation.cpp
    Exam/Exam.cpp
    Exam/ExamSection.cpp
    Exam/ExamSchedule.cpp
    Main/main.cpp
    Main/MainWindow.cpp
    Main/StudentRegistrationDialog.cpp
    Main/StudentSearchDialog.cpp
    Main/GenericListDialog.cpp
)

set(HEADERS
    Main/MainWindow.h
    Main/StudentRegistrationDialog.h
    Main/StudentSearchDialog.h
    Main/GenericListDialog.h
)

add_executable(university_system ${SOURCES} ${HEADERS})
target_link_libraries(university_system Qt6::Core Qt6::Gui Qt6::Widgets)

if(MSVC)
    target_compile_options(university_system PRIVATE /W4)
else()
    target_compile_options(university_system PRIVATE -Wall -Wextra -pedantic)
endif()

message(STATUS "Building University Management System with Qt6 GUI")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Qt6 Components: Core, Gui, Widgets")
