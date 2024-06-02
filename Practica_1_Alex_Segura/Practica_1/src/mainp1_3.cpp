#include <Arduino.h>
#define DELAY 500

uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;

void setup() {
pinMode(LED_BUILTIN, OUTPUT);
pinMode(21, OUTPUT);
Serial.begin(115200);
}

void loop(){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(21, LOW);
    *gpio_out |= (1 << 21);
    Serial.print("ON");
    delay(DELAY);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(21, HIGH);
    *gpio_out ^= (1 << 21);
    Serial.print("OFF");
    delay(DELAY);
}