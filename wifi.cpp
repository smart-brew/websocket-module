#include "wifi.hpp"

// IPAddress local_IP(10, 20, 1, 7);
// IPAddress gateway(10, 20, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

WiFiCls::WiFiCls(String _ssid, String _pwd) {
  _ssid.toCharArray(ssid, 50);
  _pwd.toCharArray(pwd, 50);
}

void WiFiCls::start() {
  Serial.println(ssid);
  Serial.println(pwd);
  Serial.println("[WIFI] Connecting wifi...");

  // Configures static IP address
  // if (!WiFi.config(local_IP, gateway, subnet)) {
  //   Serial.println("STA Failed to configure");
  // }

  // wifi login
  WiFi.begin(ssid, pwd);

  // wait to load wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WIFI] Retry wifi...");
    delay(1000);
  }

  IPAddress ip = WiFi.localIP();

  Serial.printf("[WIFI] WiFi connected (my ip: %s)\n", ip.toString().c_str());
}
