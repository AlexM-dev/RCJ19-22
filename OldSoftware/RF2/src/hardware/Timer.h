#include <Arduino.h>

class Timer {
private:
  boolean enabled;
  static void (*user_onTick)(void);
  unsigned long previousMillis;
  long del;
  
  void tick();

public:
  Timer();
  Timer(long newDel);

  void setOnTickListener( void (*)(void) );
  void update();
  void setDelay(long newDel);
  void setEnabled(bool en);
  void start();
  void stop();
  bool isEnabled();
};
