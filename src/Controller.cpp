#include "../include/Controller.h"

Controller::Controller(sf::RenderTarget& target, void* parent, size_t& clock): 
                m_parent(parent), 
                m_target(target),
                m_clock(clock) {
    
};
bool Controller::isRedraw() {
    if (m_redraw) {
        m_redraw = false;
        return true;
    }
    return false;
}

float Controller::getClock() const {
    return m_clock;
}

void Controller::reDraw() {
    m_redraw = true;
}