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

    std::string str() const {
        return  std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }

    static Date* fromString(std::string input);
};

