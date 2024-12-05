const int sensorPin2 = A6; // Dot . Pin A6
const int sensorPin1 = A7; // Dash - Pin A7
volatile unsigned long pulseCount1 = 0;
volatile unsigned long pulseCount2 = 0;
unsigned long startTime = 0;
float frequency1 = 0;
float frequency2 = 0;

unsigned long dotMillis = 0;
unsigned long dashMillis = 0;
unsigned long charMillis = 0;



const long dotTime = 2000;
const long dashTime = 5000;
const long charTime = 5000;


String morseChar = "";



void setup() {
  pinMode(sensorPin1, INPUT);  // Signal-Eingang
  attachInterrupt(digitalPinToInterrupt(sensorPin1), countPulse1, RISING);  // Interrupt bei steigender Flanke
  pinMode(sensorPin2, INPUT);  // Signal-Eingang
  attachInterrupt(digitalPinToInterrupt(sensorPin2), countPulse2, RISING);  // Interrupt bei steigender Flanke
  Serial.begin(9600);
  startTime = millis();
}

void loop() {
  if (millis() - startTime >= 1000) {  // Frequenz über 1 Sekunde messen
    noInterrupts();  // Zählsperre für konsistente Werte
    frequency1 = pulseCount1;  // Kopiere Pulsanzahl
    pulseCount1 = 0;  // Zähler zurücksetzen
    frequency2 = pulseCount2;  // Kopiere Pulsanzahl
    pulseCount2 = 0;  // Zähler zurücksetzen
    interrupts();  // Interrupts wieder aktivieren
    unsigned long currentMillis = millis();


    if(frequency1 > 100 && currentMillis - dotMillis >= dotTime) {
      dotMillis = currentMillis;
      charMillis = currentMillis;  
    
      morseChar += ".";
      //Serial.println(morseChar);
    }

    if(frequency2 > 150 && currentMillis - dashMillis >= dashTime) {
      dashMillis = currentMillis;
      charMillis = currentMillis; 

      morseChar += "-";
      //Serial.println(morseChar);
    }


    if(currentMillis - charMillis >= charTime) {
      charMillis = currentMillis;
      
      //Serial.print("Zeichen: ");
      Serial.print(getMorseChar(morseChar));
      morseChar = "";
    }

    startTime = millis();  // Startzeit aktualisieren
  }
}

void countPulse1() {
  pulseCount1++;  // Pulse zählen
}

void countPulse2() {
  pulseCount2++;  // Pulse zählen
}

// Funktion zur Dekodierung von Morsezeichen
char getMorseChar(String morse) {
  if (morse == ".-") return 'A';
  if (morse == "-...") return 'B';
  if (morse == "-.-.") return 'C';
  if (morse == "-..") return 'D';
  if (morse == ".") return 'E';
  if (morse == "..-.") return 'F';
  if (morse == "--.") return 'G';
  if (morse == "....") return 'H';
  if (morse == "..") return 'I';
  if (morse == ".---") return 'J';
  if (morse == "-.-") return 'K';
  if (morse == ".-..") return 'L';
  if (morse == "--") return 'M';
  if (morse == "-.") return 'N';
  if (morse == "---") return 'O';
  if (morse == ".--.") return 'P';
  if (morse == "--.-") return 'Q';
  if (morse == ".-.") return 'R';
  if (morse == "...") return 'S';
  if (morse == "-") return 'T';
  if (morse == "..-") return 'U';
  if (morse == "...-") return 'V';
  if (morse == ".--") return 'W';
  if (morse == "-..-") return 'X';
  if (morse == "-.--") return 'Y';
  if (morse == "--..") return 'Z';
  if (morse == ".....") return ' ';
  return '\0'; // Rückgabe eines Nullzeichens, falls kein passendes Morsezeichen gefunden wurde
}


