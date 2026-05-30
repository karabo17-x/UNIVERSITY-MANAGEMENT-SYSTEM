#include <QApplication>
#include "MainWindow.h"
#include <QTimer>
#include "StudentRegistrationDialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    // If OPEN_REG_DIALOG is set, open the Register dialog immediately for debugging
    if (qEnvironmentVariableIsSet("OPEN_REG_DIALOG")) {
        QTimer::singleShot(0, [&window]() {
            StudentRegistrationDialog dlg(nullptr, &window);
            dlg.exec();
        });
    }
    
    return app.exec();
}
