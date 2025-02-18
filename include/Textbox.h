
#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include "TextboxEventHandler.h"
#include "Controller.h"
#include "Rectangle.h"

class Textbox: public Controller {
public:
    Textbox(sf::RenderTarget& target, void* parent, sf::Text& text, size_t& clock);

    bool                running()                           override,
                        catchEvent(const sf::Event& event)  override,
                        focus()                             override;

    unsigned int        getCursorIndex() const;

    void                setCursorIndex(const unsigned int& index),
                        setString(const std::string& content),
                        setCursorFlash(const size_t& duration),
                        enter(),
                        leave();

    sf::Text&           text();

    std::function<bool(sf::RenderTarget& target, const TextboxEventHandler& handler)> 
                        textChanged   = nullptr,
                        AfterChanged  = nullptr,
                        BeforeChanged = nullptr;
    ~Textbox();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
private:
    bool                isShowCursor    =  false,
                        isMultiLine     =  false,
                        isFocus         =  false;
    unsigned int        cursorIndex     = 0,
                        m_characterSize = 23;
    sf::Color           m_char_color    = sf::Color::Black;
    sf::Vector2f        m_text_pos      = {0,0};
    std::string         m_content       = "",
                        old_content     = "";
    sf::Text            &m_text;
    Rectangle           text_cursor, 
                        *m_text_cursor  = nullptr;
    size_t              next_time       = 0,
                        cursor_duration = 200;
    void                reset_text_cursor();
};