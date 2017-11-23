/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
#include <Servo.h>
//#define REFERENCE_VOLTAGE 2516

Servo servo1, servo2, servo3, servo4, servo5;
   
int pos2 = 0;
int pos = 0;  
int estado = 0; // 0 para aberto; 1 para fechado
const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  //analogReference(INTERNAL2V56);
  // initialize serial communications at 9600 bps:
  servo1.attach(8);
  servo2.attach(9); 
  servo3.attach(10);
  servo4.attach(11);
  servo5.attach(12);  
  Serial.begin(9600);
  
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  
  if(sensorValue < 300){
     Serial.println("Relaxado");

     abrir();
     while(sensorValue < 300){
       sensorValue = analogRead(analogInPin);
       Serial.println(sensorValue);
     }
     
  }else{
    Serial.println("Contraido");
    
    fechar();
    while(sensorValue > 300){
       sensorValue = analogRead(analogInPin);
       Serial.println(sensorValue);
     }
    
    
  }

  
  
}

void fechar(){
  for(pos = 180; pos >= 1; pos -= 1){  
    
    servo2.write(pos);  
    servo3.write(pos); 
    servo4.write(pos); 
    
    servo1.write(180-pos);    
    servo5.write(180-pos);
    
    delay(15);                     
  } 
}

void abrir(){
  for(pos = 0; pos <= 180; pos++){  
    
    servo2.write(pos);  
    servo3.write(pos); 
    servo4.write(pos); 
    
    servo1.write(180-pos);    
    servo5.write(180-pos);
    
    delay(15);                     
  } 
}


