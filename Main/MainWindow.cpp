#include "MainWindow.h"
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
#include <QDate>
#include <QFrame>
#include <QTabWidget>
#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), admin(nullptr), academicAdmin(nullptr), 
      hostelA(nullptr), sportsAffiliation(nullptr) {
    
    setWindowTitle("University Management System");
    setWindowIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    setGeometry(80, 60, 1240, 820);
    setMinimumSize(980, 680);
    
    // Initialize business logic
    initializeSystemData();
    
    // Create stacked widget for screen transitions
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    // Setup screens
    setupWelcomeScreen();
    setupMainMenu();
    
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
}

void MainWindow::setupWelcomeScreen() {
    welcomeWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(welcomeWidget);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(20);
    
    // Title
    QLabel *mainTitle = new QLabel("Welcome to University Management System");
    mainTitle->setStyleSheet("font-size: 32px; font-weight: bold; color: #1a5490;");
    mainTitle->setAlignment(Qt::AlignCenter);
    
    // Subtitle
    QLabel *subtitle = new QLabel("Professional Management Solution for Higher Education");
    subtitle->setStyleSheet("font-size: 16px; color: #555555;");
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
    description->setStyleSheet("font-size: 13px; color: #333333; line-height: 1.6;");
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
}

void MainWindow::setupMainMenu() {
    menuWidget = new QWidget();
    menuWidget->setObjectName("portalRoot");

    auto *rootLayout = new QHBoxLayout(menuWidget);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    auto *sidebar = new QFrame();
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(230);
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
        connect(button, &QPushButton::clicked, this, action);
        sidebarLayout->addWidget(button);
    };

    addNavigation("Dashboard", [] {}, true);
    addNavigation("Registration", [this] { onRegisterStudent(); });
    addNavigation("Student Directory", [this] { onViewStudents(); });
    addNavigation("Academics", [this] { onAssignMarks(); });
    addNavigation("My Residences", [this] { onViewResidenceOccupancy(); });
    addNavigation("Campus Sports", [this] { onViewSports(); });
    addNavigation("My Exams", [this] { onViewExamSchedule(); });
    addNavigation("My Profile", [this] { onViewSystemInfo(); });
    sidebarLayout->addStretch();
    addNavigation("Sign out", [this] { onBackToMenu(); });

    auto *content = new QWidget();
    content->setObjectName("portalContent");
    auto *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(30, 24, 30, 28);
    contentLayout->setSpacing(16);

    auto *utilityRow = new QHBoxLayout();
    auto *portalLabel = new QLabel("Student portal");
    portalLabel->setObjectName("portalLabel");
    auto *helpButton = new QPushButton("?");
    helpButton->setObjectName("utilityButton");
    helpButton->setToolTip("Help and support");
    auto *profileButton = new QPushButton("KM");
    profileButton->setObjectName("utilityButton");
    profileButton->setToolTip("My profile");
    utilityRow->addWidget(portalLabel);
    utilityRow->addStretch();
    utilityRow->addWidget(helpButton);
    utilityRow->addWidget(profileButton);
    contentLayout->addLayout(utilityRow);

    auto *heading = new QLabel("Dashboard");
    heading->setObjectName("dashboardHeading");
    contentLayout->addWidget(heading);
    auto *accent = new QFrame();
    accent->setObjectName("headingAccent");
    accent->setFixedSize(180, 4);
    contentLayout->addWidget(accent);
    auto *subtitle = new QLabel("Welcome back. Here is your university overview.");
    subtitle->setObjectName("dashboardSubtitle");
    contentLayout->addWidget(subtitle);
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

    auto *dashboardGrid = new QGridLayout();
    dashboardGrid->setHorizontalSpacing(18);
    dashboardGrid->setVerticalSpacing(18);

    auto *calendarCard = createCard("Calendar");
    auto *calendarLayout = qobject_cast<QVBoxLayout *>(calendarCard->layout());
    auto *calendarHeader = new QHBoxLayout();
    auto *dateLabel = new QLabel(QDate::currentDate().toString("dddd, d MMMM yyyy"));
    dateLabel->setObjectName("calendarDate");
    auto *viewAll = new QPushButton("View all");
    viewAll->setObjectName("linkButton");
    connect(viewAll, &QPushButton::clicked, this, &MainWindow::onViewExamSchedule);
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

    auto *updatesCard = createCard("Updates");
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

    auto *actionsCard = createCard("Quick actions");
    auto *actionsLayout = qobject_cast<QVBoxLayout *>(actionsCard->layout());
    auto *actionGrid = new QGridLayout();
    actionGrid->setSpacing(10);
    const std::vector<std::pair<QString, std::function<void()>>> actions = {
        {"Register student", [this] { onRegisterStudent(); }},
        {"View students", [this] { onViewStudents(); }},
        {"Assign marks", [this] { onAssignMarks(); }},
        {"View residence", [this] { onViewResidenceOccupancy(); }}
    };
    for (int i = 0; i < static_cast<int>(actions.size()); ++i) {
        auto *button = new QPushButton(actions[i].first);
        button->setObjectName("quickAction");
        button->setMinimumHeight(42);
        connect(button, &QPushButton::clicked, this, actions[i].second);
        actionGrid->addWidget(button, i / 2, i % 2);
    }
    actionsLayout->addLayout(actionGrid);
    dashboardGrid->addWidget(actionsCard, 1, 1);

    dashboardGrid->setColumnStretch(0, 6);
    dashboardGrid->setColumnStretch(1, 5);
    dashboardGrid->setRowStretch(0, 3);
    dashboardGrid->setRowStretch(1, 1);
    contentLayout->addLayout(dashboardGrid, 1);

    rootLayout->addWidget(sidebar);
    rootLayout->addWidget(content, 1);
    stackedWidget->addWidget(menuWidget);
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
    QMessageBox::information(this, "Add Faculty", "Faculty management features coming soon.");
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
        admin->displayFacultyByDepartment(selectedDept.toStdString());
        QMessageBox::information(this, "Faculty by Department", "Faculty listing displayed in console.");
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
    admin->displayCourseFacultyMapping();
    QMessageBox::information(this, "Course-Faculty Mapping", "Mapping displayed in console.");
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
    
    QString roomNo = QInputDialog::getText(this, "Assign Residence", "Enter room number:", QLineEdit::Normal, "", &ok);
    if (ok && !roomNo.isEmpty()) {
        bool isInt;
        int roomNumber = roomNo.toInt(&isInt);
        if (isInt && roomNumber > 0) {
            hostelA->assignRoom(roomNumber, student);
            QMessageBox::information(this, "Success", "Room assigned successfully.");
        } else {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid room number.");
        }
    }
}

