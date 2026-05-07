# SafeSplash
A project made for the Technial University of Sofia competition 2026.
# Description
A robot that follow flame/fire and extinguishes them using water. It detects the fire using IR sensors. Goes to the fire and extinguishes it using a small submersible DC Water Pump.
# Components
1. Arduino Uno R3
2. 2x 5v DC motors
3. L293D Driver
4. Jumper wires
5. 1N4007 (DO-41)
6. IRLZ44N MOSFET
7. Submersible Mini DC Water Pump 3-6V DC
8. 9V battery for powering the Arduino and all other components (without the motors).
9. 4x 1.5V batteries for powering the motors.
10. On/Off switch
11. IR flame sensor module with 5 channels
# Connections
## Connections for One IR sensor (soon to be 5)
1. digitalIR - 2
2. analogIR - A0
## Connections for Water pump
1. pumpPin - 7 (not in use right now)
## Connections for Motor 1 pins
1. ena - 5
2. in1 - 6
3. in2 - 7
## Connections for Motor 2 pins
1. enb - 10
2. in3 - 8
3. in4 - 9
# Versions
1. Version 1.0 - Works with the motors and One IR flame sensor. Doesn't use the water pump. If a flame is detected the motors spin forward.
Need to add code for stopping at wall and code for the water pump.
