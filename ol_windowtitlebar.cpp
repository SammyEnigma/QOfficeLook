#include "ol_windowtitlebar.h"
#include <QAbstractNativeEventFilter>
#include <QEvent>
#include <QGridLayout>
#include <QMouseEvent>
#include <QShortcut>

#define WM_SYSCOMMAND 0x0112
#define WM_SYSKEYUP   0x0105


struct tagMSG {
    void *hwnd;
    long message;
};

class Filter : public QAbstractNativeEventFilter {
private:
    OL_WindowTitleBar *_bar;

public:
    Filter(OL_WindowTitleBar *bar)
    {
        _bar = bar;
        _bar->application()->installNativeEventFilter(this);
    }

    bool nativeEventFilter(const QByteArray & eventType, void * message, long * result)
    {
#ifdef Q_OS_WIN
        if (eventType == "windows_generic_MSG") {
           MSG *msg = (MSG *) message;
           if (msg->message == WM_SYSKEYUP) {
              _bar->activateSysMenu();
              return true;
           }
        }
#endif
        return false;
    }
};


OL_WindowTitleBar::OL_WindowTitleBar(QApplication * a, QMainWindow * w, QWidget *parent) : QWidget(parent)
{
    _app = a;
    _mainWin = w;

    _filter = (void *) new Filter(this);
    _app->installNativeEventFilter((Filter *) _filter);

    _title = new QLabel("<title>", this);
    _title->setAlignment(Qt::AlignCenter);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, this->palette().color(QPalette::Window));
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    _systemMenu = new OL_FlatButton(w->windowIcon(), parent);

    /*QShortcut *sm = new QShortcut(QKeySequence(Qt::Key_Space), _systemMenu);
    sm->setContext(Qt::ApplicationShortcut);
    connect(sm, SIGNAL(activated()), _systemMenu, SLOT(showMenu()));*/


    _smenu = new QMenu(w);
    _smenu->addAction(QIcon(":/icons/restore.svg"), tr("&Restore"), this, SLOT(slot_restore()));
    _smenu->addAction(tr("&Move"), this, SLOT(slot_move()));
    _smenu->addAction(tr("Size"), this, SLOT(slot_size()));
    _smenu->addAction(QIcon(":/icons/minimize.svg"), tr("Minimize"), this, SLOT(slot_minimize()));
    _smenu->addAction(QIcon(":/icons/maximize.svg"), tr("Maximize"), this, SLOT(slot_maximize()));
    _smenu->addSeparator();
    _smenu->addAction(QIcon(":/icons/close.svg"), tr("&Close"), this, SLOT(slot_close()), QKeySequence::Quit);
    _systemMenu->setMenu(_smenu);
    _systemMenu->addStyleSheet("::menu-indicator { image: url(none.jpg); }");
    _systemMenu->addStyleSheet(":hover { background: none;border: none; }");

    _close = new OL_FlatButton(QIcon(":/icons/close.svg"),  parent);
    connect(_close, SIGNAL(clicked()), this, SLOT(slot_close()));

    _restore = new OL_FlatButton(QIcon(":/icons/restore.svg"), parent);
    connect(_restore, SIGNAL(clicked()), this, SLOT(slot_restore()));

    _minimize = new OL_FlatButton(QIcon(":/icons/minimize.svg"), parent);
    connect(_minimize, SIGNAL(clicked()), this, SLOT(slot_minimize()));

    _maximize = new OL_FlatButton(QIcon(":/icons/maximize.svg"), parent);
    connect(_maximize, SIGNAL(clicked()), this, SLOT(slot_maximize()));


    QGridLayout *layout = new QGridLayout();
    this->setLayout(layout);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(1);

    _leftActions = new QWidget();
    QHBoxLayout *la_layout = new QHBoxLayout();
    la_layout->setContentsMargins(0,0,0,0);
    _leftActions->setLayout(la_layout);

    _rightActions = new QWidget();
    QHBoxLayout *ra_layout = new QHBoxLayout();
    ra_layout->setContentsMargins(0,0,0,0);
    _rightActions->setLayout(ra_layout);


    layout->addWidget(_systemMenu, 0, 0, 1, 1);
    layout->addWidget(_leftActions, 0, 1, 1, 1);
    layout->addWidget(_title, 0, 2, 1, 1, Qt::AlignCenter);
    layout->addWidget(_rightActions, 0, 3, 1, 1);
    layout->addWidget(_minimize, 0, 4, 1, 1);
    layout->addWidget(_restore, 0, 5, 1, 1);
    //layout->addWidget(_maximize,0,4,1,1);
    layout->addWidget(_close, 0, 6, 1, 1);
    layout->setColumnStretch(2, 1);

    this->adjustMenuAndButtons();
}

