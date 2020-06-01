#include "HackatonASD.h"
#include <QProgressDialog>
#include <QFileDialog>

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
    QFileDialog* qfd = new QFileDialog(this);

    QStringList file;
    qfd->setFileMode(QFileDialog::FileMode::ExistingFile);
    qfd->setDefaultSuffix(QString("csv"));
    qfd->setViewMode(QFileDialog::Detail);

    if (qfd->exec()) {
        file = qfd->selectedFiles();
    }

    if (file.size() == 0) {
        Logger::error("No files selected");
        return;
    }
    IO::inFile = file[0].toLocal8Bit().constData();

    this->man->loadData();
    this->loadDataPB->setVisible(false);
    delete loadDataPB; // free memory
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
    Logger::info(("Sorting " + std::to_string(this->man->size()) + " entries.").c_str());
    qpd->show();
    this->man->sort();
    qpd->close();

    delete qpd;
}