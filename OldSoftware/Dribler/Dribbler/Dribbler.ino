#include <Servo.h>

Servo motor;

void setup(){
   motor.attach(12);

//   for(int i = 800; i <= 1400; i++){
//     motor.write(i);
//     delay(5);  
//   }
delay(5000);
}


    

void loop(){
     motor.write(1600);
     delay(10000);  
     motor.write(1400);
     delay(9000);
     delay(1000);
}
