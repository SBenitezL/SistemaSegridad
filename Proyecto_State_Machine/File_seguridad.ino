#include "File_seguridad.h"
/**
 * @brief pass_size define the size of the password's array
 */
const int pass_size=10;
/**
 * @brief  pass Define the system password
 */
const char pass[pass_size]={'0','1','2','3','4','5','6','7','8','9'};

int pos=0;

//Pantalla
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

/**
 * @brief  contrasenia Get and save the password entered by the user
 */
char contrasenia[pass_size]={'0','0','0','0','0','0','0','0','0','0'};

/**
 * @brief leerCaracter get the character entered by the user
 * @return character entered by the user
 */

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

/**
 * @brief leerPass get characters from the user password
 */
void leerPass()
{
  for(int i=0;i<pass_size;i++)
  {
    contrasenia[i]=leerCaracter();
  }
}
/**
 * 
 */

boolean verificarCaracteres()
{
  for(int i=0;i<pass_size;i++)
  {
    if(contrasenia[i]!=pass[i])
      return false;
  }
  return true;
}


/**
 * @brief verificarCaracteres check if the password entered by the user (contrasenia) is equal to the correct password (pass)
 * @return true if equals and false if not equals
 */
bool verificarPass()
{
  boolean bandera=false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ingrese la pass");
  leerPass();
  if(verificarCaracteres())
  {
    lcd.clear();
    lcd.print("Welcome");
    encenderVerde();
    delay(1000);
    apagar();
    lcd.clear();
    return true;
  }
  else
  {
    lcd.clear();
    lcd.print("Incorrect pass");
    encenderRojo();
    delay(1000);
    apagar();
    lcd.clear();
    return false;
  }
}
