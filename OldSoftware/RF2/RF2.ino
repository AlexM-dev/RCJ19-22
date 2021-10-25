#include "src/Defines.h" 
#include "src/Context.h"
#include "src/libs/Log.h"

Context *context;

void setup(){ 
  Log::init();
  Serial3.begin(115200);
  Serial2.begin(115200);
  Serial1.begin(115200);  
  Serial.begin(115200);
  //Serial.println("Asasf");  
  //delay(10000); 
  dribler.attach(DRIBBLER_PIN);
  delay(100);
  dribler.writeMicroseconds(MID_PPM);
  delay(1750);

  context = new Context(&dribler);
  context->setup(); 
} 

void loop(){   
    //long int timep = millis();
    //
    context->updateHardware();
    context->selectStrategy();
    context->updareStrategy();
    //Serial.println(millis()-timep);    
} 
