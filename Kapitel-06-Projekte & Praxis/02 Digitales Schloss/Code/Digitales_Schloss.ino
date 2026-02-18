const int buttonPins[] = {2, 3, 4};   // Taster an Pins 
const int ledPin = 8;                 
int sequence[] = {0, 2, 1};           
// LED als Schloss-Ausgang 
// Richtige Reihenfolge: Taster 0->2->1 
int seqLength = 3;                     
int progress = 0;                      
 
void setup() { 
  for (int i=0; i<3; i++) { 
    pinMode(buttonPins[i], INPUT_PULLUP); 
  } 
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW); 
} 
 
void loop() { 
  for (int i=0; i<3; i++) { 
    if (digitalRead(buttonPins[i]) == LOW) { // Taster gedrückt 
      delay(200); // Entprellen 
      if (i == sequence[progress]) { 
        progress++; 
        if (progress == seqLength) { 
          digitalWrite(ledPin, HIGH); // Schloss geöffnet 
          progress = 0; // zurücksetzen 
        } 
      } else { 
        progress = 0; // falsche Taste -> Reset 
        digitalWrite(ledPin, LOW); 
      } 
      while (digitalRead(buttonPins[i]) == LOW); // warten bis losgelassen 
    } 
  } 
}
