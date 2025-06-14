//
// Created by JanHe on 14.06.2025.
//

#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <map>
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <core/Page.h>
#include <ArduinoJson.h>

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

    /**
     * Represents an asynchronous WebSocket endpoint used for handling WebSocket connections.
     *
     * This WebSocket is associated with the specified endpoint path "/ws" and is used to
     * facilitate communication between the client and the server in a non-blocking manner.
     */
    static AsyncWebSocket socket;

    /**
     * Handles WebSocket events by processing incoming messages, extracting information,
     * and triggering corresponding events within the application.
     *
     * This method is intended to process specific types of WebSocket events, such as
     * incoming text messages, and handle them accordingly by parsing JSON content and
     * executing associated logic.
     *
     * @param server A pointer to the AsyncWebSocket instance managing the WebSocket server.
     * @param client A pointer to the AsyncWebSocketClient instance representing the connected client.
     * @param type The type of WebSocket event being triggered (e.g., WS_EVT_DATA).
     * @param arg A void pointer to additional arguments associated with the event (e.g., frame details).
     * @param data A pointer to the data payload received in the WebSocket message.
     * @param len The length of the data payload in bytes.
     */
    static void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
                                 AwsEventType type, void* arg, uint8_t* data, size_t len)
    {
        if (type == WS_EVT_DATA)
        {
            AwsFrameInfo* info = (AwsFrameInfo*)arg;

            if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
            {
                String msg = "";
                for (size_t i = 0; i < len; i++)
                {
                    msg += (char)data[i];
                }

                // ArduinoJson 7 or so allow dynamic deserialization.
                JsonDocument doc;

                // Try to deserialize JSON Packet.
                deserializeJson(doc, msg);

                DeserializationError error = deserializeJson(doc, msg);

                if (error)
                {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.f_str());
                    client->text("{\"error\":\"Invalid JSON\"}");
                    return;
                }

                // JSON Example: {"page": "/", "component": "test123","event": "click", "data": "xyz" }
                const char* eventId = doc["event"];
                const char* eventData = doc["data"];

                if (eventId != nullptr)
                {
                    // Try to get page by id.
                    auto page = getPageById(String(doc["page"]));

                    if (page != nullptr)
                    {
                        // Try to get component by id.
                        auto component = page->getComponentById(String(doc["component"]));

                        if (component != nullptr)
                        {
                            // Trigger the right listener of the component on the right page.
                            component->triggerEvent(String(doc["event"]), doc["data"]);

                            // Send response to client.
                            client->text("{\"status\":\"Event processed\"}");
                        }
                        else
                        {
                            // Send response to client.
                            client->text("{\"error\":\"Component not found\"}");
                        }
                    }
                    else
                    {
                        // Send response to client.
                        client->text("{\"error\":\"Page not found\"}");
                    }
                }
                else
                {
                    // Send response to client.
                    client->text("{\"error\":\"No event specified\"}");
                }
            }
        }
    }

public:
    /**
     * Initializes and assigns the provided AsyncWebServer instance to the internal server.
     *
     * Add WebSocket Channel for Backend Communication on Route /ws.
     *
     * @param srv A pointer to the AsyncWebServer instance to be used by the system.
     */
    static void begin(AsyncWebServer* srv)
    {
        server = srv;

        // Register Channel Listener.
        socket.onEvent(onWebSocketEvent);

        // Add WebSocket to AsyncServer.
        server->addHandler(&socket);
    }

    /**
     * Retrieves a Page object corresponding to the given unique identifier string.
     *
     * Searches through the collection of pages and returns the Page object associated
     * with the specified identifier, if it exists.
     *
     * @param id The unique identifier string for the Page to retrieve.
     * @return A pointer to the Page object if found, or nullptr if no Page is associated with the given identifier.
     */
    static Page* getPageById(const String& id)
    {
        auto it = pages.find(id);

        if (it != pages.end())
        {
            return it->second;
        }

        return nullptr; // Not found
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

            // Send response to a client.
            request->send(response);
        });

        return page;
    }
};

#endif
