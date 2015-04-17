#include "ol_frame.h"
#include "ol_windowtitlebar.h"

#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QVBoxLayout>

static void setShadow(OL_Frame *f);
static void setNoShadow(OL_Frame *f);

OL_Frame::OL_Frame(QApplication *app, QMainWindow *parent, OL_WindowTitleBar *bar) : QFrame(parent)
{
    _app = app;
    _titleBar = bar;
    app->installEventFilter(this);
    this->setFrameStyle(QFrame::StyledPanel);
    this->setObjectName("OL_Frame");
    //this->setFrameShadow(QFrame::Raised);
    setShadow(this);

    _parent = parent;
    _inWindow = false;
    _pressed = false;
    _in_border = 0;
    QVBoxLayout *vbox = new QVBoxLayout();
    this->setLayout(vbox);
    vbox->setContentsMargins(5,5,5,5);
    vbox->getContentsMargins(&_left, &_top, &_right, &_bottom);
    vbox->setContentsMargins(0,0,0,0);
}

OL_Frame::~OL_Frame()
{

}

void setShadow(OL_Frame *f) {
    f->setStyleSheet("#OL_Frame {"
                        "border: 4px solid black;"
                        "border-left-color:  qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 rgba(80,80,80,0), stop: 0.66 rgba(80,80,80,50), stop: 1 rgba(80,80,80,255));"
                        "border-right-color:  qlineargradient(x1: 1, y1: 0, x2: 0, y2: 0, stop: 0 rgba(80,80,80,0),stop: 0.33 rgba(80,80,80,50), stop: 1 rgba(80,80,80,255));"
                        "border-top-color:  qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(80,80,80,0), stop: 0.66 rgba(80,80,80,50),stop: 1 rgba(80,80,80,255));"
                        "border-bottom-color:  qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0, stop: 0 rgba(80,80,80,0), stop: 0.33 rgba(80,80,80,50),stop: 1 rgba(80,80,80,255));"
                    "}");
}

void setNoShadow(OL_Frame *f) {
    f->setStyleSheet("#OL_Frame {"
                        "border: 0px solid black;"
                    "}");
}

bool OL_Frame::event(QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress) {
        _origin = ((QMouseEvent *) e)->globalPos();
        _size = _parent->size();
        _position = _parent->pos();
        _pressed = true;
    } else if (e->type() == QEvent::MouseButtonRelease) {
        _pressed = false;
    } else if (e->type() == QEvent::MouseMove) {
        filterMove(e);
    }

    return QFrame::event(e);
}

bool OL_Frame::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        if (obj) {
            this->filterMove(event);
        }
    } else if (event->type() == QEvent::WindowStateChange) {
        if (obj == _parent) {
            if (_parent->isMaximized()) {
                setNoShadow(this);
            } else {
                setShadow(this);
            }
            _titleBar->adjustMenuAndButtons();
        }
    }
    return QFrame::eventFilter(obj, event);
}

void OL_Frame::filterMove(QEvent *e)
{
    if (_parent->isMaximized()) {
        return;
    }

    // determine in-border situation
    QPoint p = ((QMouseEvent *) e)->globalPos();
    QPoint top = _parent->pos();
    QSize size = _parent->size();

    if (!_pressed) {
        bool left = false, right = false, up = false, bottom = false;
        _in_border = 0;

        if (p.x() >= (top.x() + size.width() - _bottom)) {
            _in_border = 2;
            right = true;
        }

        if (p.x() <= (top.x() + _top)) {
            _in_border = 1;
            left = true;
        }

        if (p.y() <= (top.y() + _left)) {
            _in_border = 3;
            up = true;
        }

        if (p.y() >= (top.y() + size.height() - _right)) {
            _in_border = 4;
            bottom = true;
        }

        if (left && up) {
            _in_border = 5;
        } else if (right && up) {
            _in_border = 6;
        } else if (left && bottom) {
            _in_border = 7;
        } else if (right && bottom) {
            _in_border = 8;
        }

        if (_in_border) {
            Qt::CursorShape s;
            switch (_in_border) {
                case 1:
                case 2: s = Qt::SizeHorCursor;
                break;
                case 3:
                case 4: s = Qt::SizeVerCursor;
                break;
                case 5:
                case 8: s = Qt::SizeFDiagCursor;
                break;
                case 6:
                case 7: s = Qt::SizeBDiagCursor;
                break;
            }
            _app->setOverrideCursor(s);
        } else {
            _app->restoreOverrideCursor();
        }
    }

    if (_pressed) {
        bool left = false , right = false , up = false, bottom = false;
        switch (_in_border) {
            case 1: left = true;
            break;
            case 2: right = true;
            break;
            case 3: up = true;
            break;
            case 4: bottom = true;
            break;
            case 5: left = true; up = true;
            break;
            case 6: right = true; up = true;
            break;
            case 7: left = true; bottom = true;
            break;
            case 8: right = true; bottom = true;
        }

        int xdiff = p.x() - _origin.x();
        int ydiff = p.y() - _origin.y();
        QSize s = _size;
        QPoint p = _position;
        QRect newGeom;
        bool do_it_hor = false, do_it_ver = false;

        if (left) {
            s.setWidth(s.width() - xdiff);
            if (xdiff < 0) {
                p.setX(p.x() + xdiff);
                do_it_hor = true;
            } else {
                QSize min = _parent->minimumSize();
                if (s.width() > min.width()) {
                    p.setX(p.x() + xdiff);
                    do_it_hor = true;
                }
            }
            newGeom = QRect(p, s);
        }

        if (right) {
            s.setWidth(s.width() + xdiff);
            QSize min = _parent->minimumSize();
            if (s.width() > min.width()) {
                do_it_hor = true;
                newGeom = QRect(p, s);
            }
        }

        if (up) {
            s.setHeight(s.height() - ydiff);
            if (ydiff < 0) {
                do_it_ver = true;
                p.setY(p.y() + ydiff);
            } else {
                QSize min = _parent->minimumSize();
                if (s.height() > min.height()) {
                    do_it_ver = true;
                    p.setY(p.y() + ydiff);
                }
            }
            newGeom = QRect(p, s);
        }

        if (bottom) {
            s.setHeight(s.height() + ydiff);
            QSize min = _parent->minimumSize();
            if (s.width() > min.width()) {
                newGeom = QRect(p, s);
                do_it_ver = true;
            }
        }

        if (do_it_hor || do_it_ver) {
            _parent->setGeometry(newGeom);
        }
    }

}
