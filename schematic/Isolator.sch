EESchema Schematic File Version 4
LIBS:DeWille-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
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
L Isolator:Si8640BA-B-IU U?
U 1 1 5DCC5B62
P 4900 3000
AR Path="/5DBF9B5A/5DCC5B62" Ref="U?"  Part="1" 
AR Path="/5DCC5B62" Ref="U?"  Part="1" 
AR Path="/5DCC37DA/5DCC5B62" Ref="U?"  Part="1" 
F 0 "U?" H 4900 3667 50  0000 C CNN
F 1 "Si8640BA-B-IU" H 4900 3576 50  0000 C CNN
F 2 "Package_SO:QSOP-16_3.9x4.9mm_P0.635mm" H 4900 2450 50  0001 C CIN
F 3 "https://www.silabs.com/documents/public/data-sheets/si864x-datasheet.pdf" H 4900 3400 50  0001 C CNN
	1    4900 3000
	1    0    0    -1  
$EndComp
$Comp
L Isolator:Si8641BA-B-IU U?
U 1 1 5DCC5B68
P 4900 4450
AR Path="/5DBF9B5A/5DCC5B68" Ref="U?"  Part="1" 
AR Path="/5DCC5B68" Ref="U?"  Part="1" 
AR Path="/5DCC37DA/5DCC5B68" Ref="U?"  Part="1" 
F 0 "U?" H 4900 5117 50  0000 C CNN
F 1 "Si8641BA-B-IU" H 4900 5026 50  0000 C CNN
F 2 "Package_SO:QSOP-16_3.9x4.9mm_P0.635mm" H 4900 3900 50  0001 C CIN
F 3 "https://www.silabs.com/documents/public/data-sheets/si864x-datasheet.pdf" H 4900 4850 50  0001 C CNN
	1    4900 4450
	1    0    0    -1  
$EndComp
Text HLabel 5950 2900 2    50   Output ~ 0
LRCK_OUT
Text HLabel 5950 3000 2    50   Output ~ 0
DATA_OUT
Text HLabel 5950 3200 2    50   Output ~ 0
SCK_OUT
Text HLabel 5950 3100 2    50   Output ~ 0
BCK_OUT
Text HLabel 5950 4350 2    50   Output ~ 0
MOSI_OUT
Text HLabel 5950 4450 2    50   Output ~ 0
SCLK_OUT
Text HLabel 5950 4650 2    50   Input ~ 0
MISO_IN
Text HLabel 5950 4550 2    50   Output ~ 0
~RST_OUT~
Text HLabel 6100 5900 2    50   Output ~ 0
~CS_L_OUT~
Text HLabel 6100 6100 2    50   Output ~ 0
~CS_R_OUT~
Wire Wire Line
	5300 2900 5950 2900
Wire Wire Line
	5950 3000 5300 3000
Wire Wire Line
	5300 3100 5950 3100
Wire Wire Line
	5950 3200 5300 3200
Wire Wire Line
	5950 4350 5300 4350
Wire Wire Line
	5950 4450 5300 4450
Wire Wire Line
	5950 4550 5300 4550
Wire Wire Line
	5950 4650 5300 4650
Wire Wire Line
	4500 4350 3850 4350
Wire Wire Line
	4500 4450 3850 4450
Wire Wire Line
	4500 4550 3850 4550
Wire Wire Line
	4500 4650 3850 4650
Wire Wire Line
	4500 3200 3850 3200
Wire Wire Line
	4500 3100 3850 3100
Wire Wire Line
	4500 3000 3850 3000
Wire Wire Line
	4500 2900 3850 2900
Text HLabel 3850 2900 0    50   Input ~ 0
LRCK_IN
Text HLabel 3850 3000 0    50   Input ~ 0
DATA_IN
Text HLabel 3850 3100 0    50   Input ~ 0
BCK_IN
Text HLabel 3850 3200 0    50   Input ~ 0
SCK_IN
Text HLabel 3850 4350 0    50   Input ~ 0
MOSI_IN
Text HLabel 3850 4450 0    50   Input ~ 0
SCLK_IN
Text HLabel 3850 4550 0    50   Input ~ 0
~RST_IN~
Text HLabel 3850 4650 0    50   Output ~ 0
MISO_OUT
Text HLabel 3800 5900 0    50   Input ~ 0
~CS_L_IN~
Text HLabel 3800 6100 0    50   Input ~ 0
~CS_R_IN~
$Comp
L Isolator:ADuM1200AR U?
U 1 1 5DCD39FF
P 4950 6000
F 0 "U?" H 4950 6467 50  0000 C CNN
F 1 "ADuM1200AR" H 4950 6376 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4950 5600 50  0001 C CIN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/ADuM1200_1201.pdf" H 4500 6400 50  0001 C CNN
	1    4950 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 5900 3800 5900
