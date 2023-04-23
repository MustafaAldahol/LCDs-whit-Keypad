# LCDs-whit-Keypad
this repo has code and simulation for dealing with Keypad and LCDs over I2c communication. 

you can put any number of lcd you want in range between 1 ==> 8

try it by copy lcd & PCF8574 chip block, and connect them to I2c bus as shown in proteus simulation

the limitation of LCDs number due to address limitation on chip

address created based on A0 A1 A2 connection status and based on the chip itself, this an example below:
A2 A1 A0 in PCF8574 chip
0  0  0 => 0x20
0  0  1 => 0x21
0  1  0 => 0x22
0  1  1 => 0x23
1  0  0 => 0x24
1  0  1 => 0x25
1  1  0 => 0x26
1  1  1 => 0x27
