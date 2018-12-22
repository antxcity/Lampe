#include "./controller.h"
#include "../oled/oled.h"

controller::controller(oled::oled oled) {
    configItems = config.getJoystickItems();
};
    
void controller::onJoystickLeft() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        ci.value = !ci.value);
        oled.showBool(ci.title, ci.value);
        // no write back to config yet
    }
    else if (ci.type = config::configItemTypes.INT) {
        if (ci.value > ci.minValue) {
            ci.value--;
            oled.showBar(ci.title, ci.value);
            // no write back to config yet
        }
    }
};

void controller::onJoystickRight() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        ci.value = !ci.value);
        oled.showBool(ci.title, ci.value);
        // no write back to config yet
    }
    else if (ci.type = config::configItemTypes.INT) {
        if (ci.value < ci.maxValue) {
            ci.value++;
            oled.showBar(ci.title, ci.value);
            // no write back to config yet
        }
    }
};

void controller::onJoystickUp() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    if (currentConfigItem == 0)
        return;

    currentConfigItem--;
    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        oled.showBool(ci.title, ci.value);
    }
    else if (ci.type = config::configItemTypes.INT) {
        oled.showBar(ci.title, ci.value);
    }
};

void controller::onJoystickDown() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    if (currentConfigItem == configItems.count - 1)
        return;

    currentConfigItem++;
    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        oled.showBool(ci.title, ci.value);
    }
    else if (ci.type = config::configItemTypes.INT) {
        oled.showBar(ci.title, ci.value);
    }
    else {
        oled.showMessage("unknown item");
    }
};

void controller::onJoystickButton() {
    if (!displayActive) {
        activateDisplay();
        return;
    }

    oled.showError("button pressed");
    delay(2000);
    activateDisplay();
};

void controller::activateDisplay() {
    displayActive = true;
    oled.activate();

    configItem ci = configItems[currentConfigItem]; // just for the shorter name
    if (ci.type = config::configItemTypes.BOOL) {
        oled.showBool(ci.title, ci.value);
    }
    else if (ci.type = config::configItemTypes.INT) {
        oled.showBar(ci.title, ci.value);
    }
}

void controller::deactivateDisplay() {
    displayActive = false;
    oled.deactivate();
}