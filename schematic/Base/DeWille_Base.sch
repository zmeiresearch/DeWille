EESchema Schematic File Version 4
LIBS:DeWille_Base-cache
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:L_Core_Ferrite L?
U 1 1 5DE60714
P 12050 1350
AR Path="/5DBF9B5A/5DE60714" Ref="L?"  Part="1" 
AR Path="/5DC88EF1/5DE60714" Ref="L?"  Part="1" 
AR Path="/5DCC3140/5DE60714" Ref="L?"  Part="1" 
AR Path="/5DDA84B4/5DE60714" Ref="L?"  Part="1" 
AR Path="/5DE60714" Ref="L101"  Part="1" 
F 0 "L101" V 12250 1400 50  0000 C CNN
F 1 "100 Ohm@100MHz" V 12150 1400 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 12050 1350 50  0001 C CNN
F 3 "FB1608-101Y; Comet 16318" H 12050 1350 50  0001 C CNN
	1    12050 1350
	0    -1   -1   0   
$EndComp
$Sheet
S 7700 3750 1650 900 
U 5E637622
F0 "Power Supply" 50
F1 "Power_Supply.sch" 50
F2 "+5V" O L 7700 4000 50 
F3 "+15V" O L 7700 4100 50 
F4 "-15V" O L 7700 4200 50 
$EndSheet
Wire Wire Line
	2400 4950 2000 4950
Wire Wire Line
	2000 4850 2400 4850
Wire Wire Line
	2400 4750 2000 4750
Wire Wire Line
	2000 4650 2400 4650
Wire Wire Line
	2400 4550 2000 4550
Wire Wire Line
	2000 4450 2400 4450
Wire Wire Line
	2400 4350 2000 4350
Wire Wire Line
	2000 4250 2400 4250
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J101
U 1 1 5DE6B9FB
P 2600 4550
F 0 "J101" H 2650 5167 50  0000 C CNN
F 1 "HN2x10" H 2650 5076 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 2600 4550 50  0001 C CNN
F 3 "~" H 2600 4550 50  0001 C CNN
	1    2600 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DE6BA01
P 2000 5250
AR Path="/5DD2C0D9/5DE6BA01" Ref="#PWR?"  Part="1" 
AR Path="/5DE6BA01" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 2000 5000 50  0001 C CNN
F 1 "GND" H 2005 5077 50  0000 C CNN
F 2 "" H 2000 5250 50  0001 C CNN
F 3 "" H 2000 5250 50  0001 C CNN
	1    2000 5250
	1    0    0    -1  
$EndComp
Connection ~ 2000 4350
Wire Wire Line
	2000 4350 2000 4250
Connection ~ 2000 4450
Wire Wire Line
	2000 4450 2000 4350
Connection ~ 2000 4550
Wire Wire Line
	2000 4550 2000 4450
Connection ~ 2000 4650
Wire Wire Line
	2000 4650 2000 4550
Connection ~ 2000 4750
Wire Wire Line
	2000 4750 2000 4650
Connection ~ 2000 4850
Wire Wire Line
	2000 4850 2000 4750
Connection ~ 2000 4950
Wire Wire Line
	2000 4950 2000 4850
Wire Wire Line
	2000 4950 2000 5250
Wire Wire Line
	2400 5050 2200 5050
Wire Wire Line
	2200 5050 2200 4150
Wire Wire Line
	2200 4150 2400 4150
