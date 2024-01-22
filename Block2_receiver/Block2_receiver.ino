#include <SPI.h>
#include <LoRa.h>

//Определяем пины, используемые трансивером
#define ss 10
#define rst 9
#define dio0 2

void setup() {
  //запускаем монитор порта
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //указываем пины трансивера
  LoRa.setPins(ss, rst, dio0);

  //замените аргумент LoRa.begin(---E-) частотой сигнала.
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  // Укажите слово синхронизации (0xF3)
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  int datchik = analogRead(A0);
  bool stat = 0;
  while (packetSize && stat == 0) {
    int datchik = analogRead(A0);
    Serial.println(packetSize);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    tone (8, 600); // включаем на пьезодинамик 600 Гц
    if (datchik < 40) {
      stat = 1;
    }
    delay(1000); // ждем 1 секунду
    tone(8, 900); // включаем на пьезодинамик 900 Гц
    if (datchik < 40) {
      stat = 1;
    }
    delay(1000); // ждем 1 секунду
    noTone(8); // отключаем пьезодинамик на пин 11
    if (datchik < 40) {
      stat = 1;
    }
  }
}
