# Future changes

## DAC_PCM1794_Rev1_0
* Change SMA connector with bigger pads
* Polygon fill on the top layer (better color!)
* Add GND and power testpads
* Consider strategic cuts in the GND polygon to separate GND current glow

## DeWille_Control_Rev_1_0
* Change SMA connector with bigger pads
* Use logo with silk-screen
* Add bottom silk screen
* Remove mask at bottom layer of Si5344
* Align GND bottom left testpad silk
* Polygon fill on the top layer (better color!)
* Change footprint for 2.5x2 oscillators for better solderability
* Change footprint for Si5344 to have longer pads
* Increase via diameter below Si5344
* Add silk text to the two TH testpads - 3.3 and far right GND
* Switch to 30pin ESP32 DevKit
* Add a protection diode + jumper for ESP32. Current ESP board connects Vin
  directly to Vusb, which is convenient during development, allowing stand-
  alone operation, but may possibly damage board and/or computer if power
  is applied on both sides
* Move nCS_FPGA and FGPA_DONE away from the UART0 pins
* Check why RX LED is on when the ESP is transmitting and vice versa
* Increase resistors on Green LEDs
* Move FPGA (and maybe the clock as well) to the other SPI bus so that 
  hardware SPI CS can be used
* Fix the ESP32 symbols mix-up (pin25 duplicated, 36 missing)
* Route nINTR Si5344 output to ESP32 so that status polling is not needed
* Make the Clock chip and power supply heat-sinks larger

## DeWille_Base_Rev_1.0
* The GNDD polygon is not correctly manufactured. Check with PCB house whether
  the issue is with the gerbers or with them
* Add Silkscreen and Zmei Research logo
* Remove silkscreen from Top GND tracks separating transformers and the rest of
  the circuit
* Change big filtering capacitors to snap-in ones
* Mark R220 DNP or change R212 to 1.5k
* Add LEDs indicating power status
