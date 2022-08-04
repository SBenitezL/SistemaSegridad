#include "file_mostrar_lecturas.h"

#define muestra 37
AsyncTask asyncTaskTemp(1000,true,read_temperature);
AsyncTask asyncTaskPhoto(1000,true,read_photoresistor);
AsyncTask asyncTaskMicro(100,true,read_microphone);

bool mostrar_salir=false;

void mostrarLecturas(int lectura)
{
  mostrar_salir=false;
  lcd.clear();
  char key = 0;
  int contador=0;
  switch(lectura)
  {
    case 0:
      asyncTaskTemp.Start();
      break;
    case 1:
      asyncTaskPhoto.Start();
      break;
    case 2:
      asyncTaskMicro.Start();
      break;
  }
  while(key==0 and mostrar_salir==false)
  {
    switch(lectura)
    {
      case 0:
        asyncTaskTemp.Update();
        break;
      case 1:
        asyncTaskPhoto.Update();
        break;
      case 2:
        asyncTaskMicro.Update();
        break;
    }
    key = keypad.getKey(); 
  }
  asyncTaskTemp.Stop();
  asyncTaskPhoto.Stop();
  asyncTaskMicro.Stop();
}

void read_temperature()
{
  lcd.clear();
  apagar();
  //read thermistor value
  long a =0.0;
  //the calculating formula of temperature
  float tempC = 0.0;
  for(int i=0;i<muestra;i++)
  {
    a=1023.0 - analogRead(analogPin);
    tempC+=beta /(log((1025.0 * 10.0 / a - 10.0) / 10.0) + beta / 298.0) - 273.0;
  }
  tempC=tempC/muestra;
  
  Serial.print(millis()/1000);
  Serial.print(",read_temp,");
  Serial.println(tempC);
  if(tempC<UTempLow)
    encenderAzul();
  else if(tempC>UTempHigh)
    encenderRojo();
  else
    encenderVerde();
  
  lcd.print("Temp: ");
  lcd.print(tempC);
}
void read_photoresistor()
{
  lcd.clear();
  long photo_value = 0.0;
  for(int i=0;i<muestra;i++)
  {
    photo_value += analogRead(photocellPin);
  }
  photo_value=photo_value/muestra;
  
  if(photo_value>=ULuz)
  {
    lcd.print("Umbral superado");
    unsigned long varTime = millis();
    while ((millis()-varTime)  <= 3000)
    {
      Serial.print("varTime: ");
      Serial.println(varTime);
      Serial.print("millis: ");
      Serial.println(millis());
      pitar();
    }
    mostrar_salir=true;
  }
  Serial.print(millis()/1000);
  Serial.print(",read_photo,");
  Serial.println(photo_value);

  lcd.print("Luz: ");
  lcd.print(photo_value);
}
void read_microphone()
{
  lcd.clear();
  apagar();
  long noise_value = 0.0;
  for(int i=0;i<muestra;i++)
  {
    noise_value += analogRead(microphonePin);
  }
  noise_value=noise_value/muestra;
  
  if (noise_value>=USonido)
  {
    encenderAzul();
  }
  Serial.print(millis()/1000);
  Serial.print(",read_noise,");
  Serial.println(noise_value);
  lcd.print("Sonido: ");
  lcd.print(noise_value);
}
void pitar()
{
  for(int i =0;i <= 8;i++) //frequence loop from 200 to 800
  {
    tone(buzzerPin,500,100); //turn the buzzer on
  }
}
