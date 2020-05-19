# ESP32 - writeToOledSSD1306

How to connect, write and refresh a simple message on an I2C OLED display using ESP32, Arduino IDE and FreeRTOS. 

**Board:** TTGO ESP32 SIM800L v1.3   
**Display:** 0.96" OLED I2C display (128 x 64 - Graphics driver IC is SSD1306) 

**Wiring your I2C (4-pin) OLED display to the ESP32:**

1. GND <--> GND
2. VCC <--> 3V3 or 5V (check your display input voltage requirements)
3. SDA <--> SDA
4. SCL <--> SCL

If you are planning on wiring more I2C devices to the same pins (using the same I2C bus), remember to add pull-up resistors (4.7K is a good start) on both SDA and SCL otherwise you might experience communication problems. 
 

