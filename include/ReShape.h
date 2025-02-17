#pragma once
#include <SFML/Graphics/Shape.hpp>

class ReShape: public sf::Shape {
public:
    virtual ReShape         *clone(const size_t& = 1)           = 0,
                            &element(const size_t& index)       = 0;
    virtual void            dispose()                           = 0;
    virtual bool            contains(const sf::Vector2f& point) = 0;
};