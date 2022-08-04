#include "file_datos.h"

char frames_datos[5][16]={{"Temperatura    "},
                          {"Luz            "},
                          {"Sonido         "},
                          {"Umbrales       "},
                          {"Salir          "}};
int frame_datos=0;
int MenuItem_datos=0;
int lastMenuItem_datos= 4;


int mostrarMenuDatos()
{
  do
  {
    lcd.clear();
    imprimirFrame_datos();
    char key=leerCaracterSinImprimir();
    switch(key)
    {
      case 'A':
        if(frame_datos>0)
          frame_datos--;
        if(MenuItem_datos>0)
          MenuItem_datos--;
        break;
      case 'B':
        if(frame_datos<lastMenuItem_datos)
          frame_datos++;
        if(MenuItem_datos<lastMenuItem_datos)
          MenuItem_datos++;
        break;
      case '*':
        return MenuItem_datos;
        break;
    }
  }while(1==1);
}
void imprimirFrame_datos()
{
  lcd.clear();
  lcd.setCursor(0,0);
  if(MenuItem_datos%2==0)
  {
    lcd.print(frames_datos[frame_datos]);
    lcd.setCursor(0,1);
    lcd.print(frames_datos[frame_datos+1]);
    lcd.setCursor(15,0);
    lcd.print("<");
  }
  else
  {
    lcd.print(frames_datos[frame_datos-1]);
    lcd.setCursor(0,1);
    lcd.print(frames_datos[frame_datos]);
    lcd.setCursor(15,1);
    lcd.print("<");
  }
}
                       
