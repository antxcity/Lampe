#include "Lamp/Lamp.h"
#include "../setup.h"

Lamp *lamp;

void setup() {
    lamp = new Lamp();

    Serial.begin(921600);
}

void loop() {

    lamp->loop();
    delay(5);
}
