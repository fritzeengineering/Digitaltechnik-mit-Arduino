// Arduino zur Sicherheitsverriegelung
const int E_STOP = 2;
const int SENSOR_GITTER = 3;
const int B1_HAND = 4;
const int B2_HAND = 5;
const int FREIGABE = 6;

void setup() 
{
  //Eingänge
  pinMode(E_STOP, INPUT_PULLUP);
  pinMode(SENSOR_GITTER, INPUT_PULLUP);
  pinMode(B1_HAND, INPUT_PULLUP);
  pinMode(B2_HAND, INPUT_PULLUP);
  //Ausgang
  pinMode(FREIGABE, OUTPUT); 
}

void loop() 
{
  bool es, sh, b1, b2, q;

    es = digitalRead(E_STOP) == HIGH; 	//Eingänge einlesen 
    sh = digitalRead(SENSOR_GITTER) == LOW; 
    b1 = digitalRead(B1_HAND) == LOW;		
    b2 = digitalRead(B2_HAND) == LOW;		
    q = (!es && sh && b1 && b2);    //Signale verknüpfen

    digitalWrite(FREIGABE, q ? HIGH : LOW);
    delay(100);
}