Wire Wire Line
	4450 6100 3800 6100
Wire Wire Line
	6100 5900 5450 5900
Wire Wire Line
	6100 6100 5450 6100
Text Notes 3750 2000 0    50   ~ 0
Clock jitter introduced by SI8640 is typ. 350ps, \nwhich should not affect quality of 16bit@44.1kHz.\nFor anything above, better quality may be obtained by removing isolation\nFor 24bit@192kHz, 0.3pS jitter is typically tolerable\n
Text HLabel 6650 2200 1    50   UnSpc ~ 0
+3V3DAC
Wire Wire Line
	5300 2700 5400 2700
Wire Wire Line
	5400 2700 5400 2600
Wire Wire Line
	5400 2600 5300 2600
Wire Wire Line
	5400 2600 5400 2250
Connection ~ 5400 2600
Wire Wire Line
	5300 4150 5400 4150
Wire Wire Line
	5400 4150 5400 4050
Wire Wire Line
	5400 4050 5300 4050
Wire Wire Line
	5400 4050 5400 3700
Connection ~ 5400 4050
Wire Wire Line
	5450 5800 5450 5300
Connection ~ 6650 3700
$Comp
L power:GNDA #PWR?
U 1 1 5DCF3883
P 5550 6300
AR Path="/5DBF9B5A/5DCF3883" Ref="#PWR?"  Part="1" 
AR Path="/5DC88EF1/5DCF3883" Ref="#PWR?"  Part="1" 
AR Path="/5DCC3140/5DCF3883" Ref="#PWR?"  Part="1" 
AR Path="/5DCC37DA/5DCF3883" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5550 6050 50  0001 C CNN
F 1 "GNDA" H 5555 6127 50  0000 C CNN
F 2 "" H 5550 6300 50  0001 C CNN
F 3 "" H 5550 6300 50  0001 C CNN
	1    5550 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 6200 5550 6200
Wire Wire Line
	5550 6200 5550 6300
$Comp
L power:GNDA #PWR?
U 1 1 5DCF4C40
P 5400 4950
AR Path="/5DBF9B5A/5DCF4C40" Ref="#PWR?"  Part="1" 
AR Path="/5DC88EF1/5DCF4C40" Ref="#PWR?"  Part="1" 
AR Path="/5DCC3140/5DCF4C40" Ref="#PWR?"  Part="1" 
AR Path="/5DCC37DA/5DCF4C40" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5400 4700 50  0001 C CNN
F 1 "GNDA" H 5405 4777 50  0000 C CNN
F 2 "" H 5400 4950 50  0001 C CNN
F 3 "" H 5400 4950 50  0001 C CNN
	1    5400 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4850 5400 4850
Wire Wire Line
	5400 4850 5400 4950
$Comp
L power:GNDA #PWR?
U 1 1 5DCF596C
P 5400 3500
AR Path="/5DBF9B5A/5DCF596C" Ref="#PWR?"  Part="1" 
AR Path="/5DC88EF1/5DCF596C" Ref="#PWR?"  Part="1" 
AR Path="/5DCC3140/5DCF596C" Ref="#PWR?"  Part="1" 
AR Path="/5DCC37DA/5DCF596C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5400 3250 50  0001 C CNN
F 1 "GNDA" H 5405 3327 50  0000 C CNN
F 2 "" H 5400 3500 50  0001 C CNN
F 3 "" H 5400 3500 50  0001 C CNN
	1    5400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3400 5400 3400
Wire Wire Line
	5400 3400 5400 3500
Wire Wire Line
	6650 3700 6650 5300
Wire Wire Line
	5400 3700 6100 3700
Wire Wire Line
	5450 5300 6100 5300
$Comp
L Device:C C?
U 1 1 5DD97A98
P 5600 2400
AR Path="/5DBF9B5A/5DD97A98" Ref="C?"  Part="1" 
AR Path="/5DC88EF1/5DD97A98" Ref="C?"  Part="1" 
AR Path="/5DCC3140/5DD97A98" Ref="C?"  Part="1" 
AR Path="/5DCC37DA/5DD97A98" Ref="C?"  Part="1" 
F 0 "C?" H 5500 2750 50  0000 L CNN
F 1 "100nF" H 5450 2650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5638 2250 50  0001 C CNN
F 3 "~" H 5600 2400 50  0001 C CNN
	1    5600 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5DD97A9E
