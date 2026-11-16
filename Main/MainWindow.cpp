#include "MainWindow.h"
#include "AuthenticationDialog.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QStyle>
#include <QStyleFactory>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QDate>
#include <QFrame>
#include <QTabWidget>
#include <QResizeEvent>
#include <QRegularExpression>
#include <QTime>
#include <QStandardPaths>
#include <QDir>
#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), admin(nullptr), academicAdmin(nullptr), 
      hostelA(nullptr), sportsAffiliation(nullptr) {
    
    setWindowTitle("University Management System");
    setWindowIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    setGeometry(80, 60, 1240, 820);
    setMinimumSize(640, 480);
    
    // Initialize business logic
    initializeSystemData();
    
    // Create stacked widget for screen transitions
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    // Setup screens
    setupWelcomeScreen();
    setupMainMenu();
    const QString accountDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    authenticationStore = new AuthenticationStore(QDir(accountDirectory).filePath("university_accounts.sqlite"));
    
    // Apply stylesheet
    applyStylesheet();
    
    // Open directly on the student portal dashboard.
    stackedWidget->setCurrentWidget(menuWidget);
}

MainWindow::~MainWindow() {
    // Cleanup
    for (auto dept : departments) {
        delete dept;
    }
    for (auto fac : faculty) {
        delete fac;
    }
    if (admin) delete admin;
    if (academicAdmin) delete academicAdmin;
    if (hostelA) delete hostelA;
    if (sportsAffiliation) delete sportsAffiliation;
    for (auto &schedule : examSchedules) delete schedule.second;
    delete authenticationStore;
}

bool MainWindow::authenticateSession() {
    AuthenticatedUser user;
    if (!AuthenticationDialog::run(authenticationStore, &user, admin, this)) return false;
    currentUser = user;
    activeRoleIndex = roleIndexForCode(user.role);
    activeRoleMask = 1 << activeRoleIndex;
    applyRoleView();
    stackedWidget->setCurrentWidget(menuWidget);
    return true;
}

void MainWindow::initializeSystemData() {
    admin = new Administration("ADM001", "Mr. Karabo Mothapo");
    academicAdmin = new AcademicAdmin("AAM001", "Mrs. Petronella Mothapo");
    hostelA = new Residence("RES001", "Hostel A", "Block A", 10, "Dr. Phillip Mphahlele");
    sportsAffiliation = new SportsAffiliation();
    
    // Initialize Departments
    departments.push_back(new ComputerScience("DEPT001", "Dr. Ahmed Hassan"));
    departments.push_back(new Electronics("DEPT002", "Prof. Sarah Johnson"));
    departments.push_back(new Mathematics("DEPT003", "Dr. Michael Smith"));
    departments.push_back(new Physics("DEPT004", "Dr. Emily Brown"));
    departments.push_back(new Statistics("DEPT005", "Prof. James Wilson"));
    departments.push_back(new Engineering("DEPT006", "Dr. Robert Davis"));
    departments.push_back(new InformationTechnology("DEPT007", "Dr. Lisa Anderson"));
    departments.push_back(new Cybersecurity("DEPT008", "Prof. David Martinez"));
    for (auto *department : departments) admin->addDepartment(department);
}

void MainWindow::setupWelcomeScreen() {
    welcomeWidget = new QWidget();
    welcomeWidget->setObjectName("welcomeScreen");
    welcomeWidget->setStyleSheet("QWidget#welcomeScreen { background-color: #f5f7fb; }");
    QVBoxLayout *layout = new QVBoxLayout(welcomeWidget);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(20);
    
    // Title
    QLabel *mainTitle = new QLabel("Welcome to University Management System");
    mainTitle->setStyleSheet("font-size: 32px; font-weight: bold; color: #174f83;");
    mainTitle->setAlignment(Qt::AlignCenter);
    
    // Subtitle
    QLabel *subtitle = new QLabel("Professional Management Solution for Higher Education");
    subtitle->setStyleSheet("font-size: 16px; color: #4b5563;");
    subtitle->setAlignment(Qt::AlignCenter);
    
    // Description
    QLabel *description = new QLabel(
        "This comprehensive system manages all aspects of university operations:\n\n"
        "• Student Registration and Academic Records\n"
        "• Faculty Management and Course Assignments\n"
        "• Department Administration\n"
        "• Residence and Accommodation Services\n"
        "• Sports Affiliations and Participation\n"
        "• Examination Scheduling and Management\n\n"
        "Click 'Enter System' to access the management dashboard."
    );
    description->setStyleSheet("font-size: 14px; color: #374151; line-height: 1.6;");
    description->setAlignment(Qt::AlignCenter);
    description->setWordWrap(true);
    
    // Add spacing
    layout->addStretch();
    layout->addWidget(mainTitle);
    layout->addWidget(subtitle);
    layout->addSpacing(20);
    layout->addWidget(description);
    layout->addSpacing(30);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    QPushButton *enterButton = new QPushButton("Enter System");
    enterButton->setMinimumWidth(150);
    enterButton->setMinimumHeight(45);
    enterButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #1a5490;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0d3a66;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #082549;"
        "}"
    );
    connect(enterButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(menuWidget);
    });
    
    QPushButton *exitButton = new QPushButton("Exit");
    exitButton->setMinimumWidth(100);
    exitButton->setMinimumHeight(45);
    exitButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #d9534f;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c9302c;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #ac2925;"
        "}"
    );
    connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);
    
    buttonLayout->addWidget(enterButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addStretch();
    
    layout->addLayout(buttonLayout);
    layout->addStretch();
    stackedWidget->addWidget(welcomeWidget);
}

