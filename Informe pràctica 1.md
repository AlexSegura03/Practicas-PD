# INFORME PRÁCTICA 1: BLINK
Para esta práctica hemos utilizado el microcontrolador __ESP32__


## 1ª parte: LED ENCENDIDO DURANTE UN TIEMPO INFINITO
### Código 1

```c
#include <Arduino.h>
#define DELAY 500

void setup() {
    pinMode(21, OUTPUT);
}

void loop() {
    digitalWrite(21, HIGH);
    delay(DELAY);
    digitalWrite(21, LOW);
    delay(DELAY);
} 
``` 
En este caso, en el *pinMode* defino el pin del microcontrolador que he utilizado para este programa: el numero **21**.

## 2ª parte: LEDS ALTERNADOS "ON" Y "OFF"
### Código 2
```C
#include <Arduino.h>
#define DELAY 500

void setup() {
pinMode(23, OUTPUT);
pinMode(21, OUTPUT);
Serial.begin(115200);
}

void loop(){
    digitalWrite(23, HIGH);
    digitalWrite(21, LOW);
    //*gpio_out |= (1 << 23);
    Serial.print("ON");
    delay(DELAY);
    digitalWrite(23, LOW);
    digitalWrite(21, HIGH);
    //*gpio_out ^= (1 << 23);
    Serial.print("OFF");
    delay(DELAY)
}
```
Para este ejercicio, hemos definido un segundo *pinMode* en el *setup* donde asignamos otro pin, el número **21**.

En el *loop* añadimos otro *digitalWrite* con el nuevo pin y pedimos al programa que escriba por la Terminal en qué estado se encuentra el LED en ese momento: **"ON"** o **"OFF"**.