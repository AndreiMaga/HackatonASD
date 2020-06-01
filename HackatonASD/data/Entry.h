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

    static Entry* fromString(std::string input) {
        Entry* e = new Entry();
        std::vector<std::string> tokens;

        std::stringstream ss(input);
        std::string token;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        e->nr = std::stoi(tokens[tokenHeader["nr"]]);
        e->name = tokens[tokenHeader["name"]];
        e->stock = std::stoi(tokens[tokenHeader["stock"]]);
        e->price = std::stod(tokens[3]);
        e->expireon = Date::fromString(tokens[tokenHeader["expireon"]]);
        e->addedon = Date::fromString(tokens[tokenHeader["addedon"]]);

        return e;
    }

    std::string str() const {
        return Utils::join(std::vector<std::string>{
            std::to_string(this->nr),
                this->name,
                std::to_string(this->stock),
                std::to_string(this->price),
                this->expireon->str(),
                this->addedon->str()
        });
    }

    static std::string join(const std::vector<Entry*>& vector, const std::string& delim);


    int getnr() {
        return this->nr;
    }

    static void setSortType(SortType st) {
        Entry::st = st;
    }

    bool operator<(const Entry& b);
    bool operator>(const Entry& b);

    void createTableItems() {
        this->nr_qtwi =  new QTableWidgetItem(QString(std::to_string(this->nr).c_str()));
        this->name_qtwi = new QTableWidgetItem(QString(this->name.c_str()));
        this->stock_qtwi= new QTableWidgetItem(QString(std::to_string(this->stock).c_str()));
        this->price_qtwi = new QTableWidgetItem(QString(std::to_string(this->price).c_str()));
        this->exp_qtwi = new QTableWidgetItem(QString(this->expireon->str().c_str()));
        this->add_qtwi = new QTableWidgetItem(QString(this->addedon->str().c_str()));
    }

    void extractFromTableItems() {
        this->nr = nr_qtwi->text().toInt();
        this->price = price_qtwi->text().toFloat();
        this->stock = stock_qtwi->text().toInt();
        this->name = name_qtwi->text().toLocal8Bit().constData();
        free(this->expireon);
        free(this->addedon);
        this->expireon = Date::fromString(exp_qtwi->text().toLocal8Bit().constData());
        this->addedon = Date::fromString(add_qtwi->text().toLocal8Bit().constData());
    }

};

