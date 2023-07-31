#include <Arduino.h>
#include "termokupl.h"
#include "SimpleTimer.h"

#define CS_PIN  25
#define SCK_PIN 26
#define SO_PIN  27
#define PED_PIN 33
#define PED_SET_VALUE 50

const int LED = 18;  /*Equals to GPIO pin 18*/
const int freq = 50; /*PWM signal frequency*/
const int LED_Channel = 0;
const int resolution = 8; /*PWM resolution*/

void setup(){
  ledcSetup(LED_Channel, freq, resolution);  /*PWM signal defined*/
  ledcAttachPin(LED, LED_Channel);
}

void loop(){
    ledcWrite(LED_Channel, 127);  
}






























/*

termokupl_t termokupl;
SimpleTimer timer;
int temperature;

void getTermokuplValue()
{
  temperature = (int)readTermokuplValue(&termokupl);
}
void on_offControl()
{
  Serial.print("Sicaklik: ");
  Serial.print(temperature);
  Serial.print("\t");

    if(temperature <= PED_SET_VALUE)
    { 
      analogWrite(PED_PIN, 127);
      Serial.print("Set Value: ");
      Serial.println(PED_SET_VALUE);
    }

    else
    {
      analogWrite(PED_PIN, 0);
      Serial.print("Set Value: ");
      Serial.println(0);
    }
    
}

void setup() {
  Serial.begin(115200);
  termokupl_init(&termokupl, CS_PIN, SCK_PIN, SO_PIN);
  timer.setInterval(200L, getTermokuplValue);
  timer.setInterval(200L, on_offControl);
}

void loop() {
//timer.run();

analogWrite(PED_PIN, 127);


}



*/

