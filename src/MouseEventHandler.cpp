#include "../include/MouseEventHandler.h"
MouseEventHandler::MouseEventHandler(const unsigned int& m_x, const unsigned int& m_y, void* m_sender, void* parent, const float& clock):
                    EventHandler(m_sender, parent, clock), 
                    x(m_x), 
                    y(m_y)
{

}