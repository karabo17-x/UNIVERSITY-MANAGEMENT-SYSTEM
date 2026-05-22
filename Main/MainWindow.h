#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <vector>
#include "StudentRegistrationDialog.h"
#include "StudentSearchDialog.h"
#include "GenericListDialog.h"
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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Student Management
    void onRegisterStudent();
    void onViewStudents();
    void onSearchStudent();
    void onDeregisterStudent();

    // Academic Management
    void onAssignMarks();
    void onViewMarks();

    // Faculty Management
    void onAddFaculty();
    void onViewFaculty();
    void onViewFacultyByDept();
    void onAssignCourse();
    void onViewCourseFacultyMapping();

    // Department Management
    void onViewDepartments();
    void onViewDeptFaculty();
    void onViewPayroll();

    // Residence Management
    void onAssignResidence();
    void onViewResidenceOccupancy();

    // Sports Management
    void onViewSports();
    void onAffiliateSport();
    void onViewStudentSports();
    void onViewSportParticipants();
    void onRemoveSportAffiliation();

    // Exam Management
    void onInitializeExamSchedule();
    void onCreateExamSection();
    void onAddExam();
    void onEnrollExamSection();
    void onViewExamSchedule();
    void onViewExamSectionDetails();

    // System
    void onViewSystemInfo();
    void onExit();
    void onBackToMenu();

private:
    // Setup methods
    void setupWelcomeScreen();
    void setupMainMenu();
    void createMenuButtons();
    void applyStylesheet();

    // UI Components
    QStackedWidget *stackedWidget;
    QWidget *welcomeWidget;
    QWidget *menuWidget;
    QLabel *titleLabel;
    QLabel *welcomeLabel;

    // Business Logic Objects
    Administration *admin;
    AcademicAdmin *academicAdmin;
    Residence *hostelA;
    SportsAffiliation *sportsAffiliation;
    std::vector<Department*> departments;
    std::vector<Student*> students;
    std::vector<Faculty*> faculty;

    // Helper methods
    void initializeSystemData();
};

#endif // MAINWINDOW_H
