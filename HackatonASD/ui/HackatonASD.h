#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HackatonASD.h"
#include <QTableWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QHeaderView> 
#include <QFrame>
#include <QProgressDialog>
#include <QFileDialog>
#include "../data/Manager.h"
#include "AddWindow.h"

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
    QPushButton* delDataPB;
    QPushButton* addDataPB;
    AddWindow* addWindow;
private:
    Ui::HackatonASDClass ui;

    void init();
    void createButtons();
    void makeconnections();

private slots:
    void loadData();
    void saveData();
    void sort(int col);
    void del();
    void add(Entry* e);
};
