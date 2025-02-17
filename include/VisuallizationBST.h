#pragma once
#include "Form.h"
#include "MouseEventHandler.h"
#include "Rectangle.h"
#include "RoundedRectangle.h"
#include "Textbox.h"
#include "Button.h"
#include <SFML/Graphics/RenderTarget.hpp>

class VisuallizationForm : public Form {
public: 
    VisuallizationForm(sf::RenderTarget& target);
    bool                            catchEvent(const sf::Event& event) override,
                                    running()                          override,
                                    focus()                            override;
    static bool addTouch_onClick(sf::RenderTarget& target, const MouseEventHandler& handler);
    ~VisuallizationForm();
    sf::Font                        m_font;
    sf::Text                        m_add_text;
    RoundedRectangle                addReg;
    Textbox                         addBox;
    Button                          addTouch;
private:
};