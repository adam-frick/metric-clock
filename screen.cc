#include "screen.hh"

namespace Screen {

    const unsigned short
        HEIGHT = 800,
        WIDTH = 800;
    const sf::Vector2f DIM(HEIGHT, WIDTH);

    sf::Vector2f getCenter() {
        return sf::Vector2f(WIDTH*0.5f, HEIGHT*0.5f);
    }
    
    unsigned short getMinDim() {
        return HEIGHT<WIDTH ? HEIGHT:WIDTH;  // returns smaller of dim
    }
}
