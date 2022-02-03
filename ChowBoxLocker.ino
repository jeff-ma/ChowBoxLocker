/*
ChowBox locker program:

This program allows the operation of LCD screen, solenoid door lock, and door actuator. It receives user input from
a bluetooth controller app and allows the locker to be opened.

Quick specs of locker box:

-12volt connected items
battery pack(10 AA batteries)
door actuator
solenoid door lock
led light
temperature display in celsius
temperature controller in celsius
2 flat heating elements

-5volt connected items
battery pack(5 AAA batteries)
Arduino Uno board
1602 LCD screem
10k potentiometer
HC-05 bluetooth module

Installation of BTcontrol.apk file on an Android compatible device with bluetooth is required for pairing and control
of the HC-05 bluetooth module. The app has a password input field along with two buttons below it with the commands 
of "open door" and "close door". The user must input the correct password along with pushing the "open door" button
in order for the locker to open. The "close door" button command is not used since the door can only be closed by hand. 
But it allows locker customization if a linear actuator were to be used instead. When the door is commanded open the 
app sends a string which contains a command + "=" + password example: "open=1234"  where "open" is the command "=" is
the separator and "1234" is the password. This program will then handle the input and determine what action to perform.

*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // LCD pin assignments
String input = ""; // Input received from the bluetooth controller app
String command = ""; // Command to open door(or close door if a linear actuator is used)
String value = ""; // Password receieved from user
String password = "7219";  // 4 digit password to open door
String message = "Food ready"; // Initial message for LCD screen
boolean inputComplete = false;
int lock = 2; // Pin number for lock wire
int actuator = 3; // Pin number for actuator wire

void setup() {
  // Start serial connection
  Serial.begin(9600); // Baud rate for HC-05 bluetooth transceiver module
  pinMode(lock, OUTPUT);
  pinMode(actuator, OUTPUT);
  // Initialize 1602 LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.print("Initializing");
  delay(3000);
  lcd.clear();
  lcd.print(message);
}

void loop() {
  lcd.clear();
  lcd.print(message);
  if (inputComplete) {
    int index = input.indexOf('=');
    if (index > -1) {
      command = input.substring(0, index); // Command to open door(or close door if a linear actuator is used)
      value = input.substring(index + 1, input.length() - 1);
      if (password.equals(value) && (command == "OPEN")) { // Send thank you message and open door
        lcd.clear();
        lcd.print("Thank you");
        delay(300);
        openDoor();
        Serial.println("Door open"); // Send message back to mobile device
        delay(3000);
        message = "Box available";
      } else { // Send an incorrect password message
        Serial.println(" Incorrect password");
        lcd.clear();
        lcd.print("Incorrect");
        lcd.setCursor(0, 1);
        lcd.print("password");
        delay(3000);
        lcd.print(message);
      }
    }
    // Clear input for next loop
    input = "";
    inputComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) { // Read each character from serial to create the input
    char character = (char)Serial.read();
    input = input + character;
    // Smartphone app appends a newline character to the end of the sent input which signals end of input
    if (character == '\n' || character == '\r') {
      inputComplete = true;
    }
  }
}

void openDoor() {
  // In order for door to open, lock must be retracted first before actuator can push door open
  digitalWrite(lock, HIGH);
  delay(100);
  digitalWrite(actuator, HIGH);
  delay(500);
  digitalWrite(lock, LOW);
  digitalWrite(actuator, LOW);
}
