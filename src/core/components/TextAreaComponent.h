//
// Created by JanHe on 15.06.2025.
//

#ifndef TEXTAREA_COMPONENT_H
#define TEXTAREA_COMPONENT_H

#include "Component.h"

class TextAreaComponent : public Component {
private:
    String value;
    int rows, cols;

public:
    TextAreaComponent(String id, int rows = 4, int cols = 40, String cssClass = "")
      : Component("textarea", id, cssClass), rows(rows), cols(cols) {}

    void setValue(const String& val) { value = val; }
    String getValue() const { return value; }

    String getContentHTML() override {
        String html = value;
        return html;
    }

    String toHTML() override {
        String html = "<textarea";
        if (!id.isEmpty()) html += " id=\"" + id + "\"";
        if (!cssClass.isEmpty()) html += " class=\"" + cssClass + "\"";
        html += " rows=\"" + String(rows) + "\" cols=\"" + String(cols) + "\"";
        html += ">";
        html += value;
        html += "</textarea>";
        return html;
    }
};

#endif
