#pragma once
#include <QDockWidget>
#include <QFrame>
#include <QString>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QLabel>
#include "../data/Entry.h"
#include "../data/Manager.h"
class AddWindow : public QObject
{
    Q_OBJECT
public:
    QFrame* qf;
    Manager* man;
    QDockWidget* qdw;
    QWidget* parent;
    QTextEdit* name;
    QDateEdit* exp, * added;
    QSpinBox * stock;
    QDoubleSpinBox* price;
    QPushButton* addPB, * clearPB;
    bool visible = false;
    AddWindow(QWidget* parent, Manager* man);
    void createlayout();
private slots:
    void add();
    void clear();

public slots:
    void toggle();

signals:
    void addEntry(Entry*);
};

