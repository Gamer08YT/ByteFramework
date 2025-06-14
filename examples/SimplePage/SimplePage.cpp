//
// Created by JanHe on 14.06.2025.
//
#include <Arduino.h>
#include <WiFi.h>

#include "../../src/service/PageService.h"
#include "../../src/core/components/Button.h"
#include "../../src/core/components/Label.h"

AsyncWebServer server(80);

void setup()
{
    // Begin Serial.
    Serial.begin(115200);

    // Setup WiFi AP.
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ByteFramework");

    // Begin Page Service.
    PageService::begin(&server);

    // Build a simple Page.
    auto index = PageService::addPage("/", new Page());

    index->setTitle("ESP32 Index");
    index->addComponent(new Label("Test 123"));

    // Add clickable Button:
    auto button = index->addComponent(new Button("submit", "Click me!"));



    // Begin Server.
    server.begin();
}

// Simple lock to save CPU Bandwith.
void loop()
{
    delay(100);
}
