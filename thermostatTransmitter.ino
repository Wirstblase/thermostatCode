#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#define DHTPIN 6
#define DHTTYPE    DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

void setup(void) {
  dht.begin();
  Serial.begin(9600);
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}



void loop(void) {

  delay(2000);

  sensors_event_t event;
  dht.temperature().getEvent(&event);


  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));

   

    if (event.temperature >= 24.0f) {
      SentMessage[0] = 000;
      

    } else if (event.temperature <= 21.0f) {
      SentMessage[0] = 111;
      

    }

    radio.write(SentMessage, 1);
    Serial.println(SentMessage[0]);

  }

}
