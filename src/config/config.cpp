#include "./config.h"
#include "./configItem.h"

config::config() {
};

configItems[] getJoystickItems() {
    configItems joystickConfigItems = new List<configItem>();
    foreach (configItem in configItems) {
        if (configItem.joystick)
            joystickConfigItems.Add(configItem);
    }

    return joystickConfigItems;
};
