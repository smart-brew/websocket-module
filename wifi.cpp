#include "wifi.hpp"

WiFiCls::WiFiCls(String _ssid, String _pwd) {
  _ssid.toCharArray(ssid, 50);
  _pwd.toCharArray(pwd, 50);
}

void WiFiCls::start() {
  Serial.println(ssid);
  Serial.println(pwd);
  Serial.println("[WIFI] Connecting wifi...");

  // wifi login
  WiFi.begin(ssid, pwd);

  // wait to load wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WIFI] Retry wifi...");
    delay(1000);
  }

  Serial.println("[WIFI] WiFi connected");
}
