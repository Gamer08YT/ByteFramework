//
// Created by JanHe on 14.06.2025.
//
#include <Arduino.h>
#include "service/PageService.h"
#include "core/components/Button.h"
#include "core/components/Label.h"

void setup()
{
    auto index = PageService::addPage("/", new Page());

    index->setTitle("ESP32 Index");
    index->addComponent(new Label("Test 123"));
    index->addComponent(new Button("submit", "Click me!"));
}

void loop()
{
}