P 5600 2550
AR Path="/5DBF9B5A/5DD97A9E" Ref="#PWR?"  Part="1" 
AR Path="/5DC88EF1/5DD97A9E" Ref="#PWR?"  Part="1" 
AR Path="/5DCC3140/5DD97A9E" Ref="#PWR?"  Part="1" 
AR Path="/5DCC37DA/5DD97A9E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5600 2300 50  0001 C CNN
F 1 "GNDA" H 5605 2377 50  0000 C CNN
F 2 "" H 5600 2550 50  0001 C CNN
F 3 "" H 5600 2550 50  0001 C CNN
	1    5600 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DD9A396
P 5600 3850
AR Path="/5DBF9B5A/5DD9A396" Ref="C?"  Part="1" 
AR Path="/5DC88EF1/5DD9A396" Ref="C?"  Part="1" 
AR Path="/5DCC3140/5DD9A396" Ref="C?"  Part="1" 
AR Path="/5DCC37DA/5DD9A396" Ref="C?"  Part="1" 
F 0 "C?" H 5500 4200 50  0000 L CNN
F 1 "100nF" H 5450 4100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5638 3700 50  0001 C CNN
F 3 "~" H 5600 3850 50  0001 C CNN
	1    5600 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5DD9A39C
P 5600 4000
AR Path="/5DBF9B5A/5DD9A39C" Ref="#PWR?"  Part="1" 
AR Path="/5DC88EF1/5DD9A39C" Ref="#PWR?"  Part="1" 
AR Path="/5DCC3140/5DD9A39C" Ref="#PWR?"  Part="1" 
AR Path="/5DCC37DA/5DD9A39C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5600 3750 50  0001 C CNN
F 1 "GNDA" H 5605 3827 50  0000 C CNN
F 2 "" H 5600 4000 50  0001 C CNN
F 3 "" H 5600 4000 50  0001 C CNN
	1    5600 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DD9BB36
P 5600 5450
AR Path="/5DBF9B5A/5DD9BB36" Ref="C?"  Part="1" 
AR Path="/5DC88EF1/5DD9BB36" Ref="C?"  Part="1" 
AR Path="/5DCC3140/5DD9BB36" Ref="C?"  Part="1" 
AR Path="/5DCC37DA/5DD9BB36" Ref="C?"  Part="1" 
F 0 "C?" H 5500 5800 50  0000 L CNN
F 1 "100nF" H 5450 5700 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5638 5300 50  0001 C CNN
F 3 "~" H 5600 5450 50  0001 C CNN
	1    5600 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5DD9BB3C
P 5600 5600
AR Path="/5DBF9B5A/5DD9BB3C" Ref="#PWR?"  Part="1" 
AR Path="/5DC88EF1/5DD9BB3C" Ref="#PWR?"  Part="1" 
AR Path="/5DCC3140/5DD9BB3C" Ref="#PWR?"  Part="1" 
AR Path="/5DCC37DA/5DD9BB3C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5600 5350 50  0001 C CNN
F 1 "GNDA" H 5605 5427 50  0000 C CNN
F 2 "" H 5600 5600 50  0001 C CNN
F 3 "" H 5600 5600 50  0001 C CNN
	1    5600 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L?
U 1 1 5DD9EAF0
P 6250 2250
AR Path="/5DBF9B5A/5DD9EAF0" Ref="L?"  Part="1" 
AR Path="/5DC88EF1/5DD9EAF0" Ref="L?"  Part="1" 
AR Path="/5DCC3140/5DD9EAF0" Ref="L?"  Part="1" 
AR Path="/5DCC37DA/5DD9EAF0" Ref="L?"  Part="1" 
F 0 "L?" V 6300 2600 50  0000 C CNN
F 1 "10 Ohm@100MHz" V 6150 2350 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 6250 2250 50  0001 C CNN
F 3 "FB1608-101Y; Comet 16318" H 6250 2250 50  0001 C CNN
	1    6250 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 2200 6650 2250
Wire Wire Line
	6100 2250 5600 2250
Connection ~ 5600 2250
Wire Wire Line
	5600 2250 5400 2250
Connection ~ 6650 2250
Wire Wire Line
	6650 2250 6650 3700
Wire Wire Line
	6400 2250 6650 2250
$Comp
L Device:L_Core_Ferrite L?
U 1 1 5DDA1A67
P 6250 3700
AR Path="/5DBF9B5A/5DDA1A67" Ref="L?"  Part="1" 
AR Path="/5DC88EF1/5DDA1A67" Ref="L?"  Part="1" 
AR Path="/5DCC3140/5DDA1A67" Ref="L?"  Part="1" 
AR Path="/5DCC37DA/5DDA1A67" Ref="L?"  Part="1" 
F 0 "L?" V 6300 4050 50  0000 C CNN
F 1 "10 Ohm@100MHz" V 6150 3800 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 6250 3700 50  0001 C CNN
F 3 "FB1608-101Y; Comet 16318" H 6250 3700 50  0001 C CNN
	1    6250 3700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6400 3700 6650 3700
