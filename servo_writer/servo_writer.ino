
#include <Servo.h>

int servoPin1 = 9;
int servoPin2 = 7;
int servoPin3 = 5;

Servo servo1;
Servo servo2;
Servo servo3;

int servoValues[3] = {90, 70, 90};
char buffer[64];

String readString;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(7);
  servo3.attach(5);
  Serial.println("Servo is ready");

  servo1.write(servoValues[0]);
  delay(3);
  servo2.write(servoValues[1]);
  delay(3);
  servo3.write(servoValues[2]);
}

void loop()
{
  if (!Serial.available()) {
    return;
  }
  while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill 
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    } 
  }
  int old1 = servoValues[0];
  int old2 = servoValues[1];
  int old3 = servoValues[2];
  parseValues();
  readString = "";

  if (old1 != servoValues[0] && old3 != servoValues[2]) {
    servo1.write(servoValues[0]);
    delay(3);
    servo2.write(servoValues[1]);
    delay(3);
    servo3.write(servoValues[2]);
  } else {
   Serial.println("Servo1");
   writeServo(servo1, old1, servoValues[0]);
   Serial.println("Servo2");
   writeServo(servo2, old2, servoValues[1]);
   Serial.println("Servo3");
   writeServo(servo3, old3, servoValues[2]); 
  }
  Serial.println("Done");
}

void writeServo(Servo servo, int oldValue, int newValue) {
  Serial.println(oldValue);
  Serial.println(newValue);
  if (oldValue < newValue) {
    for (int i = oldValue; i <= newValue; i++) {
      servo.write(i);
      delay(30);
    }
  } else {
    for (int i = oldValue; i >= newValue; i--) {
      servo.write(i);
      delay(30);
    }
  }
}
void parseValues() {
  int str_len = readString.length() + 1; 
  readString.toCharArray(buffer, str_len);
  char* value = strtok(buffer, ",");
  readString = "";
  int i = 0;
  while(value) {
    servoValues[i] = String(value).toInt();
    i++;
    value = strtok(NULL, ",");
  }
}
