/*
 * WifiSetupEsp32.cpp
 */
#include <Arduino.h>
#include <WiFi.h>
#include "WifiSetupEsp32.h"

WifiSetupEsp32::WifiSetupEsp32(String ssid, String password, String hostName, unsigned long wifiCheckIntervalMills)
{
    _ssid = ssid;
    _password = password;
    _hostName = hostName;
    _prevCheckMills = 0;
    _wifiCheckIntervalMills = wifiCheckIntervalMills;
}

void WifiSetupEsp32::wifiConnect(){
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.disconnect();
        WiFi.mode(WIFI_STA);

        Serial.print("connecting to SSID: ");
        Serial.println(_ssid.c_str());

        // Need to set host name.
        WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
        WiFi.setHostname(_hostName.c_str());

        WiFi.begin(_ssid.c_str(), _password.c_str());
        delay(10000);
    }
    Serial.print("WiFi connected: ");
    Serial.println(WiFi.localIP());
    Serial.print("Wifi mac: ");
    Serial.println(WiFi.macAddress());
}

void WifiSetupEsp32::wifiCheckLoop() {
    unsigned long curr = millis();
    if ((curr - _prevCheckMills) >= _wifiCheckIntervalMills && !checkWifiConnection()) {
        wifiConnect();
        _prevCheckMills = curr;
    }
}

bool WifiSetupEsp32::checkWifiConnection() {
    return WiFi.status() == WL_DISCONNECTED || WiFi.status() == WL_IDLE_STATUS;
}
