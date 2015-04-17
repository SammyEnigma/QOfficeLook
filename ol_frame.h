#ifndef OL_FRAME_H
#define OL_FRAME_H

#include <QApplication>
#include <QFrame>
#include <QMainWindow>

class OL_WindowTitleBar;

class OL_Frame : public QFrame
{
    Q_OBJECT

private:
    QMainWindow *_parent;
    OL_WindowTitleBar *_titleBar;
    QApplication *_app;
    QCursor _prevCursor;
    bool _inWindow;
    bool _pressed;
    int _in_border;
    int _left, _top, _bottom, _right;

    QPoint _position;
    QSize _size;
    QPoint _origin;

public:
    OL_Frame(QApplication *_app, QMainWindow *parent = 0, OL_WindowTitleBar *bar = 0);
    ~OL_Frame();

protected:
    bool event(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);
    void filterMove(QEvent *e);
};

#endif // OL_FRAME_H
