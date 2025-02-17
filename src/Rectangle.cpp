#include "../include/Rectangle.h"
#include <SFML/System/Vector2.hpp>
#include <cstring>
#include <memory.h>

Rectangle::Rectangle(const sf::Vector2f& size) {
    setSize(size);
};

bool Rectangle::contains(const sf::Vector2f& point) {
    return getGlobalBounds().contains(point);
}

ReShape* Rectangle::clone(const size_t& count) {
    Rectangle* rect = new Rectangle[count];
    for (int i = 0; i<count; i++) {
        rect[i] = *this;
    }
    return (ReShape*)rect;
}
ReShape& Rectangle::element(const size_t& index) {
    return ((Rectangle*)this)[index];
}

size_t Rectangle::getPointCount() const {
    return 4;
}

void Rectangle::setSize(const sf::Vector2f& size) {
    m_size = size;
    update();
}

void Rectangle::dispose() {
    delete[] this;
}

sf::Vector2f Rectangle::getPoint(size_t index) const {
    switch (index) {
        case 0: return {0, 0}; break;
        case 1: return {m_size.x, 0}; break;
        case 2: return {m_size.x, m_size.y}; break;
        default: return {0, m_size.y}; break;
    }
}

sf::Vector2f Rectangle::getSize() const {
    return m_size;
}
Rectangle::~Rectangle() {
    
}