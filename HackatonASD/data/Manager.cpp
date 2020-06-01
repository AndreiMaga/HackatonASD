#include "Manager.h"

void Manager::add(Entry* e)
{
    this->entries.push_back(e);
    Logger::info(("Added entry with the name:" + e->name).c_str());
}

void Manager::del(Entry* e)
{
    this->entries.erase(this->entries.begin() + this->posInList(e));
    Logger::info(("Deleted entry with the name:" + e->name).c_str());
    delete e;
}

int Manager::posInList(Entry* e)
{
    int i = 0;
    for (Entry* s : this->entries) {
        if (s == e) {
            return i;
        }
        i++;
    }
    return -1;
}

Manager::Manager(QTableWidget* qtw)
{
    this->qtw = qtw;
}

void Manager::loadData()
{
    (entries) = *IO::load();
}

void Manager::saveData() {
    IO::save(this->entries);
}

void Manager::sort() {
    quicksort<Entry>(&entries, this->reverse_sort);
    this->reverse_sort = !this->reverse_sort;
}

void Manager::qtw_init() {
    if (qtw->columnCount() != 6) {
        qtw->setColumnCount(6);
        qtw->setRowCount(this->entries.size());
        qtw->setHorizontalHeaderLabels({ "Number", "Name", "Stock", "Price", "Expires on", "Added on" });
    }
    else {
        qtw->clear();
        Logger::info(("Cleared from the table " + std::to_string(this->entries.size()) + " entries.").c_str());
    }
}

void Manager::populate()
{
    qtw_init();
    int i = 0;
    Logger::info(("Populating the table with " + std::to_string(this->entries.size()) + " entries.").c_str());
    for (Entry* e : this->entries) {
        e->createTableItems();
        qtw->setItem(i, 0, e->nr_qtwi);
        qtw->setItem(i, 1, e->name_qtwi);
        qtw->setItem(i, 2, e->stock_qtwi);
        qtw->setItem(i, 3, e->price_qtwi);
        qtw->setItem(i, 4, e->exp_qtwi);
        qtw->setItem(i, 5, e->add_qtwi);
        i++;
    }
    qtw->update();
}

int Manager::size()
{
    return this->entries.size();
}
