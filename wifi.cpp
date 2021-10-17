#include "wifi.hpp"

// wifi
WiFiMulti WiFiMulti;

void startWifi()
{
    Serial.println("[WIFI] Connecting wifi...");

    // wifi login
    WiFiMulti.addAP(WIFI_SSID, WIFI_PWD);

    // wait to load wifi
    while (WiFiMulti.run() != WL_CONNECTED)
    {
        Serial.println("[WIFI] Retry wifi...");
        delay(1000);
    }
}