void MainWindow::setupMainMenu() {
    menuWidget = new QWidget();
    menuWidget->setObjectName("portalRoot");

    auto *rootLayout = new QHBoxLayout(menuWidget);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    auto *sidebar = new QFrame();
    sidebar->setObjectName("sidebar");
    auto *sidebarScroll = new QScrollArea();
    sidebarScroll->setObjectName("sidebarScroll");
    sidebarScroll->setWidgetResizable(true);
    sidebarScroll->setFrameShape(QFrame::NoFrame);
    sidebarScroll->setFixedWidth(230);
    sidebarScroll->setWidget(sidebar);
    sidebarWidget = sidebarScroll;
    auto *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(24, 25, 20, 22);
    sidebarLayout->setSpacing(5);

    auto *brandRow = new QHBoxLayout();
    auto *brandMark = new QLabel("U");
    brandMark->setObjectName("brandMark");
    brandMark->setAlignment(Qt::AlignCenter);
    brandMark->setFixedSize(54, 54);
    auto *brandText = new QLabel("UMS");
    brandText->setObjectName("brandText");
    brandRow->addWidget(brandMark);
    brandRow->addWidget(brandText);
    brandRow->addStretch();
    sidebarLayout->addLayout(brandRow);
    sidebarLayout->addSpacing(28);

    auto addNavigation = [this, sidebarLayout](const QString &text, const std::function<void()> &action,
                                                bool selected = false) {
        auto *button = new QPushButton(text);
        button->setObjectName(selected ? "navButtonActive" : "navButton");
        button->setCursor(Qt::PointingHandCursor);
        button->setMinimumHeight(38);
        const int allowedRoles = roleMaskForLabel(text);
        connect(button, &QPushButton::clicked, this, [this, allowedRoles, action] {
            if (activeRoleMask & allowedRoles) action();
        });
        sidebarLayout->addWidget(button);
        navigationActions.append({text, allowedRoles, action, button});
    };

    addNavigation("Dashboard", [] {}, true);
    addNavigation("Registration", [this] { onRegisterStudent(); });
    addNavigation("Student Directory", [this] { onViewStudents(); });
    addNavigation("Academics", [this] { onAssignMarks(); });
    addNavigation("My Residences", [this] { onViewResidenceOccupancy(); });
    addNavigation("Campus Sports", [this] { onViewSports(); });
    addNavigation("My Exams", [this] { onViewExamSchedule(); });
    addNavigation("My account", [this] { onViewMyAccount(); });
    addNavigation("System overview", [this] { onViewSystemInfo(); });
    addNavigation("Manage accounts", [this] { onManageAccounts(); });
    addNavigation("Search students", [this] { onSearchStudent(); });
    addNavigation("Deregister student", [this] { onDeregisterStudent(); });
    addNavigation("View marks", [this] { onViewMarks(); });
    addNavigation("Faculty", [this] { onViewFaculty(); });
    addNavigation("Departments", [this] { onViewDepartments(); });
    addNavigation("Assign residence", [this] { onAssignResidence(); });
    addNavigation("Sport participants", [this] { onViewSportParticipants(); });
    addNavigation("Exam sections", [this] { onViewExamSectionDetails(); });
    addNavigation("Add faculty", [this] { onAddFaculty(); });
    addNavigation("Faculty by department", [this] { onViewFacultyByDept(); });
    addNavigation("Assign course", [this] { onAssignCourse(); });
    addNavigation("Course mapping", [this] { onViewCourseFacultyMapping(); });
    addNavigation("Department faculty", [this] { onViewDeptFaculty(); });
    addNavigation("Payroll", [this] { onViewPayroll(); });
    addNavigation("Affiliate sport", [this] { onAffiliateSport(); });
    addNavigation("Student sports", [this] { onViewStudentSports(); });
    addNavigation("Remove sport affiliation", [this] { onRemoveSportAffiliation(); });
    addNavigation("Initialize exam schedule", [this] { onInitializeExamSchedule(); });
    addNavigation("Create exam section", [this] { onCreateExamSection(); });
    addNavigation("Add exam", [this] { onAddExam(); });
    addNavigation("Enroll exam section", [this] { onEnrollExamSection(); });
    sidebarLayout->addStretch();
    addNavigation("Sign out", [this] { onBackToMenu(); });

    auto *content = new QWidget();
    content->setObjectName("portalContent");
    auto *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(30, 24, 30, 28);
    contentLayout->setSpacing(16);

    auto *utilityRow = new QHBoxLayout();
    compactNavigation = new QComboBox();
    compactNavigation->setObjectName("compactNavigation");
    connect(compactNavigation, QOverload<int>::of(&QComboBox::activated), this, [this](int index) {
        const int actionIndex = compactNavigation->itemData(index).toInt();
        if (actionIndex >= 0 && actionIndex < navigationActions.size() &&
            (activeRoleMask & navigationActions[actionIndex].roles)) navigationActions[actionIndex].invoke();
        compactNavigation->setCurrentIndex(0);
    });
    compactNavigation->setVisible(false);
    utilityRow->addWidget(compactNavigation);
    sessionLabel = new QLabel();
    sessionLabel->setObjectName("sessionLabel");
    utilityRow->addWidget(sessionLabel);
    portalLabel = new QLabel("Student portal");
    portalLabel->setObjectName("portalLabel");
    auto *helpButton = new QPushButton("?");
    helpButton->setObjectName("utilityButton");
    helpButton->setToolTip("Help and support");
    utilityRow->addWidget(portalLabel);
    utilityRow->addStretch();
    utilityRow->addWidget(helpButton);
    contentLayout->addLayout(utilityRow);

    dashboardHeadingLabel = new QLabel("Student dashboard");
    dashboardHeadingLabel->setObjectName("dashboardHeading");
    contentLayout->addWidget(dashboardHeadingLabel);
    auto *accent = new QFrame();
    accent->setObjectName("headingAccent");
    accent->setFixedSize(180, 4);
    contentLayout->addWidget(accent);
    dashboardSubtitleLabel = new QLabel("Your registration, campus life and academic information.");
    dashboardSubtitleLabel->setObjectName("dashboardSubtitle");
    contentLayout->addWidget(dashboardSubtitleLabel);
    contentLayout->addSpacing(4);

    auto createCard = [](const QString &title) {
        auto *card = new QFrame();
        card->setObjectName("portalCard");
        auto *layout = new QVBoxLayout(card);
        layout->setContentsMargins(18, 16, 18, 16);
        layout->setSpacing(10);
        auto *cardTitle = new QLabel(title);
        cardTitle->setObjectName("cardTitle");
        layout->addWidget(cardTitle);
        return card;
    };

    dashboardGrid = new QGridLayout();
    dashboardGrid->setHorizontalSpacing(18);
    dashboardGrid->setVerticalSpacing(18);

    calendarCard = createCard("Calendar");
    auto *calendarLayout = qobject_cast<QVBoxLayout *>(calendarCard->layout());
    auto *calendarHeader = new QHBoxLayout();
    auto *dateLabel = new QLabel(QDate::currentDate().toString("dddd, d MMMM yyyy"));
    dateLabel->setObjectName("calendarDate");
    auto *viewAll = new QPushButton("View all");
    viewAll->setObjectName("linkButton");
    connect(viewAll, &QPushButton::clicked, this, [this] {
        if (activeRoleMask & roleMaskForLabel("My Exams")) onViewExamSchedule();
    });
    calendarHeader->addWidget(dateLabel);
    calendarHeader->addStretch();
    calendarHeader->addWidget(viewAll);
    calendarLayout->addLayout(calendarHeader);

    auto *calendarBody = new QFrame();
    calendarBody->setObjectName("calendarBody");
    auto *calendarRows = new QVBoxLayout(calendarBody);
    calendarRows->setContentsMargins(0, 0, 0, 0);
    calendarRows->setSpacing(0);
    const QStringList times = {"All day", "08:00", "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00"};
    for (const QString &time : times) {
        auto *row = new QLabel(time);
        row->setObjectName("calendarRow");
        row->setMinimumHeight(35);
        row->setContentsMargins(12, 0, 0, 0);
        calendarRows->addWidget(row);
    }
    calendarLayout->addWidget(calendarBody, 1);
    auto *legend = new QLabel("● Registration     ● Academics     ● Residence     ● Campus life");
    legend->setObjectName("calendarLegend");
    calendarLayout->addWidget(legend);
    dashboardGrid->addWidget(calendarCard, 0, 0, 2, 1);

    updatesCard = createCard("Updates");
    auto *updatesLayout = qobject_cast<QVBoxLayout *>(updatesCard->layout());
    auto *updatesTabs = new QTabWidget();
    updatesTabs->setObjectName("updatesTabs");
    auto *notifications = new QLabel("You currently have no new notifications.");
    notifications->setObjectName("emptyState");
    notifications->setWordWrap(true);
    auto *holds = new QLabel("There are no holds on your student account.");
    holds->setObjectName("emptyState");
    holds->setWordWrap(true);
    auto *news = new QLabel("Registration services and academic records are available from the navigation menu.");
    news->setObjectName("emptyState");
    news->setWordWrap(true);
    updatesTabs->addTab(notifications, "Notifications");
    updatesTabs->addTab(holds, "Holds");
    updatesTabs->addTab(news, "News");
    updatesLayout->addWidget(updatesTabs, 1);
    dashboardGrid->addWidget(updatesCard, 0, 1);

    actionsCard = createCard("Quick actions");
    auto *actionsLayout = qobject_cast<QVBoxLayout *>(actionsCard->layout());
    quickActionGrid = new QGridLayout();
    quickActionGrid->setSpacing(10);
    const std::vector<PortalAction> actions = {
        {"Register", 1 | (1 << RegistrarRole) | (1 << AdministratorRole), [this] { onRegisterStudent(); }},
        {"Student directory", (1 << RegistrarRole) | (1 << AdministratorRole), [this] { onViewStudents(); }},
        {"Assign marks", (1 << LecturerRole) | (1 << AdministratorRole), [this] { onAssignMarks(); }},
        {"View marks", (1 << LecturerRole) | (1 << AdministratorRole), [this] { onViewMarks(); }},
        {"My exams", (1 << StudentRole) | (1 << LecturerRole) | (1 << RegistrarRole) | (1 << AdministratorRole), [this] { onViewExamSchedule(); }},
        {"Enroll in exams", (1 << StudentRole) | (1 << RegistrarRole) | (1 << AdministratorRole), [this] { onEnrollExamSection(); }},
        {"Campus sports", (1 << StudentRole) | (1 << SportsRole) | (1 << AdministratorRole), [this] { onViewSports(); }},
        {"My sports", (1 << StudentRole) | (1 << SportsRole) | (1 << AdministratorRole), [this] { onViewStudentSports(); }},
        {"My residence", (1 << StudentRole), [this] { onViewResidenceOccupancy(); }},
        {"Add faculty", (1 << AdministratorRole), [this] { onAddFaculty(); }},
        {"Departments", (1 << LecturerRole) | (1 << AdministratorRole), [this] { onViewDepartments(); }},
        {"Search students", (1 << RegistrarRole) | (1 << AdministratorRole), [this] { onSearchStudent(); }},
        {"Assign residence", (1 << ResidenceRole) | (1 << AdministratorRole), [this] { onAssignResidence(); }},
        {"Residence occupancy", (1 << ResidenceRole) | (1 << AdministratorRole), [this] { onViewResidenceOccupancy(); }},
        {"Sport participants", (1 << SportsRole) | (1 << AdministratorRole), [this] { onViewSportParticipants(); }},
        {"System overview", (1 << AdministratorRole), [this] { onViewSystemInfo(); }},
        {"Manage accounts", (1 << AdministratorRole), [this] { onManageAccounts(); }}
    };
    for (const auto &action : actions) {
        auto *button = new QPushButton(action.label);
        button->setObjectName("quickAction");
        button->setMinimumHeight(42);
        connect(button, &QPushButton::clicked, this, [this, action] {
            if (activeRoleMask & action.roles) action.invoke();
        });
        quickActions.append({action.label, action.roles, action.invoke, button});
    }
    actionsLayout->addLayout(quickActionGrid);
    dashboardGrid->addWidget(actionsCard, 1, 1);

    dashboardGrid->setColumnStretch(0, 6);
    dashboardGrid->setColumnStretch(1, 5);
    dashboardGrid->setRowStretch(0, 3);
    dashboardGrid->setRowStretch(1, 1);
    contentLayout->addLayout(dashboardGrid, 1);

    rootLayout->addWidget(sidebarScroll);
    auto *contentScroll = new QScrollArea();
    contentScroll->setWidgetResizable(true);
    contentScroll->setFrameShape(QFrame::NoFrame);
    contentScroll->setWidget(content);
    rootLayout->addWidget(contentScroll, 1);
    stackedWidget->addWidget(menuWidget);
    updateResponsiveLayout();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    updateResponsiveLayout();
}

