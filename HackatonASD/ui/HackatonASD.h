#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HackatonASD.h"
#include <QTableWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QHeaderView> 
#include "../data/Manager.h"


class HackatonASD : public QMainWindow
{
    Q_OBJECT

public:
    HackatonASD(QWidget *parent = Q_NULLPTR);
    QTableWidget* qtw;
    Manager* man;
    QDockWidget* qdwr;
    QDockWidget* qdwl;
    QDockWidget* qdwb;
    QPushButton* loadDataPB;
    QPushButton* saveDataPB;
private:
    Ui::HackatonASDClass ui;

private slots:
    void loadData();
    void saveData();
    void sort(int col);
};
