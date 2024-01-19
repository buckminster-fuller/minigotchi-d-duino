//////////////////////////////////////////////////
// pwnagotchi.cpp: handles pwnagotchi detection //
//////////////////////////////////////////////////

#include "pwnagotchi.h"
#include <ArduinoJson.h>
#include "raw80211.h"
#include <user_interface.h>
#include <ESP8266WiFi.h>

namespace {
    Pwnagotchi* pwnInstance = nullptr;

    void rawCallback(const wifi_ieee80211_mac_hdr_t *hdr, int rssi, const unsigned char *buff, short unsigned int buff_len) {
        if (pwnInstance) {
            pwnInstance->handle(hdr, rssi, buff, buff_len);
        }
    }
}

Pwnagotchi::Pwnagotchi() {
    // init the class
    essid = "de:ad:be:ef:de:ad";
    // register the function
    Raw80211::register_cb(&rawCallback);
    Serial.println("Callback registered");
}

void Pwnagotchi::getMAC(char* addr, const unsigned char* buff, int offset) {
    snprintf(addr, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
             buff[offset], buff[offset + 1], buff[offset + 2],
             buff[offset + 3], buff[offset + 4], buff[offset + 5]);
}

String Pwnagotchi::extractMAC(const unsigned char *buff) {
    char addr[] = "00:00:00:00:00:00";
    getMAC(addr, buff, 10);
    return String(addr);
}

void Pwnagotchi::detectAndHandle() {
    // cool animation here
    for (int i = 0; i < 5; ++i) {
        Serial.println("(0-o) Scanning for Pwnagotchi.");
        delay(500);
        Serial.println("(o-0) Scanning for Pwnagotchi..");
        delay(500);
        Serial.println("(0-o) Scanning for Pwnagotchi...");
        delay(500);
    }

    // static instance
    pwnInstance = this;

    // delay for scanning
    delay(5000);

    // check if the rawCallback was triggered during scanning
    if (!pwnInstance->pwnagotchiDetected) {
        // only searches on your current channel and such afaik, 
        // so this only applies for the current searching area
        Serial.println("(;-;) No Pwnagotchi found.");
    }
}

void Pwnagotchi::handle(const wifi_ieee80211_mac_hdr_t *hdr, int rssi, const unsigned char *buff, short unsigned int buff_len) {
    // check if it is a beacon frame
    if (buff[0] == 0x80) {
        // extract mac
        char addr[] = "00:00:00:00:00:00";
        String src = extractMAC(buff);

        // check if the source MAC matches "de:ad:be:ef:de:ad"
        if (src == "de:ad:be:ef:de:ad") {
            pwnagotchiDetected = true;
            Serial.println("(^-^) Pwnagotchi detected!");

            // extract the ESSID from the beacon frame
            String essid(reinterpret_cast<const char*>(&buff[36]));

            Serial.print("ESSID: ");
            Serial.println(essid);

            // load json from the ESSID
            DynamicJsonDocument jsonBuffer(1024);
            DeserializationError error = deserializeJson(jsonBuffer, essid);

            // check if json parsing is successful
            if (error) {
                Serial.print(F("(X-X) Could not parse Pwnagotchi json: "));
                Serial.println(error.c_str());
            } else {
                Serial.println("\n(^-^) Successfully parsed json");

                // find out some stats
                String name = jsonBuffer["name"].as<String>();
                String pwndTot = jsonBuffer["pwnd_tot"].as<String>();

                // print the info
                Serial.print("(^-^) Pwnagotchi name: ");
                Serial.println(name);
                Serial.print("(^-^) Pwned Networks: ");
                Serial.println(pwndTot);
            }
        }
    }
}
