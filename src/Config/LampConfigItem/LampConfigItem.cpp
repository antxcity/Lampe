#include "LampConfigItem.h"

#include "../Config.h"

void ConfigItemPresets::setValue(int value) {
        // Serial.println("ConfigItemPresets::setValue(int " + getTitle() + " : " + String(value) + ")");
        m_value = value; 
        getConfig()->setChanged(this);
}

String ConfigItemStrips::getDisplayString() 
{ 
    String result;

    switch (getValue()) {
        case 1:
            result = "X_X";
            break;
        case 2:
            result = "_X_";
            break;
        case 0:
        default:
            result = "XXX";
            break;
    }
    return result;
};

int ConfigItemStrips::mapToStripMask() {
    static int mapping[3] = { 0x7, 0x5, 0x2 };

    return mapping[getValue() % 3];
}

bool ConfigItemStrips::isStripActive(int strip_index) {
    return ((1<<strip_index) & mapToStripMask()) ? true : false;
}

String ConfigItemColorRotation::getDisplayString() 
{ 
    String result;

    switch (getValue()) {
        case 1:
            result = "sehr langsam";
            break;
        case 2:
            result = "langsam";
            break;
        case 3:
            result = "mittel";
            break;
        case 4:
            result = "schnell";
            break;
        case 5:
            result = "sehr schnell";
            break;
        case 0:
        default:
            result = "keine / Stillstand";
            break;
    }
    return result;
};


