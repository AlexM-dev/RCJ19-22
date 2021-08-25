#include <ArduinoSort.h>
#include <math.h>

#define FASTADC 1 //Включение или выключение режима ускорения АЦП

// Псевдоасемблерные команды для работы со скоростью АЦП через регистры
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define S0 6
#define S1 5
#define S2 7
#define S3 8
#define SIG A0
#define SIG2 A1

#define F_SIZE 20
#define F2_SIZE 1

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

int data[32];
int notFiltred[32][F_SIZE];

void setup() {
  Serial.begin(115200);

  #if FASTADC
  // Устнавливаем скрость чтения АЦП
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  #endif

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SIG, INPUT);
  pinMode(SIG2, INPUT);
  turnLow();
}

void turnLow() {
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
}

void loop(){ 
  readSensors();
}

void readSensors() {
  float angle[F2_SIZE];
  float dist[F2_SIZE];

  for(int f2 = 0; f2 < F2_SIZE; ++f2){
    for(int i = 0; i < 16; ++i)
      for(int  f = 0; f < F_SIZE; ++f)
        readChanel(i, f);

    for(int i = 0; i < 32; ++i){
      sortArray(notFiltred[i], F_SIZE);
      data[i] = notFiltred[i][F_SIZE-1];
    }
    data[14] = 0; 
    dist[f2] = getDist(getX(data), getY(data));
    angle[f2] = getAngle(getX(data), getY(data));
  }

  sortArray(angle, F2_SIZE);
  sortArray(dist, F2_SIZE);

  byte dt[2] = {0, 0};
  Serial.write(0xff);
  if(dist[F2_SIZE/2] == 0)
    dt[0] = 200;
  else
  dt[0] = (int)angle[F2_SIZE/2]/2;
  dt[1] = dist[F2_SIZE/2] * 10;
  Serial.write(dt, sizeof(dt));
  //Serial.println( (((dt[0]*2) + 315)%360) + 180);
}

void readChanel(int channel, int f) {
  //turnLow();
  //loop through the 4 sig
  digitalWrite(S0, muxChannel[channel][0]);
  digitalWrite(S1, muxChannel[channel][1]);
  digitalWrite(S2, muxChannel[channel][2]);
  digitalWrite(S3, muxChannel[channel][3]);

  notFiltred[channel][f] = !digitalRead(SIG);
  notFiltred[channel + 16][f] = !digitalRead(SIG2);
}

double toRadians(double degs) {
  return degs * 3.1415926553 / 180;
}
float getAngle(float x, float y) {
  float angle = atan2(x, y) * 57.2928;
  if (angle < 0)
    angle = 360 + angle;

  return angle;
}

float getX(int tsop_results[]) {
  float x = 0;
  for (int i = 0; i < 32; ++i)
    x += sin(toRadians(11.25 * i)) * tsop_results[i];
  return x;
}

float getY(int tsop_results[]) {
  float y = 0;
  for (int i = 0; i < 32; ++i)
    y += cos(toRadians(11.25 * i)) * tsop_results[i];
  return y;
}

float getDist(float x, float y) {
  return sqrt(abs(x * x + y * y));
}
