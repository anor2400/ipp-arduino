const int sensorPin = 2;        // Sensor inkopplad på digital pin D2
float hjulOmkrets = 2.1;        // Hjulets omkrets i meter (ändra till ditt hjul)

unsigned int varv = 0;          // Antal registrerade varv
float stracka = 0.0;            // Total sträcka i meter
float medelhastighet = 0.0;     // Medelhastighet i km/h

unsigned long startTid = 0;     // Starttid för att mäta medelhastighet
bool previousState = HIGH;      // Tidigare sensorstatus (för att upptäcka övergång från HIGH till LOW)

void setup() {
  pinMode(sensorPin, INPUT);    // Sätt sensorpinnen som ingång
  Serial.begin(9600);           // Starta kommunikation med datorn
  startTid = millis();          // Spara starttid
  Serial.println("Startar... Placerad magnet registreras som ett varv.");
}

void loop() {
  bool currentState = digitalRead(sensorPin);  // Läs av sensorns status

  // Om magneten passerar (från HIGH till LOW)
  if (previousState == HIGH && currentState == LOW) {
    varv++;
    stracka = varv * hjulOmkrets;  // Total sträcka = varv * omkrets

    // Tid i timmar
    unsigned long nuTid = millis();
    float tidIH = (nuTid - startTid) / 3600000.0; // omvandla ms till timmar

    if (tidIH > 0) {
      medelhastighet = (stracka / 1000.0) / tidIH; // i km/h
    }

    // Skriv till Serial Monitor
    Serial.print("Varv: ");
    Serial.print(varv);
    Serial.print(" | Sträcka: ");
    Serial.print(stracka, 2);
    Serial.print(" m | Snitt: ");
    Serial.print(medelhastighet, 2);
    Serial.println(" km/h");

    delay(300); // Debounce: vänta för att undvika dubbelregistrering
  }

  previousState = currentState; // Spara nuvarande sensorvärde
}

