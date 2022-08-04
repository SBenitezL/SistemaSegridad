#include "conexiones.h"
//Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {30, 32, 34, 36}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31,33,35,37}; //connect to the column pinouts of the keypad



LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Leds
void encenderRojo()
{
  analogWrite(rojo,255);
  analogWrite(verde,0);
  analogWrite(azul,0);
}

void encenderVerde()
{
  analogWrite(rojo,0);
  analogWrite(verde,255);
  analogWrite(azul,0);
}

void encenderAzul()
{
  analogWrite(rojo,0);
  analogWrite(verde,0);
  analogWrite(azul,255);
}
void apagar()
{
  analogWrite(rojo,0);
  analogWrite(verde,0);
  analogWrite(azul,0);
}
