#include "EntryIO.h"

std::string IO::inFile = "";
std::string IO::outFile = "";

std::vector<Entry*>* IO::load()
{
    std::vector<Entry*>* list = new std::vector<Entry*>();
    std::ifstream linestream(inFile);

    std::string line;
    while (std::getline(linestream, line)) {
        (*list).push_back(Entry::fromString(line));
    }
    linestream.close();

    std::string message = "Loaded from file ";
    message.append(std::to_string((*list).size())).append(" entries.");
    Logger::info(message.c_str());

    return list;
}

void IO::save(std::vector<Entry*> x)
{
    std::ofstream ostr;
    ostr.open(outFile);
    ostr << Entry::join(x, "\n");
    ostr.close();
    std::string message = "Saved to file ";
    message.append(std::to_string(x.size())).append(" entries.");
    Logger::info(message.c_str());
}
