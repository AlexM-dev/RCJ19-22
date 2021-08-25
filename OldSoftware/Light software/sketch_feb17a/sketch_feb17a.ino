 #include <Wire.h> // подключаем библиотеку "Wire"
//#define EN 15
#define S0 6
#define S1 5
#define S2 7
#define S3 8
#define SIG A1


// 65 Line is always visible
#define WHITE_VAL 55

#define FASTADC 1 //Включение или выключение режима ускорения АЦП

// Псевдоасемблерные команды для работы со скоростью АЦП через регистры
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

static bool muxChannel[16][4] = {
  {0, 0, 0, 0}, //channel 0
  {1, 0, 0, 0}, //channel 1
  {0, 1, 0, 0}, //channel 2
  {1, 1, 0, 0}, //channel 3
  {0, 0, 1, 0}, //channel 4
  {1, 0, 1, 0}, //channel 5
  {0, 1, 1, 0}, //channel 6
  {1, 1, 1, 0}, //channel 7
  {0, 0, 0, 1}, //channel 8
  {1, 0, 0, 1}, //channel 9
  {0, 1, 0, 1}, //channel 10
  {1, 1, 0, 1}, //channel 11
  {0, 0, 1, 1}, //channel 12
  {1, 0, 1, 1}, //channel 13
  {0, 1, 1, 1}, //channel 14
  {1, 1, 1, 1}  //channel 15
};

int data[16];

void setup() {
  Serial.begin(115200);

  #if FASTADC// Устнавливаем скрость чтения АЦП
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  #endif

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SIG, INPUT);
}

void turnLow() {
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
}

void loop() {
  Serial.write(readSensors());
}

int readSensors(){
  for (int i = 0; i < 4; i++) {
    if(readMux(i) < WHITE_VAL)
      return 1;
  }
  for (int i = 4; i < 8; i++) {
    if(readMux(i) < WHITE_VAL)
      return 2;
  }
  for (int i = 8; i < 12; i++) {
    if(readMux(i) < WHITE_VAL)
      return 3;
  }
  for (int i = 12; i < 16; i++) {
    if(readMux(i) < WHITE_VAL)
      return 4;
  }
  return 0;
}


int readMux(int channel) {
  // Set All Pins LOW
  // turnLow();

  //loop through the 4 sig
  digitalWrite(S0, muxChannel[channel][0]);
  digitalWrite(S1, muxChannel[channel][1]);
  digitalWrite(S2, muxChannel[channel][2]);
  digitalWrite(S3, muxChannel[channel][3]);

  //return the value
  return analogRead(SIG);
}
