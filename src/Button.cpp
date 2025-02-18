#include "../include/Button.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

Button::Button(sf::RenderTarget& target, void* parent, ReShape& shape, size_t& clock):
                Controller(target, parent, clock),
                m_shape(shape) {}
                
bool Button::focus() {
    if (onFocus) onFocus(m_target, EventHandler(this, m_parent, getClock()));
    return false;
}
bool Button::running() {
    if (onRunning) return onRunning(m_target, EventHandler(this, m_parent, getClock()));
    return false;
}
bool Button::catchEvent(const sf::Event& event) {
    sf::RenderWindow* window = (sf::RenderWindow*)&m_target;
    sf::View view = window->getView();
    sf::Vector2f relative = view.getCenter();
    relative.x -= view.getSize().x/2;
    relative.y -= view.getSize().y/2;
    if (event.type == sf::Event::MouseButtonPressed) {
        if (m_shape.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)) + relative)) {
            MouseEventHandler handler(event.mouseButton.x, event.mouseButton.y, this, m_parent, getClock());
            switch (event.mouseButton.button) {
                case sf::Mouse::Button::Left: handler.button = ButtonState::Left; break;
                case sf::Mouse::Button::Right: handler.button = ButtonState::Right; break;
                default: handler.button = ButtonState::Middle; break;
            }
            if (onFocus && onFocus(m_target, EventHandler(this, m_parent, getClock()))) reDraw(); 
            if (onClick &&onClick(m_target, handler)) reDraw();
            isFocus = true;
            return isRedraw();
        } else if (isFocus && lostFocus && lostFocus(m_target, EventHandler(this, m_parent, getClock()))) {
            isFocus = false;
            return isRedraw();
        }
    } else if (event.type == sf::Event::MouseButtonReleased && onReleased) {
        if (m_shape.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)) + relative)) {
            MouseEventHandler handler(event.mouseButton.x, event.mouseButton.y, this, m_parent, getClock());
            switch (event.mouseButton.button) {
                case sf::Mouse::Button::Left: handler.button = ButtonState::Left; break;
                case sf::Mouse::Button::Right: handler.button = ButtonState::Right; break;
                default: handler.button = ButtonState::Middle; break;
            }
            return onReleased(m_target, handler);
        }
    }
    return false;
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(m_shape, state);
}
Button::~Button() {

}
