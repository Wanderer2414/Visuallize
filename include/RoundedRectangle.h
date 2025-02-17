#pragma once
#include <SFML/System/Vector2.hpp>

#include "ReShape.h"
class RoundedRectangle:public ReShape {
public:
    RoundedRectangle(const sf::Vector2f& size = {0,0}, const float& radius = 0);

    bool contains(const sf::Vector2f& point) override;
    ReShape* clone(const size_t& index) override;
    ReShape& element(const size_t& index) override;
    void dispose() override;

    size_t getPointCount() const override;
    sf::Vector2f getPoint(size_t index) const override;
    void setPointCount(const size_t& count);

    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;
    void setRadius(const float& radius);
    float getRadius() const;
private:
    sf::Vector2f m_size = {0,0};
    float m_radius = 0;
    size_t point_count = 30;
    float pointEachCount;
};