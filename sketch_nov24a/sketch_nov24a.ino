const int sensorPin1 = A6; // Erster Lichtsensor an Pin A6
const int sensorPin2 = A7; // Zweiter Lichtsensor an Pin A7
volatile unsigned long pulseCount1 = 0;
volatile unsigned long pulseCount2 = 0;
unsigned long startTime = 0;
float frequency1 = 0;
float frequency2 = 0;


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


    if(frequency1 > 250) {

      Serial.println(".");
      // Hier Delay
    }

    if(frequency2 > 250) {
      Serial.println("-");
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

