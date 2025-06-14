//
// Created by JanHe on 14.06.2025.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"

class Button : public Component {
private:
    String label;

public:
    Button(String label, String id = "", String cssClass = "")
      : Component("button", id, cssClass), label(label) {}

    void setLabel(const String& newLabel) { label = newLabel; }

    String getContentHTML() override {
        return label;
    }
};

#endif

