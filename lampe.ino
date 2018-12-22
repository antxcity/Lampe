#include "src/lamp/lamp.h"
#include "setup.h"

CLamp *lamp;

void setup() {
    lamp = new CLamp();

    Serial.begin(9600);
}

void loop() {
    lamp->loop();

    delay(100);
}
