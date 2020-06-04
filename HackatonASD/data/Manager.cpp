#include "Manager.h"

void Manager::setItems(int i, Entry* e) {
    e->createTableItems();
    qtw->setItem(i, 0, e->nr_qtwi);
    qtw->setItem(i, 1, e->name_qtwi);
    qtw->setItem(i, 2, e->stock_qtwi);
    qtw->setItem(i, 3, e->price_qtwi);
    qtw->setItem(i, 4, e->exp_qtwi);
    qtw->setItem(i, 5, e->add_qtwi);
}

void Manager::add(Entry* e)
{
    this->entries.push_back(e);
    qtw->setRowCount(this->entries.size());
    setItems(this->entries.size() - 1,e);
    qtw->update();
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
    if (this->entries.size() > 10000) {
        Logger::warning("This might take a while.");
    }
    quicksort<Entry>(&entries, this->reverse_sort);
    this->reverse_sort = !this->reverse_sort;
}

void Manager::qtw_init() {
    qtw->clear();
    qtw->setColumnCount(6);
    qtw->setRowCount(this->entries.size());
    qtw->setHorizontalHeaderLabels({ "Number", "Name", "Stock", "Price", "Expires on", "Added on" });
}

void Manager::populate()
{
    qtw_init();
    Logger::info(("Populating the table with " + std::to_string(this->entries.size()) + " entries.").c_str());
    int i = 0;
    for (Entry* e : this->entries) {
        if (e->nr > max)
            max = e->nr;
        setItems(i, e);
        i++;
    }
    qtw->update();
}

int Manager::size()
{
    return this->entries.size();
}

int Manager::inc()
{
    max += 1;
    return max;
}
