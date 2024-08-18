/*
Programa: Encender y apagar un led en Arduino uno. (Blink)
Curso: Arduino UNO
Autor: Expacio Science Group
*/

#include <Wire.h>                      // Incluye la biblioteca Wire para la comunicación I2C
#include <Adafruit_Sensor.h>           // Incluye la biblioteca base para manejar sensores Adafruit
#include <Adafruit_AHTX0.h>            // Incluye la biblioteca para el sensor AHT20 (AHTX0 es el nombre de la biblioteca para AHT20)
#include <Adafruit_BMP280.h>            // Incluye la biblioteca para el sensor BMP280

// Crear objetos para los sensores
Adafruit_AHTX0 aht;                    // Crea un objeto para el sensor AHT20
Adafruit_BMP280 bmp;                   // Crea un objeto para el sensor BMP280 (usará la comunicación I2C)

// Función de configuración inicial, se ejecuta una vez al inicio
void setup() {
  Serial.begin(9600);                 // Inicializa la comunicación serie a 9600 baudios
  delay(1000);                        // Espera 1 segundo para permitir que el Monitor Serie se establezca correctamente

  Serial.println("Iniciando sensores..."); // Imprime un mensaje en el Monitor Serie indicando que los sensores se están iniciando

  // Iniciar el sensor AHT20
  if (!aht.begin()) {                 // Intenta iniciar el sensor AHT20
    Serial.println("No se pudo encontrar el sensor AHT20. Verifique la conexión."); // Mensaje de error si el sensor no se encuentra
    while (1) delay(10);             // Si no se encuentra el sensor, se detiene el programa y espera indefinidamente
  }
  Serial.println("Sensor AHT20 iniciado correctamente"); // Mensaje en el Monitor Serie indicando que el sensor AHT20 se ha iniciado correctamente

  // Iniciar el sensor BMP280 con la dirección I2C 0x77
  if (!bmp.begin(0x77)) {            // Intenta iniciar el sensor BMP280 en la dirección I2C 0x77
    Serial.println("No se pudo encontrar el sensor BMP280 en la dirección 0x77. Verifique la conexión."); // Mensaje de error si el sensor no se encuentra
    while (1) delay(10);            // Si no se encuentra el sensor, se detiene el programa y espera indefinidamente
  }
  Serial.println("Sensor BMP280 iniciado correctamente"); // Mensaje en el Monitor Serie indicando que el sensor BMP280 se ha iniciado correctamente
}

// Función principal que se ejecuta en un bucle infinito
void loop() {
  // Leer datos del sensor AHT20
  sensors_event_t humidity, temp;    // Declara variables para almacenar los eventos de humedad y temperatura
  aht.getEvent(&humidity, &temp);    // Obtiene los eventos de humedad y temperatura del sensor AHT20

  Serial.print("Temperatura AHT20: "); // Imprime el texto en el Monitor Serie
  Serial.print(temp.temperature);      // Imprime la temperatura leída del sensor AHT20
  Serial.println(" °C");              // Imprime la unidad de medida (°C) y pasa a la siguiente línea

  Serial.print("Humedad: ");          // Imprime el texto en el Monitor Serie
  Serial.print(humidity.relative_humidity); // Imprime la humedad relativa leída del sensor AHT20
  Serial.println(" %");              // Imprime el símbolo de porcentaje (%) y pasa a la siguiente línea

  // Leer datos del sensor BMP280
  float bmpTemp = bmp.readTemperature();  // Lee la temperatura del sensor BMP280 y almacena el valor en bmpTemp
  float pressure = bmp.readPressure() / 100.0F; // Lee la presión del sensor BMP280, la convierte de Pa a hPa y almacena el valor en pressure

  Serial.print("Temperatura BMP280: "); // Imprime el texto en el Monitor Serie
  Serial.print(bmpTemp);               // Imprime la temperatura leída del sensor BMP280
  Serial.println(" °C");              // Imprime la unidad de medida (°C) y pasa a la siguiente línea

  Serial.print("Presión: ");           // Imprime el texto en el Monitor Serie
  Serial.print(pressure);             // Imprime la presión leída del sensor BMP280
  Serial.println(" hPa");            // Imprime la unidad de medida (hPa) y pasa a la siguiente línea

  delay(2000);                        // Espera 2 segundos antes de realizar la siguiente lectura de los sensores
}
