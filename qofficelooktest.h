#ifndef QOFFICELOOKTEST_H
#define QOFFICELOOKTEST_H

#include <QMainWindow>
#include <qribbon.h>

class QOfficeLookTest : public QMainWindow
{
    Q_OBJECT

private:
    QRibbon *createRibbon(QWidget *parent);
public:
    explicit QOfficeLookTest(QWidget *parent = 0);
    ~QOfficeLookTest();

signals:

public slots:
    void action();
    void indexChanged(int tab);
    void slot_restore();
};

#endif // QOFFICELOOKTEST_H
