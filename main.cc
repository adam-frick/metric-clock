#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ctime>  
#include <sstream>

#include "metric.hh"
#include "hand.hh"
#include "face.hh"
#include "screen.hh"

sf::RenderWindow window(sf::VideoMode(
        Screen::WIDTH, Screen::HEIGHT), "Metric Clock", 
        sf::Style::Titlebar | sf::Style::Close);
sf::Clock clockObj;
sf::Time elapsed;
sf::Text timeText;
sf::Font font;
Face face;

std::array<Hand, 3> hands = {
    Hand(Hand::secID), 
    Hand(Hand::minID), 
    Hand(Hand::hourID)
};

// function prototypes
void free();
void setTime();
void update();
void draw();
void loadFont();

int main() {
    loadFont();
    setTime();

    const unsigned short METRIC_SEC = 864;  // in milliseconds
    
    while (window.isOpen()) {
        sf::Event event;
        
        // resets timer and inc clock when time reaches one metric second
        if (clockObj.getElapsedTime().asMilliseconds() >= METRIC_SEC) {
            clockObj.restart();
            Metric::inc();
        }
        if (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;    
                default:
                    break;
            }
        }
        // background of window
        window.clear(sf::Color::Yellow);
        
        update();
        draw();
        window.display();       
    }
    free();
    return 0;
}

void free() {
    // may not be needed
}


void setTime() {
    // finds seconds since epoch, midnight at 1970-1-1 (ISO 8601)
    std::chrono::system_clock::time_point epochSec = 
            std::chrono::system_clock::now();
    
    // converts to 24-hour time of current day
    time_t gmtTime = std::chrono::system_clock::to_time_t(epochSec);
    
    // shifts time to current time zone
    tm localTime = *localtime(&gmtTime);
    
    // finds seconds since midnight
    time_t currentSec = localTime.tm_hour*3600 + 
                        localTime.tm_min*60 + 
                        localTime.tm_sec;
    
    //converts seconds to metric seconds
    time_t metricSec = 
            currentSec * (1000.0f / 864.0f);  // direct second conversion
    
    // separates digits
    /*
     * todo: it would be better to call a function to truncate digits
     * at a given index as the operations here only work for this
     * specific case where a general case would work just as well
     */
    Metric::hour = metricSec / (Metric::MAX_MIN * Metric::MAX_SEC);
    metricSec -= Metric::hour * (Metric::MAX_MIN*Metric::MAX_SEC);
    Metric::min = metricSec / Metric::MAX_SEC;
    metricSec -= Metric::min * Metric::MAX_SEC;
    Metric::sec = metricSec;
    
    
}

void update() {  // changes rotation of hands each metric second
    for (unsigned int i = 0; (i < hands.size()); i++) {
        hands.at(i).updateShape();
    }
}

void draw() {
    Metric::drawTime(timeText);
    window.draw(timeText);
    window.draw(face);
    for (unsigned int i = (hands.size()); i > 0; i--) {
        window.draw(hands.at(i - 1));
    }
    window.draw(face.face_center);
}

void loadFont() {
    if (!font.loadFromFile(Screen::FONT)) {
        std::cout << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    }
    timeText.setFont(font);
    timeText.setFillColor(sf::Color::Black);
}
