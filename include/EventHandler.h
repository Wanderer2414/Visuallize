#pragma once
class EventHandler {
public:
    EventHandler(void* sender, void* parent, const float& clock);
    float               clock;
    void                *sender,
                        *parent;
};