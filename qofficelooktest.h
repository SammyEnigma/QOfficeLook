#ifndef QOFFICELOOKTEST_H
#define QOFFICELOOKTEST_H

#include <QMainWindow>

class QOfficeLookTest : public QMainWindow
{
    Q_OBJECT
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
