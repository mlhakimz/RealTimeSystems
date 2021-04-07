// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// LED rates
int rate = 500;  // ms

//Serial
int incomingByte = 0;

// Pins
static const int led_pin = LED_BUILTIN;

// Our task: blink an LED at one rate
void toggleLED_1(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate / portTICK_PERIOD_MS);
  }
}

// Our task: Read serial input
void ReadSerial(void *parameter) {
  while (1) {
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.parseInt(); //read next valid integer, if timeout returns 0
      if (incomingByte > 0)
      {
        rate = incomingByte;
        Serial.print("Rate: ");
        Serial.println(rate);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  // Configure pin
  pinMode(led_pin, OUTPUT);

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
    toggleLED_1,  // Function to be called
    "Toggle 1",   // Name of task
    1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
    NULL,         // Parameter to pass to function
    1,            // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL,
    app_cpu);

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
    ReadSerial,  // Function to be called
    "Read Serial",   // Name of task
    1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
    NULL,         // Parameter to pass to function
    1,            // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL,
    app_cpu);

  // If this was vanilla FreeRTOS, you'd want to call vTaskStartScheduler() in
  // main after setting up your tasks.
}

void loop() {
  // Do nothing
  // setup() and loop() run in their own task with priority 1 in core 1
  // on ESP32
}
