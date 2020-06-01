#include "HackatonASD.h"
#include <QProgressDialog>

HackatonASD::HackatonASD(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    qdwr = new QDockWidget("Table");
    qdwl = new QDockWidget("Operations");
    qdwb = new QDockWidget("Logger");


    Logger::qpte = new QPlainTextEdit();
    Logger::qpte->setReadOnly(true);
    qdwb->setWidget(Logger::qpte);

    qtw = new QTableWidget(this);
    qdwr->setWidget(qtw);
    man = new Manager(qtw);
    qtw->setSortingEnabled(true);

    connect(qtw->horizontalHeader(), SIGNAL(sectionClicked(int)),
        this, SLOT(sort(int)));
    this->setCentralWidget(qdwr);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, qdwl);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, qdwb);
    
    
    loadDataPB = new QPushButton(QString("Load"),this);
    connect(loadDataPB, SIGNAL(released()), this, SLOT(loadData()));

    saveDataPB = new QPushButton(QString("Save"), qdwl);
    connect(saveDataPB, SIGNAL(released()), this, SLOT(saveData()));
    
}

void HackatonASD::loadData() {
    this->man->loadData();
    this->loadDataPB->setVisible(false);
    this->man->populate();
}

void HackatonASD::saveData() {
    this->man->saveData();
}

void HackatonASD::sort(int col) {
    switch (col) {
        case 0:
            Entry::st = SortType::NAME;
            break;
        case 1:
            Entry::st = SortType::PRICE;
            break;
        case 2:
            Entry::st = SortType::STOCK;
            break;
        case 3:
            Entry::st = SortType::EXPIRE;
            break;
        case 4:
            Entry::st = SortType::ADDED;
            break;
    }
    QProgressDialog* qpd = new QProgressDialog();
    qpd->setLabelText(QString("Please wait..."));
    qpd->show();
    this->man->sort();

    qpd->close();

    delete qpd;
}