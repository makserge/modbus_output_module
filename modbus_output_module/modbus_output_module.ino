#include <ModbusSlave.h>

#define SLAVE_ID 1
#define RS485_BAUDRATE 9600

#define RS485_TX_ENABLE_PIN PA4

#define OUTPUT1_PIN PB7 //10
#define OUTPUT2_PIN PB6 //9
#define OUTPUT3_PIN PB5 //8
#define OUTPUT4_PIN PB4 //7
#define OUTPUT5_PIN PB3 //6
#define OUTPUT6_PIN PA15 //5
#define OUTPUT7_PIN PA12 //4
#define OUTPUT8_PIN PA11 //3
#define OUTPUT9_PIN PA7 //18
#define OUTPUT10_PIN PA6 //17
#define OUTPUT11_PIN PA5 //16

Modbus slave(SLAVE_ID, RS485_TX_ENABLE_PIN);

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
  
  slave.cbVector[CB_WRITE_COILS] = writeDigitalOut;

  Serial.setRx(PA3);
  Serial.setTx(PA2);
  Serial.begin(RS485_BAUDRATE);
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
