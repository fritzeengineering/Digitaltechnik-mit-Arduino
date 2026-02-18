const int BTN_EG = 2;
const int BTN_1OG = 3;
const int BTN_2OG = 4;

const int LED_EG = 5;
const int LED_1OG = 6;
const int LED_2OG = 7;
const int LED_DOOR = 8;

int currentFloor = 0; // 0 = EG, 1 = 1.OG, 2 = 2.OG

void setup() {
  pinMode(BTN_EG, INPUT_PULLUP);
  pinMode(BTN_1OG, INPUT_PULLUP);
  pinMode(BTN_2OG, INPUT_PULLUP);

  pinMode(LED_EG, OUTPUT);
  pinMode(LED_1OG, OUTPUT);
  pinMode(LED_2OG, OUTPUT);
  pinMode(LED_DOOR, OUTPUT);

  showFloor(currentFloor);
}

void loop() {
  int targetFloor = 0;

  // Eingaben prüfen
  if (digitalRead(BTN_EG) == LOW)
  {
    targetFloor = 0;
  } 

  if (digitalRead(BTN_1OG) == LOW) 
  {
    targetFloor = 1;
  }

  if (digitalRead(BTN_2OG) == LOW) 
  {
    targetFloor = 2;
  }

  // Aufzug bewegen
  if (currentFloor < targetFloor) {
    moveUp();
  } else if (currentFloor > targetFloor) {
    moveDown();
  } else {
    // Ziel erreicht → Tür öffnen
    digitalWrite(LED_DOOR, HIGH);
    delay(2000);
    digitalWrite(LED_DOOR, LOW);
  }
}

void showFloor(int floor) {
  switch(floor)
  {
      case 0:
      {
        digitalWrite(LED_EG, HIGH);
      }
      break;

       case 1:
      {
        digitalWrite(LED_1OG, HIGH);
      }
      break;

       case 2:
      {
        digitalWrite(LED_2OG, HIGH);
      }
      break;

  }
}

void moveUp() {
  currentFloor++;
  showFloor(currentFloor);
  delay(1500); // Fahrzeit
}

void moveDown() {
  currentFloor--;
  showFloor(currentFloor);
  delay(1500); // Fahrzeit
}
