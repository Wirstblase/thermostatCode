#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
#define RELAYPIN 8

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01

void setup(void) {

  pinMode(8,OUTPUT);

  digitalWrite(RELAYPIN,HIGH);
  delay(0);
  digitalWrite(RELAYPIN,LOW);
  delay(0);
  digitalWrite(RELAYPIN,HIGH);

  Serial.begin(9600);
  radio.begin(); // Start the NRF24L01

  radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive

  radio.startListening(); // Listen to see if information received

}

void loop(void) {

  while (radio.available())
  {
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
    Serial.println(ReceivedMessage[0]);
    if(ReceivedMessage[0] == 000){
      digitalWrite(RELAYPIN,HIGH);
    } else if(ReceivedMessage[0] == 111){
      digitalWrite(RELAYPIN,LOW);  
    }
  }
}
