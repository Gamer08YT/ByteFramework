//
// Created by JanHe on 14.06.2025.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <Arduino.h>

class Component {
protected:
    String id;
    String cssClass;
    String tag;

public:
    Component(String tag = "div", String id = "", String cssClass = "")
      : tag(tag), id(id), cssClass(cssClass) {}

    void setId(const String& newId) { id = newId; }
    void setClass(const String& newClass) { cssClass = newClass; }
    void setTag(const String& newTag) { tag = newTag; }

    String getId() const { return id; }
    String getClass() const { return cssClass; }
    String getTag() const { return tag; }

    // Template-Methode: HTML-Tag mit Attributen generieren
    virtual String getContentHTML() = 0;

    virtual String toHTML() {
        String html = "<" + tag;
        if (id.length() > 0) html += " id=\"" + id + "\"";
        if (cssClass.length() > 0) html += " class=\"" + cssClass + "\"";
        html += ">";
        html += getContentHTML();
        html += "</" + tag + ">";
        return html;
    }

    virtual ~Component() {}
};

#endif
