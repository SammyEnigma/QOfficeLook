#ifndef QOFFICELOOK_H
#define QOFFICELOOK_H

#include "qofficelook_global.h"

#include <QObject>
#include <QMainWindow>
#include <QSizeGrip>
#include <QFrame>
#include <QApplication>

class QOFFICELOOKSHARED_EXPORT QOfficeLook : public QObject
{
    Q_OBJECT

private:
    QWidget *_titleBar;
    QMainWindow *_mainWin;

public:
    static QOfficeLook *adaptMainWindow(QApplication *app, QMainWindow *w);

public:
    QMainWindow *mainWindow();

public:
    void addAction(QIcon &icon, const QObject *receiver, const char *slot = 0, const QString &tooltip = 0, const QKeySequence & shortcut = 0);
    void addRightAction(QIcon &icon, const QObject *receiver = 0, const char *slot = 0, const QString &tooltip = 0, const QKeySequence & shortcut = 0);

public:
    QOfficeLook();
};

#endif // QOFFICELOOK_H
