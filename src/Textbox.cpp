#include "../include/Textbox.h"
#include "../include/TextboxEventHandler.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#define handler TextboxEventHandler(this, m_parent, m_content, getClock())

Textbox::Textbox(sf::RenderTarget& target, void* parent, sf::Text& text, size_t& clock): 
            Controller(target, parent, clock),
            m_text_pos(text.getPosition()),
            m_text(text),
            m_char_color(text.getFillColor()),
            m_characterSize(text.getCharacterSize()),
            text_cursor({0, 1.0f*m_text.getCharacterSize()}),
            cursorIndex(0) 
{
    m_text_cursor=&text_cursor;
    text_cursor.setOutlineThickness(1.0f);
    reset_text_cursor();
    m_text_cursor->setPosition({m_text_pos.x + m_content.size()*m_text.getLetterSpacing(), m_text_pos.y});
}

bool Textbox::focus() {
    if (!isFocus) return false;
    next_time = 0;
    if (onFocus) return onFocus(m_target, EventHandler(this, m_parent, getClock()));
    else return false;
}
bool Textbox::running() {
    if (!isFocus && !isShowCursor) return false;
    if (m_text.getPosition() != m_text_pos) {
        m_text_pos = m_text.getPosition();
        m_text_cursor->setPosition({m_text_pos.x + m_content.size()*m_text.getLetterSpacing(), m_text_pos.y});
    }
    if (m_text.getCharacterSize() != m_characterSize) {
        m_characterSize = m_text.getCharacterSize();
        m_text_cursor->setSize({0, (float)m_characterSize});
    }
    if (m_text.getOutlineColor() != m_char_color) {
        m_char_color    = m_text.getFillColor();
        m_text_cursor->setOutlineColor(m_char_color);
    }
    if (getClock()<next_time) return false;
    next_time = getClock() + cursor_duration;
    isShowCursor = !isShowCursor;
    return true;
}

