#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

#define LOG_ENABLED true
#define LOG_INFO_ENABLED true
#define LOG_ERROR_ENABLED true
#define LOG_WARNING_ENABLED false

#define LOG_TYPE_INFO "[0]Info"
#define LOG_TYPE_ERROR "[1]Error"
#define LOG_TYPE_WARNING "[2]Warning"

class Log {
    private:
        

    public:
        static void init(){
            if(!LOG_ENABLED)
                return;
            Serial.begin(115200);
        }

        static void info(String tag, String text){
            if(!LOG_ENABLED)
                return;
            if(!LOG_INFO_ENABLED)
                return;    
            Serial.print(LOG_TYPE_INFO);
            Serial.print(" ");
            Serial.print(tag);
            Serial.print(" : ");
            Serial.println(text);
        }

       

        static void error(String tag, String text){
            if(!LOG_ENABLED)
                return;
            if(!LOG_ERROR_ENABLED)
                return;    
            Serial.print(LOG_TYPE_ERROR);
            Serial.print(" ");
            Serial.print(tag);
            Serial.print(" : ");
            Serial.println(text);
        }

        static void warning(String tag, String text){
            if(!LOG_ENABLED)
                return;
            if(!LOG_WARNING_ENABLED)
                return;    
            Serial.print(LOG_TYPE_WARNING);
            Serial.print(" ");
            Serial.print(tag);
            Serial.print(" : ");
            Serial.println(text);
        }
};

#endif