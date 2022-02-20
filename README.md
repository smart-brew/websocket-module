# websocket-module

## Developing

1. Rename `config (TEMPLATE).h` to `config.hpp` with correct settings

2. To use ESP32 with arduino IDE follow this manual:
   https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
   arduino.additionalUrls

   **Or** use VSCode (recommended for better IntelliSense) with Arduino extension (needs similar config as Arduino IDE)

3. Update `c_cpp_properties.json` with your path

```json
"env": {
   "pathToArduino": "your\\path\\to\\arduino",
   "pathToLib": "your\\path\\to\\lib"
},
```

4. Install libraries

- ArduinoJson by Benoit Blanchon
- WebSockets by Markus Sattler
- ESP32Servo by John K.
- OneWire by Jim Studt
  - IMPORTANT: to fix 'rtc_gpio_desc' error visit: https://githubmemory.com/repo/PaulStoffregen/OneWire/issues/100
    **or** _Find 'rtc_gpio_desc' replace with 'rtc_io_desc' in the 'OneWire_direct_gpio.h' file solved the issue_
- ModbusMaster from https://www.arduino.cc/reference/en/libraries/modbusmaster/
- Arduino-Temperature-Control-Library from https://github.com/milesburton/Arduino-Temperature-Control-Library

## Debugging help

Error during upload to **some** ESP boards - TIMED_OUT - press (5 sec) BOOT button on ESP during upload
https://randomnerdtutorials.com/solved-failed-to-connect-to-esp32-timed-out-waiting-for-packet-header/
