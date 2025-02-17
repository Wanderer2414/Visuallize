#include "Circle.h"
#include <SFML/System/Vector2.hpp>
#include <cstring>
#include <math.h>

Circle::Circle(const float& radius):m_radius(radius) {
    update();
};
bool Circle::contains(const sf::Vector2f& point) {
    sf::Vector2f dis = getPosition() + sf::Vector2f(m_radius, m_radius) - point;
    return std::sqrt(dis.x*dis.x + dis.y*dis.y)<=m_radius;
}
ReShape* Circle::clone(const size_t& count) {
    Circle* rect = new Circle[count];
    for (int i = 0; i<count; i++) {
        rect[i] = *this;
    }
    return (ReShape*)rect;
}
ReShape& Circle::element(const size_t& index) {
    return ((Circle*)this)[index];
}
void Circle::dispose() {
    delete[] this;
}

size_t Circle::getPointCount() const {
    return point_count;
}
void Circle::setPointCount(const size_t& count) {
    point_count = count;
}
sf::Vector2f Circle::getPoint(size_t index) const {
    float angle = M_PI*2*index/point_count + M_PI;
    return {m_radius + m_radius*cos(angle), m_radius+m_radius*sin(angle)};
}

void Circle::setRadius(const float& radius) {
    m_radius = radius;
    update();
}
float Circle::getRadius() const {
    return m_radius;
}