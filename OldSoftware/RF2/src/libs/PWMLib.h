#ifndef PWMPIN_H
#define PWMPIN_H

#include <Arduino.h>

class PWMPin {
  public:
    PWMPin(int pin){
        this->pin = pin;
        async = true;
        t = 20000;
        tOn = 0;
        
        state = false;
        curDel = tOn;
        prevMicros = micros();
    }
    
    void rotateServo(int angle){
        tOn = map(angle, 0,180,544,2400);
    }
        
    void update() {
        if(async){
            if(micros() - prevMicros >= curDel && tOn != 0){
                if(state) {
                curDel = t - tOn;
                digitalWrite(pin,LOW);
                state = false;  
                } else {
                curDel = tOn;
                state = true;
                digitalWrite(pin,HIGH);
                }
                prevMicros = micros();
            }
        } else {
            digitalWrite(pin,HIGH);
            delayMicroseconds(tOn);
            digitalWrite(pin,LOW);
            delayMicroseconds(t - tOn);
        }
    }
    
    void setT(int t){
        this->t = t;
    }
    
    void setTon(int tOn){
        this->tOn = tOn;
    }
    
    void setToff(int tOff){
        this->tOn = t - tOff;
    }
    
    void setAsync(bool async){
        this->async = async;
    }
    
    void setTonProzent(int prozent){
        this->tOn = map(prozent, 0, 100, 0, t); 
    }
  
  private:
  	unsigned long long prevMicros;
  	bool async, state;
 	unsigned int pin, t, tOn, curDel;
};

#endif
