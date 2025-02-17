#pragma once
#include "ReShape.h"
#include "Controller.h"
#include <SFML/Window/Event.hpp>
#include <functional>
#include "MouseEventHandler.h"

class Button: public Controller {
public:
    Button(sf::RenderTarget& target, void* parent, ReShape& shape, size_t& clock);
    ReShape         &m_shape;
    bool            catchEvent(const sf::Event& event)  override,
                    running()                           override,
                    focus()                             override;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    std::function<bool(sf::RenderTarget& target, const MouseEventHandler& handler)> 
                    onClick     = nullptr,
                    onReleased  = nullptr;
    ~Button();
protected:
private:
};