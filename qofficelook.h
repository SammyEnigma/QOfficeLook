#ifndef QOFFICELOOK_H
#define QOFFICELOOK_H

#include "qofficelook_global.h"

#include <QObject>
#include <QMainWindow>
#include <QSizeGrip>
#include <QFrame>
#include <QApplication>
#include <QStatusBar>

class QOFFICELOOKSHARED_EXPORT QOfficeLook : public QObject
{
    Q_OBJECT

private:
    QWidget *_titleBar;
    QMainWindow *_mainWin;
    QStatusBar *_statusbar;

private:
    QString color, derived_color1, derived_color2;

public:
    static QOfficeLook *adaptMainWindow(QApplication *app, QMainWindow *w);

public:
    QMainWindow *mainWindow();

public:
    void addAction(const QIcon icon, const QObject *receiver, const char *slot = 0, const QString &tooltip = 0, const QKeySequence & shortcut = 0);
    void addRightAction(const QIcon icon, const QObject *receiver = 0, const char *slot = 0, const QString &tooltip = 0, const QKeySequence & shortcut = 0);
public:
    QStatusBar *statusBar();

public:
    QOfficeLook();
};

#endif // QOFFICELOOK_H
