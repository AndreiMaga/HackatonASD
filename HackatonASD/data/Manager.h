#pragma once
#include "../io/EntryIO.h"
#include "Entry.h"
#include "../misc/Quicksort.h"
#include <QTableWidget>
#include <QString>
#include <QTableWidgetItem>
class Manager
{

    std::vector<Entry*> entries;
    void adauga(Entry* e);
    void sterge(Entry* e);
    int posInList(Entry* e);

    QTableWidget* qtw;

public:

    Manager(QTableWidget*);

    void loadData();
    void saveData();
    void sort();
    void qtw_init();
    void populate();
    void forceUpdate();
};