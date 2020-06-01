#include "Entry.h"
std::map<std::string, int> Entry::tokenHeader = {
    {"nr", 0},
    {"name", 1},
    {"stock", 2},
    {"price", 3},
    {"expireon", 4},
    {"addedon", 5}
};

Entry* Entry::fromString(std::string input) {
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

std::string Entry::str() const {
    return Utils::join(std::vector<std::string>{
        std::to_string(this->nr),
            this->name,
            std::to_string(this->stock),
            std::to_string(this->price),
            this->expireon->str(),
            this->addedon->str()
    });
}

std::string Entry::join(const std::vector<Entry*>& vector, const std::string& delim = "\n") {
    std::ostringstream s;
    for (const auto& i : vector) {
        if (&i != &vector[0]) {
            s << delim;
        }
        i->extractFromTableItems();
        s << i->str();
    }

    return s.str();
}

void Entry::setSortType(SortType st) {
    Entry::st = st;
}

SortType Entry::st = SortType::NR;

bool Entry::operator<(const Entry& b) {
    switch (st) {
    case SortType::NR:
        return this->nr < b.nr;
    case SortType::NAME:
        return this->name < b.name;
    case SortType::PRICE:
        return this->price < b.price;
    case SortType::STOCK:
        return this->stock < b.stock;
    case SortType::EXPIRE:
        return this->expireon < b.expireon;
    case SortType::ADDED:
        return this->addedon < b.addedon;
    default:
        return false;
    }
}

bool Entry::operator>(const Entry& b) {
    switch (st) {
    case SortType::NR:
        return this->nr > b.nr;
    case SortType::NAME:
        return this->name > b.name;
    case SortType::PRICE:
        return this->price > b.price;
    case SortType::STOCK:
        return this->stock > b.stock;
    case SortType::EXPIRE:
        return this->expireon > b.expireon;
    case SortType::ADDED:
        return this->addedon > b.addedon;
    default:
        return false;
    }
}

void Entry::createTableItems() {
    this->nr_qtwi = new QTableWidgetItem(QString(std::to_string(this->nr).c_str()));
    this->name_qtwi = new QTableWidgetItem(QString(this->name.c_str()));
    this->stock_qtwi = new QTableWidgetItem(QString(std::to_string(this->stock).c_str()));
    this->price_qtwi = new QTableWidgetItem(QString(std::to_string(this->price).c_str()));
    this->exp_qtwi = new QTableWidgetItem(QString(this->expireon->str().c_str()));
    this->add_qtwi = new QTableWidgetItem(QString(this->addedon->str().c_str()));
}

void Entry::extractFromTableItems() {
    this->nr = nr_qtwi->text().toInt();
    this->price = price_qtwi->text().toFloat();
    this->stock = stock_qtwi->text().toInt();
    this->name = name_qtwi->text().toLocal8Bit().constData();
    delete this->expireon;
    delete this->addedon;
    this->expireon = Date::fromString(exp_qtwi->text().toLocal8Bit().constData());
    this->addedon = Date::fromString(add_qtwi->text().toLocal8Bit().constData());
}
