#include "../include/Node.h"
#include <SFML/Graphics/RenderTarget.hpp>

Node::Node(sf::RenderTarget& target,  void* m_parent, const float& radius, const sf::Font& font, size_t& clock):
        Controller(target, m_parent, clock),
        m_text("", font),
        m_circle(radius),
        m_radius(radius)
{
}
void Node::setText(const std::string& string) {
    m_text.setString(string);
    reDraw();
}
void Node::setPosition(const float& x, const float& y) {
    m_circle.setPosition(x, y);
    m_text.setPosition(x+m_radius - 1.0f*m_text.getString().getSize()/2*m_text.getCharacterSize(), y + m_radius - 1.0f*m_text.getCharacterSize()/2);
    reDraw();
}
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_circle);
    target.draw(m_text);
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