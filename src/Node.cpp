#include "../include/Node.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <bits/types/cookie_io_functions_t.h>

Node::Node(sf::RenderTarget& target,  void* m_parent, const float& radius, const sf::Font& font, size_t& clock):
        Controller(target, m_parent, clock),
        m_text("", font),
        m_circle(radius),
        m_radius(radius)
{
    auto color = m_circle.getFillColor();
    m_text.setFillColor(sf::Color(255-color.a, 255-color.b, 255-color.b));
}
void Node::setText(const std::string& string) {
    m_text.setString(string);
    reDraw();
}
void Node::setPosition(const float& x, const float& y) {
    m_circle.setPosition(x, y);
    auto bound = m_text.getGlobalBounds();
    m_text.setPosition(x+m_radius - bound.width/2, y + m_radius - bound.height/2);
    reDraw();
}
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_circle);
    target.draw(m_text);
}
sf::Vector2f Node::getPosition() const {
    return m_circle.getPosition();
}

bool Node::catchEvent(const sf::Event& event) {
    return false;
}
bool Node::running() {
    return false;
}
bool Node::focus() {
    return false;
}