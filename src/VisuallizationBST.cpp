#include "../include/VisuallizationBST.h"
#include <SFML/Graphics/Color.hpp>
#include <stdexcept>
VisuallizationForm::VisuallizationForm(sf::RenderTarget& target):
            Form(target, nullptr, m_clock),
            addBox(target, this, m_add_text,m_clock),
            addTouch(target, this, addReg, m_clock),
            addReg({150,50}, 10)
{
    if (!m_font.loadFromFile("Oswald-Regular.ttf")) std::runtime_error("Font not found");

    addTouch.m_shape.setPosition(10, 10);
    addTouch.onClick = [&](sf::RenderTarget& target, const MouseEventHandler& handler)->bool {
        addBox.enter();
        return false;
    };
    addBox.text().setFillColor(sf::Color::Black);
    addBox.text().setFont(m_font);
    addBox.text().setPosition(15,20);
    addReg.setFillColor(sf::Color::White);
    setFPS(20);
    children.add(&addTouch);
    children.add(&addBox);
    reDraw();
}
bool VisuallizationForm::catchEvent(const sf::Event& event) {
    return false;
}
bool VisuallizationForm::running() {
    return false;
}
bool VisuallizationForm::focus() {
    return false;
}
VisuallizationForm::~VisuallizationForm() {
    
}