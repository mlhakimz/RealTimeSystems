#include <Arduino_FreeRTOS.h>

// LED rates
static const int rate_1 = 500;
static const int rate_2 = 200;
static const int rate_3 = 100;

// Pins
static const int led_pin1 = 4;
static const int led_pin2 = 5;
static const int led_pin3 = 6;

// Our task: blink an LED at one rate
void toggleLED_1(void *parameter) {
  while (1) {
    digitalWrite(led_pin1, HIGH);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    digitalWrite(led_pin1, LOW);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
  }
}

// Our task: blink an LED at another rate
void toggleLED_2(void *parameter) {
  while (1) {
    digitalWrite(led_pin2, HIGH);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
    digitalWrite(led_pin2, LOW);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
  }
}

// Our task: blink an LED at another rate
void toggleLED_3(void *parameter) {
  while (1) {
    digitalWrite(led_pin3, HIGH);
    vTaskDelay(rate_3 / portTICK_PERIOD_MS);
    digitalWrite(led_pin3, LOW);
    vTaskDelay(rate_3 / portTICK_PERIOD_MS);
  }
}

void setup() {

  // Configure pin
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);

  // Task to run forever
  xTaskCreate(      // Create task
    toggleLED_1,    // Function to be called
    "Toggle 1",     // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    1,              // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL);          // Task handle

  // Task to run forever
  xTaskCreate(      // Create task
    toggleLED_2,    // Function to be called
    "Toggle 2",     // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    1,              // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL);          // Task handle

  // Task to run forever
  xTaskCreate(      // Create task
    toggleLED_3,    // Function to be called
    "Toggle 3",     // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    1,              // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL);          // Task handle

}

void loop() {
  // Do nothing
}
