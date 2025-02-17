#include "../include/TextboxEventHandler.h"

TextboxEventHandler::TextboxEventHandler(void* sender, void* parent, std::string& m_content, const float& clock):
    EventHandler(sender, parent, clock),
    content(m_content)
{

}