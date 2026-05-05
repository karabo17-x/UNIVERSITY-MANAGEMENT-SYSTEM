cmake_minimum_required(VERSION 3.10)
project(UniversityManagementSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    Person.cpp
    Student.cpp
    Faculty.cpp
    Department.cpp
    Administration.cpp
    AcademicAdmin.cpp
    Residence.cpp
    Sports/Sports.cpp
    Sports/SportsAffiliation.cpp
    Exam/Exam.cpp
    Exam/ExamSection.cpp
    Exam/ExamSchedule.cpp
    main.cpp
)

add_executable(university_system ${SOURCES})

if(MSVC)
    target_compile_options(university_system PRIVATE /W4)
else()
    target_compile_options(university_system PRIVATE -Wall -Wextra -pedantic)
endif()

message(STATUS "Building University Management System")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
