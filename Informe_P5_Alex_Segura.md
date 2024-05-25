# INFORME PRÁCTICA 5: Buses de comunicación I (introducción y I2C)

El objetivo de la practica es comprender el funcionamiento de los buses sistemas de comunicación entre periféricos; estos elementos pueden ser internos o externos al procesador.

## Código 1
```c
#include <Arduino.h>

#include <Wire.h>


void setup()
{
  Wire.begin();
  Serial.begin(115200);
  while (!Serial);           
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);          
}

```

Este código nos muestra por la pantalla del terminal la dirección de cada esclavo conectado al microprocesador. En este caso, nos muestra la dirección de una pantalla LCD con el bus I2C.

### Inclusión de librerías
```c
#include <Arduino.h>
#include <Wire.h>
```
+ _Arduino.h_: Proporciona las definiciones y funciones básicas de Arduino.
+ _Wire.h_: Proporciona las funciones necesarias para la comunicación I2C
    

### Función _setup()_
```c
void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial);  
  Serial.println("\nI2C Scanner");
}
```
+ _Wire.begin()_: Inicializa la biblioteca Wire para la comunicación I2C.
+ _Serial.begin(115200)_: Inicializa la comunicación serial a 115200 baudios.
+ _while (!Serial);_: Espera hasta que el monitor serial esté listo.
+ _Serial.println("\nI2C Scanner");_: Imprime el mensaje "I2C Scanner" en el monitor serial.


### Función _loop()_
**EXPLICACIÓN POR PARTES:**

#### Declaración de variables
```c
byte error, address;
int nDevices;
```  

  + _error_: Almacena el código de error de la transmisión I2C.
  + _address_: Almacena las direcciones I2C.
  + _nDevices_: Cuenta el número de dispositivos encontrados.
   

#### Inicio del escaneo
```c
Serial.println("Scanning...");
nDevices = 0;
```
+ Imprime "Scanning..." en el monitor serial.
+ Inicializa el contador de dispositivos nDevices a 0.

#### Escaneo de direcciones del bus I2C
```c
for(address = 1; address < 127; address++ ) {
  Wire.beginTransmission(address);
  error = Wire.endTransmission();
```
+ Utiliza un bucle for para iterar sobre todas las posibles direcciones I2C (de 1 a 126).
+ _Wire.beginTransmission(address)_: Inicia una transmisión I2C hacia la dirección address.
+ _error = Wire.endTransmission()_: Finaliza la transmisión y captura el código de error.

#### Procesamiento del resultado del escaneo
```c
if (error == 0) {
  Serial.print("I2C device found at address 0x");
  if (address < 16)
    Serial.print("0");
  Serial.print(address, HEX);
  Serial.println("  !");
  nDevices++;
}
```
+ Si _error_ es igual a 0, significa que el dispositivo a reconocido la dirección.
+ Imprime la dirección del dispositivo en formato hexadecimal y se incrementa el contador nDevices

```c
else if (error == 4) {
  Serial.print("Unknown error at address 0x");
  if (address < 16)
    Serial.print("0");
  Serial.println(address, HEX);
}
```
+ Si _error_ es igual a 4, quiere decir que no reconoce ninguna conexión.
+ Imprime un mensaje indicando un error desconocido en esa dirección.

#### Resumen del escaneo
```c
if (nDevices == 0)
  Serial.println("No I2C devices found\n");
else
  Serial.println("done\n");

delay(5000); 
```
+ Al final del escaneo, se imprime un mensaje indicando si se encontraron los dispositivos o no.
+ Se esperan 5 segundos para volver a iniciar otro escaneo.


![](https://i.ibb.co/5GbH1fb/Terminal-P5.png)

Como se puede ver en la imagen, la dirección de nuestro periferico en formato hexadecimal corresponde a **0x27**.





## Ejercicio práctico 2
Para este ejercicio, he vuelto a usar el display OLED anterior. Con dirección **0x27**, la he conectado al ESP32-S3 y he utilizado el siguiente código:

### Código 2
```c
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 3;


LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  lcd.setCursor(0, 0);
  
  lcd.print("HOLA");
  delay(10000);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("QUE");
  delay(8000);
  lcd.clear();

  lcd.setCursor(0,2);
  lcd.print("TAL");
  delay(6000);
  lcd.clear();

  lcd.setCursor(0,3);
  lcd.print("ESTAS");
  delay(4000);
  lcd.clear();
}
```
### Inclusión de librerías
```c
#include <LiquidCrystal_I2C.h>
```
+ _LiquidCrystal_I2C.h_: Esta librería permite controlar pantallas LCD a través de la interfaz I2C.

### Configuración inicial
```c
int lcdColumns = 16;
int lcdRows = 3;
```
+ Se definen las variables lcdColumns y lcdRows para especificar el número de columnas y filas de la pantalla LCD. En este caso, la pantalla tiene 16 columnas y 3 filas.

### Configuración del LCD
```c
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
```
+ Se crea un objeto lcd de la clase LiquidCrystal_I2C con la dirección I2C del LCD (0x27) y las dimensiones especificadas.

### Función _setup()_
```c
void setup() {
  lcd.init();      
  lcd.backlight();  
}
```
+ lcd.init(): Inicializa la pantalla LCD.
+ lcd.backlight(): Enciende la retroiluminación de la pantalla LCD.

### Función _loop()_
```c
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("HOLA");
  delay(10000);
  lcd.clear();

  lcd.setCursor(0, 1);
  lcd.print("QUE");
  delay(8000);
  lcd.clear();

  lcd.setCursor(0, 2);
  lcd.print("TAL");
  delay(6000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ESTAS");
  delay(4000);
  lcd.clear();
}
```
El _loop_ esta dividido en 4 partes, que son las 4 palabaras que se muestran por el LCD. Son idénticas, solo cambian las palabras que se ven y el tiempo que estan en pantalla.

+ _lcd.setCursor(0, 1)_: Se indica la colocación del cursor. El primer numero indica la columna y el segundo la fila.
+ _lcd.print("PALABRA")_: Imprime la palabra que quieras.
+ _delay(10000)_: Indica el tiempo que esta en la pantalla. En este caso está durante 10 segundos.
+ _lcd.clear()_: Borra la pantalla. Se puede poner o no, depende de si quieres hacer texto o solo mostrar palabras.

#### Imagen de lo que se ve en la LCD:

![](https://i.ibb.co/z26yhfK/Imagen-LCD.jpg)


#### Imagen del montaje
![](https://i.ibb.co/gFBmNrC/Montaje-P5.jpg)