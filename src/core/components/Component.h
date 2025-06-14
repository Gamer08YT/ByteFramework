//
// Created by JanHe on 14.06.2025.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <Arduino.h>

/**
 * @class Component
 * @brief Represents a generic HTML component with a tag, ID, and CSS class.
 *
 * This class provides a base for creating custom HTML components by defining
 * the basic structure and attributes such as `tag`, `id`, and `cssClass`.
 * It also provides methods for generating the HTML representation of the component.
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

    String getId() const { return id; }
    String getClass() const { return cssClass; }
    String getTag() const { return tag; }

    // Template-Methode: HTML-Tag mit Attributen generieren
    virtual String getContentHTML() = 0;

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

    virtual ~Component()
    {
    }
};

#endif
