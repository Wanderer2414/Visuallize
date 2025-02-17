#include "VisuallizationBST.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
int main() {
    sf::RenderWindow window(sf::VideoMode(600,600), "Binary tree");
    VisuallizationForm form(window);
    form.run();
    return 0;
}