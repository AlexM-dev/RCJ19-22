#include <SPI.h>

#define tsopCS 6
#define lineCS 21
#define dispCS 11
#define butnCS 22

void setup() {
  Serial.begin(115200);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

byte received = 0;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(butnCS, LOW);
  digitalWrite(dispCS, LOW);
  digitalWrite(lineCS, LOW);
  digitalWrite(tsopCS, HIGH);
  received = SPI.transfer(1);
  Serial.println(received);
  delay(100);
}
