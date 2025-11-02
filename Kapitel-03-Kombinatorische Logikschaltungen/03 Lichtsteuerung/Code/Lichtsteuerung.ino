// Arduino zur Lichtsteuerung
const int SCHALTER = 2;
const int MOV_SENS = 3;
const int LICHT_SENS = 4;
const int LAMPE = 5;

void setup() 
{
  //Eingänge
  pinMode(SCHALTER, INPUT_PULLUP);
  pinMode(MOV_SENS, INPUT_PULLUP);
  pinMode(LICHT_SENS, INPUT_PULLUP);
  //Ausgang
  pinMode(LAMPE, OUTPUT); 
}

void loop() 
{
  bool a, b, c, q;

    a = digitalRead(SCHALTER) == LOW; 	//Eingänge einlesen 
    b = digitalRead(MOV_SENS) == LOW; 
    c = digitalRead(LICHT_SENS) == LOW;		
    q = (a || b) && !c;                  //Signale verknüpfen

    digitalWrite(LAMPE, q ? HIGH : LOW);
}
