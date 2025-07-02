#pragma once
#include <string>
#include <iostream>

class Notification {
public:
    explicit Notification(const std::string& msg) : message(msg) {}
    std::string getMessage() const { return message; }

private:
    std::string message;
};
