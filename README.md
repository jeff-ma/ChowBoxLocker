# ChowBoxLocker
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