//
// Created by JanHe on 14.06.2025.
//
#include <Arduino.h>
#include <WiFi.h>

#include "service/PageService.h"
#include "core/components/Button.h"
#include "core/components/Label.h"

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

    // Set Title of Page.
    index->setTitle("ESP32 Index");

    // Add Label Component.
    index->addComponent(new Label("Test 123"));

    // Add Button Component.
    auto button = index->addComponent(new Button("submit", "Click me!"));

    // Add Click Listener to Button.
    button->addListener("click", [](JsonObject data)
    {
        // Print to Serial.
        Serial.println("Button Clicked!");

        // Alert in Frontend.
        PageService::eval("alert('Response from Backend!');");
    });



    // Begin Server.
    server.begin();
}

// Simple lock to save CPU Bandwith.
void loop()
{
    delay(100);
}