void MainWindow::onViewResidenceOccupancy() {
    QMessageBox::information(this, "Residence Occupancy", "Viewing occupancy status...");
    hostelA->displayRoomOccupancy();
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
    
    QStringList studentIds;
    for (auto student : students) {
        studentIds.append(QString::fromStdString(student->getId()));
    }
    
    QStringList sportIds;
    for (auto sport : sports) {
        sportIds.append(QString::fromStdString(sport->getSportId()));
    }
    
    bool ok;
    QString studentId = QInputDialog::getItem(this, "Affiliate Sport", "Select Student:", studentIds, 0, false, &ok);
    if (!ok || studentId.isEmpty()) return;
    
    QString sportId = QInputDialog::getItem(this, "Affiliate Sport", "Select Sport:", sportIds, 0, false, &ok);
    if (ok && !sportId.isEmpty()) {
        sportsAffiliation->affiliateStudentWithSport(studentId.toStdString(), sportId.toStdString());
        QMessageBox::information(this, "Success", "Student affiliated with sport successfully.");
    }
}

void MainWindow::onViewStudentSports() {
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
        sportsAffiliation->displaySportParticipants(sportId.toStdString());
        QMessageBox::information(this, "Sport Participants", "Participant list displayed in console.");
    }
}

void MainWindow::onRemoveSportAffiliation() {
    auto students = admin->getRegisteredStudents();
    if (students.empty()) {
        QMessageBox::information(this, "Remove Sport", "No students registered.");
        return;
    }
    
    QStringList studentIds;
    for (auto student : students) {
        studentIds.append(QString::fromStdString(student->getId()));
    }
    
    bool ok;
    QString studentId = QInputDialog::getItem(this, "Remove Sport", "Select Student:", studentIds, 0, false, &ok);
    if (!ok || studentId.isEmpty()) return;
    
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
    QMessageBox::information(this, "Initialize Exam Schedule", "Exam schedule initialization feature available.");
}

void MainWindow::onCreateExamSection() {
    QMessageBox::information(this, "Create Exam Section", "Exam section creation feature available.");
}

void MainWindow::onAddExam() {
    QMessageBox::information(this, "Add Exam", "Exam management feature available.");
}

void MainWindow::onEnrollExamSection() {
    QMessageBox::information(this, "Enroll in Exam", "Exam enrollment feature available.");
}

void MainWindow::onViewExamSchedule() {
    QMessageBox::information(this, "Exam Schedule", "Exam schedule viewing feature available.");
}

void MainWindow::onViewExamSectionDetails() {
    QMessageBox::information(this, "Exam Details", "Exam section details feature available.");
}

void MainWindow::onViewSystemInfo() {
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
          QString::number(faculty.size()));
    
    QMessageBox::information(this, "System Information", info);
}

void MainWindow::onBackToMenu() {
    stackedWidget->setCurrentWidget(welcomeWidget);
}

void MainWindow::onExit() {
    qApp->quit();
}
