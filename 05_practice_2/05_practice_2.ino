#define PIN_LED 7

int count=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("Hello World");
  digitalWrite(PIN_LED,0);
  delay(1000);
  digitalWrite(PIN_LED,1);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_LED,0);
  delay(100);
  digitalWrite(PIN_LED,1);
  delay(100);
  count++;
  Serial.println(count);
  if(count>=5) while(1){}
}
