Features:
- PCM1792 w/MCU control
- Volume control through PCM1792 internal attenuator
- I2S Input
- S/PDIF optical and coax input
- Optional DSD interface
- Mono mode
- NOS/No-NOS selectable in HW or SW
- PCM1792 fully isolated from digital section
- Space for IV converter
- Optional display interface (graphical?)
- Iref by CCS
- Signal processing via an FPGA w/ dedicated memory - implement reclocking/fifo



Random notes:
1792/1794 uses SCLK for internal processing purposes. Hence BCK jitter is not 
that important, at least in non-NOS mode. 
