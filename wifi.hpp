#include <WiFi.h>

#include "config/config.hpp"

class WiFiCls {
 private:
  char pwd[50];
  char ssid[50];

 public:
  void start();
  WiFiCls(String ssid, String pwd);
};
