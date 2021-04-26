// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Globals
static const int led_pin = LED_BUILTIN;
static char message[255];
static char c;
static int i, len = 0;
static TimerHandle_t one_shot_timer = NULL;

// Callback function: Turn off LED when timer expires
void autoDimmerCallback(TimerHandle_t xTimer) {
  digitalWrite(led_pin, LOW);
}

// Our task: Echo message input by user
void EchoMessage(void *parameter)
{
  while (1)
  {
    if (Serial.available())
    {
      c = Serial.read();

      // Turn on the LED
      digitalWrite(led_pin, HIGH);

      message[i] = c;
      i++;
      if (c == '\n')
      {
        len = i;
        i = 0;
        message[len - 1] = '\0';
        Serial.println(message);

        // Start timer (if timer is already running, this will act as xTimerReset() instead)
        xTimerStart(one_shot_timer, portMAX_DELAY);
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  // Configure Serial
  Serial.begin(115200);
  
  // Configure LED pin
  pinMode(led_pin, OUTPUT);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  // Create a one-shot timer
  one_shot_timer = xTimerCreate(
                      "One-shot timer",             // Name of timer
                      5000 / portTICK_PERIOD_MS,    // Period of timer (in ticks)
                      pdFALSE,                      // Auto-reload
                      (void *)0,                    // Timer ID
                      autoDimmerCallback);          // Callback function

  // Start command line interface (CLI) task
  xTaskCreatePinnedToCore(EchoMessage,
                          "Echo Message",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
