#pragma once
#include <SFML/System/Vector2.hpp>

#include "ReShape.h"
class Rectangle:public ReShape {
public:
    Rectangle(const sf::Vector2f& size = {0,0});

    bool                contains(const sf::Vector2f& point) override;

    ReShape             *clone(const size_t& index) override,
                        &element(const size_t& index) override;

    void                dispose() override,
                        setSize(const sf::Vector2f& size);

    size_t              getPointCount() const override;

    sf::Vector2f        getPoint(size_t index) const override,
                        getSize() const;
    ~Rectangle();
private:
    sf::Vector2f        m_size = {0,0};
};