$Comp
L Device:L_Core_Ferrite L?
U 1 1 5DDA6022
P 6250 5300
AR Path="/5DBF9B5A/5DDA6022" Ref="L?"  Part="1" 
AR Path="/5DC88EF1/5DDA6022" Ref="L?"  Part="1" 
AR Path="/5DCC3140/5DDA6022" Ref="L?"  Part="1" 
AR Path="/5DCC37DA/5DDA6022" Ref="L?"  Part="1" 
F 0 "L?" V 6300 5650 50  0000 C CNN
F 1 "10 Ohm@100MHz" V 6150 5400 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 6250 5300 50  0001 C CNN
F 3 "FB1608-101Y; Comet 16318" H 6250 5300 50  0001 C CNN
	1    6250 5300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6400 5300 6650 5300
$Comp
L power:GND #PWR?
U 1 1 5DD44168
P 4400 3500
F 0 "#PWR?" H 4400 3250 50  0001 C CNN
F 1 "GND" H 4405 3327 50  0000 C CNN
F 2 "" H 4400 3500 50  0001 C CNN
F 3 "" H 4400 3500 50  0001 C CNN
	1    4400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3400 4400 3400
Wire Wire Line
	4400 3400 4400 3500
$Comp
L power:GND #PWR?
U 1 1 5DD45A7A
P 4400 4950
F 0 "#PWR?" H 4400 4700 50  0001 C CNN
F 1 "GND" H 4405 4777 50  0000 C CNN
F 2 "" H 4400 4950 50  0001 C CNN
F 3 "" H 4400 4950 50  0001 C CNN
	1    4400 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 4850 4400 4850
Wire Wire Line
	4400 4850 4400 4950
$Comp
L power:GND #PWR?
U 1 1 5DD46B6D
P 4350 6300
F 0 "#PWR?" H 4350 6050 50  0001 C CNN
F 1 "GND" H 4355 6127 50  0000 C CNN
F 2 "" H 4350 6300 50  0001 C CNN
F 3 "" H 4350 6300 50  0001 C CNN
	1    4350 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 6200 4350 6200
Wire Wire Line
	4350 6200 4350 6300
Text HLabel 3150 2200 1    50   UnSpc ~ 0
+3V3D
Wire Wire Line
	4400 2600 4500 2600
Wire Wire Line
	4400 2600 4400 2250
Wire Wire Line
	4400 4050 4500 4050
Wire Wire Line
	4400 4050 4400 3700
Wire Wire Line
	4350 5800 4350 5300
Connection ~ 3150 3700
Wire Wire Line
	3150 3700 3150 5300
Wire Wire Line
	4400 3700 4200 3700
Wire Wire Line
	4350 5300 4200 5300
$Comp
L Device:C C?
U 1 1 5DD4DF4E
P 4200 2400
AR Path="/5DBF9B5A/5DD4DF4E" Ref="C?"  Part="1" 
AR Path="/5DC88EF1/5DD4DF4E" Ref="C?"  Part="1" 
AR Path="/5DCC3140/5DD4DF4E" Ref="C?"  Part="1" 
AR Path="/5DCC37DA/5DD4DF4E" Ref="C?"  Part="1" 
F 0 "C?" H 4100 2750 50  0000 L CNN
F 1 "100nF" H 4050 2650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4238 2250 50  0001 C CNN
F 3 "~" H 4200 2400 50  0001 C CNN
	1    4200 2400
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DD4DF5A
P 4200 3850
AR Path="/5DBF9B5A/5DD4DF5A" Ref="C?"  Part="1" 
AR Path="/5DC88EF1/5DD4DF5A" Ref="C?"  Part="1" 
AR Path="/5DCC3140/5DD4DF5A" Ref="C?"  Part="1" 
AR Path="/5DCC37DA/5DD4DF5A" Ref="C?"  Part="1" 
F 0 "C?" H 4100 4200 50  0000 L CNN
F 1 "100nF" H 4050 4100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4238 3700 50  0001 C CNN
F 3 "~" H 4200 3850 50  0001 C CNN
	1    4200 3850
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DD4DF66
P 4200 5450
AR Path="/5DBF9B5A/5DD4DF66" Ref="C?"  Part="1" 
AR Path="/5DC88EF1/5DD4DF66" Ref="C?"  Part="1" 
AR Path="/5DCC3140/5DD4DF66" Ref="C?"  Part="1" 
AR Path="/5DCC37DA/5DD4DF66" Ref="C?"  Part="1" 
F 0 "C?" H 4100 5800 50  0000 L CNN
F 1 "100nF" H 4050 5700 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4238 5300 50  0001 C CNN
F 3 "~" H 4200 5450 50  0001 C CNN
	1    4200 5450
	-1   0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L?
