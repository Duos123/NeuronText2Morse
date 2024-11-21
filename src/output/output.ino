const int sensorPin1 = A6; // Erster Lichtsensor an Pin A6
const int sensorPin2 = A7; // Zweiter Lichtsensor an Pin A7
int sensorValue1 = 0;      // Variable für den gelesenen Wert des ersten Sensors
int sensorValue2 = 0;      // Variable für den gelesenen Wert des zweiten Sensors
float smoothedValue1 = 0;  // Geglätteter Wert des ersten Sensors
float smoothedValue2 = 0;  // Geglätteter Wert des zweiten Sensors
const int smoothingFactor = 10; // Anzahl der Werte für den gleitenden Durchschnitt

void setup() {
  Serial.begin(9600); // Seriellen Monitor starten
  pinMode(sensorPin1, INPUT); // Ersten Sensor-Pin als Eingang definieren
  pinMode(sensorPin2, INPUT); // Zweiten Sensor-Pin als Eingang definieren
  Serial.println("Time(ms),Voltage1(V),Voltage2(V)"); // Header für CSV-Datei
}

void loop() {
  // Werte von den Sensoren lesen (0-1023)
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);

  // Gleitenden Durchschnitt berechnen
  smoothedValue1 = (smoothedValue1 * (smoothingFactor - 1) + sensorValue1) / smoothingFactor;
  smoothedValue2 = (smoothedValue2 * (smoothingFactor - 1) + sensorValue2) / smoothingFactor;

  // Spannungen berechnen (bei einem 10-Bit-ADC und 5V Versorgung)
  float voltage1 = smoothedValue1 * (5.0 / 1023.0);
  float voltage2 = smoothedValue2 * (5.0 / 1023.0);

  // Zeitstempel und Spannungen ausgeben (CSV-Format)
  unsigned long currentTime = millis();
  Serial.print(currentTime); 
  Serial.print(",");
  Serial.print(voltage1, 3); // Voltage1 auf 3 Dezimalstellen
  Serial.print(",");
  Serial.println(voltage2, 3); // Voltage2 auf 3 Dezimalstellen

  delay(10); // Kleines Delay für bessere Darstellung (10 ms)
}
