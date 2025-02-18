#pragma once
#include <cstddef>
class EventHandler {
public:
    EventHandler(void* sender, void* parent, const size_t& clock);
    size_t              clock;
    void                *sender,
                        *parent;
};