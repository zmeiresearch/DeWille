# DeWille - A modular Audio DAC platform

DeWille is designed to be a set of building blocks for audio DACs. Currently, the following 'blocks' are planned:
* A Base board - Power supplies, interconnects, physical board support
* A Control board - Input selection, reclocking, other digital signal processing
* A PCM1792 DAC board
* An I/V converter board


## Features:
### Inputs/Outputs and interface
* Supports multiple input and output formats:
  * I2S, Left-justified and right-justified PCM
  * S/PDIF, optical and coaxial
  * (Maybe) DSD
* Supports at least 24-bit@192kHz
* Configurable asynchronous reclocking with a FIFO
* Provision for USB support based on either XMOS or Amanero COTS board 
* Provision for Bluetooth audio support
* Provision for playback via WiFi
* Provision for an (oled?) display

### Analog side
* DAC section based on PCM1792
* Supports DAC Mono mode
* Supports PCM1792(4) in NOS mode (inspired by DDAC)
* CCS for PCM1792 Iref
* Supports multiple I/V Converters
* Low-noise power supply for both analog and digital sections

## Design considerations

### Control board
The control board is by far the most complex one in the set. It implements input selection, reclocking as well as all
the signal conversion and processing required to drive the DACs. Several distinct components work together to do this 
- an FPGA, a clock generator block and an MCU module. All the blocks are connected to each other via an SPI bus, with 
the MCU acting as master. The SPI bus also connects to the two DAC boards, allowing on-the-fly reconfiguration as 
required.

#### Hardware Design
* **FPGA**
The FPGA is the one actually doing all the signal manipulation and transformation work. It takes I2S data (PCM and DSD
planned for the future), does the actual reclocking (if told to do so) and outputs I2S (DSD planned for the future) to
the two separate DAC board.

The choice of an FPGA has been a difficult one. First and foremost, an SMD(QFP) package is a must. I have no problem
hand-soldering 0402 components, but I have neither the equipment nor the expertise to handle BGAs reliably. This 
alone limits the choice to basically Xilinx Spartan 3 and some Lattice families. (Intel and Microchip not considered
for different reasons). With ISE 14.7 the last one supporting Spartan 3 and the family NRND for new designs in general
I settled on Lattice, LFXP2-8E-5TN144 in particular. MachXO2 is also an option for a future redesign.

There is an on-board 8-bit wide SRAM chip, with a maximal capacity of 8MBit. Possiblity for a future update is either 
increasing the SRAM size (larger buffer) or increasing the datapath width (better throughput/lower latency).

The FPGA can also be programmed and debugged using the integrated FT2232 interface or the standard Lattice JTAG
connector. If using the FT2232, the second channel is connected to two FPGA pins that could implement a debug UART.

* **Clock generator**
The clock generator block is implemented with two oscillators (at 24.576MHz and 22.5792MHz) and an Si5344 multiplexer,
jitter reduction and clock output buffer circuit. Two of the clock outputs go directly to the DAC boards via either 
the pin header or a dedicated SMA interconnect, while the third is distributed to the FPGA to drive the reclocking 
internally. This clock arrangement is guaranteed to introduce a phase margin between the master clock and the bit/data
clock, but the PCM1794(2) and, in theory, all other DACs that require a System/Master clock do not need a specific 
relation between the two, as long as it remains a fixed one.
Regular oscillators are used rather than TCXOs because the actual frequency and long term drift are not that important 
to the sound quality and the Si5344 performance dominates the short-term jitter performance 

Possibility for a future enchancement is to also route the SCK input from the two I2S inputs to the remaining two
Si5344 inputs to allow source-synchronous operation as well.

* **MCU**
A ESP32-DevKit module was selected for the main MCU. The rationale to use an off-the-shelf MCU module is two-fold.
_First,_ by using an COTS hardware module with a well-established and easy to use software ecosystem behind it, I'll
be able to focus on the signal processing part of the project.
_Second,_ it will be much easier to implement other functionality in the future - OTA updates, including the FPGA 
bitstream, WiFi streaming, Alexa/Google home integration, etc.

* **Power Supply**
The control board takes a single, 5V regulated power supply. There is an on-board protection by means of a polyfuse
and a 6.8V Transil. This is powering a total of 6 voltage regulators:
  * +3V3_IO and +3V3_FPGA -  used for FPGA I/O ports, Debug/Program USB and on-board LEDs
  * +1V2_FPGA - FPGA Core supply
  * +3V3_CLKOUT - Clock outputs of Si5344
  * +3V3_VDDACLK and +1V8VDDCLK - analog and digital sections of Si5344 respectively
  * +3v3_VDDOSC - the two crystal oscillators
  * The on-module voltage regulator in the ESP32 module.

### DAC PCM1794(2)

### Base Board
The base board is responsible for physically carying the different modules together, connecting them electrically and
providing all the required power supplies. In addition, it implements input signal galvanic isolation to limit the harm
in case of failure of signal sources.

* **Power supply**
The base board takes a 220/110VAC mains supply and has two separate sets of transformers. Either 50VAC toroidal power
transformers or PCB-mounted sealed ones can be used. One of the transformers is providing the +5V regulated supply
necessary for the digital part of the schematic, while the other provides a +/- 15V supply.

All three +5V power supplies are filtered and regulated using a hybrid capacitance multiplier/regulator circut. In
addition, there are also two 3.3V regulators for the input galvanic isolators - an LDO for the 'in' side and a 
DC-DC for the 'out' side.

### I to V module
**WiP/TBD.** Assumed to have the same dimensions as the DAC module while creating the Base board.

## FAQ
* **Is DeWille HiFi/Audiophile grade?**
  No. It will just sound good.
* **Where does the name DeWille come from?**
  It was inspired by a [Frey Wille](https://www.freywille.com) scharf that happened to be around while thinking about
  a name for the project.

