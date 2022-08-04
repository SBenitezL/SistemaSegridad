#include "fileMenuConfig.h"

//Menu Config
int frame=0;
int MenuItem=0;
bool salir=false;
bool retorno=false;
int lastMenuItem= 7;

int UTempHigh=25;
int UTempLow=18;
int ULuz=500;
int USonido = 35;

const char frames[8][16]={{"UTempHigh      "},
                            {"UTempLow       "},
                            {"ULuz           "},
                            {"USonido        "},
                            {"Guardar        "},
                            {"Reset          "},
                            {"Siguiente      "},
                            {"Salir          "}};



char leerCaracterImprimir()
{
  char key;
  do
  {
    key = keypad.getKey();
  }
  while(key==0);
  if(key)
  {
    lcd.print(key);
  }
  return key;
}
char leerCaracterSinImprimir()
{
  char key;
  do
  {
    key = keypad.getKey();
  }
  while(key==0);
  return key;
}
bool menu()
{
  
  salir=false;
  frame=0;
  MenuItem=0;
  retorno=false;
  do
  {
    imprimirFrame();
    char key=leerCaracterSinImprimir();
    switch(key)
    {
      case 'A':
        if(frame>0)
          frame--;
        if(MenuItem>0)
          MenuItem--;
        Serial.print("Menu Item: ");
        Serial.println(MenuItem);
        Serial.print("Frame: ");
        Serial.println(frame);
        break;
      case 'B':
        if(frame<lastMenuItem)
            frame++;
        if(MenuItem<lastMenuItem)
          MenuItem++;
        Serial.print("Menu Item: ");
        Serial.println(MenuItem);
        Serial.print("Frame: ");
        Serial.println(frame);
        break;
      case '*':
        Serial.println("i'm here");
        opcion();
        break;
    }
  }while(salir==false);
  return retorno;
}



void imprimirFrame()
{
  lcd.clear();
  lcd.setCursor(0,0);
  if(MenuItem%2==0)
  {
    lcd.print(frames[frame]);
    lcd.setCursor(0,1);
    lcd.print(frames[frame+1]);
    lcd.setCursor(15,0);
    lcd.print("<");
  }
  else
  {
    lcd.print(frames[frame-1]);
    lcd.setCursor(0,1);
    lcd.print(frames[frame]);
    lcd.setCursor(15,1);
    lcd.print("<");
  }
}



void opcion()
{
  Serial.println("Entre a opcion");
  Serial.print("Menu Item: ");
  Serial.println(MenuItem);
  lcd.clear();
  switch(MenuItem)
  {
    case 0:
      UTempHigh=opcion("UTempHigh", UTempLow+3, 60, UTempHigh);
      break;
    case 1:
      UTempLow=opcion("UTempLow", 0, UTempHigh, UTempLow);
      break;
    case 2:
      ULuz=opcion("ULuz", 0, 999, ULuz);
      break;
    case 3:
        USonido=opcion("USonido", 1, 999, USonido);
        break;
  }
  if(MenuItem==4)
    guardar();
  if(MenuItem==5)
  {
      UTempHigh=25;
      UTempLow=18;
      ULuz=500;
      USonido=35;
      lcd.print("values reset");
      delay(1500);
  }
  if(MenuItem==6)
  {
    salir=true;
    retorno=true;
  }
  if(MenuItem==7)
  {
    salir=true;
    retorno=false;
  }
}


int opcion(char nombre[], int rango_low, int rango_high, int variable)
{
    lcd.setCursor(0,0);
    lcd.print(nombre);
    lcd.setCursor(12,0);
    lcd.print(variable);
    lcd.setCursor(0,1);
    lcd.print("[");
    lcd.print(rango_low);
    lcd.print(" - ");
    lcd.print(rango_high);
    lcd.print("]C: ");

    int value=armarEntero();
    if (comprobarRango(rango_low,rango_high,value))
      return value;
    return variable;
}



void guardar()
{
    if(ULuz>=100)
    {
      EEPROM.write(centenas_ULuz, trunc(ULuz/100));
      EEPROM.write(addr_ULuz, ULuz-trunc(ULuz/100)*100);
    }
    else
    {
      EEPROM.write(addr_ULuz, ULuz);
      EEPROM.write(centenas_ULuz, 0);
    }
    EEPROM.write(addr_UTempHigh, UTempHigh);
    EEPROM.write(addr_UTempLow, UTempLow);
    lcd.setCursor(0,0);
    lcd.print("values save");
    delay(1500);
    lcd.clear();
}



boolean comprobarRango(int low, int high, int value)
{
  lcd.clear();
  lcd.setCursor(0,0);
  if(value<=high && value>=low)
  {
    lcd.print("Value ");
    lcd.print(value);
    lcd.print(" save");
    delay(1500);
    return true;
  }
  lcd.print("Valor no valido");
  delay(1500);
  return false;
}

int armarEntero()
{
  int numero=-100;
  int orden=0;
  char key;
  int contador=0;
  while(contador<3)
  {
    key=leerCaracterImprimir();
    if(key=='*')
      break;
    if(contador==0)
      numero=0;
    numero=numero*10;
    numero=numero+(key-'0');
    contador++;
  }
  
  return numero;
}
