EESchema Schematic File Version 4
LIBS:DeWille_Control-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 7500 4300 2    50   Output ~ 0
~CS_DACL~
Text HLabel 7500 4100 2    50   Output ~ 0
~CS_DACR~
Text HLabel 4650 4500 0    50   Output ~ 0
~CS_FPGA~
Text HLabel 7500 3900 2    50   Output ~ 0
~CS_CLK~
Text HLabel 7500 3800 2    50   Output ~ 0
~RST_CLK~
Text HLabel 7500 4200 2    50   Output ~ 0
~RST_DACL~
Text HLabel 7500 4000 2    50   Output ~ 0
~RST_DACR~
Text HLabel 4650 3900 0    50   Output ~ 0
TX
Text HLabel 4650 3800 0    50   Input ~ 0
RX
Text HLabel 4650 4100 0    50   Output ~ 0
SCLK
Text HLabel 4650 4800 0    50   Output ~ 0
MOSI
Text HLabel 4650 4200 0    50   Input ~ 0
MISO
Wire Wire Line
	5050 4100 4650 4100
Wire Wire Line
	5050 4200 4650 4200
Wire Wire Line
	5050 4800 4650 4800
Wire Wire Line
	4650 3800 5050 3800
Wire Wire Line
	5050 3900 4650 3900
$Comp
L Zmei_elements:ESP32DevKit U301
U 1 1 5E265BB1
P 6050 4100
F 0 "U301" H 6025 5215 50  0000 C CNN
F 1 "ESP32DevKit" H 6025 5124 50  0000 C CNN
F 2 "Zmei_Footprints:ESP32DevKit" H 5950 2850 50  0001 C CNN
F 3 "https://www.aliexpress.com/item/32992390199.html?spm=a2g0s.9042311.0.0.23c84c4dkfKnQl" H 5150 5400 50  0001 C CNN
	1    6050 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 3600 7200 3600
$Comp
L power:GND #PWR?
U 1 1 5E26E263
P 7200 5150
AR Path="/5DD2C0D9/5E26E263" Ref="#PWR?"  Part="1" 
AR Path="/5E26E263" Ref="#PWR?"  Part="1" 
AR Path="/5DDEE9E3/5E26E263" Ref="#PWR0302"  Part="1" 
F 0 "#PWR0302" H 7200 4900 50  0001 C CNN
F 1 "GND" H 7205 4977 50  0000 C CNN
F 2 "" H 7200 5150 50  0001 C CNN
F 3 "" H 7200 5150 50  0001 C CNN
	1    7200 5150
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E26E6FE
P 4950 5150
AR Path="/5DD2C0D9/5E26E6FE" Ref="#PWR?"  Part="1" 
AR Path="/5E26E6FE" Ref="#PWR?"  Part="1" 
AR Path="/5DDEE9E3/5E26E6FE" Ref="#PWR0301"  Part="1" 
F 0 "#PWR0301" H 4950 4900 50  0001 C CNN
F 1 "GND" H 4955 4977 50  0000 C CNN
F 2 "" H 4950 5150 50  0001 C CNN
F 3 "" H 4950 5150 50  0001 C CNN
	1    4950 5150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4950 4300 5050 4300
Wire Wire Line
	5050 4900 4950 4900
Wire Wire Line
	4950 4900 4950 4300
Wire Wire Line
	7200 5150 7200 3600
Wire Wire Line
	4950 4900 4950 5150
Connection ~ 4950 4900
Text HLabel 7500 3100 2    50   Output ~ 0
+5V
Wire Wire Line
	7500 3100 7100 3100
Wire Wire Line
	7500 3700 7100 3700
Wire Wire Line
	7500 3800 7100 3800
Wire Wire Line
	7500 3900 7100 3900
Wire Wire Line
	7500 4000 7100 4000
Wire Wire Line
	7500 4200 7100 4200
Wire Wire Line
	7500 4300 7100 4300
Wire Wire Line
	4650 4500 5050 4500
Wire Wire Line
	4650 4600 5050 4600
Wire Wire Line
	7100 4100 7500 4100
