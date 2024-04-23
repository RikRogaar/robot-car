#include "controllers/MotorController.h"  // Include the MotorController header file

// Define MotorController objects for each motor
MotorController frontLeftMotor(2, 3);
MotorController frontRightMotor(5, 4);
MotorController backLeftMotor(7, 6);
MotorController backRightMotor(9, 8);

// Define pins for ultrasonic sensor, buzzer, and sensorPin
const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = 12;
const int sensorPin = 2;

int incomingByte = 0;  // Variable to store incoming serial data
float duration_us, distance_cm;  // Variables for ultrasonic sensor data

void setup() {
  Serial.begin(115200);  // Start serial communication
  
  // Set pin modes for ultrasonic sensor, buzzer, and sensorPin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  // Print instructions for selecting the direction of movement
  Serial.println("Select the direction of movement:");
  Serial.println("8. Forward");
  Serial.println("4. Left");
  Serial.println("6. Right");
  Serial.println("2. Backward");
  Serial.println("5. Stop");
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse
  duration_us = pulseIn(echoPin, HIGH);
  // Convert the duration to distance in centimeters
  distance_cm = 0.017 * duration_us;

  // Print distance measured by the ultrasonic sensor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Check if an obstacle is detected within 10 cm
  if (distance_cm < 10) {
    // Stop all motors and activate the buzzer
    frontLeftMotor.stop();
    frontRightMotor.stop();
    backLeftMotor.stop();
    backRightMotor.stop();
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Move all motors forward and deactivate the buzzer
    frontLeftMotor.forward();
    frontRightMotor.forward();
    backLeftMotor.forward();
    backRightMotor.forward();
    digitalWrite(buzzerPin, LOW);
  }

  // Check if serial data is available
  if (Serial.available() > 0) {
    incomingByte = Serial.read();  // Read the incoming byte

    // Switch case to handle different movement commands
    switch (incomingByte) {
      case '8':  // Move forward
        frontLeftMotor.forward();
        frontRightMotor.forward();
        backLeftMotor.forward();
        backRightMotor.forward();
        break;
      case '4':  // Turn left
        frontLeftMotor.forward();
        frontRightMotor.stop();
        backLeftMotor.stop();
        backRightMotor.stop();
        break;
      case '6':  // Turn right
        frontLeftMotor.stop();
        frontRightMotor.forward();
        backLeftMotor.stop();
        backRightMotor.stop();
        break;
      case '5':  // Stop
        frontLeftMotor.stop();
        frontRightMotor.stop();
        backLeftMotor.stop();
        backRightMotor.stop();
        break;
      case '2':  // Move backward
        frontLeftMotor.backward();
        frontRightMotor.backward();
        backLeftMotor.backward();
        backRightMotor.backward();
        break;
    }

    delay(200);  // Delay for stability
  }
}
