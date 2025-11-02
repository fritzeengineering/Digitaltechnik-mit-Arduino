// Wahlfreie Schaltstelle
const int S1_IN = 2;
const int S2_IN = 3;
const int S3_IN = 4;
const int Y_OUT = 8;

void setup() 
{
  //Eingänge
  pinMode(S1_IN, INPUT_PULLUP);
  pinMode(S2_IN, INPUT_PULLUP);
  pinMode(S3_IN, INPUT_PULLUP);
  //Ausgang, Servomotor Pin 8 
  pinMode(Y_OUT, OUTPUT);
}

void loop() 
{
  bool s1, s2, s3, y;

    s1 = digitalRead(S1_IN) == LOW; 	//Eingänge einlesen 
    s2 = digitalRead(S2_IN) == LOW; 
    s3 = digitalRead(S3_IN) == LOW;		//Signale verknüpfen

    y = (s1 && !s2 && !s3) || (!s1 && s2 && !s3) || (!s1 && !s2 && s3) || (s1 && s2 && s3);
    // Zwischen den einzelnen Positionen gibt es eine Pause
    // Position 1 ansteuern mit dem Winkel 0°
    digitalWrite(Y_OUT, y ? HIGH : LOW);	
}
