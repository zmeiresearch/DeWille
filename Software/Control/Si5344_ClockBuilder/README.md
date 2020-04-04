# ClockBuilder Pro configuration project and outputs for Si5344

Use CBP to easily generate a configuration file for Si5344, export the config 
using the wizard.

Then combine two or more configs (e.g. with different clock sources) into a 
single file that can be used by DeWille firmware by executing 

```bash
python3 ./SiMerge.py Si5344_RevD_DeWille01.h Si5344-RevD-DeWille01-Registers_225792_SingleIn.h Si5344-RevD-DeWille01-Registers_24576_SingleIn.h
```
