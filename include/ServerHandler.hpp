#pragma once
#include "httplib.h"
#include "ClimateHandler.hpp"
#include <memory>

class ServerHandler {
public:
    ServerHandler(std::shared_ptr<Climate_Handler> handler);
    void run();

private:
    std::shared_ptr<Climate_Handler> climateHandler;
    httplib::Server svr;

    void setupRoutes();
    std::string loadHtml(const std::string& filename);
};
