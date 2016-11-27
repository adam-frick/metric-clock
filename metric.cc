#include <SFML/Graphics/Text.hpp>

#include "metric.hh"


namespace Metric {
    
    std::stringstream timeStr("");
    
    unsigned char sec = 0;
    unsigned char min = 0;
    unsigned char hour = 0;
     
    void inc() {  // increments time, wraps around accordingly
        ++sec %= MAX_SEC;

        if (sec == 0) {
            ++min %= MAX_MIN;

            if (min == 0) {
                ++hour %= MAX_HOUR;   
            }
        }
    }

    void drawTime(sf::Text& text) {  // draws metric time (HH:MM:SS) to top-left
        timeStr.str("");
        timeStr
                  << (int)hour 
                  << ":"

                  << std::setfill('0') << std::setw(2)
                  << (int)min 
                  << ":"

                  << std::setfill('0') << std::setw(2)  
                  << (int)sec;

        text.setString(timeStr.str());
    }

}
