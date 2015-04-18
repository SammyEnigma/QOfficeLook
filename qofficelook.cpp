#include "qofficelook.h"
#include "ol_windowtitlebar.h"
#include "ol_frame.h"

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>


QOfficeLook::QOfficeLook()
{
}

QOfficeLook *QOfficeLook::adaptMainWindow(QApplication *app, QMainWindow *w)
{
    QWidget *mainwin = w->centralWidget();

    OL_WindowTitleBar *tb = new OL_WindowTitleBar(app, w, w);
    QString t = w->windowTitle();
    tb->setTitle(t);

    QWidget *frame = new OL_Frame(app, w, tb);
    QVBoxLayout *flayout = (QVBoxLayout *) frame->layout();

    QWidget *central = new QWidget(frame);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    central->setLayout(layout);

    layout->addWidget(tb);
    if (!mainwin) {
        mainwin = new QWidget(central);
    } else {
        mainwin->setParent(central);
    }
    layout->addWidget(mainwin, 1);

    flayout->addWidget(central);

    w->setCentralWidget(frame);
    w->setWindowFlags(Qt::FramelessWindowHint);

    QOfficeLook *officeLook = new QOfficeLook();
    officeLook->_mainWin = w;
    officeLook->_titleBar = tb;

    return officeLook;
}

QMainWindow *QOfficeLook::mainWindow()
{
    return _mainWin;
}

void QOfficeLook::addAction(QIcon &icon, const QObject *receiver, const char *slot, const QString &tooltip, const QKeySequence &shortcut)
{
    ((OL_WindowTitleBar *) _titleBar)->addAction(icon,receiver,slot,tooltip,shortcut);
}

void QOfficeLook::addRightAction(QIcon &icon, const QObject *receiver, const char *slot, const QString &tooltip, const QKeySequence &shortcut)
{
    ((OL_WindowTitleBar *) _titleBar)->addRightAction(icon,receiver,slot,tooltip,shortcut);
}


