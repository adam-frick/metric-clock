#ifndef METRIC_HH
#define METRIC_HH

#include <iostream>
#include <sstream>
#include <iomanip>

namespace Metric {
    
    extern void inc();
    extern void drawTime(sf::Text&);
   
    extern std::stringstream timeStr;
    
    extern unsigned char sec;   // 100 in a metric minute
    extern unsigned char min;   // 100 in a metric hour (every 10,000 metric seconds)
    extern unsigned char hour;  // 10 in a metric day (every 100,000 metric seconds)
    
    const unsigned char MAX_SEC = 100;
    const unsigned char MAX_MIN = 100;
    const unsigned char MAX_HOUR = 10;
};



#endif 
