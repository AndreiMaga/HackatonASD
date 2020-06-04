#include "HackatonASD.h"


HackatonASD::HackatonASD(QWidget* parent)
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
    qtw->setSortingEnabled(true);
    man = new Manager(qtw);
    addWindow = new AddWindow(this, this->man);


    this->setCentralWidget(qdwm);
    qfl = new QFrame(qdwl);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, qdwl);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, qdwb);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, addWindow->qdw);
    qdwl->setWidget(qfl);
    qfl->setMinimumWidth(200);
    createButtons();
}

void HackatonASD::createButtons() {
    loadDataPB = new QPushButton(QString("Load"), qfl);
    saveDataPB = new QPushButton(QString("Save"), qfl);
    delDataPB = new QPushButton(QString("Delete"), qfl);
    addDataPB = new QPushButton(QString("Add"), qfl);
    saveDataPB->setVisible(false);
    delDataPB->setVisible(false);
    addDataPB->setVisible(false);
    saveDataPB->setGeometry(100, 100, 100, 50);
    loadDataPB->setGeometry(0, 100, 100, 50);
    addDataPB->setGeometry(0, 200, 100, 50);
    delDataPB->setGeometry(100, 200, 100, 50);

    makeconnections();
}

void HackatonASD::makeconnections() {

    connect(qtw->horizontalHeader(), SIGNAL(sectionClicked(int)),
        this, SLOT(sort(int)));

    connect(loadDataPB, SIGNAL(released()), this, SLOT(loadData()));
    connect(saveDataPB, SIGNAL(released()), this, SLOT(saveData()));
    connect(delDataPB, SIGNAL(released()), this, SLOT(del()));
    connect(addDataPB, SIGNAL(released()), addWindow, SLOT(toggle()));
    connect(addWindow, SIGNAL(addEntry(Entry*)), this, SLOT(add(Entry*)));
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
    IO::outFile = IO::inFile;
    this->man->loadData();
    this->saveDataPB->setVisible(true);
    this->delDataPB->setVisible(true);
    this->addDataPB->setVisible(true);
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

void HackatonASD::del() {
    QTableWidgetItemEntry<Entry>* current = dynamic_cast<QTableWidgetItemEntry<Entry>*>(qtw->currentItem());
    this->man->del(current->e);
    this->qtw->removeRow(qtw->currentRow());
    // current already deleted inside manager
}

void HackatonASD::add(Entry* e)
{
    this->man->add(e);
}
