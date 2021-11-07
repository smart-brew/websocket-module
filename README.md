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
