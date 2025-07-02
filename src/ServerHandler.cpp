#include "../include/ServerHandler.hpp"
#include <fstream>
#include <sstream>

ServerHandler::ServerHandler(std::shared_ptr<Climate_Handler> handler)
    : climateHandler(handler) {}

void ServerHandler::run() {
    setupRoutes();
    std::cout << "Servidor escuchando en http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
}

void ServerHandler::setupRoutes() {
    svr.Get("/", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(loadHtml("views/menu.html"), "text/html");
    });

    svr.Post("/climate/up_temp", [&](const httplib::Request&, httplib::Response& res) {
        climateHandler->Up_Temp(1);
        res.set_content("Temperatura aumentada", "text/plain");
    });

    svr.Post("/climate/down_temp", [&](const httplib::Request&, httplib::Response& res) {
        climateHandler->Down_Temp(1);
        res.set_content("Temperatura disminuida", "text/plain");
    });

    svr.Get("/climate/status", [&](const httplib::Request&, httplib::Response& res) {
        std::string status = "Temperatura: " + std::to_string(climateHandler->Read_Temp()) +
                            "°C<br>Humedad: " + std::to_string(climateHandler->Read_Humidity()) + "%";
        res.set_content(status, "text/html");
    });

    // Persistir valores actuales (POST)
    svr.Post("/climate/save", [&](const httplib::Request&, httplib::Response& res) {
        int temp = climateHandler->Read_Temp();
        int hum = climateHandler->Read_Humidity();
        climateHandler->GetPersistence()->Persist("Estado guardado -> Temp: " + std::to_string(temp) +
                                                ", Humedad: " + std::to_string(hum));
        res.set_content("Estado actual guardado en archivo.", "text/plain");
    });

    // Mostrar el histórico como lista
    svr.Get("/climate/logs", [&](const httplib::Request&, httplib::Response& res) {
        std::vector<std::string> data = climateHandler->GetPersistence()->GetData(4);
        std::string html = "<ul>";
        for (const auto& entry : data) {
            html += "<li>" + entry + "</li>";
        }
        html += "</ul>";
        res.set_content(html, "text/html");
    });

    svr.Post("/climate/save_csv", [&](const httplib::Request&, httplib::Response& res) {
        int temp = climateHandler->Read_Temp();
        int hum = climateHandler->Read_Humidity();

        std::ofstream file("climate_data.csv", std::ios::app);
        if (file.is_open()) {
            file << "Temperatura: " << temp << ", Humedad: " << hum << "\n";
            file.close();
            res.set_content("Datos guardados en climate_data.csv", "text/plain");
        } else {
            res.set_content("Error al guardar CSV", "text/plain");
        }
    });

    // Subir humedad
    svr.Post("/climate/up_humidity", [&](const httplib::Request&, httplib::Response& res) {
        climateHandler->Up_Humidity(1);
        res.set_content("Humedad aumentada", "text/plain");
    });

    // Bajar humedad
    svr.Post("/climate/down_humidity", [&](const httplib::Request&, httplib::Response& res) {
        climateHandler->Down_Humidity(1);
        res.set_content("Humedad disminuida", "text/plain");
    });

    // Podés seguir agregando más rutas POST/GET aquí...
}

std::string ServerHandler::loadHtml(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    return "Error al cargar la interfaz HTML.";
}