Text Label 5550 4050 0    50   ~ 0
MISO
Text Label 5550 3950 0    50   ~ 0
MOSI
Text Label 5550 4150 0    50   ~ 0
SCLK
Text Label 5550 4250 0    50   ~ 0
~DACL_CS~
Text Label 5600 5450 0    50   ~ 0
~DACR_CS~
Text Label 5600 4650 0    50   ~ 0
DACR_SCK
Text Label 5600 5050 0    50   ~ 0
DACR_BCK
Text Label 5600 4950 0    50   ~ 0
DACR_DATA
Text Label 5600 4850 0    50   ~ 0
DACR_LRCK
Text Label 5550 3750 0    50   ~ 0
DACL_DATA
Text Label 5550 3850 0    50   ~ 0
DACL_BCK
Text Label 5550 3450 0    50   ~ 0
DACL_SCK
Text Label 5550 3650 0    50   ~ 0
DACL_LRCK
Text Label 5600 5250 0    50   ~ 0
MISO
Text Label 5600 5150 0    50   ~ 0
MOSI
Text Label 5600 5350 0    50   ~ 0
SCLK
Text Label 5550 4350 0    50   ~ 0
~DACL_RST~
Text Label 5600 5550 0    50   ~ 0
~DACR_RST~
Wire Wire Line
	4500 4350 4900 4350
Wire Wire Line
	4900 4250 4500 4250
Wire Wire Line
	4500 4150 4900 4150
Wire Wire Line
	4900 4050 4500 4050
Wire Wire Line
	4500 3950 4900 3950
Wire Wire Line
	4900 3850 4500 3850
Wire Wire Line
	4500 3750 4900 3750
Wire Wire Line
	4900 3650 4500 3650
Wire Wire Line
	4500 3550 4900 3550
Wire Wire Line
	4900 3450 4500 3450
Wire Wire Line
	4500 5550 4900 5550
Wire Wire Line
	4900 5450 4500 5450
Wire Wire Line
	4500 5350 4900 5350
Wire Wire Line
	4900 5250 4500 5250
Wire Wire Line
	4500 5150 4900 5150
Wire Wire Line
	4900 5050 4500 5050
Wire Wire Line
	4500 4950 4900 4950
Wire Wire Line
	4900 4850 4500 4850
Wire Wire Line
	4500 4750 4900 4750
Wire Wire Line
	4900 4650 4500 4650
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J103
U 1 1 5DE87163
P 5100 5050
F 0 "J103" H 5150 5667 50  0000 C CNN
F 1 "HN2x10" H 5150 5576 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 5100 5050 50  0001 C CNN
F 3 "~" H 5100 5050 50  0001 C CNN
	1    5100 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 5550 5800 5550
Wire Wire Line
	5800 5450 5400 5450
Wire Wire Line
	5400 5350 5800 5350
Wire Wire Line
	5800 5250 5400 5250
Wire Wire Line
	5400 5150 5800 5150
Wire Wire Line
	5800 5050 5400 5050
Wire Wire Line
	5400 4950 5800 4950
Wire Wire Line
	5800 4850 5400 4850
Wire Wire Line
	5800 4650 5400 4650
Wire Wire Line
	6050 4750 6050 5750
Wire Wire Line
	5400 4750 6050 4750
Wire Wire Line
	6050 4750 6050 3550
Wire Wire Line
	5400 3550 6050 3550
Connection ~ 6050 4750
Wire Wire Line
	5400 3450 5800 3450
Wire Wire Line
	5800 3650 5400 3650
Wire Wire Line
	5400 3750 5800 3750
Wire Wire Line
	5800 3850 5400 3850
Wire Wire Line
	5400 3950 5800 3950
Wire Wire Line
	5800 4050 5400 4050
Wire Wire Line
	5400 4150 5800 4150
Wire Wire Line
	5800 4250 5400 4250
Wire Wire Line
	5400 4350 5800 4350
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J102
U 1 1 5DE87180
P 5100 3850
F 0 "J102" H 5150 4467 50  0000 C CNN
F 1 "HN2x10" H 5150 4376 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 5100 3850 50  0001 C CNN
F 3 "~" H 5100 3850 50  0001 C CNN
	1    5100 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DE87186
