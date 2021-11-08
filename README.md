# websocket-module

## Developing

1. Rename `config (TEMPLATE).h` to `config.hpp` with correct settings

2. To use ESP32 with arduino IDE follow this manual:
   https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
   arduino.additionalUrls

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
  - to fix 'rtc_gpio_desc' error visit: https://githubmemory.com/repo/PaulStoffregen/OneWire/issues/100
- ModbusMaster from https://www.arduino.cc/reference/en/libraries/modbusmaster/
- Arduino-Temperature-Control-Library from https://github.com/milesburton/Arduino-Temperature-Control-Library
