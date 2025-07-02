#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <memory>

class Persistence_Handler {
public:
    void Persist(const std::string& log);
    void GetLog(const std::string& log) const;
    std::vector<std::string> GetData(int lastN = 4) const;
private:
    const std::string filename = "climate_logs.txt";
};
