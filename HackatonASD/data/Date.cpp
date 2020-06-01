#include "Date.h"


bool Date::operator< (const Date& b) {
    /*year*/
    if (this->year < b.year)
        return true;
    if (this->year > b.year)
        return false;
    /*month*/
    if (this->month < b.month)
        return true;
    if (this->month > b.month)
        return false;
    /*day*/
    if (this->day < b.day)
        return true;

    /*if this->day > b.day or this->day == b.day return false*/
    return false;
}

bool Date::operator> (const Date& b) {
    /*year*/
    if (this->year < b.year)
        return false;
    if (this->year > b.year)
        return true;
    /*month*/
    if (this->month < b.month)
        return false;
    if (this->month > b.month)
        return true;
    /*day*/
    if (this->day > b.day)
        return true;

    /*if this->day < b.day or this->day == b.day return false*/
    return false;
}

bool Date::operator==(const Date& b)
{
    if (this->year == b.year && this->month == b.month && this->day == b.day)
        return true;
    return false;
}

bool Date::operator<=(const Date& b)
{
    /*year*/
    if (this->year < b.year)
        return true;
    if (this->year > b.year)
        return false;
    /*month*/
    if (this->month < b.month)
        return true;
    if (this->month > b.month)
        return false;
    /*day*/
    if (this->day < b.day)
        return true;
    if (this->day > b.day)
        return false;
    /*if all are equals return true*/
    return true;
}

Date* Date::fromString(std::string input)
{
    Date* date = new Date();
    std::vector<std::string> tokens;

    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, '/')) {
        tokens.push_back(token);
    }

    date->day = std::stoi(tokens[0]);
    date->month = std::stoi(tokens[1]);
    date->year = std::stoi(tokens[2]);
    return date;

}
