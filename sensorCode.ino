#include <Wire.h>
#include "temp.h"
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int buttonPin = 2;
tempState temperature;

//LED setup
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

void setup() {
  //Button setup
  pinMode(buttonPin, INPUT);
  //Sensor setup
  Serial.begin(9600);  
  mlx.begin();  
  //LED pin settings
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop() {
  checkButtonState();
  delay(500);
}

void checkButtonState() {
  //Button loop
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    sensorOn();
  }
}

void sensorOn() {
  Serial.print("Temperature : ");
  int currentTemp = mlx.readObjectTempC();
  Serial.print(currentTemp); 
  checkTemp(currentTemp);
  Serial.println("Celsius");

  Serial.println();
}

void checkTemp(int currentTemp) {
  //checks temperature for high, low or normal
  if (currentTemp >= 38) {
    temperature = HIGH_TEMP;
    RGB_color(255, 0, 0); // Red
  } else if (currentTemp <= 35) {
    temperature = LOW_TEMP;
    RGB_color(0, 0, 255); // Blue
  } else {
    temperature = NORMAL_TEMP;
    RGB_color(0, 255, 0); // Green
  }

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
