#include "Controller.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstddef>
#include <functional>
#include <vector>

class Form: public Controller {
public:
    Form(sf::RenderTarget& target, void* parent, size_t& clock);

    virtual bool                    catchEvent(const sf::Event& event) override = 0,
                                    running()                          override = 0,
                                    focus()                            override = 0;

    class Children {
    public:
        friend class Form;

        Children(Form& parent);

        size_t                      size() const;
        Controller                  *operator[](const size_t& index),
                                    *index(const size_t& index) const;
        void                        add(Controller* control),
                                    remove(Controller* control),
                                    remove(const size_t& index);
        ~Children();
    private:
        std::vector<Controller*>    m_controls;
        Form&                       m_parent;
    };
    friend class Children;

    Children                        children;

    void                            run(),
                                    show(),
                                    hide(),
                                    close(),
                                    setFPS(const size_t& fps);

    std::function<bool(sf::RenderTarget& target, const size_t& clock)>
                                    onFocus     =   nullptr,
                                    lostFocus   =   nullptr,
                                    closing     =   nullptr,
                                    closed      =   nullptr,
                                    begin       =   nullptr;

    ~Form();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    size_t                          m_clock     =   0;
private:
    bool                            m_visible   =   true;
    size_t                          m_spf       =   50;
    sf::RenderWindow&               m_window;
};