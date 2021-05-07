#include <Servo.h>

Servo motor;

void setup(){
   motor.attach(12);

   for(int i = 800; i <= 1400; i++){
     motor.write(i);
     delay(5);  
   }
}


    

void loop(){
     motor.write(1500);
     delay(1000);  
     motor.write(0);
     delay(9000);
     delay(1000);
}