U 1 1 5DD4DF72
P 3550 2250
AR Path="/5DBF9B5A/5DD4DF72" Ref="L?"  Part="1" 
AR Path="/5DC88EF1/5DD4DF72" Ref="L?"  Part="1" 
AR Path="/5DCC3140/5DD4DF72" Ref="L?"  Part="1" 
AR Path="/5DCC37DA/5DD4DF72" Ref="L?"  Part="1" 
F 0 "L?" V 3600 2600 50  0000 C CNN
F 1 "10 Ohm@100MHz" V 3450 2350 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 3550 2250 50  0001 C CNN
F 3 "FB1608-101Y; Comet 16318" H 3550 2250 50  0001 C CNN
	1    3550 2250
	0    1    -1   0   
$EndComp
Wire Wire Line
	3150 2200 3150 2250
Wire Wire Line
	3700 2250 4200 2250
Connection ~ 4200 2250
Wire Wire Line
	4200 2250 4400 2250
Connection ~ 3150 2250
Wire Wire Line
	3150 2250 3150 3700
Wire Wire Line
	3400 2250 3150 2250
$Comp
L Device:L_Core_Ferrite L?
U 1 1 5DD4DF7F
P 3550 3700
AR Path="/5DBF9B5A/5DD4DF7F" Ref="L?"  Part="1" 
AR Path="/5DC88EF1/5DD4DF7F" Ref="L?"  Part="1" 
AR Path="/5DCC3140/5DD4DF7F" Ref="L?"  Part="1" 
AR Path="/5DCC37DA/5DD4DF7F" Ref="L?"  Part="1" 
F 0 "L?" V 3600 4050 50  0000 C CNN
F 1 "10 Ohm@100MHz" V 3450 3800 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 3550 3700 50  0001 C CNN
F 3 "FB1608-101Y; Comet 16318" H 3550 3700 50  0001 C CNN
	1    3550 3700
	0    1    -1   0   
$EndComp
Wire Wire Line
	3400 3700 3150 3700
$Comp
L Device:L_Core_Ferrite L?
U 1 1 5DD4DF86
P 3550 5300
AR Path="/5DBF9B5A/5DD4DF86" Ref="L?"  Part="1" 
AR Path="/5DC88EF1/5DD4DF86" Ref="L?"  Part="1" 
AR Path="/5DCC3140/5DD4DF86" Ref="L?"  Part="1" 
AR Path="/5DCC37DA/5DD4DF86" Ref="L?"  Part="1" 
F 0 "L?" V 3600 5650 50  0000 C CNN
F 1 "10 Ohm@100MHz" V 3450 5400 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 3550 5300 50  0001 C CNN
F 3 "FB1608-101Y; Comet 16318" H 3550 5300 50  0001 C CNN
	1    3550 5300
	0    1    -1   0   
$EndComp
Wire Wire Line
	3400 5300 3150 5300
Connection ~ 4200 3700
Wire Wire Line
	4200 3700 3700 3700
Connection ~ 4200 5300
Wire Wire Line
	4200 5300 3700 5300
Wire Wire Line
	4450 5800 4350 5800
$Comp
L power:GND #PWR?
U 1 1 5DD690CF
P 4200 2550
F 0 "#PWR?" H 4200 2300 50  0001 C CNN
F 1 "GND" H 4205 2377 50  0000 C CNN
F 2 "" H 4200 2550 50  0001 C CNN
F 3 "" H 4200 2550 50  0001 C CNN
	1    4200 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD69446
P 4200 4000
F 0 "#PWR?" H 4200 3750 50  0001 C CNN
F 1 "GND" H 4205 3827 50  0000 C CNN
F 2 "" H 4200 4000 50  0001 C CNN
F 3 "" H 4200 4000 50  0001 C CNN
	1    4200 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD698EF
P 4200 5600
F 0 "#PWR?" H 4200 5350 50  0001 C CNN
F 1 "GND" H 4205 5427 50  0000 C CNN
F 2 "" H 4200 5600 50  0001 C CNN
F 3 "" H 4200 5600 50  0001 C CNN
	1    4200 5600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
