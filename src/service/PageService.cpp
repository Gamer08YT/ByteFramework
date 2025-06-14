//
// Created by JanHe on 14.06.2025.
//

#include "PageService.h"

std::map<String, Page*> PageService::pages = std::map<String, Page*>();
AsyncWebServer* PageService::server = nullptr;