#include "src/Core.h" 

#include "src/Utils/Log.h" 

Core *core;

void setup(){
    Log::init();
    core = new Core();
}


void loop(){
    core->update();
}
