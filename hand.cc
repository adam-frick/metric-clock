#include "hand.hh"
#include <iostream>
#include "screen.hh" 
#include "metric.hh"

Hand::Hand(unsigned char ID) : m_ID(ID), angle(0) {
    setShape();
}

Hand::~Hand() {
    
}

void Hand::setShape() {
    
    // fills hand to screen, to be scaled later
    handShape.setSize(Screen::DIM);
    
    // shape of hand based on type of hand
    /* todo: reduce redundancy with using cases only 
     * to determine method parameters */

    switch (m_ID) {
        case secID:
            handShape.scale(0.01, 0.40);
            handShape.setFillColor(sf::Color::Red);
            handShape.setOutlineColor(sf::Color::Red);
            break;
        case minID:
            handShape.scale(0.03, 0.30);
            handShape.setFillColor(sf::Color::Green);
            handShape.setOutlineColor(sf::Color::Green);
            break;
        case hourID:
            handShape.scale(0.03, 0.35);
            handShape.setFillColor(sf::Color::Blue);
            handShape.setOutlineColor(sf::Color::Blue);
            break;
    }
    handShape.setOrigin(handShape.getSize().x/2, handShape.getSize().y);
    handShape.setPosition(Screen::getCenter());
}

void Hand::updateShape() {
    
    // updates hand based on type of hand
    switch (m_ID) {
        case secID:
            handShape.setRotation(Metric::sec * 3.6);  // 1 rotation / MAX_SEC
            break;
        case minID:
            handShape.setRotation(Metric::min * 3.6);  // 1 rotation / MAX_MIN
            break;
        case hourID:
            handShape.setRotation(Metric::hour * 36);  // 1 rotation / MAX_HOUR
            break;
    }
}

void Hand::draw(sf::RenderTarget& target, sf::RenderStates states) const {     
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(handShape, states);
}
