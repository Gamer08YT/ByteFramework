//
// Created by JanHe on 14.06.2025.
//

#include "PageService.h"

// Define default Map.
std::map<String, Page*> PageService::pages = std::map<String, Page*>();

// Define defaults of Static Server.
AsyncWebServer* PageService::server = nullptr;

// Define default WebSocket Route.
AsyncWebSocket PageService::socket = AsyncWebSocket("/ws");
