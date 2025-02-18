#include "../include/VisuallizationBST.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <stdexcept>
#include <iostream>
VisuallizationForm::VisuallizationForm(sf::RenderTarget& target):
            Form(target, nullptr, m_clock),
            addBox(target, this, m_add_text,m_clock),
            addTouch(target, this, addReg, m_clock),
            addReg({150,50}, 10)
{
    if (!m_font.loadFromFile("Oswald-Regular.ttf")) std::runtime_error("Font not found");

    addTouch.m_shape.setPosition(10, 10);
    addTouch.onClick = addTouch_onClick;
    addTouch.lostFocus = addTouch_onLostFocus;
    addBox.text().setFillColor(sf::Color::Black);
    addBox.text().setFont(m_font);
    addBox.text().setPosition(15,20);
    addBox.isOk = addBox_Ok;
    addReg.setFillColor(sf::Color::White);
    setFPS(50);
    children.add(&addTouch);
    children.add(&addBox);
    reDraw();
}
bool VisuallizationForm::addTouch_onClick(sf::RenderTarget &target, const MouseEventHandler &handler) {
    auto form = (VisuallizationForm*)handler.parent;
    form->addBox.enter();
    return true;
}
bool VisuallizationForm::addTouch_onLostFocus(sf::RenderTarget &target, const EventHandler& handler) {
    auto form = (VisuallizationForm*)handler.parent;
    form->addBox.leave();
    return true;
}
bool VisuallizationForm::addBox_Ok(sf::RenderTarget &target, const TextboxEventHandler &handler) {
    VisuallizationForm* form = (VisuallizationForm*)handler.parent;
    Node* node = new Node(target, form, 50, form->m_font, form->m_clock);
    if (form->m_nodes.size()) {
        auto tmp = form->m_nodes.back();
        if (tmp) node->setPosition(tmp->getPosition().x, tmp->getPosition().y + 150);
    } else node->setPosition(100, 100);
    node->setText(handler.content);
    node->m_text.setFillColor(sf::Color::Black);
    node->onRunning = Node_running;
    form->m_nodes.push_back(node);
    form->children.add(node);
    return true;
}
bool VisuallizationForm::Node_running(sf::RenderTarget &target, const EventHandler& handler) {
    Node* node = (Node*)handler.sender;
    auto i = (VisuallizationForm*)handler.parent;
    float x = 100*std::cos(handler.clock*M_PI/1000);
    float y = 100*std::sin(handler.clock*M_PI/1000);
    node->setPosition(x+200, y+200);
    return true;
}
bool VisuallizationForm::catchEvent(const sf::Event& event) {
    auto m_window = (sf::RenderWindow*)&m_target;
    if (!isDrag && event.type == sf::Event::MouseButtonPressed) {
        isDrag = true;
        oldMouse = sf::Mouse::getPosition(*m_window);
    } else if (isDrag && event.type == sf::Event::MouseButtonReleased) {
        isDrag = false;
    }
    return false;
}
bool VisuallizationForm::running() {
    if (isDrag) {
        auto m_window = (sf::RenderWindow*)&m_target;
        sf::Vector2i cur = sf::Mouse::getPosition(*m_window);
        sf::View view(m_window->getView());
        view.setCenter(view.getCenter() + sf::Vector2f((oldMouse.x - cur.x), (oldMouse.y - cur.y)));
        std::cout << view.getCenter().x << " " << view.getCenter().y << std::endl;
        m_window->setView(view);
        oldMouse = cur;
        return true;
    }
    return false;
}
bool VisuallizationForm::focus() {
    return false;
}
VisuallizationForm::~VisuallizationForm() {
    for (auto i:m_nodes) delete i;
}