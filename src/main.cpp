#include <Arduino.h>
#include <SPI.h>
#include <esp_task_wdt.h>

void task1(void *p){
  SPISettings s1(40000000,MSBFIRST,SPI_MODE0); // cd = 4097
  while(1){
    SPI.beginTransaction(s1);
    uint32_t cd = SPI.getClockDivider();
    SPI.endTransaction();
    if(cd!=4097){
      Serial.printf("task1 SPI clock wverwritten: %8u %u\n",millis(),cd);
    }
    // delay(1);
  }
  vTaskDelete(NULL);
}
void task2(void *p){
  SPISettings s2(1000000,MSBFIRST,SPI_MODE0); // cd = 10227713
  while(1){
    SPI.beginTransaction(s2);
    uint32_t cd = SPI.getClockDivider();
    SPI.endTransaction();
    if(cd!=10227713){
      Serial.printf("task2 SPI clock wverwritten: %8u %u\n",millis(),cd);
    }
    // delay(1);
  }
  vTaskDelete(NULL);
}

void setup() {
  // here is no delay in tasks so watchdog must be disabled
  esp_task_wdt_init(100000, false);
  Serial.begin(115200);
  Serial.printf("\n--->START<---\n");
  SPI.begin();
  // multiple task per core mandatory to reveal issue
  // othervise it might take so long before any fail
  xTaskCreatePinnedToCore(task1,"task1",4096,NULL,5,NULL,0);
  xTaskCreatePinnedToCore(task2,"task2",4096,NULL,5,NULL,1);
  xTaskCreatePinnedToCore(task1,"task1",4096,NULL,5,NULL,0);
  xTaskCreatePinnedToCore(task2,"task2",4096,NULL,5,NULL,1);
  xTaskCreatePinnedToCore(task1,"task1",4096,NULL,5,NULL,0);
  xTaskCreatePinnedToCore(task2,"task2",4096,NULL,5,NULL,1);
  xTaskCreatePinnedToCore(task1,"task1",4096,NULL,5,NULL,0);
  xTaskCreatePinnedToCore(task2,"task2",4096,NULL,5,NULL,1);
  xTaskCreatePinnedToCore(task1,"task1",4096,NULL,5,NULL,0);
  xTaskCreatePinnedToCore(task2,"task2",4096,NULL,5,NULL,1);
  xTaskCreatePinnedToCore(task1,"task1",4096,NULL,5,NULL,0);
  xTaskCreatePinnedToCore(task2,"task2",4096,NULL,5,NULL,1);
}

void loop() {
}