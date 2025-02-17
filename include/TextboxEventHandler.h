#pragma once
#include "EventHandler.h"
#include <string>
class TextboxEventHandler:public EventHandler {
public:
    TextboxEventHandler(void* sender, void* parent, std::string& content, const float& clock);
    std::string&            content;
private:
};