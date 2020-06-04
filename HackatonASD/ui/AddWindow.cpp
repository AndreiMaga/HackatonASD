#include "AddWindow.h"

AddWindow::AddWindow(QWidget* parent, Manager* man)
{
    this->parent = parent;
    this->man = man;
    this->qdw = new QDockWidget(QString("Add Window"),parent);
    this->qf = new QFrame(qdw);
    this->qdw->setWidget(qf);
    this->qdw->setVisible(this->visible);
    qf->setMinimumWidth(300);
    this->createlayout();
}

void AddWindow::createlayout() {
    /*This will get deleted when the app will close*/
    QLabel* nume_label= new QLabel("Nume",this->qf);
    QLabel* stock_label = new QLabel("Stock", this->qf);
    QLabel* price_label = new QLabel("Price", this->qf);
    QLabel* exp_label = new QLabel("Expires on", this->qf);
    QLabel* added_label = new QLabel("Added on", this->qf);

    nume_label->setGeometry(0, 100, 25, 25);
    name = new QTextEdit(this->qf);
    name->setGeometry(30, 100, 270, 25);

    stock_label->setGeometry(0, 130, 25, 25);
    stock = new QSpinBox(this->qf);
    stock->setMinimum(0);
    stock->setGeometry(30, 130, 270, 25);

    price_label->setGeometry(0, 160, 25, 25);
    price = new QDoubleSpinBox(this->qf);
    price->setMinimum(0);
    price->setGeometry(30, 160, 270, 25);

    exp_label->setGeometry(0, 190, 25, 25);
    exp = new QDateEdit(this->qf);
    exp->setCalendarPopup(true);
    exp->setGeometry(30, 190, 270, 25);

    added_label->setGeometry(0, 220, 25, 25);
    added = new QDateEdit(this->qf);
    added->setCalendarPopup(true);
    added->setGeometry(30, 220, 270, 25);

    addPB = new QPushButton("ADD", this->qf);
    clearPB = new QPushButton("CLEAR", this->qf);

    connect(addPB, SIGNAL(released()), this, SLOT(add()));
    connect(clearPB, SIGNAL(released()), this, SLOT(clear()));

    addPB->setGeometry(0, 260, 150, 30);
    clearPB->setGeometry(150, 260, 150, 30);
}

void AddWindow::add() {
    Entry* e = new Entry();
    e->nr = man->inc();
    e->name = name->toPlainText().toLocal8Bit();
    e->stock = stock->value();
    e->price = (float)price->value();
    e->expireon = Date::fromString(exp->text().toLocal8Bit().constData());
    e->addedon = Date::fromString(added->text().toLocal8Bit().constData());
    emit addEntry(e);
}

void AddWindow::clear() {
    name->clear();
    stock->clear();
    price->clear();
    exp->clear();
    added->clear();
}


void AddWindow::toggle() {
    this->visible = !this->visible;
    this->qdw->setVisible(this->visible);
}
