#pragma once
#include "EventHandler.h"
enum ButtonState {
    None,
    Left,
    Middle,
    Right
};

class MouseEventHandler: public EventHandler {
public:
    MouseEventHandler(const unsigned int& x, const unsigned int& y, void* sender, void* parent, const float& clock);
    unsigned int                x, 
                                y;
    ButtonState                 button;
private:
};
