#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define IR_Sensor 0
#define PIN_LED 9
#define PIN_SERVO 10

#define DIST_MIN 100
#define DIST_MAX 250

#define _EMA_ALPHA 0.5

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  pinMode(PIN_LED,OUTPUT);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(57600);
}

float dist_ema,dist_prev=DIST_MIN;

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  a_value = analogRead(IR_Sensor);
  //a_value = analogRead(PIN_POTENTIOMETER);
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  // we need distance range filter here !!!
  // we need EMA filter here !!!

  // map distance into duty
  //duty = map(a_value, 0, 1023, _DUTY_MIN, _DUTY_MAX);
  //yservo.writeMicroseconds(duty);

  float dist=(6762.0/(a_value-9)-4.0)*10.0;

  if(dist<DIST_MIN){
    dist=dist_prev;
    digitalWrite(PIN_LED,1);
  }
  else if(dist>DIST_MAX){
    dist=dist_prev;
    digitalWrite(PIN_LED,1);
  }
  else{
    digitalWrite(PIN_LED,0);
    dist_prev=dist;
  }

  dist_ema=_EMA_ALPHA*dist+(1-_EMA_ALPHA)*dist_ema;
  if(dist_ema<DIST_MIN){
    myservo.writeMicroseconds(_DUTY_MIN);
  }
  else if(dist_ema>DIST_MAX){
    myservo.writeMicroseconds(_DUTY_MAX);
  }
  else{
    duty=DIST_MIN+12.3*(dist-100);
    myservo.writeMicroseconds(duty);
  }

  // print IR sensor value, distnace, duty !!!
  //Serial.print("ADC Read: "); Serial.print(a_value);
  //Serial.print(" = ");
  //Serial.print((a_value / 1024.0) * 5.0);
  //Serial.print(" Volt => Duty : ");
  //Serial.print(duty);
  //Serial.println("usec");
  Serial.print("MIN:"); Serial.print(DIST_MIN);
  Serial.print(",IR:"); Serial.print(a_value);
  Serial.print(",dist:"); Serial.print(dist);
  Serial.print(",ema:"); Serial.print(dist_ema);
  Serial.print(",servo:"); Serial.print(duty);
  Serial.print(",MAX:"); Serial.print(DIST_MAX);
  Serial.println("");
}
