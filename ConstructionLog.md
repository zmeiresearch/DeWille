# This is an annotated account of the build&construction activities around DeWille

## 26-Nov-2019
*DeWille_Control_Rev_1_0* and *DAC_PCM1794_Rev1_0*, rev. #7dc6edd, sent to 
[SeeedStudio](https://www.seeedstudio.com/fusion_pcb.html) for fabrication. Total cost is $74.20:
* $4.90 for 10 pcs of DAC_PCM1794
* $49.90 for 10pcs of DeWille_Control
* $19.40 shipping

## 13-Dec-2019
Parts for first two prototypes ordered from [Comet](http://www.comet.bg) and [Mouser](http://www.mouser.bg)

## 17-Dec-2019
Parts arrived

## 02-Jan-2020
Control and DAC Boards arrived
![Bare Boards](Media/DeWille_01_BareBoards.jpg)

## 08-Jan-2020
Started soldering one Control board.

## 09-Jan-2020
One BaseBoard sent to [Selectra](http://www.selectrapcb.com) for fabrication

## 11-Jan-2020
Control board soldering complete, with the exception of the FPGA, the Si5344 and the non-washable components (SMA 
connectors and DIP switces). Applied power and verified that all supply voltages are correct. Gave a final wash
to the Control board to clean flux residue.
![Control Soldering](Media/DeWille_02_ControlSoldering.jpg)

## 12-Jan-2020
Soldered two DAC boards without the DAC chips. Applied power and verified supply voltages.
Soldered the rest of the components on the Control board.
![Control done](Media/DeWille_03_ControlDone.jpg)

## 25-Jan-2020
BaseBoard received from PCB house

## 2-Feb-2020
Soldered BaseBoard components without transformers and big filtering caps. Powered the +5V regulator from bench
supply, got +4.6V output due to error in schematic (R217/R220 divider not taken into account when calculating
reference voltage). Changed R212 to 1.5k and got +4.99V output into a 56 Ohm dummy load, verified that regulator
is stable with scope and left it for ~2 hours. With a 6.6 Ohm load(little less than 1A current) and no heat-sink,
the regulator transistor experienced a non-destructive thermal runaway (but the output voltage increased, so 
it may have potentially damaged the rest of the circuit) - probably need to reconsider the topology for later.

Because of the above, decided to use the analog supplies in capacitance multiplier mode rather than regulator, so 
removed U201, U202 and the resistors around them.
![Base test](Media/DeWille_04_BaseTest.jpg)
