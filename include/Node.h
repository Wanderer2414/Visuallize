#pragma once
#include "Controller.h"
#include "Circle.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
class Node : public Controller {
public:
    Node(sf::RenderTarget& target, void* m_parent, const float& radius, const sf::Font& font, size_t& clock);
    int                 value;
    Node                *left = nullptr, *right = nullptr, *parent = nullptr;
    virtual bool        catchEvent(const sf::Event& event)  override,
                        running()                           override,
                        focus()                             override;
    void                setPosition(const float& x, const float& y),
                        setText(const std::string& string);
    sf::Vector2f        getPosition() const;
    Circle              m_circle;
    sf::Text            m_text;
protected:
    void draw(sf::RenderTarget& render, sf::RenderStates states) const override;
private:
    float               m_radius;
};