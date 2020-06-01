#pragma once
#include <vector>
#include "../data/Entry.h"
#include <fstream>
#include "Logger.h"

class IO
{
public:
    static std::string inFile;
    static std::string outFile;
    static std::vector<Entry*>* load();
    static void save(std::vector<Entry*>);
};

