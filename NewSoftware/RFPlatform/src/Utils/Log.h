#pragma once

#include <Arduino.h>

#define LOG_ENABLED true
#define LOG_INFO_ENABLED true
#define LOG_ERROR_ENABLED true
#define LOG_WARNING_ENABLED true

#define LOG_COLOR_ENABLED true

#define LOG_CTI "\x1B["
#define LOG_NORMAL "0m"
#define LOG_RED "91m"
#define LOG_GREEN "92m"
#define LOG_YELLOW "93m"
#define LOG_BLUE "94m"
#define LOG_WHITE "97m"

class Log
{
public:
    static void init(){
        if(!LOG_ENABLED)
            return;
        Serial.begin(115200);
    }

     static void nl()
    {
        if(!LOG_ENABLED)
            return;
        Serial.println();
    }

    static void error(uint16_t message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_ERROR_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_RED);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void error(String message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_ERROR_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_RED);
        Serial.print(message);
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void error(double message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_ERROR_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_RED);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }

    static void warning(uint16_t message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_WARNING_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_YELLOW);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void warning(String message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_WARNING_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_YELLOW);
        Serial.print(message);
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void warning(double message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_WARNING_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_YELLOW);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void info(float message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_INFO_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_WHITE);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void info(int message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_INFO_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_WHITE);
        Serial.print(" " + String(message) + " ");
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void info(uint8_t message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_INFO_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_WHITE);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void info(uint16_t message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_INFO_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_WHITE);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void info(String message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_INFO_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_WHITE);
        Serial.print(message);
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void info(double message)
    {
        if(!LOG_ENABLED)
            return;
        if(!LOG_INFO_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_WHITE);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }

    static void success(uint16_t message)
    {
        if(!LOG_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_GREEN);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void success(String message)
    {
        if(!LOG_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_GREEN);
        Serial.print(message);
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }
    static void success(double message)
    {
        if(!LOG_ENABLED)
            return;
        Serial.print(LOG_CTI);
        Serial.print(LOG_GREEN);
        Serial.print(String(message));
        Serial.print(LOG_CTI);
        Serial.println(LOG_NORMAL);     
    }

};