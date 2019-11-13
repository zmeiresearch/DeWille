Requirements:
To be hand-solderable (i.e. no BGA!)
At least 70 IOs (40 IOs for 1MB/16bit RAM, 5 for MCU interface, 4 audio interfaces x 4 IOs each, 5 misc)
Development tools to be easily available.



Initial requirements opted for a much smaller pin count, as external RAM was not required. Choice went to LCMXO2-1200 in a 32-pin QFN package. It proved impossible to find any documentation listing pinouts, will all references either dead or requiring to install Lattice Diamond. 

After re-evaluating the requirements, it was decided to include an external RAM memory for a FIFO inplementation with a sufficient depth. This bumped the requirements for pin count to 70I/Os at least, as 40 extra lanes were required and requiring additional logic gates for the implementation as well. Thus, a Xilinx XC3S100 in a TQFP-100 package was selected. 

However, Spartan 3 is supported only by ISE 14.7, which, in turn is not supported on Win10. All the parts that are supported by the newer toolset appear to be BGA, bringing back the preference to Lattice (Intel out of question due to bad sentiment). So far, LFXP2-8E-5TN144C seems to be the winner, offering a good balance between logic density, timing and price
