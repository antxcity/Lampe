#ifndef __INC_ANTXCITY_LEDLIGHT_H
#define __INC_ANTXCITY_LEDLIGHT_H

#include "../../setup.h"
#include "LedStrip.h"
#include "../Config/Config.h"

class LedLight {
private:
    LedStripBase *m_ledstrips[NUM_STRIPS];
    bool m_changed = true;

    unsigned long m_last_action_time = 0;
    long m_last_elapsed_time = 0;
    int m_timeouts[6] = { 10, 1*60, 5*60, 15*60, 30*60, 60*60 };
    int m_time_left = 0;
    int m_timeout = 0;

public:
    LedLight();
    ~LedLight();

    void applyConfig(Config *config);
    void show();
    void resetTimer();

    int getTimeOut() { return m_timeout; };
    int getCurrentTimeLeft() { return m_time_left; };

    void applyDayLight(Config *config);
    void applyRedLight(Config *config);
    void applyBlueLight(Config *config);
    void applyLowLight(Config *config);
}; 


#endif