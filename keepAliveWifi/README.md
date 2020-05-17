# ESP32 - keepAliveWifi

An example of how to keep your WiFi connection alive using the ESP32, Arduino IDE and FreeRTOS. 

**Config:** Insert your own `WIFI_SSID` and `WIFI_PASSWORD`

**Logic:**

1. If no connection found, try connecting for 20 seconds.
2. Once connected, checks the WiFi connection every 10 seconds. 
3. If connection attempt fails, retry in 30 seconds. 

Example of serial output: 

```
14:13:04.228 -> [keepAliveWifi] Connecting to Lab-educate
14:13:04.228 -> .........................................
14:13:24.745 -> [keepAliveWifi] Connection failed. Retrying in 30 seconds.
14:13:54.731 -> [keepAliveWifi] Connecting to Lab-educate
14:13:54.731 -> .........................................
14:14:15.253 -> [keepAliveWifi] Connection failed. Retrying in 30 seconds.
14:14:45.255 -> [keepAliveWifi] Connecting to Lab-educate
14:14:45.255 -> .............................
14:14:59.752 -> [keepAliveWifi] WiFi Connected. IP: 192.168.8.100
```