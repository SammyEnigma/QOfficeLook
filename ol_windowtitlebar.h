#ifndef OL_WINDOWTITLEBAR_H
#define OL_WINDOWTITLEBAR_H

#include "ol_flatbutton.h"

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSizeGrip>
#include <QApplication>

class OL_WindowTitleBar : public QWidget
{
    Q_OBJECT

private:
    QLabel *_title;
    QMenu  *_smenu;
    OL_FlatButton *_systemMenu, *_close, *_minimize, *_maximize, *_restore;
    QApplication * _app;
    QMainWindow *_mainWin;
    QPoint _origin;
    QWidget*_leftActions, *_rightActions;
    void *_filter;

public:
    void adjustMenuAndButtons();
    QApplication *application();
    void activateSysMenu();

public:
    void setTitle(const QString &t);
    void toggleSize();

public:
    void addAction(QIcon &icon, const QObject *receiver, const char *slot = 0, const QString &tooltip = 0, const QKeySequence & shortcut = 0);
    void addRightAction(QIcon &icon, const QObject *receiver = 0, const char *slot = 0, const QString &tooltip = 0, const QKeySequence & shortcut = 0);

public:
    explicit OL_WindowTitleBar(QApplication *a, QMainWindow *w, QWidget *parent = 0);
    ~OL_WindowTitleBar();

signals:

protected:
    bool event(QEvent *e);

private slots:
    void slot_close();
    void slot_restore();
    void slot_minimize();
    void slot_maximize();
    void slot_size();
    void slot_move();
};

#endif // OL_WINDOWTITLEBAR_H
