#ifndef WIFI_SETUP_ESP32
#define WIFI_SETUP_ESP32
#include <Arduino.h>

class WifiSetupEsp32 {
public:
    WifiSetupEsp32(String ssid, String password, String hostName="ESP32", unsigned long wifiCheckInterval = 60000);
    void wifiConnect();
    void wifiCheckLoop();

private:
    String _ssid;
    String _password;
    String _hostName;
    unsigned long _prevCheckMills;
    unsigned long _wifiCheckIntervalMills;
    bool isWifiDisconnected();
};

#endif
