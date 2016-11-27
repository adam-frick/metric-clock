#ifndef FACE_CENTER_HH
#define FACE_CENTER_HH

#include <SFML/Graphics.hpp>

class Face_Center : public sf::Drawable, public sf::Transformable {
public:
    Face_Center();
    ~Face_Center();
    void setShape();
private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    sf::CircleShape faceCenter;
    sf::VertexArray vertices;
    sf::Texture texture;
};


#endif

