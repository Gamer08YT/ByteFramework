//
// Created by JanHe on 14.06.2025.
//

#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <map>
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <core/Page.h>

class PageService
{
private:
    /**
     * Represents a static collection that maps a unique identifier string to Page pointers.
     *
     * The map is used to store and manage Page objects, where each page is identified
     * by a unique string key.
     */
    static std::map<String, Page*> pages;

    /**
     * Pointer to an AsyncWebServer instance responsible for managing and handling HTTP requests asynchronously.
     *
     * This object facilitates the setup and management of web server functionalities such as routing,
     * handling client connections, serving files, and other web-based interactions without blocking execution.
     */
    static AsyncWebServer* server;

public:
    /**
     * Initializes and assigns the provided AsyncWebServer instance to the internal server.
     *
     * @param srv A pointer to the AsyncWebServer instance to be used by the system.
     */
    static void begin(AsyncWebServer* srv)
    {
        server = srv;
    }

    /**
     * Adds a new page to the collection using the specified path as the identifier.
     *
     * @param path The identifier for the page, typically representing a URL or route.
     * @param page A pointer to the Page object to be added.
     * @return A pointer to the Page object that was added.
     */
    static Page* addPage(const String& path, Page* page)
    {
        pages[path] = page;

        server->on(path.c_str(), HTTP_GET, [=](AsyncWebServerRequest* request)
        {
            // Prepare custom response.
            AsyncWebServerResponse* response = request->beginResponse(200, "text/html", page->render());

            // Add Framework Header.
            response->addHeader("X-Framework", "ByteFramework");

            // Send response to client.
            request->send(response);
        });

        return page;
    }
};

#endif
