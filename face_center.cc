#include "face_center.hh"
#include "screen.hh"

Face_Center::Face_Center() {
    setShape();
}

Face_Center::~Face_Center() {
    
}

void Face_Center::setShape() {
    faceCenter.setRadius(Screen::getMinDim()*0.02);
    faceCenter.setOrigin(faceCenter.getRadius(), faceCenter.getRadius());
    faceCenter.setPosition(Screen::getCenter());
    faceCenter.setFillColor(sf::Color::Black);
}

void Face_Center::draw(
    sf::RenderTarget& target, sf::RenderStates states) const { 
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(faceCenter, states);    
}
