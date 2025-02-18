#pragma once
#include "EventHandler.h"
#include "Form.h"
#include "MouseEventHandler.h"
#include "Rectangle.h"
#include "RoundedRectangle.h"
#include "Textbox.h"
#include "Button.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include "Node.h"
#include "TextboxEventHandler.h"

class VisuallizationForm : public Form {
public: 
    VisuallizationForm(sf::RenderTarget& target);
    bool                            catchEvent(const sf::Event& event) override,
                                    running()                          override,
                                    focus()                            override;
    static bool addTouch_onClick(sf::RenderTarget& target, const MouseEventHandler& handler);
    static bool addBox_Ok(sf::RenderTarget& target, const TextboxEventHandler& handler);
    static bool Node_running(sf::RenderTarget& target, const EventHandler& clock);
    ~VisuallizationForm();
    sf::Font                        m_font;
    sf::Text                        m_add_text;
    RoundedRectangle                addReg;
    Textbox                         addBox;
    Button                          addTouch;
    std::vector<Node*>              m_nodes;
private:
    bool                            isDrag = false;
    sf::Vector2i                    oldMouse = {0, 0};
};