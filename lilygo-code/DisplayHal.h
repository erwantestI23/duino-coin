#ifndef DISPLAY_HAL_H
#define DISPLAY_HAL_H

#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

void screen_setup() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.println("Duino-Coin");
    tft.println("TFT Ready");
    delay(1500);
}

void display_boot() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.println("Boot...");
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println(__DATE__);
    tft.println(__TIME__);
    delay(1500);
}

void display_info(String message) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.println("Info:");
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println(message);
}

void display_mining_results(String hashrate, String accepted_shares, String total_shares, String uptime, String node, 
                            String difficulty, String sharerate, String ping, String accept_rate) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.printf("HR:%s kH/s\n", hashrate.c_str());
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(1);
    tft.printf("Shares: %s/%s\n", accepted_shares.c_str(), total_shares.c_str());
    tft.printf("Uptime: %s\n", uptime.c_str());
    tft.printf("Node: %s\n", node.c_str());
    tft.printf("Diff: %s\n", difficulty.c_str());
    tft.printf("Shr/s: %s\n", sharerate.c_str());
    tft.printf("Ping: %sms\n", ping.c_str());
    tft.printf("OK: %s%%\n", accept_rate.c_str());
}

#endif
