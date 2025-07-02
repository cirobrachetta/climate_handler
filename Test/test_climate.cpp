#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../include/ClimateHandler.hpp"
#include <fstream>

TEST_CASE("Temperatura y Humedad inicial", "[clima]") {
    Climate_Handler handler;

    REQUIRE(handler.Read_Temp() == 25);
    REQUIRE(handler.Read_Humidity() == 50);
}

TEST_CASE("Subir temperatura", "[clima]") {
    Climate_Handler handler;
    handler.Up_Temp(5);
    REQUIRE(handler.Read_Temp() == 30);
}

TEST_CASE("Bajar temperatura", "[clima]") {
    Climate_Handler handler;
    handler.Down_Temp(3);
    REQUIRE(handler.Read_Temp() == 22);
}

TEST_CASE("Persistencia al subir humedad", "[persistencia]") {
    Climate_Handler handler;
    handler.Up_Humidity(10);

    auto logs = handler.GetPersistence()->GetData();
    REQUIRE_FALSE(logs.empty());
    REQUIRE(logs.back().find("Humedad subida a") != std::string::npos);
}

TEST_CASE("Guardar CSV", "[persistencia][csv]") {
    Climate_Handler handler;
    std::ofstream file("climate_data.csv", std::ios::app);
    REQUIRE(file.is_open());

    int temp = handler.Read_Temp();
    int hum = handler.Read_Humidity();
    file << "Temperatura: " << temp << ", Humedad: " << hum << "\n";
    file.close();

    std::ifstream infile("climate_data.csv");
    std::string last_line;
    while (infile.peek() != EOF) {
        std::getline(infile, last_line);
    }

    std::string expected = "Temperatura: " + std::to_string(temp) + ", Humedad: " + std::to_string(hum);
    REQUIRE(last_line == expected);
}
