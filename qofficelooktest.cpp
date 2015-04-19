#include "qofficelooktest.h"

#include <qribbonsection.h>
#include <qribbon.h>
#include <QScrollArea>

#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <stdio.h>

#include <QPlainTextEdit>


QOfficeLookTest::QOfficeLookTest(QWidget *parent) : QMainWindow(parent)
{
    // main widget
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    // editing content etc.
    QPlainTextEdit *textEdit = new QPlainTextEdit(widget);
    textEdit->insertPlainText("Hallo allemaal!\n\nDit is een tekst!");
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //textEdit->addScrollBarWidget(new QPushButton("Hi", widget), Qt::AlignTop);
    //textEdit->addScrollBarWidget(new QLabel("HI!", widget), Qt::AlignTop);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    /*QWidget *left_tab = new QWidget(widget);
    textEdit->setViewportMargins(100,0,0,0);
    QVBoxLayout *v = new QVBoxLayout();
    left_tab->setLayout(v);
    v->addWidget(new QLabel("Hi!"));
    v->addWidget(new QPushButton("JO!"));*/



    QRibbon *ribbon = createRibbon(this);

    layout->addWidget(ribbon);
    layout->addWidget(textEdit);
    widget->setLayout(layout);
    setCentralWidget(widget);
}

QOfficeLookTest::~QOfficeLookTest()
{

}

void QOfficeLookTest::indexChanged(int tab) {
    printf("current tab = %d\n", tab);
    fflush(stdout);
}

void QOfficeLookTest::slot_restore()
{
    if (QMainWindow::windowState() == Qt::WindowNoState) {
        QMainWindow::setWindowState(Qt::WindowMaximized);
    } else {
        QMainWindow::setWindowState(Qt::WindowNoState);
    }
}

void QOfficeLookTest::action() {
    QAction *a = (QAction *) sender();
    printf("action = %p\n",a);
    if (a->objectName() == "bb") {
        printf("JE!\n");
        QApplication::quit();
    }
    fflush(stdout);
}


QRibbon *QOfficeLookTest::createRibbon(QWidget *parent)
{
    QPushButton *b1 = new QPushButton("Hi!", parent);
    b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *b2 = new QPushButton("Hallo", parent);
    connect(b1, SIGNAL(clicked()), parent, SLOT(action()));
    connect(b2, SIGNAL(clicked()), parent, SLOT(action()));

    QRibbon *ribbon = new QRibbon(parent);
    QWidget* tab = ribbon->addRibbonTab("Start", "start");

    QRibbonSection *one = new QRibbonSection(tab, "Section One", "one");
    one->addWidget(b1, "b1");
    one->addWidget(b2, "b2");

    one->nextRow();
    QAction *a1 = new QAction(QIcon(":/icons/test.svg"), "&Test", one);
    one->addAction(a1, "a1");
    connect(a1, SIGNAL(triggered()), parent, SLOT(action()));

    QAction *a2 = new QAction(QIcon(":/icons/test.svg"), "", one);
    one->addLargeAction(a2, "a2");
    connect(a2, SIGNAL(triggered()), parent, SLOT(action()));

    QRibbonSection *two = new QRibbonSection(tab, "Section two", "two");
    QAction *aa = new QAction(QIcon(":/icons/test.svg"), "", two);
    aa->setObjectName("aa");
    connect(aa, SIGNAL(triggered()), parent, SLOT(action()));
    two->addLargeAction(aa, "aa");
    QAction *bb = new QAction(QIcon(":/icons/RibbonPoint.svg"), "", two);
    bb->setObjectName("bb");
    connect(bb, SIGNAL(triggered()), parent, SLOT(action()));
    two->addLargeAction(bb, "bb");
    QAction *det = new QAction(two);
    two->setDetailsAction(det);

    ribbon->addSection("start", one);
    ribbon->addSection("start", two);

    QWidget *tab2 = new QWidget();
    ribbon->addTab(tab2, "Tab 2", "tab2");
    QRibbonSection *three = new QRibbonSection(tab2, "Section 3", "three");
    QAction *a3 = new QAction(QIcon(":/icons/QRibbonDetails.svg"), "", three);
    connect(a3, SIGNAL(triggered()), parent, SLOT(action()));
    QComboBox *cbox = new QComboBox();
    cbox->addItem("hi");
    cbox->addItem("hoi");
    cbox->addItem("jae");
    three->addWidget(cbox, "cbox", 2);
    QAction *a4 = new QAction(QIcon(":/icons/test.svg"), "", three);
    connect(a4, SIGNAL(triggered()), parent, SLOT(action()));
    three->nextRow();
    three->addAction(a4, "a4");
    three->addWidget(new QLabel("HI"), "");
    three->addLargeAction(a3, "a3");


    ribbon->addSection("tab2", three);
    connect(ribbon,SIGNAL(currentIndexChanged(int)),parent,SLOT(indexChanged(int)));

    return ribbon;
}
