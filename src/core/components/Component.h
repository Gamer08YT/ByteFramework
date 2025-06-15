//
// Created by JanHe on 14.06.2025.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <Arduino.h>
#include <map>
#include <ArduinoJson.h>

/**
 * @class Component
 * @brief Represents a generic HTML component with a tag, ID, and CSS class.
 *
 * This class provides a base for creating custom HTML components by defining
 * the basic structure and attributes such as `tag`, `id`, and `cssClass`.
 * It also provides methods for generating the HTML representation of the component.
 *
 * The Listener Map contains dynamically executed Actions from the Frontend.
 * Currently, is no session support implemented.
 *
 * Derived classes must implement the `getContentHTML` method to define the specific
 * content structure within the component.
 */
class Component
{
protected:
    String id;
    String cssClass;
    String tag;
    std::map<String, std::function<void(JsonObject)>> listeners;

public:
    /**
     * @brief Constructs a Component with specified tag, ID, and CSS class.
     *
     * This constructor initializes a Component object with the given HTML tag,
     * ID, and CSS class. If no parameters are provided, a default tag is set to "div",
     * and the ID and CSS class are initialized as empty strings.
     *
     * @param tag The HTML tag name for the component (default is "div").
     * @param id The ID attribute for the component (default is an empty string).
     * @param cssClass The CSS class or classes for the component (default is an empty string).
     */
    Component(String tag = "div", String id = "", String cssClass = "")
        : tag(tag), id(id), cssClass(cssClass)
    {
    }


    /**
     * @brief Adds a listener for a specific event.
     *
     * Registers a callback function to be invoked when the specified event occurs.
     *
     * @param eventId A unique identifier representing the event to listen for.
     * @param callback The function to be executed when the event with the given `eventId` is triggered. It takes a `String` parameter representing event-specific data.
     */
    void addListener(const String& eventId, std::function<void(JsonObject)> callback)
    {
        listeners[eventId] = callback;
    }

    /**
     * @brief Triggers an event and executes the associated listener with the given data.
     *
     * This method looks up the specified event ID in the listeners map and, if a listener is found,
     * invokes the listener function with the provided data.
     *
     * @param eventId The identifier of the event to trigger.
     * @param data The data to pass to the listener associated with the event.
     */
    void triggerEvent(const String& eventId, const JsonObject& data)
    {
        auto it = listeners.find(eventId);

        if (it != listeners.end())
        {
            it->second(data);
        }
    }

    /**
     * @brief Sets the ID of the component.
     *
     * This method updates the ID attribute of the component with the provided value.
     *
     * @param newId The new ID to assign to the component.
     */
    void setId(const String& newId) { id = newId; }

    /**
     * @brief Sets the CSS class for the component.
     *
     * This method updates the `cssClass` attribute of the component to the specified value.
     *
     * @param newClass The new CSS class to assign to the component.
     */
    void setClass(const String& newClass) { cssClass = newClass; }

    /**
     * @brief Sets the tag name of the HTML component.
     *
     * This method allows configuring the tag name that will be used for the HTML representation
     * of the component. It validates the tag name to ensure it meets expected format criteria.
     *
     * @param tag The string representing the HTML tag name to set.
     */
    void setTag(const String& newTag) { tag = newTag; }

    /**
     * @brief Retrieves the ID associated with this instance.
     *
     * This method returns the unique identifier of the object,
     * allowing access to its associated `id` value.
     *
     * @return A string representing the object's ID.
     */
    String getId() const { return id; }

    /**
     * @brief Retrieves the CSS class associated with the component.
     *
     * This method returns the CSS class name as a string,
     * which can be used for styling purposes.
     *
     * @return The CSS class name of the component.
     */
    String getClass() const { return cssClass; }

    /**
     * @brief Retrieves the tag name of the component.
     *
     * This method returns the HTML tag name associated with the component.
     *
     * @return The tag name as a String.
     */
    String getTag() const { return tag; }

    /**
     * @brief Generates the HTML content specific to the derived component.
     *
     * This pure virtual method must be implemented by derived classes to define
     * the specific inner HTML content structure for the component. The method should
     * return the component's encapsulated content in HTML format.
     *
     * @return A string representing the HTML content of the component.
     */
    virtual String getContentHTML() = 0;

    /**
     * @brief Generates the HTML representation of the component.
     *
     * Constructs the HTML structure of the component using its tag, ID,
     * and CSS class attributes. Derived classes are responsible for
     * implementing the `getContentHTML` method, which defines the specific
     * content to be inserted within the component.
     *
     * @return A string containing the full HTML representation of the component.
     */
    virtual String toHTML()
    {
        String html = "<" + tag;
        if (id.length() > 0) html += " id=\"" + id + "\"";
        if (cssClass.length() > 0) html += " class=\"" + cssClass + "\"";
        html += ">";
        html += getContentHTML();
        html += "</" + tag + ">";
        return html;
    }

    /**
     * @brief Virtual destructor for the Component class.
     *
     * Ensures proper cleanup of resources when a derived Component object is destroyed.
     * Allows for polymorphic deletion when dealing with base class pointers.
     */
    virtual ~Component()
    {
    }

    /**
     * @brief Checks if the component has any registered listeners.
     *
     * This method determines whether there are any listeners currently associated
     * with the component by evaluating the size of the listeners collection.
     *
     * @return True if there is at least one registered listener; otherwise, false.
     */
    bool hasListeners()
    {
        return listeners.size() > 0;
    }

    /**
     * @brief Retrieves a map of listeners for handling JSON object actions.
     *
     * This method returns a map containing keys as string identifiers and
     * values as corresponding function callbacks. These callbacks handle
     * actions represented by JSON objects.
     *
     * @return A map where keys are string identifiers and values are
     *         std::function<void(JsonObject)> representing action handlers.
     */
    std::map<String, std::function<void(JsonObject)>> getListener()
    {
        return listeners;
    }
};

#endif
