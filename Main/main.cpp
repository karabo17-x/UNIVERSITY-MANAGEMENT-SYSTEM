#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("University Management System");
    QCoreApplication::setApplicationName("UniversityManagementSystem");
    
    MainWindow window;
    if (!window.authenticateSession()) return 0;
    window.show();
    return app.exec();
}
