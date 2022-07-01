
#include <LiquidCrystal.h>
#include <Keypad.h>

//Pantalla
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 0, en = 1, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*  The circuit:
 * LCD RS(4) pin to digital pin 0
 * LCD Enable(6) pin to digital pin 1
 * LCD D4() pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * 
  */

//Keypad
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {35,33,31}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int pos=0;

//RGB
const int rojo=8 ;
const int verde=7;
const int azul=6;


//Programa
const int pass_size=10;
char pass[pass_size]={'0','1','2','3','4','5','6','7','8','9'};
char contrasenia[pass_size]={'0','0','0','0','0','0','0','0','0','0'};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  pinMode(rojo,OUTPUT);
  pinMode(verde,OUTPUT);
  pinMode(azul,OUTPUT);
}

void loop() {
 
  // put your main code here, to run repeatedly:
  apagar();
  verificarPass();
}

char leerCaracter()
{
  char key;
  do
  {
    key = keypad.getKey();
  }
  while(key==0);
  if(key)
  {
    lcd.setCursor(pos++,1);
    lcd.print(key);
  }
  if(pos>=pass_size)
    pos=0;
  return key;
}
void leerPass()
{
  for(int i=0;i<pass_size;i++)
  {
    contrasenia[i]=leerCaracter();
  }
}
boolean verificarCaracteres()
{
  for(int i=0;i<pass_size;i++)
  {
    if(contrasenia[i]!=pass[i])
      return false;
  }
  return true;
}
void verificarPass()
{
  boolean bandera=false;
  for(int i=0;i<3;i++)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ingrese la pass");
    leerPass();
    if(verificarCaracteres())
    {
      passCheck();
      bandera=true;
      break;
    }
    else
      passWrong();
  }
  if (!bandera)
    sistemaBloqueado();
}
void passCheck()
{
    encenderVerde();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pass correcta :)");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("welcome");
    delay(10000);
}
void passWrong()
{
    encenderAzul();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pass incorrecta");
    delay(2000);
    apagar();
}
void sistemaBloqueado()
{
  encenderRojo();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sistema bloqueado");
  delay(10000);//Tiempo muerto 10 segundos
  //Secuencia de leds
}

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
  analogWrite(azul,250);
}
void apagar()
{
  analogWrite(rojo,0);
  analogWrite(verde,0);
  analogWrite(azul,0);
}
