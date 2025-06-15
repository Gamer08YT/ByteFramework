//
// Created by JanHe on 15.06.2025.
//

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Component.h"

class Checkbox : public Component {
private:
    bool checked;

public:
    Checkbox(String id, bool checked = false, String cssClass = "")
      : Component("input", id, cssClass), checked(checked) {}

    void setChecked(bool c) { checked = c; }
    bool isChecked() const { return checked; }

    String getContentHTML() override {
        return "";
    }

    String toHTML() override {
        String html = "<input type=\"checkbox\"";
        if (!id.isEmpty()) html += " id=\"" + id + "\"";
        if (!cssClass.isEmpty()) html += " class=\"" + cssClass + "\"";
        if (checked) html += " checked";
        html += ">";
        return html;
    }
};

#endif
