#include "DHT.h"

#define DHTPIN A2  
#define DHTTYPE DHT11 
int smokeA0 = A1;
int pin_red=8;
int pin_green=9;
int buzzer=6;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(pin_red,OUTPUT);
  pinMode(pin_green,OUTPUT);
  pinMode(buzzer,OUTPUT);
  dht.begin();
 }

void loop() {
  delay(2000);
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
  int analogSensor = analogRead(smokeA0);
  Serial.print(" Smoke: ");
  Serial.print(analogSensor);
  Serial.println("");
  if(analogSensor>200&&t<40){
    Serial.println(" !Smoke Alert");
    tone(buzzer,800,800);
    delay(200);
    tone(buzzer,600,800);
    delay(200);
    delay(1000);
  }
  if(t>40&&h<35){
    Serial.println(" !Fire Alert Evacuate");
    tone(buzzer,800,800);
    delay(200);
    tone(buzzer,600,800);
    delay(200);
    delay(1000);
   set_outputs_plus_ground(pin_red,pin_green);
   delay(1000);
  }
  else{
    digitalWrite(pin_red,LOW);
    digitalWrite(pin_green,LOW);
  }
}
void set_outputs_plus_ground(int pin_plus, int pin_ground)
{
  //set both pins low first so you don't have them pushing 5 volts into eachother
  digitalWrite(pin_plus,LOW);  
  digitalWrite(pin_ground,LOW);
  //set output pin as high
  digitalWrite(pin_plus,HIGH);  
  } 
