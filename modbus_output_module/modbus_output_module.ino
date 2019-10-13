#include <SoftwareSerial.h>
#include <ModbusSlave.h>

#define SLAVE_ID 1
#define RS485_BAUDRATE 9600

#define RS485_RX_PIN 2
#define RS485_TX_PIN 3
#define RS485_TX_ENABLE_PIN 4

#define OUTPUT1_PIN 6
#define OUTPUT2_PIN 7
#define OUTPUT3_PIN 8
#define OUTPUT4_PIN 9
#define OUTPUT5_PIN 10
#define OUTPUT6_PIN 11
#define OUTPUT7_PIN 12
#define OUTPUT8_PIN 13
#define OUTPUT9_PIN A0
#define OUTPUT10_PIN A1
#define OUTPUT11_PIN A2
#define OUTPUT12_PIN A3

SoftwareSerial mySerial(RS485_RX_PIN, RS485_TX_PIN);
//Modbus slave(mySerial, SLAVE_ID, RS485_TX_ENABLE_PIN);
Modbus slave(mySerial, SLAVE_ID);

void setup() {
  pinMode(OUTPUT1_PIN, OUTPUT);
  pinMode(OUTPUT2_PIN, OUTPUT);
  pinMode(OUTPUT3_PIN, OUTPUT);
  pinMode(OUTPUT4_PIN, OUTPUT);
  pinMode(OUTPUT5_PIN, OUTPUT);
  pinMode(OUTPUT6_PIN, OUTPUT);
  pinMode(OUTPUT7_PIN, OUTPUT);
  pinMode(OUTPUT8_PIN, OUTPUT);
  pinMode(OUTPUT9_PIN, OUTPUT);
  pinMode(OUTPUT10_PIN, OUTPUT);
  pinMode(OUTPUT11_PIN, OUTPUT);
  pinMode(OUTPUT12_PIN, OUTPUT);
  
  slave.cbVector[CB_WRITE_COILS] = writeDigitalOut;
  
  mySerial.begin(RS485_BAUDRATE);
  slave.begin(RS485_BAUDRATE);
}

void loop() {
  slave.poll();
}

/**
 * Handle Force Single Coil (FC=05) and Force Multiple Coils (FC=15)
 * set digital output pins (coils).
 */
uint8_t writeDigitalOut(uint8_t fc, uint16_t address, uint16_t length) {
  for (int i = 0; i < length; i++) {
    digitalWrite(address + i, slave.readCoilFromBuffer(i));
  }
  return STATUS_OK;
}
