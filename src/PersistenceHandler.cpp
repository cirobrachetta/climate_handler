#include "../include/PersistenceHandler.hpp"
#include <fstream>
#include <iostream>
#include <deque>

void Persistence_Handler::Persist(const std::string& log) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << log << "\n";
        file.close();
    }
}

void Persistence_Handler::GetLog(const std::string& log) const {
    std::cout << "[LOG PEDIDO] " << log << std::endl;
}

std::vector<std::string> Persistence_Handler::GetData(int lastN) const {
    std::ifstream file(filename, std::ios::in);
    std::deque<std::string> lastLines;
    std::string line;

    while (std::getline(file, line)) {
        if (lastLines.size() >= lastN)
            lastLines.pop_front();
        lastLines.push_back(line);
    }

    return std::vector<std::string>(lastLines.begin(), lastLines.end());
}
