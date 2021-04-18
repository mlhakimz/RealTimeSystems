// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// LED variables
static int blinkcount = 0;
static const int maxcount = 100;
static const int led_pin = LED_BUILTIN;

// Serial input variables
static char message[255];
static char command[] = "delay ";
static char c;
static int i, len = 0;
static int echo = 0;

// Queue variables
static const int msg_queue_len = 5;
static const int delay_queue_len = 5;
static QueueHandle_t delay_queue;
static QueueHandle_t msg_queue;



// Our task: blink an LED based on user input
void Blinky(void *parameter) {
  int rate = 500;                       //default rate.
  char msg[] = "Blinked 100 times.";
  
  while (1) {
    if (xQueueReceive(delay_queue, (void *)&rate, 0) == pdTRUE) {
      Serial.print("Delay updated: ");
      Serial.println(rate);
    }
    
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate / portTICK_PERIOD_MS);
    blinkcount++;
    
    if (blinkcount == 100)
    {
      if (xQueueSend(msg_queue, (void *)&msg, 10) != pdTRUE) {
        Serial.println("ERROR: Could not put item on delay queue.");
      }
      blinkcount = 0;
    }
  }
}

// Our task: Read serial input and echo/update delay
void ReadSerial(void *parameter) {
  int rate;
  char msg[255];
  
  while (1)
  {
    if (xQueueReceive(msg_queue, (void *)&msg, 0) == pdTRUE) {
      Serial.println(msg);
    }
    
    if (Serial.available())
    {
      c = Serial.read();
      message[i] = c;
      i++;
      if (c == '\n')
      {
        len = i;
        i = 0;
        message[len - 1] = '\0';

        for (int i = 0;  i < 6; i++)
        {
          if ( message[i] != command[i] )
          {
            echo = 1;
            break;
          }
          echo = 2;
        }
      }
    }

    if (echo == 1)
    {
      Serial.println(message);
      echo = 0;
    }
    else if (echo == 2)
    {
      rate = atoi(&message[6]);
      if (xQueueSend(delay_queue, (void *)&rate, 10) != pdTRUE) {
        Serial.println("ERROR: Could not put item on delay queue.");
      }
      echo = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Configure pin
  pinMode(led_pin, OUTPUT);

  // Create queues
  delay_queue = xQueueCreate(delay_queue_len, sizeof(int));
  msg_queue = xQueueCreate(msg_queue_len, 255);

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
    Blinky,  // Function to be called
    "Blink LED",   // Name of task
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

    
}

void loop() {
  // Do nothing
  // setup() and loop() run in their own task with priority 1 in core 1
  // on ESP32
}
