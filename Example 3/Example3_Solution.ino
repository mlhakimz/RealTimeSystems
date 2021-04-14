// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Globals
static char message[255];
static char c;
static int i, len = 0;
static char *msg_ptr = NULL;
static volatile bool msg_flag = 0;

// Our task: Read serial input and allocate memory
void ReadSerial(void *parameter) {
  while (1) {
    if ((msg_flag == 0) && (Serial.available()))
    {
      c = Serial.read();
      message[i] = c;
      i++;
      if (c == '\n')
      {
        len = i;
        i = 0;
        message[len - 1] = '\0';
        msg_ptr = (char *)pvPortMalloc(len * sizeof(char));

        // If malloc returns 0 (out of memory), throw an error and reset
        configASSERT(msg_ptr);

        // Copy message
        memcpy(msg_ptr, message, len);

        // Notify other task that message is ready
        msg_flag = 1;
      }
    }
  }
}

// Our task: Print message input by user and clear memory
void EchoMessage(void *parameter) {
  while (1) {
    if (msg_flag == 1)
    {
      Serial.println(msg_ptr);
      Serial.print("Free heap (bytes): ");
      Serial.println(xPortGetFreeHeapSize());

      // Free buffer, set pointer to null, and clear flag
      vPortFree(msg_ptr); // Without this, the heap memory will build up with each serial input.
      msg_ptr = NULL;
      msg_flag = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
    ReadSerial,  // Function to be called
    "Read Serial",   // Name of task
    1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
    NULL,         // Parameter to pass to function
    1,            // Task priority (0 to configMAX_PRIORITIES - 1)
    NULL,
    app_cpu);

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
    EchoMessage,  // Function to be called
    "Echo Message",   // Name of task
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
