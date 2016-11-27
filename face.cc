#include "face.hh"
#include "screen.hh"
#include <cmath>
#include <iostream>

Face::Face() {
    setShape();
    setFace();
}

Face::~Face() {
    
}

void Face::setShape() {  // sets properties
    faceCircle.setRadius(Screen::getMinDim()*0.5*0.90);
    faceCircle.setOrigin(faceCircle.getRadius(), faceCircle.getRadius());
    faceCircle.setPosition(Screen::getCenter());
    faceCircle.setFillColor(sf::Color::Transparent);
    faceCircle.setOutlineColor(sf::Color::Black);
    faceCircle.setOutlineThickness(10);
}

void Face::setFace() {  // arranges layout of clock face to show ticks & numbers
    for (unsigned int i = 0; i < ticks.size(); i++) {
        
        if (!font.loadFromFile("LiberationMono-Regular.ttf")) {
            std::cout << "Failed to load font" << std::endl;
            exit(EXIT_FAILURE);
        }

        
        ticks.at(i).setFillColor(sf::Color::Black);
        
        // sets tick to fill screen, to scale later
        ticks.at(i).setSize(Screen::DIM);
        
        // sets origin for transformations at top-center of tick rect
        ticks.at(i).setOrigin(ticks.at(i).getSize().x/2, 0);
        
        // sets position of tick around clock using polar coordinates
        ticks.at(i).setPosition(
            Screen::getMinDim()*0.5*0.9 * 
            cos(360.0f/ticks.size()*i * (M_PI/180) - M_PI/2) + 
            Screen::getCenter().x,
                
            Screen::getMinDim()*0.5*0.9 * 
            sin(360.0f/ticks.size()*i * (M_PI/180) - M_PI/2) + 
            Screen::getCenter().y
        );
        
        // makes tick longer if at a decisecond
        if (i % (ticks.size()/10)) {
            ticks.at(i).scale(0.005, 0.05);
        }
        else {
            ticks.at(i).scale(0.005, 0.07);
           
        }
        
        // rotates ticks so top side faces center
        ticks.at(i).setRotation((360.0f/ticks.size()*i));
    }
    
    for (unsigned int i = 0; i < nums.size(); i++) {
        nums.at(i).setFont(font);
        nums.at(i).setFillColor(sf::Color::Black);
        nums.at(i).setOutlineColor(sf::Color::Black);
        nums.at(i).setCharacterSize(Screen::getMinDim()*0.075);
        
        // sets string of clock number for corresponding hour
        nums.at(i).setString(std::to_string(i));
        
        // sets origin to center of number
        nums.at(i).setOrigin(
            nums.at(i).getCharacterSize()/2, 
            nums.at(i).getCharacterSize()/2
        );  
        
        // sets position of number around clock based on polar coordinates
        
        /* 
         * issue: numbers don't line up perfectly along ticks, might
         *  be due to inconsistent position of each number or
         *  calculating a face center that differs from the actual center.
         * workaround: used number size in calculation and divided by 5,
         *  gives a near-intended result
         */
        nums.at(i).setPosition(
            Screen::getMinDim()*0.5*0.70 * 
            cos(360.0f/ticks.size()*(i*10) * (M_PI/180) - M_PI/2) + 
            Screen::getCenter().x + nums.at(i).getCharacterSize()/5,
                
            Screen::getMinDim()*0.5*0.70 * 
            sin(360.0f/ticks.size()*(i*10) * (M_PI/180) - M_PI/2) + 
            Screen::getCenter().y - nums.at(i).getCharacterSize()/5
        );
    }
    
}

void Face::draw(sf::RenderTarget& target, sf::RenderStates states) const { 

    /*
     * issue: number edges appear "cut off", there might be a rendering 
     * setting to fix this
     */
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(faceCircle, states);
    
    for (unsigned int i = 0; i < ticks.size(); i++) {
        target.draw(ticks.at(i), states);
        target.draw(nums.at(i/10), states);
    }
    
}
