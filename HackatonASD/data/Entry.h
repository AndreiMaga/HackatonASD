#pragma once
#include <string>
#include "Date.h"
#include "../misc/Utils.h"
#include <map>
#include "SortType.h"
#include <QTableWidgetItem>
class Entry
{
public:

    int nr = 0;
    int stock = 0;
    float price = 0;
    std::string name = "";
    Date* expireon = new Date();
    Date* addedon = new Date();

    QTableWidgetItem* nr_qtwi = 0;
    QTableWidgetItem* name_qtwi = 0;
    QTableWidgetItem* stock_qtwi = 0;
    QTableWidgetItem* price_qtwi = 0;
    QTableWidgetItem* exp_qtwi = 0;
    QTableWidgetItem* add_qtwi = 0;

    static SortType st;

    static std::map<std::string, int> tokenHeader;

    static Entry* fromString(std::string input);

    std::string str() const;

    static std::string join(const std::vector<Entry*>& vector, const std::string& delim);

    static void setSortType(SortType st);

    bool operator<(const Entry& b);
    bool operator>(const Entry& b);

    void createTableItems();

    void extractFromTableItems();

};

