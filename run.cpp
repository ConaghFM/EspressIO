#include <math.h>

enum FSMState{
  STANDBY,
  DIFFUSING,
  POURING
};

// Global variables
float targetTemp = 93.0; // degrees Celcius
FSMState state = STANDBY;
float pourStart;
// Pinout Config
const int thermistorInput = 0;
const int diffuseSwitch = 13;
const int pourSwitch = 14;
const int diffusionValve = 15;
const int pumpRelay = 16;
const int boilerRelay = 17;

float getTemp() {
  float R1 = 10000 // 10 kOhm Resistor
  // Steinhart-Hart coefficients
  float A = 1;
  float B = 1;
  float C = 1;
  float T; // Temperature in Kelvin

  // Votage Divider for Thermistor reading:
  // Vout = Vin(R2/(R1+R2))
  int Vout = analogRead(thermistorInput);
  float thermistorResistance = R1 * ( ( 1023.0 / (float)Vout ) -1);
  T = 1/( A + B*log(thermistorResistance) + C*pow(log(thermistorResistance), 3.0) );
  return T − 273.15; // Kelvin to Celcius
}

void setBoiler(float setPoint, float measurement){
  // Boiler Config
  float tolerance = 0.5; // in degrees

  float error = measurement - setPoint;
  if(abs(error) >= tolerance){
    if(error > 0.0 && boilerOn == true){
      boilerOn = false;
      digitalWrite(boilerRelay, LOW);
    }
    else if(error < 0.0 && boilerOn == false){
      boilerOn = true;
      digitalWrite(boilerRelay, HIGH);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(thermistorInput, INPUT);
  pinMode(diffuseSwitch, INPUT);
  pinMode(pourSwitch, INPUT);
  pinMode(diffusionValve, OUTPUT);
  pinMode(pumpRelay, OUTPUT);
  pinMode(boilerRelay, OUTPUT);
}

void loop() {
  delay(200); // ms
  setBoiler(targetTemp, getTemp())
  switch(state){

    case STANDBY:
      if (digitalRead(diffuseSwitch) == HIGH || digitalRead(pourSwitch == HIGH)){
        digitalWrite(diffusionValve, HIGH);
        state = DIFFUSING;
        delay(1000); // force diffusion state momentarily before switching to pouring
      }
      break;

    case DIFFUSING:
      if (digitalRead(pourSwitch) == HIGH){
        digitalWrite(pumpRelay, HIGH);
        state = POURING;
        pourStart = millis();
      }
      else if (digitalRead(diffuseSwitch) == LOW && digitalRead(pourSwitch) == LOW){
        delay(100); // ms
        // This checks that the switch wasn't just caught in the broken state
        // between 'diffuse' and 'pump'
        if (digitalRead(diffuseSwitch) == LOW && digitalRead(pourSwitch) == LOW){
          digitalWrite(diffusionValve, LOW);
          state = STANDBY;
        }
      }
      break;

    case POURING:
      if(digitalRead(pourSwitch) == LOW){
        digitalWrite(pumpRelay, LOW);
        delay(500);
        if(digitalRead(pourSwitch) == HIGH){
          digitalWrite(pumpRelay, HIGH);
        }
        else if(digitalRead(diffuseSwitch) == LOW){
          Serial.write("Pour Time: ");
          Serial.write(millis() - pourStart);
          delay(4500); // wait for pump pressure to equalise before closing the valve
          digitalWrite(diffusionValve, LOW);
          state = STANDBY;
        }
        else{ // Switch is in 'diffuse' position
          Serial.write("Pour Time: ");
          Serial.write(millis() - pourStart);
          delay(4500); // wait for pump pressure to equalise before moving to diffusing state, since valve could then be closed
          state = DIFFUSING;
        }
      }
      break;
  }
}
