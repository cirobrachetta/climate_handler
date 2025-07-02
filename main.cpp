#include "./include/ClimateHandler.hpp"
#include "./include/ServerHandler.hpp"
#include <memory>

int main() {
    auto handler = std::make_shared<Climate_Handler>();
    ServerHandler server(handler);
    server.run();
    return 0;
}
