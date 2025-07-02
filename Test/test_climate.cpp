#include "../src/cpp/ClimateHandler.cpp"
#include <cassert>

int main() {
    Climate_Handler handler;
    handler.Up_Temp(5);
    assert(handler.Read_Temp() == 30);
    handler.Down_Humidity(10);
    assert(handler.Read_Humidity() == 40);
    return 0;
}
