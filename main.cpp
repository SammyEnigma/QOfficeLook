#include <QApplication>

#include "qofficelooktest.h"
#include "qofficelook.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("QtProject");
    app.setApplicationName("Application Example");
    QOfficeLookTest mainWin;
    mainWin.setWindowTitle("Test Applicatie");
    mainWin.setWindowIcon(QIcon(":/icons/application.svg"));
    QOfficeLook *look = QOfficeLook::adaptMainWindow(&app, &mainWin);
    look->addRightAction(QIcon(":/icons/help.svg"), &mainWin, SLOT(slot_restore()));
    mainWin.show();
    int exitcode = app.exec();
    delete look;
    return exitcode;
}

