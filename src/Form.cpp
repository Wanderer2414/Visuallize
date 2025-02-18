#include "../include/Form.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include <string>
#include <iostream>
#include <thread>

Form::Children::Children(Form& parent): m_parent(parent) {};

size_t Form::Children::size() const {
    return m_controls.size();
}

Controller* Form::Children::operator[](const size_t& index) {
    return m_controls[index];
}
Controller* Form::Children::index(const size_t& index) const {
    return m_controls[index];
}
void Form::Children::add(Controller* control) {
    m_controls.push_back(control);
}
void Form::Children::remove(Controller* control) {
    auto tmp = std::find(m_controls.begin(), m_controls.end(), control);
    m_controls.erase(tmp);
}
void Form::Children::remove(const size_t& index) {
    m_controls.erase(m_controls.begin() + index);
}
Form::Children::~Children() {

}

Form::Form(sf::RenderTarget& target, void* parent, size_t& clock):
                    Controller(target, parent, clock),
                    children(*this),
                    m_window(*(sf::RenderWindow*)&target)
{

}

void Form::show() {
    m_window.setVisible(true);
    m_visible = true;
}

void Form::hide() {
    m_window.setVisible(false);
    m_visible = false;
}

void Form::close() {
    m_window.close();
}
void Form::setFPS(const size_t& fps) {
    m_spf = 1000/fps;
}
void Form::run() { 
    #define now std::chrono::system_clock::now()
    auto    start = now,
            last_time = start;
    while (m_window.isOpen()) {
        last_time = now;
        m_clock = std::chrono::duration_cast<std::chrono::milliseconds>(last_time-start).count();
        sf::Event   event;
        
        if (running()) reDraw();

        if (onRunning && onRunning(m_target, EventHandler(this, m_parent, m_clock))) reDraw();

        for (int i = 0; i<children.size(); i++) {
            if (children[i]->running()) reDraw();
            if (children[i]->onRunning && children[i]->onRunning(m_target, EventHandler(children[i], this, m_clock)))
                reDraw();
        }

        while (m_window.pollEvent(event)) {
            if (catchEvent(event)) reDraw();
            for (int i = 0; i<children.size(); i++) 
                if (children[i]->catchEvent(event)) reDraw();

            if (event.type == sf::Event::Closed) {
                if (closing && closing(m_target, m_clock)) reDraw();
                close();
                if (closed && closed(m_target, m_clock)) reDraw();
            }

        }
        if (isRedraw() && m_visible) {
            m_window.clear();
            m_window.draw(*this); 
            m_window.display();
        }
        if (now - last_time > std::chrono::milliseconds(10*m_spf)) throw std::runtime_error("Runtime error!");
        std::this_thread::sleep_until(last_time + std::chrono::milliseconds(m_spf));
    }
}

void Form::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    for (int i = 0; i<children.size(); i++) 
        target.draw(*children.index(i));
}
Form::~Form() {

}