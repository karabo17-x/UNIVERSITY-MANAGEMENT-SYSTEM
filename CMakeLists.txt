cmake_minimum_required(VERSION 3.10)
project(UniversityManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    Person.cpp
    Student.cpp
    Faculty.cpp
    Department.cpp
    Administration.cpp
    AcademicAdmin.cpp
    Residence.cpp
    main.cpp
)

# Create executable
add_executable(university_system ${SOURCES})

# Optional: Add compiler flags
if(MSVC)
    target_compile_options(university_system PRIVATE /W4)
else()
    target_compile_options(university_system PRIVATE -Wall -Wextra -pedantic)
endif()

# Print project info
message(STATUS "Building University Management System")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
