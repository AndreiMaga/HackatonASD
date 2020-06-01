#include "Entry.h"
std::map<std::string, int> Entry::tokenHeader = {
    {"nr", 0},
    {"name", 1},
    {"stock", 2},
    {"price", 3},
    {"expireon", 4},
    {"addedon", 5}
};

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