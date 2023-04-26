# Spearhead_Ground


This repository countains code for the ground station for the Spearhead payload suite. It consists of two parts, arduino code to recieve radio signals from the rocket, and then a viewer to display the code on a graphical display.



## Serial Messages
The following section contains code pertaining to what messages will be sent over the serial channel. The message will consist of a set of tokens separated by spaces.

### First Token
0 - Everything is nomimal, a radio transmission is attached to this message 
1 - No radio transmission, exact error specified below

### Rest of Message - Nominal
Following Format Is Used (may undergo revisions) each part is separated by a space in order.
Packet Number (1 digit) - a looping number from 0-9 to so we can see if miss packets

Gravity_X (8 digits)

Gravity_Y (8 digits)

Gravity_Z (8 digits)

Accel_X (8 digits)

Accel_Y (8 digits)

Accel_Z (8 digits)

Linear_Accel_X (8 digits)

Linear_Accel_Y (8 digits)

Linear_Accel_Z (8 digits)

BMP_Altitude (8 digits)

BMP_Pressure (8 digits)

GPS_Altitute (8 digits)

Pitot_Pressure (8 digits)

Pitot_Velocity (8 digits)

Thermo_Nose_1 (8 digits)

Thermo_Nose_2 (8 digits)

Thermo_Nose_3 (8 digits)

Thermo_Nose_4 (8 digits)

Thermo_Nose_5 (8 digits)

Thermo_Nose_6 (8 digits)

Thermo_Body_1 (8 digits)


Thermo_Body_2 (8 digits)

RSSI (2 digits) - Signal Strength, negative, so closer to zero (higher) is better.

These packets plus a space digit total 202 digits (max is 250 or so)

### Rest of Message - Error
0 - No radio message recieved
1 - Radio Timeout (in effect the same as no message recieved)
2 - Radio Initialization Failed
3 - Radio Frequency Set Failed

