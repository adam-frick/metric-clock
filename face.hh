#ifndef FACE_HH
#define FACE_HH
#include <SFML/Graphics.hpp>

#include "screen.hh"
#include "face_center.hh"

class Face : public sf::Drawable, public sf::Transformable {
public:
    Face();
    ~Face();
    void setShape();
    void setFace();
     
    Face_Center face_center;
private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    
    sf::CircleShape faceCircle;
    sf::VertexArray vertices;
    sf::Texture texture;
    sf::Font font;
    
    enum {TICK_QTY = 100, NUM_QTY = 10};
    
    std::array<sf::RectangleShape, TICK_QTY> ticks;
    std::array<sf::Text, NUM_QTY> nums;
    
};


#endif