bool Textbox::catchEvent(const sf::Event& event) {
    if (!isFocus) return false;
    if (event.type == sf::Event::KeyPressed) {
        char insert = 0;
        if (sf::Keyboard::Scancode::A <= event.key.scancode && event.key.scancode <= sf::Keyboard::Scancode::Z) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                insert = event.key.scancode + 'A';
            else insert = event.key.scancode + 'a';
        } else if (sf::Keyboard::Scancode::Num1 <= event.key.scancode && event.key.scancode <= sf::Keyboard::Scancode::Num0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
                switch (event.key.scancode) {
                    case sf::Keyboard::Scancode::Num1: insert = '!'; break;
                    case sf::Keyboard::Scancode::Num2: insert = '@'; break;
                    case sf::Keyboard::Scancode::Num3: insert = '#'; break;
                    case sf::Keyboard::Scancode::Num4: insert = '$'; break;
                    case sf::Keyboard::Scancode::Num5: insert = '%'; break;
                    case sf::Keyboard::Scancode::Num6: insert = '^'; break;
                    case sf::Keyboard::Scancode::Num7: insert = '&'; break;
                    case sf::Keyboard::Scancode::Num8: insert = '*'; break;
                    case sf::Keyboard::Scancode::Num9: insert = '('; break;
                    default: insert = ')';
                }
            } else {
                if (event.key.scancode != sf::Keyboard::Scancode::Num0) 
                    insert = event.key.scancode -sf::Keyboard::Scancode::Num1 + '1';
                else insert = '0';
            }
        } else if (sf::Keyboard::Scancode::Numpad1 <= event.key.scancode && event.key.scancode<=sf::Keyboard::Scancode::Numpad0) {
            if (event.key.scancode != sf::Keyboard::Scancode::Numpad0) {
                insert = event.key.scancode - sf::Keyboard::Scancode::Numpad1 + '1';
            } else insert = '0';
        }
        else switch (event.key.scancode) {
            case sf::Keyboard::Scancode::Enter: {
                if (isMultiLine) insert = '\n';
                else {
                    if (isOk        && isOk(m_target, handler))         reDraw();
                    if (lostFocus   && lostFocus(m_target, EventHandler(this, m_parent, getClock()))) reDraw();
                    isFocus = false;
                    return isRedraw();
                }
            }
                break;
            case sf::Keyboard::Scancode::Escape: {

            }
                break;
            case sf::Keyboard::Scancode::Backspace: {
                if (getCursorIndex()) {
                    if (BeforeChanged && BeforeChanged(m_target, handler)) reDraw();
                    m_content.erase(m_content.begin()+getCursorIndex() - 1);
                    m_text.setString(m_content);
                    setCursorIndex(getCursorIndex() - 1);
                    if (AfterChanged && AfterChanged(m_target, handler)) reDraw();
                    return isRedraw();
                } else return false;
            }
                break;
            case sf::Keyboard::Scancode::Tab: {
                insert = '\t';
            }
                break;
            case sf::Keyboard::Scancode::Space: {
                insert = ' ';
            }
                break;
            case sf::Keyboard::Scancode::Hyphen: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '_'; else insert = '-';
            }
                break;
            case sf::Keyboard::Scancode::Equal: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '+'; else insert = '=';
            }
                break;
            case sf::Keyboard::Scancode::LBracket: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '{'; else insert = '[';
            }
                break;
            case sf::Keyboard::Scancode::RBracket: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '}'; else insert = ']';
            }
                break;
            case sf::Keyboard::Scancode::Backslash: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '|'; else insert = '\\';
            }
                break;
            case sf::Keyboard::Scancode::Semicolon: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = ':'; else insert = ';';
            }
                break;
            case sf::Keyboard::Scancode::Apostrophe: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '"'; else insert = '\'';
            }
                break;
            case sf::Keyboard::Scancode::Grave: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '~'; else insert = '`';
            }
                break;
            case sf::Keyboard::Scancode::Comma: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '<'; else insert = '.';
            }
                break;
            case sf::Keyboard::Scancode::Period: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '>'; else insert = '.';
            }
                break;
            case sf::Keyboard::Scancode::Slash: {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    insert = '?'; else insert = '/';
            }
                break;
            case sf::Keyboard::Scancode::Delete: {
                if (auto index = getCursorIndex(); index != m_content.size()) {
                    m_content.erase(m_content.begin() + getCursorIndex());
                    m_text.setString(m_content);
                    return true;
                } else return false;
            }
                break;
            case sf::Keyboard::Scancode::NumpadDivide: {
                insert = '/';
            }
                break;
            case sf::Keyboard::Scancode::NumpadMultiply: {
                insert = '*';
            }
                break;
            case sf::Keyboard::Scancode::NumpadMinus: {
                insert = '-';
            }
                break;
            case sf::Keyboard::Scancode::NumpadPlus: {
                insert = '+';
            }
                break;
            case sf::Keyboard::Scancode::NumpadEqual: {
                insert = '=';
            }
                break;
            case sf::Keyboard::Scancode::NumpadEnter: {
                insert = '\n';
            }
                break;
            case sf::Keyboard::Scancode::NumpadDecimal: {
                insert = '.';
            }
                break;
            case sf::Keyboard::Scancode::Left: {
                if (auto index = getCursorIndex(); index) {
                    setCursorIndex(index - 1);
                    return true;
                } else return false;
            }
                break;
            case sf::Keyboard::Scancode::Right: {
                if (auto index = getCursorIndex(); index<m_content.size()) {
                    setCursorIndex(index + 1);
                    return true;
                }
            }
                break;
            default: break;
        }
        if (insert) {
            if (BeforeChanged) BeforeChanged(m_target, handler);
            m_content.insert(m_content.begin() + getCursorIndex(), insert);
            m_text.setString(m_content);
            setCursorIndex(getCursorIndex() + 1);
            if (AfterChanged) AfterChanged(m_target, handler);
            return true;
        }
    }
    return false;
}

unsigned int Textbox::getCursorIndex() const {
    return cursorIndex;
}

sf::Text& Textbox::text() {
    return m_text;
}

void Textbox::setString(const std::string& content) {
    if (BeforeChanged) BeforeChanged(m_target, handler);
    m_text.setString(content);
    if (AfterChanged) AfterChanged(m_target, handler);
}

void Textbox::setCursorIndex(const unsigned int& index) {
    cursorIndex = index;
    if (index<m_content.size()) {
        sf::Vector2f        pos = m_text.findCharacterPos(index);
        text_cursor.setPosition(pos.x, pos.y);
    } else {
        sf::Vector2f        pos = m_text.findCharacterPos(m_content.size());
        text_cursor.setPosition(pos.x, pos.y);
    }
}

void Textbox::enter() {
    isFocus = true;
    if (onFocus && onFocus(m_target, EventHandler(this, m_parent, getClock()))) reDraw();
}

void Textbox::reset_text_cursor() {
    text_cursor.setFillColor(sf::Color::Transparent);
    text_cursor.setOutlineColor(m_text.getFillColor());
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(m_text);
    if (isShowCursor && isFocus) target.draw(text_cursor);
}
void Textbox::leave() {
    isFocus = false;
    if (isOk && isOk(m_target, handler)) reDraw();
    if (lostFocus && lostFocus(m_target, EventHandler(this,m_parent, getClock()))) reDraw();
}
Textbox::~Textbox() {
    
}