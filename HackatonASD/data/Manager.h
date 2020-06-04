#pragma once
#include "../io/EntryIO.h"
#include "Entry.h"
#include "../misc/Quicksort.h"
#include <QTableWidget>
#include <QString>
#include <QTableWidgetItem>
class Manager
{
    bool reverse_sort = false;
    std::vector<Entry*> entries;
    int posInList(Entry* e);
    QTableWidget* qtw;

public:
    int max = 0;
    Manager(QTableWidget*);
    void setItems(int i,Entry* e);
    void add(Entry* e);
    void del(Entry* e);
    void loadData();
    void saveData();
    void sort();
    void qtw_init();
    void populate();
    int size();
    int inc();
};