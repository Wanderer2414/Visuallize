#pragma once
#include "EventHandler.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

class Controller: public sf::Drawable {
public:
    Controller(sf::RenderTarget& target, void* m_parent, size_t& clock);

    virtual bool        catchEvent(const sf::Event& event) = 0,
                        running() = 0,
                        focus() = 0;

    float               getClock() const;

    std::function<bool(sf::RenderTarget& target, const EventHandler& clock)>
                        onFocus = nullptr,
                        onRunning = nullptr,
                        lostFocus = nullptr;
protected:
    bool                isRedraw();
    void                *m_parent,
                        reDraw();

    sf::RenderTarget    &m_target;
private:
    bool                m_redraw = false;

    size_t              &m_clock;
};