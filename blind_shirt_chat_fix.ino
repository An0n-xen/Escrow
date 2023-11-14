const int trigPin0 = 4;
const int echoPin0 = 5;
const int buzz0 = 8;

const int trigPin1 = 6;
const int echoPin1 = 7;
const int buzz1 = 9;

float duration0, distance0;
float duration1, distance1;

unsigned long previousMillis0 = 0;
unsigned long previousMillis1 = 0;
unsigned long interval0 = 1000; // Default to 1 second to avoid immediate buzzing
unsigned long interval1 = 1000; // Default to 1 second to avoid immediate buzzing

bool buzzerState0 = LOW;
bool buzzerState1 = LOW;

void setup() {
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(buzz0, OUTPUT);
  digitalWrite(buzz0, LOW);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzz1, OUTPUT);
  digitalWrite(buzz1, LOW);
  
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  distance0 = getDistance(trigPin0, echoPin0);
  Serial.print("Distance0: ");
  Serial.println(distance0);
  
  distance1 = getDistance(trigPin1, echoPin1);
  Serial.print("Distance1: ");
  Serial.println(distance1);

  // Handle buzzer 0
  if (distance0 <= 50) {
    interval0 = map(distance0, 10, 150, 50, 1000);
    handleBuzzer(buzz0, previousMillis0, interval0, buzzerState0, currentMillis);
  } else {
    digitalWrite(buzz0, LOW); // Turn off buzzer if out of range
  }

  // Handle buzzer 1
  if (distance1 <= 50) {
    interval1 = map(distance1, 10, 150, 50, 1000);
    handleBuzzer(buzz1, previousMillis1, interval1, buzzerState1, currentMillis);
  } else {
    digitalWrite(buzz1, LOW); // Turn off buzzer if out of range
  }
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  return (duration * 0.0343) / 2;
}

void handleBuzzer(int buzzerPin, unsigned long &previousMillis, unsigned long interval, bool &buzzerState, unsigned long currentMillis) {
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last toggle time
    buzzerState = !buzzerState; // Toggle state
    digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
  }
}
