//
// Created by JanHe on 14.06.2025.
//

#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <map>
#include <Arduino.h>
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

public:
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

        return page;
    }
};

#endif