void MainWindow::updateResponsiveLayout() {
    if (!sidebarWidget || !compactNavigation || !dashboardGrid || !calendarCard || !updatesCard || !actionsCard) return;
    const bool compact = width() < 900;
    sidebarWidget->setVisible(!compact);
    compactNavigation->setVisible(compact);
    while (QLayoutItem *item = dashboardGrid->takeAt(0)) delete item;
    if (compact) {
        dashboardGrid->addWidget(calendarCard, 0, 0);
        dashboardGrid->addWidget(updatesCard, 1, 0);
        dashboardGrid->addWidget(actionsCard, 2, 0);
        dashboardGrid->setColumnStretch(0, 1);
        dashboardGrid->setColumnStretch(1, 0);
        dashboardGrid->setRowStretch(0, 1);
        dashboardGrid->setRowStretch(1, 0);
        dashboardGrid->setRowStretch(2, 0);
    } else {
        dashboardGrid->addWidget(calendarCard, 0, 0, 2, 1);
        dashboardGrid->addWidget(updatesCard, 0, 1);
        dashboardGrid->addWidget(actionsCard, 1, 1);
        dashboardGrid->setColumnStretch(0, 6);
        dashboardGrid->setColumnStretch(1, 5);
        dashboardGrid->setRowStretch(0, 3);
        dashboardGrid->setRowStretch(1, 1);
    }
}

int MainWindow::roleMaskForLabel(const QString &label) const {
    const int student = 1 << StudentRole;
    const int lecturer = 1 << LecturerRole;
    const int administrator = 1 << AdministratorRole;
    const int registrar = 1 << RegistrarRole;
    const int residence = 1 << ResidenceRole;
    const int sports = 1 << SportsRole;
    const int everyone = student | lecturer | administrator | registrar | residence | sports;

    if (label == "Dashboard" || label == "Sign out") return everyone;
    if (label == "Registration") return registrar | administrator;
    if (label == "Student Directory" || label == "Search students" || label == "Deregister student") return registrar | administrator;
    if (label == "Academics" || label == "View marks" || label == "Faculty by department" ||
        label == "Course mapping" || label == "Department faculty" || label == "Faculty" || label == "Departments")
        return lecturer | administrator;
    if (label == "My Residences") return student | residence | administrator;
    if (label == "Assign residence") return residence | administrator;
    if (label == "Campus Sports" || label == "Student sports" || label == "Affiliate sport") return student | sports | administrator;
    if (label == "My Exams" || label == "Exam sections") return student | lecturer | registrar | administrator;
    if (label == "Enroll exam section") return student | registrar | administrator;
    if (label == "My account") return everyone;
    if (label == "System overview" || label == "Manage accounts") return administrator;
    if (label == "Sport participants") return sports | administrator;
    if (label == "Affiliate sport" || label == "Remove sport affiliation") return student | sports | administrator;
    if (label == "Add faculty" || label == "Assign course" || label == "Payroll" ||
        label == "Initialize exam schedule" || label == "Create exam section") return administrator;
    if (label == "Add exam") return lecturer | administrator;
    return everyone;
}

void MainWindow::applyRoleView() {
    const QStringList roleNames = {"Student", "Lecturer", "Administrator", "Registrar", "Residence staff", "Sports coordinator"};
    const int roleIndex = qBound(0, activeRoleIndex, RoleCount - 1);
    const QString roleName = roleNames[roleIndex];
    activeRoleMask = 1 << roleIndex;

    if (sessionLabel) sessionLabel->setText(QString("%1 · %2").arg(currentUser.fullName, roleName));
    if (portalLabel) portalLabel->setText(roleName.toUpper() + " PORTAL");
    if (dashboardHeadingLabel) dashboardHeadingLabel->setText(roleName + " dashboard");
    if (dashboardSubtitleLabel) {
        const QStringList descriptions = {
            "Your registration, campus life and academic information.",
            "Teaching tools, course assignments and exam information.",
            "University operations, people and academic services.",
            "Student records, registration and exam enrollment.",
            "Room assignments and residence occupancy.",
            "Campus sports, affiliations and participant lists."
        };
        dashboardSubtitleLabel->setText(descriptions[roleIndex]);
    }

    for (const auto &action : navigationActions)
        if (action.button) action.button->setVisible(action.roles & activeRoleMask);

    if (compactNavigation) {
        compactNavigation->clear();
        compactNavigation->addItem("Go to…", -1);
        for (int i = 0; i < navigationActions.size(); ++i) {
            const auto &action = navigationActions[i];
            if (action.roles & activeRoleMask) compactNavigation->addItem(action.label, i);
        }
    }

    while (quickActionGrid && quickActionGrid->count()) {
        QLayoutItem *item = quickActionGrid->takeAt(0);
        delete item;
    }
    int visibleAction = 0;
    for (const auto &action : quickActions) {
        const bool visible = action.roles & activeRoleMask;
        if (action.button) action.button->setVisible(visible);
        if (visible && quickActionGrid) quickActionGrid->addWidget(action.button, visibleAction / 2, visibleAction % 2);
        if (visible) ++visibleAction;
    }
}

int MainWindow::roleIndexForCode(const QString &role) const {
    if (role == "student") return StudentRole;
    if (role == "lecturer") return LecturerRole;
    if (role == "administrator") return AdministratorRole;
    if (role == "registrar") return RegistrarRole;
    if (role == "residence") return ResidenceRole;
    if (role == "sports") return SportsRole;
    return AdministratorRole;
}

void MainWindow::setupLegacyMenu() {
    menuWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(menuWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title
    titleLabel = new QLabel("UNIVERSITY MANAGEMENT SYSTEM - MAIN MENU");
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #1a5490;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(15);
    
    // Scrollable content
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");
    
    QWidget *scrollWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setSpacing(10);
    
    int row = 0;
    int col = 0;
    
    // Student Management Section
    QLabel *studentLabel = new QLabel("STUDENT MANAGEMENT");
    studentLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(studentLabel, row++, 0, 1, 2);
    
    QStringList studentButtons = {
        "1. Register New Student", "2. View All Students",
        "3. Search Student by ID", "4. Deregister Student"
    };
    
    for (const QString &text : studentButtons) {
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(35);
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            if (text.contains("Register")) onRegisterStudent();
            else if (text.contains("View All")) onViewStudents();
            else if (text.contains("Search")) onSearchStudent();
            else if (text.contains("Deregister")) onDeregisterStudent();
        });
        gridLayout->addWidget(btn, row, col);
        col = (col + 1) % 2;
        if (col == 0) row++;
    }
    row++;
    
    // Academic Management
    QLabel *academicLabel = new QLabel("ACADEMIC MANAGEMENT");
    academicLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(academicLabel, row++, 0, 1, 2);
    
    QStringList academicButtons = {
        "5. Assign Marks to Student", "6. View Student Marks"
    };
    
    for (const QString &text : academicButtons) {
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(35);
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            if (text.contains("Assign")) onAssignMarks();
            else onViewMarks();
        });
        gridLayout->addWidget(btn, row, col);
        col = (col + 1) % 2;
        if (col == 0) row++;
    }
    row++;
    
    // Faculty Management
    QLabel *facultyLabel = new QLabel("FACULTY MANAGEMENT");
    facultyLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(facultyLabel, row++, 0, 1, 2);
    
    QStringList facultyButtons = {
        "7. Add Faculty Member", "8. View All Faculty Members",
        "9. View Faculty by Department", "10. Assign Course to Faculty",
        "11. View Course-Faculty Mapping", ""
    };
    
    for (const QString &text : facultyButtons) {
        if (text.isEmpty()) continue;
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(35);
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            if (text.contains("Add Faculty")) onAddFaculty();
            else if (text.contains("View All Faculty")) onViewFaculty();
            else if (text.contains("Department")) onViewFacultyByDept();
            else if (text.contains("Assign Course")) onAssignCourse();
            else if (text.contains("Course-Faculty")) onViewCourseFacultyMapping();
        });
        gridLayout->addWidget(btn, row, col);
        col = (col + 1) % 2;
        if (col == 0) row++;
    }
    row++;
    
    // Department Management
    QLabel *deptLabel = new QLabel("DEPARTMENT MANAGEMENT");
    deptLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(deptLabel, row++, 0, 1, 2);
    
    QStringList deptButtons = {
        "12. View All Departments", "13. View Department Faculty",
        "14. Faculty Payroll (Salary Info)", ""
    };
    
    for (const QString &text : deptButtons) {
        if (text.isEmpty()) continue;
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(35);
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            if (text.contains("All Departments")) onViewDepartments();
            else if (text.contains("Faculty")) onViewDeptFaculty();
            else if (text.contains("Payroll")) onViewPayroll();
        });
        gridLayout->addWidget(btn, row, col);
        col = (col + 1) % 2;
        if (col == 0) row++;
    }
    row++;
    
    // Residence Management
    QLabel *resLabel = new QLabel("RESIDENCE MANAGEMENT");
    resLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(resLabel, row++, 0, 1, 2);
    
    QStringList resButtons = {
        "15. Assign Residence Room", "16. View Residence Occupancy"
    };
    
    for (const QString &text : resButtons) {
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(35);
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            if (text.contains("Assign")) onAssignResidence();
            else onViewResidenceOccupancy();
        });
        gridLayout->addWidget(btn, row, col);
        col = (col + 1) % 2;
        if (col == 0) row++;
    }
    row++;
    
    // Sports Management
    QLabel *sportsLabel = new QLabel("SPORTS MANAGEMENT");
    sportsLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(sportsLabel, row++, 0, 1, 2);
    
    QStringList sportsButtons = {
        "17. View All Available Sports", "18. Affiliate Student with Sport",
        "19. View Student Sports Profile", "20. View Sport Participants",
        "21. Remove Student from Sport", ""
    };
    
    for (const QString &text : sportsButtons) {
        if (text.isEmpty()) continue;
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(35);
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            if (text.contains("Available Sports")) onViewSports();
            else if (text.contains("Affiliate")) onAffiliateSport();
            else if (text.contains("Sports Profile")) onViewStudentSports();
            else if (text.contains("Participants")) onViewSportParticipants();
            else if (text.contains("Remove")) onRemoveSportAffiliation();
        });
        gridLayout->addWidget(btn, row, col);
        col = (col + 1) % 2;
        if (col == 0) row++;
    }
    row++;
    
    // Exam Management
    QLabel *examLabel = new QLabel("EXAM MANAGEMENT");
    examLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(examLabel, row++, 0, 1, 2);
    
    QStringList examButtons = {
        "22. Initialize Department Exam Schedule", "23. Create Exam Section",
        "24. Add Exam to Section", "25. Enroll Student in Exam Section",
        "26. View Department Exam Schedule", "27. View Exam Section Details"
    };
    
    for (const QString &text : examButtons) {
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumHeight(35);
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            if (text.contains("Initialize")) onInitializeExamSchedule();
            else if (text.contains("Create Exam Section")) onCreateExamSection();
            else if (text.contains("Add Exam")) onAddExam();
            else if (text.contains("Enroll")) onEnrollExamSection();
            else if (text.contains("Schedule")) onViewExamSchedule();
            else if (text.contains("Details")) onViewExamSectionDetails();
        });
        gridLayout->addWidget(btn, row, col);
        col = (col + 1) % 2;
        if (col == 0) row++;
    }
    row++;
    
    // System Info
    QLabel *sysLabel = new QLabel("SYSTEM INFO");
    sysLabel->setStyleSheet("font-weight: bold; color: #1a5490; margin-top: 10px;");
    gridLayout->addWidget(sysLabel, row++, 0, 1, 2);
    
    QPushButton *infoBtn = new QPushButton("28. View System Information");
    infoBtn->setMinimumHeight(35);
    connect(infoBtn, &QPushButton::clicked, this, &MainWindow::onViewSystemInfo);
    gridLayout->addWidget(infoBtn, row, 0);
    
    row++;
    
    // Bottom Navigation
    QHBoxLayout *navLayout = new QHBoxLayout();
    navLayout->addStretch();
    
    QPushButton *backBtn = new QPushButton("Back to Welcome");
    backBtn->setMinimumWidth(120);
    backBtn->setMinimumHeight(35);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::onBackToMenu);
    
    QPushButton *exitBtn = new QPushButton("Exit");
    exitBtn->setMinimumWidth(100);
    exitBtn->setMinimumHeight(35);
    connect(exitBtn, &QPushButton::clicked, this, &QApplication::quit);
    
    navLayout->addWidget(backBtn);
    navLayout->addWidget(exitBtn);
    
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea, 1);
    mainLayout->addLayout(navLayout);
    
    // Add widgets to stacked widget
    stackedWidget->addWidget(welcomeWidget);
    stackedWidget->addWidget(menuWidget);
}

