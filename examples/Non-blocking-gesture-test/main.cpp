#include <Arduino.h>
#include "SparkFun_APDS9960.h"

SparkFun_APDS9960 apds = SparkFun_APDS9960();

#define CHECK(f, msg)  \
    ar = f;            \
    Serial.print(msg); \
    Serial.println((ar) ? " OK" : " failed")

const char *gestureName[] = {"Left", "Right", "Up", "Down"};

void setup() {
    // Initialize Serial port
    Serial.begin(115200);
    Serial.println();
    Serial.println(F("-----------------------"));
    Serial.println(F("APDS-9960 - GestureTest"));
    Serial.println(F("-----------------------"));

    // Initialize APDS-9960 (configure I2C and initial values)
    if (apds.init()) {
        Serial.println(F("APDS-9960 initialization complete"));
    } else {
        Serial.println(F("Something went wrong during APDS-9960 init!"));
    }

    // Start running the APDS-9960 gesture sensor engine
    if (apds.enableGestureSensor(true)) {
        Serial.println(F("Gesture sensor is now running"));
    } else {
        Serial.println(F("Something went wrong during gesture sensor init!"));
    }

    bool ar;
    CHECK(apds.setGestureLEDDrive(2), "gesture LED drive");
    CHECK(apds.setGestureIntEnable(0), "int en");
    CHECK(apds.setGestureGain(GGAIN_4X), "gesture gain");
    CHECK(apds.enableProximitySensor(false), "Prox sensor");
    CHECK(apds.setProximityGain(PGAIN_4X), "Prox gain");
    // CHECK(apds.setGestureTimeout(3000), "Gesture timeout");
}

void loop() {
    Gesture gesture = apds.checkGesture();

    switch (gesture) {
        case DIR_UP:
        case DIR_DOWN:
        case DIR_LEFT:
        case DIR_RIGHT:
            Serial.println(gestureName[gesture - 1]);
            break;
        case DIR_NEAR:
            Serial.println("NEAR");
            break;
        case DIR_FAR:
            Serial.println("FAR");
            break;
        case DIR_PENDING:
            Serial.print("...");
        default:
            // Don't print, we'll be here a LOT!
            // Serial.print("/");
            break;
    }
}