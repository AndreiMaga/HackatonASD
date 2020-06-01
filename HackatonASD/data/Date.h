#pragma once
#include <string>
#include <vector>
#include <sstream>
class Date
{
private:
    int day, month, year;

public:
    bool operator<(const Date& b);
    bool operator>(const Date& b);
    bool operator==(const Date& b);
    bool operator<=(const Date& b);

    std::string str() const;

    static Date* fromString(std::string input);
};