bool OL_WindowTitleBar::event(QEvent *e)
{
    if (e->type() == QEvent::MouseButtonDblClick) {
        this->toggleSize();
    } else if (e->type() == QEvent::MouseButtonPress) {
        _origin = ((QMouseEvent *) e)->pos();
    } else if (e->type() == QEvent::MouseMove) {
        QPoint p = ((QMouseEvent *) e)->globalPos();
        if (!_mainWin->isMaximized()) {
            _mainWin->move(p - _origin);
        }
    }
    return QWidget::event(e);
}

void OL_WindowTitleBar::toggleSize()
{
    if (_mainWin->windowState() == Qt::WindowNoState) {
        _mainWin->setWindowState(Qt::WindowMaximized);
    } else {
        _mainWin->setWindowState(Qt::WindowNoState);
    }
}

void OL_WindowTitleBar::addAction(const QIcon icon, const QObject *receiver, const char *slot, const QString &tooltip, const QKeySequence &shortcut)
{
    QPushButton *btn = new OL_FlatButton(icon, _leftActions);
    btn->setIcon(icon);
    btn->setShortcut(shortcut);
    btn->setToolTip(tooltip);
    connect(btn, SIGNAL(clicked()), receiver, slot);
    QLayout *l = _leftActions->layout();
    l->addWidget(btn);
}

void OL_WindowTitleBar::addLeftAction(const QIcon icon, const QObject *receiver, const char *slot, const QString &tooltip, const QKeySequence &shortcut)
{
    addAction(icon, receiver, slot, tooltip, shortcut);
}

void OL_WindowTitleBar::addRightAction(const QIcon icon, const QObject *receiver, const char *slot, const QString &tooltip, const QKeySequence &shortcut)
{
    QPushButton *btn = new OL_FlatButton(icon, _rightActions);
    btn->setIcon(icon);
    btn->setShortcut(shortcut);
    btn->setToolTip(tooltip);
    connect(btn, SIGNAL(clicked()), receiver, slot);
    QLayout *l = _rightActions->layout();
    l->addWidget(btn);
}

OL_WindowTitleBar::~OL_WindowTitleBar()
{
    Filter *f = (Filter *) _filter;
    delete f;
}

void OL_WindowTitleBar::slot_close()
{
    _mainWin->close();
}

void OL_WindowTitleBar::slot_restore()
{
    _mainWin->setWindowState(Qt::WindowNoState);
}

void OL_WindowTitleBar::slot_maximize()
{
    _mainWin->setWindowState(Qt::WindowMaximized);
}

void OL_WindowTitleBar::slot_minimize()
{
    _mainWin->setWindowState(Qt::WindowMinimized);
}

void OL_WindowTitleBar::slot_size()
{

}

void OL_WindowTitleBar::slot_move()
{

    QPoint p = _mainWin->pos();
    QSize  s = this->size();
    int midx = s.width() / 2  + p.x();
    int midy = s.height() / 2 + p.y();
    this->cursor().setPos(QPoint(midx, midy));
}

void OL_WindowTitleBar::adjustMenuAndButtons()
{
    int state = _mainWin->windowState();
    bool restore = state != Qt::WindowNoState;
    bool maximize = state != Qt::WindowMaximized;
    bool minimize = state != Qt::WindowMinimized;

    _smenu->actions().at(0)->setEnabled(restore);  // restore
    _smenu->actions().at(1)->setEnabled(maximize); // move
    _smenu->actions().at(2)->setEnabled(maximize); // size
    _smenu->actions().at(3)->setEnabled(minimize); // minimize
    _smenu->actions().at(4)->setEnabled(maximize); // maximize

    QGridLayout *layout = (QGridLayout *) this->layout();
    if (restore) {
        layout->removeWidget(_maximize);
        layout->addWidget(_restore, 0, 5, 1, 1);
        _restore->setVisible(true);
        _maximize->setVisible(false);
    }
    if (maximize) {
        layout->removeWidget(_restore);
        layout->addWidget(_maximize, 0, 5, 1, 1);
        _maximize->setVisible(true);
        _restore->setVisible(false);
    }
}

QApplication *OL_WindowTitleBar::application()
{
    return _app;
}

void OL_WindowTitleBar::activateSysMenu()
{
    _systemMenu->showMenu();
}

void OL_WindowTitleBar::setTitle(const QString &t)
{
    _title->setText(t);
}