P 6050 5750
AR Path="/5DD2C0D9/5DE87186" Ref="#PWR?"  Part="1" 
AR Path="/5DE87186" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 6050 5500 50  0001 C CNN
F 1 "GND" H 6055 5577 50  0000 C CNN
F 2 "" H 6050 5750 50  0001 C CNN
F 3 "" H 6050 5750 50  0001 C CNN
	1    6050 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DE8718C
P 4500 5750
AR Path="/5DD2C0D9/5DE8718C" Ref="#PWR?"  Part="1" 
AR Path="/5DE8718C" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 4500 5500 50  0001 C CNN
F 1 "GND" H 4505 5577 50  0000 C CNN
F 2 "" H 4500 5750 50  0001 C CNN
F 3 "" H 4500 5750 50  0001 C CNN
	1    4500 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 5750 4500 5550
Connection ~ 4500 3550
Wire Wire Line
	4500 3550 4500 3450
Wire Wire Line
	4500 3650 4500 3550
Connection ~ 4500 3750
Wire Wire Line
	4500 3750 4500 3650
Connection ~ 4500 3850
Wire Wire Line
	4500 3850 4500 3750
Connection ~ 4500 3950
Wire Wire Line
	4500 3950 4500 3850
Connection ~ 4500 4050
Wire Wire Line
	4500 4050 4500 3950
Connection ~ 4500 4150
Wire Wire Line
	4500 4150 4500 4050
Connection ~ 4500 4250
Wire Wire Line
	4500 4250 4500 4150
Connection ~ 4500 4350
Wire Wire Line
	4500 4350 4500 4250
Connection ~ 4500 4650
Wire Wire Line
	4500 4650 4500 4350
Connection ~ 4500 4750
Wire Wire Line
	4500 4750 4500 4650
Connection ~ 4500 4850
Wire Wire Line
	4500 4850 4500 4750
Connection ~ 4500 4950
Wire Wire Line
	4500 4950 4500 4850
Connection ~ 4500 5050
Wire Wire Line
	4500 5050 4500 4950
Connection ~ 4500 5150
Wire Wire Line
	4500 5150 4500 5050
Connection ~ 4500 5250
Wire Wire Line
	4500 5250 4500 5150
Connection ~ 4500 5350
Wire Wire Line
	4500 5350 4500 5250
Connection ~ 4500 5450
Wire Wire Line
	4500 5450 4500 5350
Connection ~ 4500 5550
Wire Wire Line
	4500 5550 4500 5450
Text Label 2250 4150 0    50   ~ 0
+5V
Text Label 3000 4150 0    50   ~ 0
SCK1
Text Label 3000 4250 0    50   ~ 0
BCK
Text Label 3000 4350 0    50   ~ 0
LRCK1
Text Label 3000 4450 0    50   ~ 0
DATA1
Text Label 3000 4550 0    50   ~ 0
SCK2
Text Label 3000 4650 0    50   ~ 0
BCK2
Text Label 3000 4750 0    50   ~ 0
LRCK2
Text Label 3000 4850 0    50   ~ 0
DATA2
Text Label 3000 4950 0    50   ~ 0
SPDIF1
Text Label 3000 5050 0    50   ~ 0
SPDIF2
Wire Wire Line
	2900 4150 3300 4150
Wire Wire Line
	2900 4250 3300 4250
Wire Wire Line
	2900 4350 3300 4350
Wire Wire Line
	2900 4450 3300 4450
Wire Wire Line
	2850 4550 3250 4550
Wire Wire Line
	2900 4650 3300 4650
Wire Wire Line
	2900 4750 3300 4750
Wire Wire Line
	2900 4850 3300 4850
Wire Wire Line
	2900 4950 3300 4950
Wire Wire Line
	2900 5050 3300 5050
Wire Notes Line
	1200 2800 1200 6450
Wire Notes Line
	1200 6450 6500 6450
Wire Notes Line
	6500 2800 1200 2800
Wire Notes Line
	6500 2800 6500 6450
Text Notes 3550 3050 0    50   ~ 0
Control
Connection ~ 4500 3650
$EndSCHEMATC
