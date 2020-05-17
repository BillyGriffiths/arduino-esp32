# ESP32 - calcBatteryVoltage

An example of how to calculate battery voltage using the ESP32, Arduino IDE and FreeRTOS. 

**Board:** TTGO ESP32 SIM800L v1.3

Task calcBatteryVoltage() reads pin 35 and calculates the voltage based on a 10 x analogRead() average.
The formula was created and tested while monitoring a connected 1S 1200mAh LiPo battery using a multimeter.  

Note: Pin 35 seems to output the system input voltage, and not that of the connected battery specifically.
If you know of a way to get the USB-C and battery voltage separately, please let me know. 
 
Example of serial output: 

```
16:34:05.483 -> [calcBatteryVoltage] 4.74V
16:34:05.483 -> [calcBatteryVoltage] 4.74V
16:34:15.533 -> [calcBatteryVoltage] 4.74V
16:34:15.533 -> [calcBatteryVoltage] 4.74V
16:34:21.333 -> [calcBatteryVoltage] 4.74V
16:34:23.733 -> [calcBatteryVoltage] 4.74V
16:34:28.933 -> [calcBatteryVoltage] 4.74V
16:34:34.035 -> [calcBatteryVoltage] 4.74V
16:34:38.733 -> [calcBatteryVoltage] 4.74V
16:34:44.633 -> [calcBatteryVoltage] 4.74V
16:34:48.733 -> [calcBatteryVoltage] 4.74V
16:34:54.583 -> [calcBatteryVoltage] 4.74V
16:35:01.780 -> [calcBatteryVoltage] 4.74V
16:35:03.734 -> [calcBatteryVoltage] 4.74V

```