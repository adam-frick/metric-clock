#ifndef HAND_HH
#define HAND_HH
#include <SFML/Graphics.hpp>

class Hand : public sf::Drawable, public sf::Transformable {
public:
    Hand(unsigned char ID);
    ~Hand();
    void setShape();
    void updateShape();
    
    enum handID {secID, minID, hourID};
   
private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    sf::VertexArray vertices;
    sf::Texture texture;
    
    sf::Vector2f pos;
    sf::Vector2f m_dim;
    sf::RectangleShape handShape;
    
    unsigned char m_ID;
    float angle;
};

#endif

