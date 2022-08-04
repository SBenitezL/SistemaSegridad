+6//**
*
*/
#include "StateMachineLib.h"
#include "File_seguridad.h"
#include "fileMenuConfig.h"
#include "file_datos.h"
#include "file_mostrar_lecturas.h"
#include "conexiones.h"

void timer_pass();
AsyncTask asyncTaskPass(10,true,timer_pass);

int intentos=0;
int opcion_datos=-1;
bool primera_iteracion=true;

// State Alias
enum State
{
  PosicionA = 0,
  PosicionB = 1,
  PosicionC = 2,
  PosicionD = 3
};

// Input Alias
enum Input
{
  Reset = 0,
  Forward = 1,
  Backward = 2,
  Unknown = 3,
};

// Create new StateMachine
StateMachine stateMachine(4, 10);

// Stores last user input
Input input;

// Setup the State Machine
void setupStateMachine()
{
  // Add transitions
  stateMachine.AddTransition(PosicionA, PosicionB, []() { return input == Forward; });
  stateMachine.AddTransition(PosicionA, PosicionA, []() { return input == Reset; });

  stateMachine.AddTransition(PosicionB, PosicionA, []() { return input == Backward; });
  stateMachine.AddTransition(PosicionB, PosicionC, []() { return input == Forward; });
  stateMachine.AddTransition(PosicionB, PosicionA, []() { return input == Reset; });

  stateMachine.AddTransition(PosicionC, PosicionB, []() { return input == Backward; });
  stateMachine.AddTransition(PosicionC, PosicionD, []() { return input == Forward; });
  stateMachine.AddTransition(PosicionC, PosicionA, []() { return input == Reset; });

  stateMachine.AddTransition(PosicionD, PosicionC, []() { return input == Backward; });
  stateMachine.AddTransition(PosicionD, PosicionA, []() { return input == Reset; });

  // Add actions
  stateMachine.SetOnEntering(PosicionA, outputA);
  stateMachine.SetOnEntering(PosicionB, outputB);
  stateMachine.SetOnEntering(PosicionC, outputC);
  stateMachine.SetOnEntering(PosicionD, outputD);

  stateMachine.SetOnLeaving(PosicionA, []() {Serial.println("Leaving A"); });
  stateMachine.SetOnLeaving(PosicionB, []() {Serial.println("Leaving B"); });
  stateMachine.SetOnLeaving(PosicionC, []() {Serial.println("Leaving C"); });
  stateMachine.SetOnLeaving(PosicionD, []() {Serial.println("Leaving D"); });
}

void setup() 
{
  Serial.begin(9600);

  Serial.println("Starting State Machine...");
  setupStateMachine();  
  Serial.println("Start Machine Started");
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  pinMode(rojo,OUTPUT);
  pinMode(verde,OUTPUT);
  pinMode(azul,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  UTempHigh=EEPROM.read(addr_UTempHigh);
  UTempLow=EEPROM.read(addr_UTempLow);
  ULuz=EEPROM.read(addr_ULuz)+EEPROM.read(centenas_ULuz)*100;
  // Initial state
  stateMachine.SetState(PosicionA, false, true);
}

void loop() 
{
  // Update State Machine
  stateMachine.Update();
}

int readInput(char prm)
{
  Input currentInput = Input::Unknown;
  switch (prm)
  {
    case 'R': currentInput = Input::Reset;  break;
    case 'A': currentInput = Input::Backward; break;
    case 'D': currentInput = Input::Forward; break;
    default: break;
  }
  return currentInput;
}
// Auxiliar output functions that show the state debug
void timer_pass()
{
  unsigned long varTime = millis();
  while ((millis()-varTime)  <= 30000)
  {}
  lcd.clear();
  lcd.print("Tiempo de espera");
  lcd.setCursor(0,1);
  lcd.print("Superado");
  delay(2000);
  stateMachine.SetState(PosicionA, false, true);
}

void outputA()
{
  asyncTaskPass.Start();
  if(verificarPass())
  {
    input = static_cast<Input>(readInput('D'));
  }
  else
  {
    intentos++;
    if(intentos>2)
    {
      lcd.clear();
      lcd.print("System block");
      encenderRojo();
      delay(10000);
      intentos=0;
    }
    input = static_cast<Input>(readInput('R'));
  }
  asyncTaskPass.Reset();
  asyncTaskPass.Stop();
}

void outputB()
{
  if(!primera_iteracion)
    input = static_cast<Input>(readInput('D'));
  else if(menu())
  {
    input = static_cast<Input>(readInput('D'));
    primera_iteracion=false;
  }
  else
    input = static_cast<Input>(readInput('R'));
}

void outputC()
{
  opcion_datos=mostrarMenuDatos();
  if(opcion_datos==3)
  {
    input = static_cast<Input>(readInput('A'));
    primera_iteracion=true;
  }
  else if (opcion_datos==4)
  {
    input = static_cast<Input>(readInput('R'));
  }
  else
    input = static_cast<Input>(readInput('D'));
}

void outputD()
{
  mostrarLecturas(opcion_datos);
  input = static_cast<Input>(readInput('A'));
}
