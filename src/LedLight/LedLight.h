#ifndef __INC_ANTXCITY_LEDLIGHT_H
#define __INC_ANTXCITY_LEDLIGHT_H

#include "../../setup.h"
#include "LedStrip.h"
#include "../Config/Config.h"

class LedLight {
private:
    LedStripBase *m_ledstrips[NUM_STRIPS];

public:
    LedLight();
    ~LedLight();

    void applyConfig(Config *config);
}; 


#endif