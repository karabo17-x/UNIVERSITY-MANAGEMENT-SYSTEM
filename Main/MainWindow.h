#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QComboBox>
#include <QFrame>
#include <QGridLayout>
#include <QVector>
#include <functional>
#include <map>
#include <vector>
#include "StudentRegistrationDialog.h"
#include "StudentSearchDialog.h"
#include "GenericListDialog.h"
#include "AuthenticationStore.h"
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
    bool authenticateSession();

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
    void onViewMyAccount();
    void onManageAccounts();
    void onExit();
    void onBackToMenu();

private:
    enum PortalRole { StudentRole, LecturerRole, AdministratorRole, RegistrarRole, ResidenceRole, SportsRole, RoleCount };
    struct PortalAction {
        QString label;
        int roles;
        std::function<void()> invoke;
        QPushButton *button = nullptr;
    };

    // Setup methods
    void setupWelcomeScreen();
    void setupMainMenu();
    void setupLegacyMenu();
    void createMenuButtons();
    void applyStylesheet();
    void updateResponsiveLayout();
    void applyRoleView();
    int roleMaskForLabel(const QString &label) const;
    int roleIndexForCode(const QString &role) const;

protected:
    void resizeEvent(QResizeEvent *event) override;

    // UI Components
    QStackedWidget *stackedWidget;
    QWidget *welcomeWidget;
    QWidget *menuWidget;
    QLabel *titleLabel;
    QLabel *welcomeLabel;
    QFrame *sidebarWidget = nullptr;
    QComboBox *compactNavigation = nullptr;
    QLabel *sessionLabel = nullptr;
    QLabel *portalLabel = nullptr;
    QLabel *dashboardHeadingLabel = nullptr;
    QLabel *dashboardSubtitleLabel = nullptr;
    QGridLayout *dashboardGrid = nullptr;
    QGridLayout *quickActionGrid = nullptr;
    QWidget *calendarCard = nullptr;
    QWidget *updatesCard = nullptr;
    QWidget *actionsCard = nullptr;
    QVector<PortalAction> navigationActions;
    QVector<PortalAction> quickActions;
    int activeRoleMask = 1;
    int activeRoleIndex = 0;
    AuthenticatedUser currentUser;

    // Business Logic Objects
    Administration *admin;
    AcademicAdmin *academicAdmin;
    Residence *hostelA;
    SportsAffiliation *sportsAffiliation;
    std::vector<Department*> departments;
    std::vector<Faculty*> faculty;
    std::map<std::string, ExamSchedule*> examSchedules;
    AuthenticationStore *authenticationStore = nullptr;

    // Helper methods
    void initializeSystemData();
};

#endif // MAINWINDOW_H
