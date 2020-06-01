#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HackatonASD.h"
#include <QTableWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QHeaderView> 
#include <QFrame>
#include "../data/Manager.h"

class HackatonASD : public QMainWindow
{
    Q_OBJECT

public:
    HackatonASD(QWidget *parent = Q_NULLPTR);
    QTableWidget* qtw;
    Manager* man;
    QDockWidget* qdwm;
    QDockWidget* qdwl;
    QDockWidget* qdwb;
    QFrame* qfl;
    QPushButton* loadDataPB;
    QPushButton* saveDataPB;
private:
    Ui::HackatonASDClass ui;

    void init();
    void makeconnections();

private slots:
    void loadData();
    void saveData();
    void sort(int col);
};
