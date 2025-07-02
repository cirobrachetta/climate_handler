#pragma once
#include "Notification.hpp"
#include <iostream>
#include <memory>

class Notifier {
public:
    void Notify(const std::shared_ptr<Notification>& notification) {
        std::cout << "[ALERTA] " << notification->getMessage() << std::endl;
    }
};
