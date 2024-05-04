const int sensorPin1 = 8;
const int sensorPin2 = 9;
const int switchPin1 = 10;  // Digital pins
const int switchPin2 = 11;
int readPin = A3;
int voltage = 0;
float newVolts = 0;
const unsigned long lightDuration = 2000;  // Light duration in milli for 3 minutes then restart motion monitor
String msg, cmd;

unsigned long lightOnDuration = 5000;
unsigned long lastMotionTime1 = 0;
unsigned long lastMotionTime2 = 0;
bool light1IsOn = false;
bool light2IsOn = false;


void setup() {
  pinMode(switchPin1, OUTPUT);
  digitalWrite(switchPin1, LOW);  // Initialize the SSR pins as output for relay switch
  pinMode(switchPin2, OUTPUT);
  digitalWrite(switchPin2, LOW);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // To read message received from other Bluetooth Device

  if (Serial.available() > 0){ // Check if there is data coming
    msg = Serial.readString();
    Serial.println("Android Command: " + msg);
  }

  voltage = analogRead(readPin);
  newVolts = voltage * (5.0/1023.0);
  
  // Control LED in Arduino boardq
  if (msg == "<refresh>"){
    voltage = analogRead(readPin);  // read the input pin
    Serial.println("V" + String(newVolts));
    msg = ""; // reset command
  } else if (msg == "<turn on>"){
    digitalWrite(switchPin1, LOW); // Turn on LED
    Serial.println("LED is turned on\n"); // Then send status message to Android
    msg = ""; // reset command
  } else if (msg == "<turn off>") {
    digitalWrite(switchPin1, HIGH); // Turn off LED
    Serial.println("LED is turned off\n"); // Then send status message to Android
    msg = ""; // reset command
  } else if (msg == "<turn on2>") {
    digitalWrite(switchPin2, LOW); // Turn off LED
    Serial.println("LED2 is turned on\n"); // Then send status message to Android
    msg = "";
  } else if (msg == "<turn off2>") {
    digitalWrite(switchPin2, HIGH); // Turn off LED
    Serial.println("LED2 is turned off\n"); // Then send status message to Android
    msg = "";
  } else if (msg == "<motion>") {
    if (digitalRead(sensorPin1) == HIGH) {
      digitalWrite(switchPin1, LOW);
      delay(5000);
      digitalWrite(switchPin1, HIGH);
    }
    if (digitalRead(sensorPin2) == HIGH) {
      digitalWrite(switchPin2, LOW);
      delay(5000);
      digitalWrite(switchPin2, HIGH);
    }
  } else if (msg == "<manual>") {
    digitalWrite(switchPin2, HIGH);
    digitalWrite(switchPin1, HIGH);
  }
  delay(10);
}
