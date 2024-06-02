#include <Arduino.h>

void anotherTask( void * parameter );
void ThirdTask( void * parameter );

void setup()
{
  Serial.begin(112500);
  /* we create a new task here */
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(19, OUTPUT);
  xTaskCreate(
    anotherTask, /* Task function. */
    "another Task", /* name of task. */
    1000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */

    xTaskCreate(
    ThirdTask, /* Task function. */
    "Third Task", /* name of task. */
    1000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */
}
/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{
  Serial.println("this is ESP32 Task");
  vTaskDelay(300);
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(300);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(300);
}


/* this function will be invoked when additionalTask was created */
void anotherTask( void * parameter )
{
/* loop forever */
  for(;;)
{
    Serial.println("this is another Task");
    vTaskDelay(10000);
}
}
void ThirdTask( void * parameter )
{
/* loop forever */
  for(;;)
{
    Serial.println("this is the third Task");
    vTaskDelay(1000);
    digitalWrite(19, HIGH);
    vTaskDelay(1000);
    digitalWrite(19, LOW);
    vTaskDelay(1000);
}

/* delete a task when finish, this will never happen because this is infinity loop */
vTaskDelete( NULL );
}
