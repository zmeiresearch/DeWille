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


## FAQ
* **Is DeWille HiFi/Audiophile grade?**
  No. It will just sound good.
* **Where does the name DeWille come from?**
  It was inspired by a [Frey Wille](https://www.freywille.com) scharf.
