#pragma once
#include "Controller.h"
#include "Circle.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
class Node : public Controller {
    Node(sf::RenderTarget& target, void* m_parent, const float& radus, const sf::Font& font, size_t& clock);

    virtual bool        catchEvent(const sf::Event& event)  override,
                        running()                           override,
                        focus()                             override;
    void setPosition(const float& x, const float& y);
    void setText(const std::string& string);
protected:
    void draw(sf::RenderTarget& render, sf::RenderStates states) const override;
private:
    Circle              m_circle;
    sf::Text            m_text;
    float               m_radius;
};