Text HLabel 4650 4700 0    50   BiDi ~ 0
~FPGA_PROGRAM~
Text HLabel 4650 4000 0    50   BiDi ~ 0
~FPGA_INIT~
Text HLabel 4650 4600 0    50   BiDi ~ 0
FPGA_DONE
Wire Wire Line
	7100 3500 7500 3500
Text HLabel 4650 3500 0    50   Output ~ 0
LED1
Text HLabel 4650 3600 0    50   Output ~ 0
LED2
Wire Wire Line
	5050 3600 4650 3600
Wire Wire Line
	4650 3500 5050 3500
$Comp
L Switch:SW_DIP_x02 SW301
U 1 1 60548328
P 8350 4700
F 0 "SW301" H 8350 5067 50  0000 C CNN
F 1 "SW_DIP_x02" H 8350 4976 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 8350 4700 50  0001 C CNN
F 3 "~" H 8350 4700 50  0001 C CNN
	1    8350 4700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7100 4600 7800 4600
Wire Wire Line
	8050 4700 7550 4700
Wire Wire Line
	8650 4600 8750 4600
Wire Wire Line
	8750 4600 8750 4700
Wire Wire Line
	8650 4700 8750 4700
Connection ~ 8750 4700
Wire Wire Line
	8750 4700 8750 4800
$Comp
L power:GND #PWR?
U 1 1 6054AF43
P 8750 4800
AR Path="/5DD2C0D9/6054AF43" Ref="#PWR?"  Part="1" 
AR Path="/6054AF43" Ref="#PWR?"  Part="1" 
AR Path="/5DDEE9E3/6054AF43" Ref="#PWR0146"  Part="1" 
F 0 "#PWR0146" H 8750 4550 50  0001 C CNN
F 1 "GND" H 8755 4627 50  0000 C CNN
F 2 "" H 8750 4800 50  0001 C CNN
F 3 "" H 8750 4800 50  0001 C CNN
	1    8750 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6055116C
P 7800 4900
AR Path="/5DBF9B5A/6055116C" Ref="R?"  Part="1" 
AR Path="/5DCC3140/6055116C" Ref="R?"  Part="1" 
AR Path="/5DD2C0D9/6055116C" Ref="R?"  Part="1" 
AR Path="/5DDC09A7/6055116C" Ref="R?"  Part="1" 
AR Path="/6055116C" Ref="R?"  Part="1" 
AR Path="/5DDEE9E3/6055116C" Ref="R302"  Part="1" 
F 0 "R302" H 7600 4900 50  0000 L CNN
F 1 "10k" H 7600 4800 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7730 4900 50  0001 C CNN
F 3 "~" H 7800 4900 50  0001 C CNN
	1    7800 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60551616
P 7550 4900
AR Path="/5DBF9B5A/60551616" Ref="R?"  Part="1" 
AR Path="/5DCC3140/60551616" Ref="R?"  Part="1" 
AR Path="/5DD2C0D9/60551616" Ref="R?"  Part="1" 
AR Path="/5DDC09A7/60551616" Ref="R?"  Part="1" 
AR Path="/60551616" Ref="R?"  Part="1" 
AR Path="/5DDEE9E3/60551616" Ref="R301"  Part="1" 
F 0 "R301" H 7350 4900 50  0000 L CNN
F 1 "10k" H 7350 4800 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7480 4900 50  0001 C CNN
F 3 "~" H 7550 4900 50  0001 C CNN
	1    7550 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4750 7550 4700
Connection ~ 7550 4700
Wire Wire Line
	7550 4700 7100 4700
Wire Wire Line
	7800 4750 7800 4600
Connection ~ 7800 4600
Wire Wire Line
	7800 4600 8050 4600
Wire Wire Line
	7100 4900 7300 4900
Wire Wire Line
	7300 4900 7300 5100
Wire Wire Line
	7300 5100 7550 5100
Wire Wire Line
	7800 5100 7800 5050
Wire Wire Line
	7550 5050 7550 5100
Connection ~ 7550 5100
Wire Wire Line
	7550 5100 7800 5100
Text HLabel 4650 4400 0    50   Output ~ 0
~RST_FPGA~
Wire Wire Line
	4650 4400 5050 4400
Wire Wire Line
	5050 4700 4650 4700
Wire Wire Line
	5050 4000 4650 4000
$EndSCHEMATC
