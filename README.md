# Adafruit sht31-d for Raspberry PI #

## Referance material ##

https://www.kernel.org/doc/Documentation/i2c/dev-interface

https://github.com/adafruit/Adafruit_SHT31

https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/Humidity_and_Temperature_Sensors/Sensirion_Humidity_and_Temperature_Sensors_SHT3x_Datasheet_digital.pdf
 
 
### Enable i2c on the PI in the usual way ###

-     Run raspi-confid -> select enable i2c

     -- or --

-     This is for raspbian jessie, wheezy is different.

-     edit /etc/modules and add

-     i2c-bcm2708

-     ic2-dev

-     edit /boot/config and add

-     dtparam=i2c_arm=on

-     dtparam=i2c1_baudrate=100000   <-  This is default, remove 1 zero for this sht31 implimentation to work.
 
## Prerequisites ##
 
This sh131 implimentation depends on i2c dev lib

- sudo apt-get install libi2c-dev
 
Below is also a good one to have while debugging, but be careful i2cdump from the below cause the sht31 interface to become unstable for me and requires a hard-reset to recover correctly.

- sudo apt-get install i2c-tools
 
on PI make sure below 2 commands are in /boot/config.txt

- dtparam=i2c_arm=on

- dtparam=i2c1_baudrate=10000

I know we are slowing down the baurate from optimal, but it seems to be the most stable setting in my testing. add another 0 to the above baudrate for max setting, ie dtparam=i2c1_baudrate=100000
