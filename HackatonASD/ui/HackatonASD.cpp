#include "HackatonASD.h"
#include <QProgressDialog>
#include <QFileDialog>

HackatonASD::HackatonASD(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    init();
}

void HackatonASD::init() {
    qdwm = new QDockWidget("Table");
    qdwl = new QDockWidget("Operations");
    qdwb = new QDockWidget("Logger");

    Logger::qpte = new QPlainTextEdit();
    Logger::qpte->setReadOnly(true);
    qdwb->setWidget(Logger::qpte);

    qtw = new QTableWidget(this);
    qdwm->setWidget(qtw);
    man = new Manager(qtw);
    qtw->setSortingEnabled(true);
    this->setCentralWidget(qdwm);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, qdwl);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, qdwb);
    qfl = new QFrame(qdwl);
    qfl->resize(500, qfl->height());

    loadDataPB = new QPushButton(QString("Load"), qfl);
    saveDataPB = new QPushButton(QString("Save"), qfl);
    saveDataPB->setVisible(false);

    makeconnections();
}

void HackatonASD::makeconnections() {

    connect(qtw->horizontalHeader(), SIGNAL(sectionClicked(int)),
        this, SLOT(sort(int)));

    connect(loadDataPB, SIGNAL(released()), this, SLOT(loadData()));

    connect(saveDataPB, SIGNAL(released()), this, SLOT(saveData()));
}

void HackatonASD::loadData() {
    QFileDialog* qfd = new QFileDialog(this);

    QStringList file;
    qfd->setFileMode(QFileDialog::FileMode::ExistingFile);
    qfd->setDefaultSuffix(QString("csv"));
    qfd->setViewMode(QFileDialog::Detail);

    if (qfd->exec()) {
        file = qfd->selectedFiles();
    }

    if (file.size() == 0) {
        Logger::error("No file selected.");
        return;
    }
    delete qfd;
    IO::inFile = file[0].toLocal8Bit().constData();

    this->man->loadData();
    this->saveDataPB->setVisible(true);
    this->man->populate();
}

void HackatonASD::saveData() {
    QProgressDialog* qpd = new QProgressDialog();
    qpd->setLabelText(QString("Please wait..."));
    qpd->show();
    this->man->saveData();
    qpd->close();

    delete qpd;
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
    Logger::info(("Sorting " + std::to_string(this->man->size()) + " entries.").c_str());
    qpd->show();
    this->man->sort();
    qpd->close();

    delete qpd;
}