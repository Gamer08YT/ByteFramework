//
// Created by JanHe on 14.06.2025.
//

#ifndef LABEL_H
#define LABEL_H

#include "Component.h"

class Label : public Component {
private:
    String text;

public:
    Label(String text, String id = "", String cssClass = "")
      : Component("p", id, cssClass), text(text) {}

    void setText(const String& newText) { text = newText; }

    String getContentHTML() override {
        return text;
    }
};

#endif
