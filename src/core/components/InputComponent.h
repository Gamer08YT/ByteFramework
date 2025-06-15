//
// Created by JanHe on 15.06.2025.
//

#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "Component.h"

class InputComponent : public Component {
private:
    String type;
    String value;
    String placeholder;

public:
    InputComponent(const String& id, const String& type = "text", const String& placeholder = "", const String& cssClass = "")
      : Component("input", id, cssClass), type(type), placeholder(placeholder) {}

    void setValue(const String& val) { value = val; }
    String getValue() const { return value; }

    void setPlaceholder(const String& ph) { placeholder = ph; }

    String getContentHTML() override {
        return "";
    }

    String toHTML() override {
        String html = "<input";
        html += " type=\"" + type + "\"";
        if (!id.isEmpty()) html += " id=\"" + id + "\"";
        if (!cssClass.isEmpty()) html += " class=\"" + cssClass + "\"";
        if (!placeholder.isEmpty()) html += " placeholder=\"" + placeholder + "\"";
        if (!value.isEmpty()) html += " value=\"" + value + "\"";
        html += ">";
        return html;
    }
};

#endif

