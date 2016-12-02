#ifndef SCREEN_HH
#define SCREEN_HH

#include <SFML/Graphics.hpp>

namespace Screen {
    extern const unsigned short
        HEIGHT,
        WIDTH;
    extern const sf::Vector2f DIM;
    extern const char * const FONT;
    
    extern sf::Vector2f getCenter();
    extern unsigned short getMinDim();
}

#endif
