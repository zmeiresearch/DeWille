# Future changes

## DAC_PCM1794_Rev1_0
* Change SMA connector with bigger pads
* Polygon fill on the top layer (better color!)
* Add GND and power testpads

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

## DeWille_Base_Rev_1.0
* The GNDD polygon is not correctly manufactured. Check with PCB house whether
  the issue is with the gerbers or with them
* Add Silkscreen and Zmei Research logo
* Remove silkscreen from Top GND tracks separating transformers and the rest of
  the circuit
* Change big filtering capacitors to snap-in ones
* Mark R220 DNP or change R212 to 1.5k
* Add LEDs indicating power status
