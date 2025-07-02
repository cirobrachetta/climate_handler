#pragma once

class MS_Forecast {
public:
    virtual void Up_Temp(int x) = 0;
    virtual void Down_Temp(int x) = 0;
    virtual void Up_Humidity(int x) = 0;
    virtual void Down_Humidity(int x) = 0;
    virtual int Read_Temp() = 0;
    virtual int Read_Humidity() = 0;
};
