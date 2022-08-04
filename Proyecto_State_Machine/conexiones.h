#include <LiquidCrystal.h>
#include <Keypad.h>

#define rs  8
#define en  7
#define d4  5
#define d5  4
#define d6  3
#define d7  2


/*  The circuit LCD:
 * LCD VSS(1) pin to ground
 * LCD VCC(2) pin to 5V
 * LCD RS(4) pin to digital pin 8
 * LCD R/W(5) pin to ground
 * LCD Enable(6) pin to digital pin 7
 * LCD D4(11) pin to digital pin 5
 * LCD D5(12) pin to digital pin 4
 * LCD D6(13) pin to digital pin 3
 * LCD D7(14) pin to digital pin 2
 * LCD 15 pin to 5v
 * LCD 16 pin to gnd
 * 
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * 
  */
extern LiquidCrystal lcd;
extern Keypad keypad;

#include <EEPROM.h>
//Emprom
#define addr_UTempHigh 0
#define addr_UTempLow 1
#define addr_ULuz 2
#define centenas_ULuz 3

//Temperatura https://learn.sunfounder.com/lesson-10-analog-temperature-sensor-2/
#define analogPin A0 //the thermistor attach to
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistorvoid setup()

//Luz https://learn.sunfounder.com/lesson-21-photoresistor-sensor/
#define photocellPin A1

//Microfono
#define microphonePin A2

//Buzzer
#define buzzerPin 10

//RGB
#define rojo 11
#define verde 12
#define azul 13


void encenderRojo();
void encenderVerde();
void encenderAzul();
void apagar();
