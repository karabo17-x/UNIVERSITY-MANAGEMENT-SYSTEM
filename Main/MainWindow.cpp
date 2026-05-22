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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), admin(nullptr), academicAdmin(nullptr), 
      hostelA(nullptr), sportsAffiliation(nullptr) {
    
    setWindowTitle("University Management System");
    setWindowIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    setGeometry(100, 100, 1000, 700);
    
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
    
    // Show welcome screen first
    stackedWidget->setCurrentWidget(welcomeWidget);
}

MainWindow::~MainWindow() {
    // Cleanup
    for (auto dept : departments) {
        delete dept;
    }
    for (auto student : students) {
        delete student;
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
    
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(245, 245, 250));
    darkPalette.setColor(QPalette::WindowText, QColor(0, 0, 0));
    darkPalette.setColor(QPalette::Base, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::AlternateBase, QColor(240, 240, 245));
    darkPalette.setColor(QPalette::Button, QColor(220, 220, 230));
    darkPalette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    darkPalette.setColor(QPalette::Highlight, QColor(26, 84, 144));
    darkPalette.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
    
    qApp->setPalette(darkPalette);
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
          QString::number(students.size()),
          QString::number(faculty.size()));
    
    QMessageBox::information(this, "System Information", info);
}

void MainWindow::onBackToMenu() {
    stackedWidget->setCurrentWidget(welcomeWidget);
}

void MainWindow::onExit() {
    qApp->quit();
}
