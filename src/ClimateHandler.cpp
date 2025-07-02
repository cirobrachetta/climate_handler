#include "../include/ClimateHandler.hpp"
#include "../include/Notification.hpp"
#include <iostream>

Climate_Handler::Climate_Handler()
    : ActualTemp(25), ActualHumity(50),
      persistence(std::make_shared<Persistence_Handler>()),
      notifier(std::make_shared<Notifier>()) {}

void Climate_Handler::Up_Temp(int x) {
    ActualTemp += x;
    persistence->Persist("Temp subida a " + std::to_string(ActualTemp));
    checkThresholds();
}

void Climate_Handler::Down_Temp(int x) {
    ActualTemp -= x;
    persistence->Persist("Temp bajada a " + std::to_string(ActualTemp));
    checkThresholds();
}

void Climate_Handler::Up_Humidity(int x) {
    ActualHumity += x;
    persistence->Persist("Humedad subida a " + std::to_string(ActualHumity));
    checkThresholds();
}

void Climate_Handler::Down_Humidity(int x) {
    ActualHumity -= x;
    persistence->Persist("Humedad bajada a " + std::to_string(ActualHumity));
    checkThresholds();
}

int Climate_Handler::Read_Temp() {
    return ActualTemp;
}

int Climate_Handler::Read_Humidity() {
    return ActualHumity;
}

void Climate_Handler::checkThresholds() {
    if (ActualTemp > 30 || ActualHumity > 70) {
        auto alert = std::make_shared<Notification>("Condicion critica de clima detectada.");
        notifier->Notify(alert);
    }
}

void Climate_Handler::Menu() {
    std::cout << "Temperatura actual: " << ActualTemp << "\n";
    std::cout << "Humedad actual: " << ActualHumity << "\n";
}

std::shared_ptr<Persistence_Handler> Climate_Handler::GetPersistence() const {
    return persistence;
}