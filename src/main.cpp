#include <Arduino.h>
#include "termokupl.h"
#include "SimpleTimer.h"


#define TERMOKUPL_CS_PIN  25
#define TERMOKUPL_SCK_PIN 26
#define TERMOKUPL_SO_PIN  27

#define PED_PIN 33
#define PED_SET_TEMPERATURE 60
#define PAD_SUPPLY_VOLTAGE 16
#define MAX_PED_VOLTAGE 7

#define PID_DEBUG
#define PID_SAMPLE_TIME 200
#define Kp 7.0f
#define Ki 0.5f
#define Kd 3.0f

termokupl_t termokupl;
SimpleTimer timer;


void pedBegin()
{
  pinMode(PED_PIN, OUTPUT);
}

float calculatePID(float setTemperature, float realTemperature, int maxOutputValue)
{
  #define MAX_PED_VOLTAGE_FORMULA(setVoltage, supplyVoltage)  ( (255 * setVoltage) / supplyVoltage ) 
  #define MAX_PED_VOLTAGE_CAL   MAX_PED_VOLTAGE_FORMULA(MAX_PED_VOLTAGE, PAD_SUPPLY_VOLTAGE)

  static float pidLastEror;
  static float pidIntegral;
  float time = ((float)PID_SAMPLE_TIME / 1000);

  float eror       =  (setTemperature - realTemperature);
  pidIntegral     +=  (eror * time);
  float derivative =  ( (realTemperature - pidLastEror) / time );
  float pidOutput  =  (Kp * eror) + (Ki * pidIntegral) + (Kd * derivative);

  pidLastEror = realTemperature;

  #ifdef PID_DEBUG
  Serial.print("RAW PWM: ");
  Serial.print(pidOutput);
  #endif

  if(pidOutput > MAX_PED_VOLTAGE_CAL)
    pidOutput = MAX_PED_VOLTAGE_CAL;
  else if(pidOutput <= 0)
    pidOutput = 0;

  return pidOutput;
}
void pidControl()
{
  int temperature = (int)readTermokuplValue(&termokupl);

  int PWM = calculatePID(PED_SET_TEMPERATURE, temperature, MAX_PED_VOLTAGE);

  #ifdef PID_DEBUG
  analogWrite(PED_PIN, PWM);
  Serial.print("  SICAKLIK: ");
  Serial.print(temperature);

  Serial.print("  SET VALUE: ");
  Serial.print(PED_SET_TEMPERATURE);

  Serial.print("  PWM SIGNAL: ");
  Serial.println(PWM);

  #else 
  Serial.println("DEBUG KAPALI");
  #endif

}


void setup() 
{
  Serial.begin(115200);
  termokupl_init(&termokupl, TERMOKUPL_CS_PIN, TERMOKUPL_SCK_PIN, TERMOKUPL_SO_PIN);
  pedBegin();
  timer.setInterval(PID_SAMPLE_TIME, pidControl);
}

void loop()
{
  timer.run();
}

