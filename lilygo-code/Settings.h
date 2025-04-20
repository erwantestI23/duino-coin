// Settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

// ---------------------- General settings ---------------------- //
// Change the part in brackets to your Duino-Coin username
extern char *DUCO_USER = "";
// Change the part in brackets to your mining key (if you have set it in the wallet)
extern char *MINER_KEY = "";
// Change the part in brackets if you want to set a custom miner name
// Use Auto to autogenerate, None for no custom identifier
extern char *RIG_IDENTIFIER = "Lilygo";
// Change the part in brackets to your WiFi name
extern const char SSID[] = "";
// Change the part in brackets to your WiFi password
extern const char PASSWORD[] = "";
// -------------------------------------------------------------- //

// -------------------- Advanced options ------------------------ //
// Uncomment if you want to host the dashboard page (available on ESPs IP address and mDNS)
// #define WEB_DASHBOARD

// Comment out the line below if you wish to disable LED blinking
#define LED_BLINKING

// Uncomment if you want to use LAN8720. WLAN-credentials will be ignored using LAN
// Select correct Board in ArduinoIDE!!! Really!
// #define USE_LAN

// Comment out the line below if you wish to disable Serial printing
#define SERIAL_PRINTING

// Edit the line below if you wish to change the serial speed (low values may reduce performance but are less prone to interference)
#define SERIAL_BAUDRATE 500000

// ESP8266 WDT loop watchdog. Do not edit this value, but if you must - do not set it too low or it will falsely trigger during mining!
#define LWD_TIMEOUT 30000

// Uncomment to disable ESP32 brownout detector if you're suffering from faulty insufficient power detection
// #define DISABLE_BROWNOUT

// Uncomment to enable WiFiManager captive portal in AP mode
// The board will create its own network you connect to and change the settings
// REQUIRES WiFiManager library by tzapu (https://github.com/tzapu/WiFiManager)
// #define CAPTIVE_PORTAL
// -------------------------------------------------------------- //

// ------------------------ Displays ---------------------------- //

// #define DISPLAY_SSD1306
// #define DISPLAY_16X2
// #define BLUSHYBOX

// Uncomment to enable TFT ST7735 display (custom)
// Requires TFT_eSPI library and correct User_Setup.h
#define DISPLAY_TFT_ST7735
// -------------------------------------------------------------- //

// ---------------------- IoT examples -------------------------- //
// https://github.com/revoxhere/duino-coin/wiki/Duino's-take-on-the-Internet-of-Things

// Uncomment the line below if you wish to use the internal temperature sensor (Duino IoT example)
// Only ESP32-S2, -S3, -H2, -C2, -C3, -C6 and some old models have one!
// More info: https://www.espboards.dev/blog/esp32-inbuilt-temperature-sensor/
// NOTE: Mining performance will decrease by about 20 kH/s!
// #define USE_INTERNAL_SENSOR

// Uncomment the line below if you wish to use a DS18B20 temperature sensor (Duino IoT example)
// NOTE: Mining performance should stay the same
// #define USE_DS18B20

// Uncomment the line below if you wish to use a DHT11/22 temperature and humidity sensor (Duino IoT example)
// NOTE: Mining performance should stay the same
// #define USE_DHT

// Uncomment the line below if you wish to use a HSU07M sensor (Duino IoT Example)
// NOTE: Untested as of right now
// #define USE_HSU07M
// -------------------------------------------------------------- //

// ---------------- Variables and definitions ------------------- //
// You generally do not need to edit stuff below this line
// unless you're know what you're doing.

#if defined(ESP8266)
    // ESP8266
    #define LED_BUILTIN 2
#elif defined(CONFIG_FREERTOS_UNICORE) 
    #if defined(CONFIG_IDF_TARGET_ESP32C3)
      // ESP32-C3
      #define LED_BUILTIN 8
    #else
      // ESP32-S2
      #define LED_BUILTIN 15
    #endif
#else
    // ESP32
    #ifndef LED_BUILTIN
      #define LED_BUILTIN 2
    #endif
    #if defined(BLUSHYBOX)
      #define LED_BUILTIN 4
    #endif
#endif

#define BLINK_SETUP_COMPLETE 2
#define BLINK_CLIENT_CONNECT 5

#define SOFTWARE_VERSION "4.3"
extern unsigned int hashrate = 0;
extern unsigned int hashrate_core_two = 0;
extern unsigned int difficulty = 0;
extern unsigned long share_count = 0;
extern unsigned long accepted_share_count = 0;
extern String node_id = "";
extern String WALLET_ID = "";
extern unsigned int ping = 0;

#if defined(USE_INTERNAL_SENSOR)
  #include "driver/temp_sensor.h"
#endif

#if defined(USE_DS18B20)
  // Install OneWire and DallasTemperature libraries if you get an error
  #include <OneWire.h>
  #include <DallasTemperature.h>
  // Change 12 to the pin you've connected your sensor to
  const int DSPIN = 12;
  
  OneWire oneWire(DSPIN);
  DallasTemperature extern sensors(&oneWire);
#endif

#if defined(USE_DHT)
  // Install "DHT sensor library" if you get an error
  #include <DHT.h>
  // Change 12 to the pin you've connected your sensor to
  #define DHTPIN 12
  // Set DHT11 or DHT22 type accordingly
  #define DHTTYPE DHT11
  
  DHT extern dht(DHTPIN, DHTTYPE);
#endif

#if defined(USE_HSU07M)
    #include "Wire.h"
    #define HSU07M_ADDRESS 0x4B // Change this if your sensor has a different address

    float read_hsu07m() {
      Wire.beginTransmission(HSU07M_ADDRESS);
      Wire.write(0x00);
      Wire.endTransmission();
      delay(100);
      Wire.requestFrom(HSU07M_ADDRESS, 2);
      if(Wire.available() >= 2) {
          byte tempMSB = Wire.read();
          byte tempLSB = Wire.read();
          int tempRaw = (tempMSB << 8) | tempLSB;
          float tempC = (tempRaw / 16.0) - 40.0;
          return tempC;
      }
      return -1.0;
    }
#endif

IPAddress DNS_SERVER(1, 1, 1, 1); // Cloudflare DNS server

#endif  // End of SETTINGS_H
