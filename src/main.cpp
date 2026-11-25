#include <Arduino.h>
#include <VL53L0X.h>
#include <Wire.h>

constexpr int forcePullupPin = 1;
constexpr int forceSensePin = 2;
constexpr int buzzerControlPin = 6;
constexpr int distanceSdaPin = 18;
constexpr int distanceSclPin = 19;

bool showForceReadings = true;

void printMenu() {
    Serial0.println("f = force sensor | d = distance sensor | b = buzzer | ? = help");
}

void testDistanceSensor() {
    if (!Wire.begin(distanceSdaPin, distanceSclPin, 100000)) {
        Serial0.println("Could not start the I2C bus.");
        return;
    }

    VL53L0X sensor;
    sensor.setTimeout(250);
    // The library checks the VL53L0X chip ID before configuring the sensor.
    if (sensor.init()) {
        Serial0.println("VL53L0X detected. Move an object in front of the sensor.");
        for (int sample = 0; sample < 20; ++sample) {
            const uint16_t distance = sensor.readRangeSingleMillimeters();
            if (sensor.timeoutOccurred()) {
                Serial0.println("Distance measurement timed out.");
                break;
            }
            Serial0.printf("Distance: %u mm\n", static_cast<unsigned>(distance));
            delay(200);
        }
    } else {
        Serial0.println("VL53L0X not detected. Check the sensor model, power, SDA, and SCL.");
    }
    Wire.end();
}

void testBuzzer() {
    Serial0.println("Pulsing the buzzer driver on GPIO6 for 250 ms.");
    digitalWrite(buzzerControlPin, HIGH);
    delay(250);
    digitalWrite(buzzerControlPin, LOW);
}

void setup() {
    Serial0.begin(115200);
    // GPIO1 provides the internal pull-up for the node measured by GPIO2.
    pinMode(forcePullupPin, INPUT_PULLUP);
    pinMode(buzzerControlPin, OUTPUT);
    digitalWrite(buzzerControlPin, LOW);
    printMenu();
}

void loop() {
    if (Serial0.available()) {
        switch (Serial0.read()) {
            case 'f':
                showForceReadings = true;
                break;
            case 'd':
                showForceReadings = false;
                testDistanceSensor();
                printMenu();
                break;
            case 'b':
                showForceReadings = false;
                testBuzzer();
                printMenu();
                break;
            case '?':
                showForceReadings = false;
                printMenu();
                break;
        }
    }

    if (showForceReadings) {
        Serial0.printf("FSR raw: %d\n", analogRead(forceSensePin));
    }
    delay(100);
}
