______      _                    ______ _    ____  ___
| ___ \    | |                   | ___ \ |  | |  \/  |
| |_/ /___ | |_ __ _ _ __ _   _  | |_/ / |  | | .  . |
|    // _ \| __/ _` | '__| | | | |  __/| |/\| | |\/| |
| |\ \ (_) | || (_| | |  | |_| | | |   \  /\  / |  | |
\_| \_\___/ \__\__,_|_|   \__, | \_|    \/  \/\_|  |_/
                           __/ |                      
                          |___/                       
					by Jakub Dylag

README

  Rotary PWM is avr software designed to assist with pwm electronics development.
  The software is desgined for use with the Microchip at90usb1286 8-bit AVR microcontroller, 
  as well as the La Fortuna board made by the University of Southampton.

USAGE

  The rotary switch on the La Fortuna can be adjusted to increase or decrease the duty cycle of the pwm signal.
  Frequency of the pwm is set to be 488Hz (8000000 clock speed / 64 pre scaler * 256).
  PWM signal is outputted both to the inbuild LED on pin PB7 as well as the IO pin PD0.
  Plug in any motor controller, LED or other pwm compatible devices to ping PD0, and the GND pin next to it.

INSTALL

  1. Downloading, and unzip files from:
  	https://github.com/JakubDylag/RotaryPWM-LaFortuna-at90usb1286/
  
  2. install the following programs: GNU make, avr-gcc, dfu-programmer.
  
  3. Run the following commands in the termnial to build and upload the program to the at90usb1286:
	
	make build
	make upload
	make clean

DEBUG

  Another script can be run to test AVR microcontroller PWM functionality, as well as the inbuild LED.
  1. replace the pwm.c with pulsingLED.c, making sure to save pwm.c outside of the folder
  2. re run the installation instructions

CONTACT
  
  email: jd8g19@soton.ac.uk


