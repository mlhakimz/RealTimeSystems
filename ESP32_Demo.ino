// LED rates
static const int rate_1 = 500;
static const int rate_2 = 200;
static const int rate_3 = 100;

// Pins
static const int led_pin1 = 18;
static const int led_pin2 = 19;
static const int led_pin3 = 21;

// Our task: blink an LED at one rate
void toggleLED_1(void *parameter) {
  while (1) {
    Serial.print("Task 1: ");
    Serial.println(xPortGetCoreID());
    digitalWrite(led_pin1, HIGH);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    digitalWrite(led_pin1, LOW);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
  }
}

// Our task: blink an LED at another rate
void toggleLED_2(void *parameter) {
  while (1) {
    Serial.print("Task 2: ");
    Serial.println(xPortGetCoreID());
    digitalWrite(led_pin2, HIGH);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
    digitalWrite(led_pin2, LOW);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
  }
}

// Our task: blink an LED at another rate
void toggleLED_3(void *parameter) {
  while (1) {
    Serial.print("Task 3: ");
    Serial.println(xPortGetCoreID());
    digitalWrite(led_pin3, HIGH);
    vTaskDelay(rate_3 / portTICK_PERIOD_MS);
    digitalWrite(led_pin3, LOW);
    vTaskDelay(rate_3 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(9600);

  // Configure pin
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreatePinnedToCore() to create a task on a specific core.
    toggleLED_1,            // Function to be called
    "Toggle 1",             // Name of task
    1024,                   // Stack size
    NULL,                   // Parameter to pass to function
    1,                      // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL,                   // Task handle
    1);                     // Core number

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreatePinnedToCore() to create a task on a specific core.
    toggleLED_2,            // Function to be called
    "Toggle 2",             // Name of task
    1024,                   // Stack size
    NULL,                   // Parameter to pass to function
    1,                      // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL,                   // Task handle
    0);                     // Core number

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreatePinnedToCore() to create a task on a specific core.
    toggleLED_3,            // Function to be called
    "Toggle 3",             // Name of task
    1024,                   // Stack size
    NULL,                   // Parameter to pass to function
    1,                      // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL,                   // Task handle
    1);                     // Core number
}

void loop() {
  // Do nothing
  // Don't remove the loop function, the program will not work without it.
}