void MainWindow::applyStylesheet() {
    qApp->setStyle(QStyleFactory::create("Fusion"));
    
    QString globalStylesheet = R"(
        QWidget { color: #303039; font-family: "Segoe UI", "Arial", sans-serif; }
        QWidget#portalRoot, QWidget#portalContent { background: #f5f5f7; }
        QFrame#sidebar { background: #ffffff; border-right: 1px solid #e5e5e9; }
        QLabel#brandMark { background: #6f168d; color: white; border-radius: 16px; font-size: 30px; font-weight: 800; }
        QLabel#brandText { color: #6f168d; font-size: 24px; font-weight: 700; letter-spacing: 1px; }
        QPushButton#navButton, QPushButton#navButtonActive { border: 0; border-radius: 6px; padding: 0 12px; text-align: left; font-size: 14px; }
        QPushButton#navButton { background: transparent; color: #68717d; }
        QPushButton#navButton:hover { background: #f2edf5; color: #6f168d; }
        QPushButton#navButtonActive { background: #f0e7f4; color: #6f168d; font-weight: 700; border-left: 3px solid #6f168d; }
        QLabel#portalLabel { color: #8a8a92; font-size: 13px; }
        QLabel#sessionLabel { color: #4d3b57; font-size: 13px; font-weight: 600; padding: 0 8px; }
        QPushButton#utilityButton { min-width: 34px; max-width: 34px; min-height: 34px; max-height: 34px; border: 0; border-radius: 7px; background: #e4e4e7; color: #6f168d; font-weight: 700; }
        QPushButton#utilityButton:hover { background: #d8c7e1; }
        QLabel#dashboardHeading { color: #34343a; font-size: 42px; font-weight: 800; }
        QFrame#headingAccent { background: #6f3b95; }
        QLabel#dashboardSubtitle { color: #55555d; font-size: 15px; }
        QFrame#portalCard { background: white; border: 1px solid #e5e4e8; border-radius: 12px; }
        QLabel#cardTitle { color: #2f3036; font-size: 20px; font-weight: 700; }
        QLabel#calendarDate { color: #34343a; font-size: 14px; font-weight: 600; }
        QPushButton#linkButton { border: 0; background: transparent; color: #008fbd; font-weight: 700; padding: 4px; }
        QPushButton#linkButton:hover { color: #6f168d; }
        QFrame#calendarBody { border: 1px solid #ededf0; background: #ffffff; }
        QLabel#calendarRow { color: #50515a; border-bottom: 1px solid #eeeeef; font-size: 13px; }
        QLabel#calendarLegend { color: #6f168d; font-size: 12px; padding-top: 4px; }
        QTabWidget#updatesTabs::pane { border: 0; border-top: 1px solid #dddddf; }
        QTabBar::tab { background: transparent; color: #777780; padding: 8px 16px; font-size: 14px; }
        QTabBar::tab:selected { color: #6f168d; border-bottom: 3px solid #00a2c7; font-weight: 700; }
        QLabel#emptyState { color: #4e4f57; padding: 16px 10px; font-size: 14px; }
        QPushButton#quickAction { background: #f7f3f9; color: #6f168d; border: 1px solid #dfd1e7; border-radius: 6px; font-weight: 600; padding: 7px; }
        QPushButton#quickAction:hover { background: #e9dcee; }
        QComboBox#compactNavigation { min-height: 34px; min-width: 170px; padding: 2px 8px; border: 1px solid #ddd6e3; border-radius: 6px; background: white; color: #4d3b57; }
        QComboBox#compactNavigation:focus { border: 2px solid #6f168d; }
        QLineEdit { color: #202027; background-color: #ffffff; border: 1px solid #c9c9d0; border-radius: 4px; padding: 6px; selection-background-color: #6f168d; }
        QLineEdit:focus { border: 2px solid #6f168d; }
        QDialog { background-color: #f5f5f7; }
    )";
    
    qApp->setStyleSheet(globalStylesheet);
}

// Slot implementations - all menu actions
void MainWindow::onRegisterStudent() {
    StudentRegistrationDialog dialog(admin, this);
    dialog.exec();
}

void MainWindow::onViewStudents() {
    auto students = admin->getRegisteredStudents();
    QStringList studentList;
    for (auto student : students) {
        QString entry = QString("ID: %1 | Name: %2 | GPA: %3")
            .arg(QString::fromStdString(student->getId()),
                 QString::fromStdString(student->getName()),
                 QString::number(student->getGPA()));
        studentList.append(entry);
    }
    
    if (studentList.isEmpty()) {
        QMessageBox::information(this, "View Students", "No students registered yet.");
    } else {
        GenericListDialog dialog("Registered Students", studentList, this);
        dialog.exec();
    }
}

void MainWindow::onSearchStudent() {
    StudentSearchDialog dialog(admin, this);
    dialog.exec();
}

void MainWindow::onDeregisterStudent() {
    auto students = admin->getRegisteredStudents();
    if (students.empty()) {
        QMessageBox::information(this, "Deregister Student", "No students registered.");
        return;
    }
    
    QStringList studentIds;
    for (auto student : students) {
        studentIds.append(QString::fromStdString(student->getId()));
    }
    
    bool ok;
    QString selectedId = QInputDialog::getItem(this, "Deregister Student",
        "Select Student ID:", studentIds, 0, false, &ok);
    
    if (ok && !selectedId.isEmpty()) {
        Student* student = admin->searchStudent(selectedId.toStdString());
        if (student) {
            const auto choice = QMessageBox::question(this, "Confirm deregistration",
                QString("Remove %1 (%2) from the student register?")
                    .arg(QString::fromStdString(student->getName()), selectedId),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if (choice != QMessageBox::Yes) return;
            admin->deregisterStudent(selectedId.toStdString());
            QMessageBox::information(this, "Success", "Student deregistered successfully.");
        }
    }
}

void MainWindow::onAssignMarks() {
    auto students = admin->getRegisteredStudents();
    if (students.empty()) {
        QMessageBox::information(this, "Assign Marks", "No students registered.");
        return;
    }
    
    QStringList studentIds;
    for (auto student : students) {
        studentIds.append(QString::fromStdString(student->getId()));
    }
    
    bool ok;
    QString studentId = QInputDialog::getItem(this, "Assign Marks", "Select Student:", studentIds, 0, false, &ok);
    if (!ok || studentId.isEmpty()) return;
    
    QString course = QInputDialog::getText(this, "Assign Marks", "Enter course name:", QLineEdit::Normal, "", &ok);
    if (!ok || course.isEmpty()) return;
    
    QString marks = QInputDialog::getText(this, "Assign Marks", "Enter marks (0-100):", QLineEdit::Normal, "", &ok);
    if (ok && !marks.isEmpty()) {
        bool isDouble;
        double marksValue = marks.toDouble(&isDouble);
        if (isDouble && marksValue >= 0 && marksValue <= 100) {
            academicAdmin->assignMarks(studentId.toStdString(), course.toStdString(), marksValue);
            QMessageBox::information(this, "Success", "Marks assigned successfully.");
        } else {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid mark between 0 and 100.");
        }
    }
}

void MainWindow::onViewMarks() {
    auto students = admin->getRegisteredStudents();
    QStringList marksList;
    for (auto student : students) {
        QString entry = QString("ID: %1 | Name: %2")
            .arg(QString::fromStdString(student->getId()),
                 QString::fromStdString(student->getName()));
        marksList.append(entry);
    }
    
    if (marksList.isEmpty()) {
        QMessageBox::information(this, "View Marks", "No student marks available.");
    } else {
        GenericListDialog dialog("Student Marks", marksList, this);
        dialog.exec();
    }
}

void MainWindow::onAddFaculty() {
    bool ok = false;
    const QString id = QInputDialog::getText(this, "Add faculty", "Faculty record ID:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || id.isEmpty()) return;
    const QString employeeId = QInputDialog::getText(this, "Add faculty", "Employee ID:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || employeeId.isEmpty()) return;
    for (auto *member : admin->getFacultyList()) {
        if (QString::fromStdString(member->getEmployeeId()) == employeeId) {
            QMessageBox::warning(this, "Duplicate employee ID", "A faculty member with this employee ID already exists.");
            return;
        }
    }
    const QString name = QInputDialog::getText(this, "Add faculty", "Full name:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || name.isEmpty()) return;
    const QString email = QInputDialog::getText(this, "Add faculty", "Email address:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || email.isEmpty() || !email.contains('@') || !email.contains('.')) {
        if (ok) QMessageBox::warning(this, "Invalid email", "Enter a valid email address.");
        return;
    }
    const QString phone = QInputDialog::getText(this, "Add faculty", "Phone number:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || phone.isEmpty()) return;
    QStringList departmentNames;
    for (auto *department : admin->getDepartments()) departmentNames.append(QString::fromStdString(department->getDepartmentName()));
    const QString departmentName = QInputDialog::getItem(this, "Add faculty", "Department:", departmentNames, 0, false, &ok);
    if (!ok || departmentName.isEmpty()) return;
    const QString designation = QInputDialog::getText(this, "Add faculty", "Designation:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || designation.isEmpty()) return;
    const double salary = QInputDialog::getDouble(this, "Add faculty", "Monthly salary (R):", 30000.0, 0.0, 10000000.0, 2, &ok);
    if (!ok) return;
    auto *member = new Faculty(id.toStdString(), name.toStdString(), email.toStdString(), phone.toStdString(),
                               employeeId.toStdString(), departmentName.toStdString(), designation.toStdString(), salary);
    admin->addFaculty(member);
    faculty.push_back(member);
    for (auto *department : admin->getDepartments()) {
        if (departmentName.toStdString() == department->getDepartmentName()) {
            department->addFaculty(member);
            break;
        }
    }
    QMessageBox::information(this, "Faculty added", QString("%1 has been added to %2.").arg(name, departmentName));
}

void MainWindow::onViewFaculty() {
    auto facultyList = admin->getFacultyList();
    QStringList facultyItems;
    for (auto fac : facultyList) {
        QString entry = QString("ID: %1 | Name: %2")
            .arg(QString::fromStdString(fac->getEmployeeId()),
                 QString::fromStdString(fac->getName()));
        facultyItems.append(entry);
    }
    
    if (facultyItems.isEmpty()) {
        QMessageBox::information(this, "View Faculty", "No faculty members found.");
    } else {
        GenericListDialog dialog("Faculty Members", facultyItems, this);
        dialog.exec();
    }
}

void MainWindow::onViewFacultyByDept() {
    auto depts = admin->getDepartments();
    QStringList deptNames;
    for (auto dept : depts) {
        deptNames.append(QString::fromStdString(dept->getDepartmentName()));
    }
    
    bool ok;
    QString selectedDept = QInputDialog::getItem(this, "Select Department", "Department:", deptNames, 0, false, &ok);
    if (ok && !selectedDept.isEmpty()) {
        QStringList facultyItems;
        for (auto *member : admin->getFacultyList()) {
            if (QString::fromStdString(member->getDepartment()) == selectedDept) {
                facultyItems.append(QString("%1 | %2 | %3")
                    .arg(QString::fromStdString(member->getEmployeeId()),
                         QString::fromStdString(member->getName()),
                         QString::fromStdString(member->getDesignation())));
            }
        }
        if (facultyItems.isEmpty()) facultyItems.append("No faculty members are assigned to this department.");
        GenericListDialog dialog("Faculty in " + selectedDept, facultyItems, this);
        dialog.exec();
    }
}

void MainWindow::onAssignCourse() {
    auto facultyList = admin->getFacultyList();
    QStringList facultyIds;
    for (auto fac : facultyList) {
        facultyIds.append(QString::fromStdString(fac->getEmployeeId()));
    }
    
    if (facultyIds.isEmpty()) {
        QMessageBox::information(this, "Assign Course", "No faculty members available.");
        return;
    }
    
    bool ok;
    QString facultyId = QInputDialog::getItem(this, "Assign Course", "Select Faculty:", facultyIds, 0, false, &ok);
    if (!ok || facultyId.isEmpty()) return;
    
    QString course = QInputDialog::getText(this, "Assign Course", "Enter course name:", QLineEdit::Normal, "", &ok);
    if (ok && !course.isEmpty()) {
        admin->assignFacultyToCourse(facultyId.toStdString(), course.toStdString());
        QMessageBox::information(this, "Success", "Course assigned successfully.");
    }
}

void MainWindow::onViewCourseFacultyMapping() {
    QStringList mapping;
    for (auto *member : admin->getFacultyList()) {
        const auto courses = member->getCoursesTaught();
        for (const auto &course : courses) {
            mapping.append(QString("%1 — %2 (%3)")
                .arg(QString::fromStdString(course), QString::fromStdString(member->getName()),
                     QString::fromStdString(member->getEmployeeId())));
        }
    }
    if (mapping.isEmpty()) mapping.append("No courses have been assigned to faculty yet.");
    GenericListDialog dialog("Course–Faculty Mapping", mapping, this);
    dialog.exec();
}

void MainWindow::onViewDepartments() {
    auto depts = admin->getDepartments();
    QStringList deptList;
    for (auto dept : depts) {
        QString entry = QString("ID: %1 | Name: %2 | Head: %3")
            .arg(QString::fromStdString(dept->getDepartmentId()),
                 QString::fromStdString(dept->getDepartmentName()),
                 QString::fromStdString(dept->getHeadOfDepartment()));
        deptList.append(entry);
    }
    
    GenericListDialog dialog("All Departments", deptList, this);
    dialog.exec();
}

void MainWindow::onViewDeptFaculty() {
    auto depts = admin->getDepartments();
    QStringList deptNames;
    for (auto dept : depts) {
        deptNames.append(QString::fromStdString(dept->getDepartmentName()));
    }
    
    bool ok;
    QString selectedDept = QInputDialog::getItem(this, "Department Faculty", "Select Department:", deptNames, 0, false, &ok);
    if (ok && !selectedDept.isEmpty()) {
        auto dept = admin->getDepartments()[deptNames.indexOf(selectedDept)];
        auto faculty = dept->getFacultyMembers();
        
        QStringList facultyList;
        for (auto fac : faculty) {
            QString entry = QString("ID: %1 | Name: %2 | Salary: %3")
                .arg(QString::fromStdString(fac->getEmployeeId()),
                     QString::fromStdString(fac->getName()),
                     QString::number(fac->getSalary(), 'f', 2));
            facultyList.append(entry);
        }
        
        GenericListDialog dialog("Faculty in " + selectedDept, facultyList, this);
        dialog.exec();
    }
}

void MainWindow::onViewPayroll() {
    auto depts = admin->getDepartments();
    QStringList payrollList;
    for (auto dept : depts) {
        auto faculties = dept->getFacultyMembers();
        for (auto fac : faculties) {
            QString entry = QString("Faculty: %1 | Department: %2 | Salary: %3")
                .arg(QString::fromStdString(fac->getName()),
                     QString::fromStdString(dept->getDepartmentName()),
                     QString::number(fac->getSalary()));
            payrollList.append(entry);
        }
    }
    
    if (payrollList.isEmpty()) {
        QMessageBox::information(this, "Payroll", "No faculty payroll data available.");
    } else {
        GenericListDialog dialog("Faculty Payroll", payrollList, this);
        dialog.exec();
    }
}

void MainWindow::onAssignResidence() {
    auto students = admin->getRegisteredStudents();
    if (students.empty()) {
        QMessageBox::information(this, "Assign Residence", "No students registered.");
        return;
    }
    
    QStringList studentIds;
    for (auto student : students) {
        studentIds.append(QString::fromStdString(student->getId()));
    }
    
    bool ok;
    QString studentId = QInputDialog::getItem(this, "Assign Residence", "Select Student:", studentIds, 0, false, &ok);
    if (!ok || studentId.isEmpty()) return;
    
    auto student = admin->searchStudent(studentId.toStdString());
    if (!student) {
        QMessageBox::warning(this, "Error", "Student not found.");
        return;
    }
    if (!student->getResidenceBlock().empty()) {
        QMessageBox::information(this, "Residence already assigned",
            QString("This student already has a room assigned: %1.").arg(QString::fromStdString(student->getResidenceBlock())));
        return;
    }
    
    QString roomNo = QInputDialog::getText(this, "Assign Residence", "Enter room number:", QLineEdit::Normal, "", &ok);
    if (ok && !roomNo.isEmpty()) {
        bool isInt;
        int roomNumber = roomNo.toInt(&isInt);
        if (isInt && roomNumber > 0 && roomNumber <= hostelA->getTotalRooms()) {
            if (hostelA->getRoomOccupant(roomNumber)) {
                QMessageBox::warning(this, "Room unavailable", "That room is already occupied.");
                return;
            }
            hostelA->assignRoom(roomNumber, student);
            QMessageBox::information(this, "Success", "Room assigned successfully.");
        } else {
            QMessageBox::warning(this, "Invalid Input", QString("Enter a room number from 1 to %1.").arg(hostelA->getTotalRooms()));
        }
    }
}

void MainWindow::onViewResidenceOccupancy() {
    if (activeRoleIndex == StudentRole) {
        if (currentUser.linkedId.isEmpty()) {
            QMessageBox::information(this, "My residence", "Your account is not linked to a student record yet.");
            return;
        }
        Student *student = admin->searchStudent(currentUser.linkedId.toStdString());
        const QString assignment = student && !student->getResidenceBlock().empty()
            ? QString::fromStdString(student->getResidenceBlock()) : "No residence room is assigned to your account.";
        QMessageBox::information(this, "My residence", assignment);
        return;
    }
    QStringList rooms;
    for (int room = 1; room <= hostelA->getTotalRooms(); ++room) {
        Student *occupant = hostelA->getRoomOccupant(room);
        rooms.append(occupant
            ? QString("Room %1 — %2 (%3)").arg(room).arg(QString::fromStdString(occupant->getName()), QString::fromStdString(occupant->getId()))
            : QString("Room %1 — Available").arg(room));
    }
    GenericListDialog dialog(QString("%1 · %2/%3 occupied")
        .arg(QString::fromStdString(hostelA->getResidenceName()))
        .arg(hostelA->getOccupiedRooms()).arg(hostelA->getTotalRooms()), rooms, this);
    dialog.exec();
}

void MainWindow::onViewSports() {
    auto sports = sportsAffiliation->getAllSports();
    QStringList sportsList;
    for (auto sport : sports) {
        QString entry = QString("Sport: %1 | Coordinator: %2")
            .arg(QString::fromStdString(sport->getSportId()),
                 QString::fromStdString(sport->getCoordinator()));
        sportsList.append(entry);
    }
    
    if (sportsList.isEmpty()) {
        QMessageBox::information(this, "View Sports", "No sports available.");
    } else {
        GenericListDialog dialog("Available Sports", sportsList, this);
        dialog.exec();
    }
}

void MainWindow::onAffiliateSport() {
    auto students = admin->getRegisteredStudents();
    if (students.empty()) {
        QMessageBox::information(this, "Affiliate Sport", "No students registered.");
        return;
    }
    
    auto sports = sportsAffiliation->getAllSports();
    if (sports.empty()) {
        QMessageBox::information(this, "Affiliate Sport", "No sports available.");
        return;
    }
    
    QString studentId;
    bool ok = false;
    if (activeRoleIndex == StudentRole) {
        studentId = currentUser.linkedId;
        if (studentId.isEmpty() || !admin->searchStudent(studentId.toStdString())) {
            QMessageBox::warning(this, "Student account", "Your account must be linked to an active student record before joining a sport.");
            return;
        }
    } else {
        QStringList studentIds;
        for (auto student : students) studentIds.append(QString::fromStdString(student->getId()));
        studentId = QInputDialog::getItem(this, "Affiliate Sport", "Select Student:", studentIds, 0, false, &ok);
        if (!ok || studentId.isEmpty()) return;
    }
    QStringList sportIds;
    for (auto sport : sports) {
        sportIds.append(QString::fromStdString(sport->getSportId()));
    }
    
    QString sportId = QInputDialog::getItem(this, "Affiliate Sport", "Select Sport:", sportIds, 0, false, &ok);
    if (ok && !sportId.isEmpty()) {
        sportsAffiliation->affiliateStudentWithSport(studentId.toStdString(), sportId.toStdString());
        QMessageBox::information(this, "Success", "Student affiliated with sport successfully.");
    }
}

void MainWindow::onViewStudentSports() {
    if (activeRoleIndex == StudentRole) {
        if (currentUser.linkedId.isEmpty()) {
            QMessageBox::information(this, "My sports", "Your account is not linked to a student record yet.");
            return;
        }
        QStringList sports;
        for (const auto &sportId : sportsAffiliation->getStudentAffiliations(currentUser.linkedId.toStdString())) {
            Sports *sport = sportsAffiliation->getSport(sportId);
            if (sport) sports.append(QString::fromStdString(sport->getSportName()));
        }
        if (sports.isEmpty()) sports.append("You are not affiliated with any campus sports yet.");
        GenericListDialog dialog("My sports", sports, this);
        dialog.exec();
        return;
    }
    auto students = admin->getRegisteredStudents();
    if (students.empty()) {
        QMessageBox::information(this, "Student Sports", "No students registered.");
        return;
    }
    
    QStringList studentIds;
    for (auto student : students) {
        studentIds.append(QString::fromStdString(student->getId()));
    }
    
    bool ok;
    QString studentId = QInputDialog::getItem(this, "Student Sports", "Select Student:", studentIds, 0, false, &ok);
    if (ok && !studentId.isEmpty()) {
        auto sportIds = sportsAffiliation->getStudentAffiliations(studentId.toStdString());
        QStringList sportList;
        for (auto sportId : sportIds) {
            auto sport = sportsAffiliation->getSport(sportId);
            if (sport) {
                sportList.append(QString::fromStdString(sport->getSportName()));
            }
        }
        
        if (sportList.isEmpty()) {
            QMessageBox::information(this, "Student Sports", "No sports found for this student.");
        } else {
            GenericListDialog dialog("Student Sports Profile", sportList, this);
            dialog.exec();
        }
    }
}

void MainWindow::onViewSportParticipants() {
    auto sports = sportsAffiliation->getAllSports();
    if (sports.empty()) {
        QMessageBox::information(this, "Sport Participants", "No sports available.");
        return;
    }
    
    QStringList sportIds;
    for (auto sport : sports) {
        sportIds.append(QString::fromStdString(sport->getSportId()));
    }
    
    bool ok;
    QString sportId = QInputDialog::getItem(this, "Sport Participants", "Select Sport:", sportIds, 0, false, &ok);
    if (ok && !sportId.isEmpty()) {
        Sports *sport = sportsAffiliation->getSport(sportId.toStdString());
        QStringList participants;
        if (sport) {
            for (const auto &studentId : sport->getAffiliatedStudents()) {
                Student *student = admin->searchStudent(studentId);
                participants.append(student
                    ? QString("%1 — %2").arg(QString::fromStdString(studentId), QString::fromStdString(student->getName()))
                    : QString::fromStdString(studentId));
            }
        }
        if (participants.isEmpty()) participants.append("No students are affiliated with this sport yet.");
        GenericListDialog dialog("Sport Participants", participants, this);
        dialog.exec();
    }
}

void MainWindow::onRemoveSportAffiliation() {
    auto students = admin->getRegisteredStudents();
    if (students.empty()) {
        QMessageBox::information(this, "Remove Sport", "No students registered.");
        return;
    }
    
    bool ok = false;
    QString studentId;
    if (activeRoleIndex == StudentRole) {
        studentId = currentUser.linkedId;
        if (studentId.isEmpty() || !admin->searchStudent(studentId.toStdString())) {
            QMessageBox::warning(this, "Student account", "Your account must be linked to an active student record.");
            return;
        }
    } else {
        QStringList studentIds;
        for (auto student : students) studentIds.append(QString::fromStdString(student->getId()));
        studentId = QInputDialog::getItem(this, "Remove Sport", "Select Student:", studentIds, 0, false, &ok);
        if (!ok || studentId.isEmpty()) return;
    }
    
    auto sportIds = sportsAffiliation->getStudentAffiliations(studentId.toStdString());
    if (sportIds.empty()) {
        QMessageBox::information(this, "Remove Sport", "Student not affiliated with any sport.");
        return;
    }
    
    QStringList sportIdList;
    for (auto sportId : sportIds) {
        sportIdList.append(QString::fromStdString(sportId));
    }
    
    QString sportId = QInputDialog::getItem(this, "Remove Sport", "Select Sport:", sportIdList, 0, false, &ok);
    if (ok && !sportId.isEmpty()) {
        sportsAffiliation->removeStudentFromSport(studentId.toStdString(), sportId.toStdString());
        QMessageBox::information(this, "Success", "Student removed from sport successfully.");
    }
}

void MainWindow::onInitializeExamSchedule() {
    QStringList departments;
    for (auto *department : admin->getDepartments()) departments.append(QString::fromStdString(department->getDepartmentName()));
    bool ok = false;
    const QString department = QInputDialog::getItem(this, "Initialize exam schedule", "Department:", departments, 0, false, &ok);
    if (!ok || department.isEmpty()) return;
    const QString semester = QInputDialog::getText(this, "Initialize exam schedule", "Semester (for example, Semester 1 2026):", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || semester.isEmpty()) return;
    const std::string key = department.toStdString();
    if (examSchedules.count(key)) {
        QMessageBox::warning(this, "Schedule exists", "An exam schedule already exists for this department.");
        return;
    }
    const QString id = QString("%1-%2").arg(department, semester).replace(QRegularExpression("[^A-Za-z0-9-]"), "-");
    examSchedules[key] = new ExamSchedule(id.toStdString(), key, semester.toStdString());
    QMessageBox::information(this, "Schedule created", QString("The %1 exam schedule is ready.").arg(department));
}

void MainWindow::onCreateExamSection() {
    QStringList available;
    for (const auto &entry : examSchedules) available.append(QString::fromStdString(entry.first));
    if (available.isEmpty()) { QMessageBox::information(this, "Create exam section", "Initialize a department schedule first."); return; }
    bool ok = false;
    const QString department = QInputDialog::getItem(this, "Create exam section", "Department:", available, 0, false, &ok);
    if (!ok || department.isEmpty()) return;
    ExamSchedule *schedule = examSchedules.at(department.toStdString());
    const QString id = QInputDialog::getText(this, "Create exam section", "Section ID:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || id.isEmpty()) return;
    if (schedule->getExamSectionById(id.toStdString())) { QMessageBox::warning(this, "Duplicate section", "That section ID already exists."); return; }
    const QString name = QInputDialog::getText(this, "Create exam section", "Section name:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || name.isEmpty()) return;
    const QString invigilator = QInputDialog::getText(this, "Create exam section", "Invigilator:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || invigilator.isEmpty()) return;
    const QString room = QInputDialog::getText(this, "Create exam section", "Room:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || room.isEmpty()) return;
    const int capacity = QInputDialog::getInt(this, "Create exam section", "Capacity:", 30, 1, 1000, 1, &ok);
    if (!ok) return;
    schedule->addExamSection(new ExamSection(id.toStdString(), name.toStdString(), department.toStdString(), invigilator.toStdString(), capacity, room.toStdString()));
    QMessageBox::information(this, "Section created", QString("%1 was added to the %2 schedule.").arg(name, department));
}

void MainWindow::onAddExam() {
    QStringList available;
    for (const auto &entry : examSchedules) if (!entry.second->getExamSections().empty()) available.append(QString::fromStdString(entry.first));
    if (available.isEmpty()) { QMessageBox::information(this, "Add exam", "Create a department schedule and section first."); return; }
    bool ok = false;
    const QString department = QInputDialog::getItem(this, "Add exam", "Department:", available, 0, false, &ok);
    if (!ok || department.isEmpty()) return;
    ExamSchedule *schedule = examSchedules.at(department.toStdString());
    QStringList sectionIds;
    for (auto *section : schedule->getExamSections()) sectionIds.append(QString::fromStdString(section->getSectionId()));
    const QString sectionId = QInputDialog::getItem(this, "Add exam", "Section:", sectionIds, 0, false, &ok);
    if (!ok || sectionId.isEmpty()) return;
    ExamSection *section = schedule->getExamSectionById(sectionId.toStdString());
    const QString id = QInputDialog::getText(this, "Add exam", "Exam ID:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || id.isEmpty()) return;
    if (section->getExamById(id.toStdString())) { QMessageBox::warning(this, "Duplicate exam", "That exam ID already exists in this section."); return; }
    const QString name = QInputDialog::getText(this, "Add exam", "Exam or course name:", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok || name.isEmpty()) return;
    const QString type = QInputDialog::getItem(this, "Add exam", "Type:", {"Midterm", "Final", "Quiz", "Assignment"}, 0, false, &ok);
    if (!ok || type.isEmpty()) return;
    const QString date = QInputDialog::getText(this, "Add exam", "Date (DD/MM/YYYY):", QLineEdit::Normal, {}, &ok).trimmed();
    if (!ok) return;
    const QDate parsedDate = QDate::fromString(date, "dd/MM/yyyy");
    if (!parsedDate.isValid() || parsedDate.toString("dd/MM/yyyy") != date) { QMessageBox::warning(this, "Invalid date", "Enter a valid date as DD/MM/YYYY."); return; }
    const QString time = QInputDialog::getText(this, "Add exam", "Time (HH:MM):", QLineEdit::Normal, "09:00", &ok).trimmed();
    if (!ok) return;
    if (!QTime::fromString(time, "HH:mm").isValid()) { QMessageBox::warning(this, "Invalid time", "Enter a valid time as HH:MM."); return; }
    const int duration = QInputDialog::getInt(this, "Add exam", "Duration in minutes:", 120, 1, 1440, 1, &ok);
    if (!ok) return;
    const int marks = QInputDialog::getInt(this, "Add exam", "Maximum marks:", 100, 1, 10000, 1, &ok);
    if (!ok) return;
    const QString venue = QInputDialog::getText(this, "Add exam", "Venue:", QLineEdit::Normal, QString::fromStdString(section->getRoomNumber()), &ok).trimmed();
    if (!ok || venue.isEmpty()) return;
    Exam *exam = nullptr;
    if (type == "Midterm") exam = new Midterm(id.toStdString(), name.toStdString(), department.toStdString(), date.toStdString(), time.toStdString(), duration, marks, venue.toStdString());
    else if (type == "Final") exam = new Final(id.toStdString(), name.toStdString(), department.toStdString(), date.toStdString(), time.toStdString(), duration, marks, venue.toStdString());
    else if (type == "Quiz") exam = new Quiz(id.toStdString(), name.toStdString(), department.toStdString(), date.toStdString(), time.toStdString(), duration, marks, venue.toStdString());
    else exam = new Assignment(id.toStdString(), name.toStdString(), department.toStdString(), date.toStdString(), time.toStdString(), duration, marks, venue.toStdString());
    section->addExam(exam);
    QMessageBox::information(this, "Exam added", QString("%1 was added to section %2.").arg(name, sectionId));
}

void MainWindow::onEnrollExamSection() {
    QStringList available;
    for (const auto &entry : examSchedules) if (!entry.second->getExamSections().empty()) available.append(QString::fromStdString(entry.first));
    if (available.isEmpty()) { QMessageBox::information(this, "Enroll in exam section", "Create a department schedule and section first."); return; }
    bool ok = false;
    const QString department = QInputDialog::getItem(this, "Enroll in exam section", "Department:", available, 0, false, &ok);
    if (!ok || department.isEmpty()) return;
    ExamSchedule *schedule = examSchedules.at(department.toStdString());
    QStringList sectionIds;
    for (auto *section : schedule->getExamSections()) sectionIds.append(QString::fromStdString(section->getSectionId()));
    const QString sectionId = QInputDialog::getItem(this, "Enroll in exam section", "Section:", sectionIds, 0, false, &ok);
    if (!ok || sectionId.isEmpty()) return;
    ExamSection *section = schedule->getExamSectionById(sectionId.toStdString());
    QString studentId;
    if (activeRoleIndex == StudentRole) {
        studentId = currentUser.linkedId;
        if (studentId.isEmpty() || !admin->searchStudent(studentId.toStdString())) {
            QMessageBox::warning(this, "Student account", "Your account must be linked to an active student record before enrolling.");
            return;
        }
    } else {
        QStringList studentIds;
        for (auto *student : admin->getRegisteredStudents()) studentIds.append(QString::fromStdString(student->getId()));
        if (studentIds.isEmpty()) { QMessageBox::information(this, "Enroll in exam section", "Register students before enrolling them."); return; }
        studentId = QInputDialog::getItem(this, "Enroll in exam section", "Student:", studentIds, 0, false, &ok);
        if (!ok || studentId.isEmpty()) return;
    }
    if (section->isStudentEnrolled(studentId.toStdString())) { QMessageBox::information(this, "Already enrolled", "This student is already in the selected section."); return; }
    if (section->getEnrolledCount() >= section->getCapacity()) { QMessageBox::warning(this, "Section full", "This exam section has reached capacity."); return; }
    section->enrollStudent(studentId.toStdString());
    QMessageBox::information(this, "Enrollment complete", QString("Student %1 is enrolled in %2.").arg(studentId, sectionId));
}

void MainWindow::onViewExamSchedule() {
    QStringList available;
    for (const auto &entry : examSchedules) available.append(QString::fromStdString(entry.first));
    if (available.isEmpty()) { QMessageBox::information(this, "Exam schedule", "No exam schedules have been created yet."); return; }
    bool ok = false;
    const QString department = QInputDialog::getItem(this, "View exam schedule", "Department:", available, 0, false, &ok);
    if (!ok || department.isEmpty()) return;
    ExamSchedule *schedule = examSchedules.at(department.toStdString());
    QStringList rows;
    for (auto *section : schedule->getExamSections()) {
        rows.append(QString("%1 — %2 | Room %3 | %4/%5 enrolled | Invigilator: %6")
            .arg(QString::fromStdString(section->getSectionId()), QString::fromStdString(section->getSectionName()),
                 QString::fromStdString(section->getRoomNumber()))
            .arg(section->getEnrolledCount()).arg(section->getCapacity())
            .arg(QString::fromStdString(section->getInvigilator())));
        for (auto *exam : section->getExams()) rows.append(QString("   %1 · %2 · %3 %4 · %5 min")
            .arg(QString::fromStdString(exam->getExamName()), QString::fromStdString(exam->getExamType()),
                 QString::fromStdString(exam->getDate()), QString::fromStdString(exam->getTime())).arg(exam->getDuration()));
    }
    if (rows.isEmpty()) rows.append("No exam sections have been added to this schedule.");
    GenericListDialog dialog(QString("%1 — %2").arg(department, QString::fromStdString(schedule->getSemester())), rows, this);
    dialog.exec();
}

void MainWindow::onViewExamSectionDetails() {
    QStringList available;
    for (const auto &entry : examSchedules) if (!entry.second->getExamSections().empty()) available.append(QString::fromStdString(entry.first));
    if (available.isEmpty()) { QMessageBox::information(this, "Exam section details", "No exam sections have been created yet."); return; }
    bool ok = false;
    const QString department = QInputDialog::getItem(this, "Exam section details", "Department:", available, 0, false, &ok);
    if (!ok || department.isEmpty()) return;
    ExamSchedule *schedule = examSchedules.at(department.toStdString());
    QStringList sectionIds;
    for (auto *section : schedule->getExamSections()) sectionIds.append(QString::fromStdString(section->getSectionId()));
    const QString sectionId = QInputDialog::getItem(this, "Exam section details", "Section:", sectionIds, 0, false, &ok);
    if (!ok || sectionId.isEmpty()) return;
    ExamSection *section = schedule->getExamSectionById(sectionId.toStdString());
    QStringList details = {QString::fromStdString(section->getSectionName()),
        QString("Department: %1 | Invigilator: %2").arg(department, QString::fromStdString(section->getInvigilator())),
        QString("Room: %1 | Enrollment: %2/%3").arg(QString::fromStdString(section->getRoomNumber())).arg(section->getEnrolledCount()).arg(section->getCapacity()),
        "Exams:"};
    for (auto *exam : section->getExams()) details.append(QString("%1 — %2 | %3 %4 | %5 minutes | %6 marks | %7")
        .arg(QString::fromStdString(exam->getExamType()), QString::fromStdString(exam->getExamName()),
             QString::fromStdString(exam->getDate()), QString::fromStdString(exam->getTime()))
        .arg(exam->getDuration()).arg(exam->getMaxMarks()).arg(QString::fromStdString(exam->getVenue())));
    details.append("Enrolled students:");
    for (const auto &id : section->getEnrolledStudents()) {
        Student *student = admin->searchStudent(id);
        details.append(student ? QString("%1 — %2").arg(QString::fromStdString(id), QString::fromStdString(student->getName())) : QString::fromStdString(id));
    }
    GenericListDialog dialog(QString("Exam section %1").arg(sectionId), details, this);
    dialog.exec();
}

void MainWindow::onViewSystemInfo() {
    if (activeRoleIndex != AdministratorRole) return;
    QString info = QString(
        "University Management System\n"
        "Version 2.0 - Qt6 GUI Edition\n\n"
        "Administration: %1\n"
        "Academic Admin: %2\n"
        "Departments: %3\n"
        "Students: %4\n"
        "Faculty: %5"
    ).arg(QString::fromStdString(admin->getAdminName()), 
          QString::fromStdString(academicAdmin->getAdminName()), 
          QString::number(departments.size()), 
          QString::number(admin->getTotalRegistrations()),
          QString::number(admin->getFacultyList().size()));
    
    QMessageBox::information(this, "System Information", info);
}

void MainWindow::onViewMyAccount() {
    QString details = QString("Name: %1\nUsername: %2\nRole: %3")
        .arg(currentUser.fullName, currentUser.username,
             QStringList{"Student", "Lecturer", "Administrator", "Registrar", "Residence staff", "Sports coordinator"}[activeRoleIndex]);
    if (!currentUser.linkedId.isEmpty()) details += QString("\nLinked university ID: %1").arg(currentUser.linkedId);
    QMessageBox accountBox(QMessageBox::Information, "My account", details, QMessageBox::Close, this);
    QPushButton *changePassword = accountBox.addButton("Change password", QMessageBox::ActionRole);
    accountBox.exec();
    if (accountBox.clickedButton() != changePassword) return;
    bool ok = false;
    const QString oldPassword = QInputDialog::getText(this, "Change password", "Current password:", QLineEdit::Password, {}, &ok);
    if (!ok) return;
    const QString newPassword = QInputDialog::getText(this, "Change password", "New password (at least 10 characters):", QLineEdit::Password, {}, &ok);
    if (!ok) return;
    const QString confirmation = QInputDialog::getText(this, "Confirm password", "Repeat the new password:", QLineEdit::Password, {}, &ok);
    if (!ok) return;
    if (newPassword != confirmation) {
        QMessageBox::warning(this, "Password mismatch", "The new passwords do not match.");
        return;
    }
    QString error;
    if (!authenticationStore->changePassword(currentUser.username, oldPassword, newPassword, &error)) {
        QMessageBox::warning(this, "Password not changed", error);
        return;
    }
    QMessageBox::information(this, "Password changed", "Your password has been updated.");
}

void MainWindow::onManageAccounts() {
    if (activeRoleIndex != AdministratorRole || !authenticationStore) return;
    QMessageBox accountList(QMessageBox::Information, "University accounts",
        authenticationStore->accountSummaries().join('\n'), QMessageBox::Close, this);
    QPushButton *createAccount = accountList.addButton("Create account", QMessageBox::ActionRole);
    accountList.exec();
    if (accountList.clickedButton() != createAccount) return;
    QDialog dialog(this);
    dialog.setWindowTitle("Create account");
    dialog.setMinimumWidth(440);
    dialog.setStyleSheet(R"(
        QDialog { background: #f5f7fb; }
        QLabel { color: #303744; }
        QLineEdit, QComboBox { color: #202632; background: #ffffff; border: 1px solid #b9c2ce; border-radius: 5px; padding: 6px 9px; }
        QPushButton { color: #253246; background: #ffffff; border: 1px solid #aeb8c5; border-radius: 5px; padding: 7px 14px; min-width: 94px; min-height: 34px; font-weight: 600; }
        QPushButton:hover { background: #eaf1f8; border-color: #245f98; }
        QPushButton:default { color: #ffffff; background: #245f98; border-color: #245f98; }
    )");
    auto *layout = new QVBoxLayout(&dialog);
    layout->setContentsMargins(24, 22, 24, 20);
    layout->setSpacing(14);
    auto *form = new QFormLayout();
    form->setSpacing(10);
    auto *username = new QLineEdit();
    auto *fullName = new QLineEdit();
    auto *role = new QComboBox();
    role->addItem("Student", "student");
    role->addItem("Lecturer", "lecturer");
    role->addItem("Administrator", "administrator");
    role->addItem("Registrar", "registrar");
    role->addItem("Residence staff", "residence");
    role->addItem("Sports coordinator", "sports");
    auto *linkedId = new QLineEdit();
    linkedId->setPlaceholderText("Student ID or employee ID");
    auto *password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    auto *confirmation = new QLineEdit();
    confirmation->setEchoMode(QLineEdit::Password);
    for (QLineEdit *field : {username, fullName, linkedId, password, confirmation}) field->setMinimumHeight(34);
    form->addRow("Username", username);
    form->addRow("Full name", fullName);
    form->addRow("Role", role);
    form->addRow("Linked record", linkedId);
    form->addRow("Password", password);
    form->addRow("Confirm password", confirmation);
    QWidget *linkedIdLabel = form->labelForField(linkedId);
    auto updateLinkedField = [role, linkedId, linkedIdLabel] {
        const QString code = role->currentData().toString();
        const bool required = code == "student" || code == "lecturer";
        linkedId->setVisible(required);
        if (linkedIdLabel) linkedIdLabel->setVisible(required);
    };
    connect(role, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog, updateLinkedField);
    updateLinkedField();
    layout->addLayout(form);
    auto *status = new QLabel();
    status->setWordWrap(true);
    status->setStyleSheet("color: #b42318;");
    layout->addWidget(status);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    buttons->button(QDialogButtonBox::Save)->setText("Create account");
    buttons->button(QDialogButtonBox::Save)->setDefault(true);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [this, &dialog, username, fullName, role, linkedId, password, confirmation, status] {
        const QString roleCode = role->currentData().toString();
        const QString universityId = linkedId->text().trimmed();
        if (password->text() != confirmation->text()) {
            status->setText("The passwords do not match.");
            return;
        }
        if ((roleCode == "student" || roleCode == "lecturer") && universityId.isEmpty()) {
            status->setText("Enter the student ID or employee ID to link this account.");
            return;
        }
        bool recordExists = true;
        if (roleCode == "student") recordExists = admin->searchStudent(universityId.toStdString()) != nullptr;
        if (roleCode == "lecturer") {
            recordExists = false;
            for (auto *member : admin->getFacultyList())
                if (QString::fromStdString(member->getEmployeeId()) == universityId) recordExists = true;
        }
        if (!recordExists) {
            status->setText(roleCode == "student" ? "Register the student before creating this account."
                                                   : "Add the lecturer before creating this account.");
            return;
        }
        QString error;
        if (!authenticationStore->createAccount(username->text(), password->text(), fullName->text(),
                                                 roleCode, universityId, &error)) {
            status->setText(error);
            return;
        }
        dialog.accept();
    });
    layout->addWidget(buttons);
    username->setFocus();
    dialog.exec();
}

void MainWindow::onBackToMenu() {
    if (!authenticateSession()) qApp->quit();
}

void MainWindow::onExit() {
    qApp->quit();
}
