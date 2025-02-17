#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>

#include "ReShape.h"

class Circle: public ReShape {
public:
    Circle(const float& radius = 0);

    bool                contains(const sf::Vector2f& point) override;

    float               getRadius() const;

    ReShape             &element(const size_t& index) override,
                        *clone(const size_t& index) override;
    
    size_t              getPointCount() const override;

    sf::Vector2f getPoint(size_t index) const override;

    void                dispose() override,
                        setPointCount(const size_t& count),
                        setRadius(const float& radius);
private:
    float               m_radius = 0;
    size_t              point_count = 30;
};