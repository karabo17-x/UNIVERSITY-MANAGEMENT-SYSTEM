cmake_minimum_required(VERSION 3.16)
project(UniversityManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(UMS_CORE_SOURCES
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
)

add_library(ums_core STATIC ${UMS_CORE_SOURCES})
target_link_libraries(ums_core PUBLIC Qt6::Core)
target_include_directories(ums_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(university_system
    Main/main.cpp
    Main/MainWindow.cpp
    Main/StudentRegistrationDialog.cpp
    Main/StudentSearchDialog.cpp
    Main/GenericListDialog.cpp
    Main/MainWindow.h
    Main/StudentRegistrationDialog.h
    Main/StudentSearchDialog.h
    Main/GenericListDialog.h
)
target_link_libraries(university_system PRIVATE ums_core Qt6::Gui Qt6::Widgets)

if(MSVC)
    target_compile_options(ums_core PRIVATE /W4)
    target_compile_options(university_system PRIVATE /W4)
else()
    target_compile_options(ums_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(university_system PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(ums_core_tests tests/core_tests.cpp)
    target_link_libraries(ums_core_tests PRIVATE ums_core)
    add_test(NAME ums_core_tests COMMAND ums_core_tests)
endif()

message(STATUS "Building University Management System with Qt6 GUI")
