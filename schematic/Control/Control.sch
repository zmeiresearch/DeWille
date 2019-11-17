EESchema Schematic File Version 4
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
Text HLabel 7500 3700 2    50   Output ~ 0
~CS_DACL~
Text HLabel 7500 3800 2    50   Output ~ 0
~CS_DACR~
Text HLabel 7500 3900 2    50   Output ~ 0
~CS_FPGA~
Text HLabel 7500 4000 2    50   Output ~ 0
~CS_CLK~
Text HLabel 7500 4200 2    50   Output ~ 0
~RST_CLK~
Text HLabel 7500 4300 2    50   Output ~ 0
~RST_FPGA~
Text HLabel 7500 4400 2    50   Output ~ 0
~RST_DACL~
Text HLabel 7500 4500 2    50   Output ~ 0
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
L Zmei_elements:ESP32DevKit U?
U 1 1 5E265BB1
P 6050 4100
F 0 "U?" H 6025 5215 50  0000 C CNN
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
AR Path="/5DDEE9E3/5E26E263" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7200 4900 50  0001 C CNN
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
AR Path="/5DDEE9E3/5E26E6FE" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4950 4900 50  0001 C CNN
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
	7500 4400 7100 4400
Wire Wire Line
	7500 4500 7100 4500
$EndSCHEMATC
