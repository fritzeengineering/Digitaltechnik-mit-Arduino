// Arduino zur Steuerung einer Zugangskontrolle
// die Bibliothek Servo.h wird eingebunden, sie steuert den Motor
#include <Servo.h>
// der Servomotor erhält den Namen Servomotor
Servo Servomotor;

const int RFID_OK = 2;
const int CODE_OK = 3;
const int MASTER_SW = 4;
const int SERVO = 8;

void setup() 
{
  //Eingänge
  pinMode(RFID_OK, INPUT_PULLUP);
  pinMode(CODE_OK, INPUT_PULLUP);
  pinMode(MASTER_SW, INPUT_PULLUP);
  //Ausgang, Servomotor wird Pin 8 zugeordnet
  Servomotor.attach(SERVO);  
}

void loop() 
{
  bool a, b, c, q;

    a = digitalRead(RFID_OK) == LOW; 	//Eingänge einlesen 
    b = digitalRead(CODE_OK) == LOW; 
    c = digitalRead(MASTER_SW) == LOW;		//Signale verknüpfen

    q = (a && b) || c;
    // Zwischen den einzelnen Positionen gibt es eine Pause
    // Position 1 ansteuern mit dem Winkel 0°
    if(q)
    {
      Servomotor.write(0);    // Position 1 mit dem Winkel 0° ansteuern 
      delay(500);             //500ms Pause
      Servomotor.write(120);  // Position 2 mit dem Winkel 120° ansteuern 
      delay(500);             //500ms Pause
      Servomotor.write(0);    // Position 1 mit dem Winkel 0° ansteuern 
      delay(500);
    }
}
