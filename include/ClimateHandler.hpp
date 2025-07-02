#pragma once
#include "PersistenceHandler.hpp"
#include "Notifier.hpp"
#include "MSForecast.hpp"
#include <memory>

class Climate_Handler : public MS_Forecast {
public:
    Climate_Handler();
    void Menu();

    // Implementación de MS-Forecast API
    void Up_Temp(int x) override;
    void Down_Temp(int x) override;
    void Up_Humidity(int x) override;
    void Down_Humidity(int x) override;
    int Read_Temp() override;
    int Read_Humidity() override;
    std::shared_ptr<Persistence_Handler> GetPersistence() const;

private:
    int ActualTemp;
    int ActualHumity;
    std::shared_ptr<Persistence_Handler> persistence;
    std::shared_ptr<Notifier> notifier;

    void checkThresholds();
};
