#include <SPI.h>
#include <LoRa.h>

//Определяем пины, используемые трансивером
#define ss 10
#define rst 9
#define dio0 2

int schet = 0;

String LoRaDataPast = " ";

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
  Serial.print("packetSize:");
  Serial.println(packetSize);
  if (packetSize == 0)
  {
    schet++;
  }
  if (packetSize > 2)
  {
    Serial.println(schet);
    schet = 0;
  }
  if (schet > 15)
  {
    tone (8, 600); // включаем на пьезодинамик 600 Гц
    delay(500);
    noTone(8);
  }
  if (schet < 15)
  {
    noTone(8);
  }
  int datchik = analogRead(A0);
  bool stat = 0;
  String LoRaDataPresent = LoRa.readString();
  delay(300);
  char poezd = LoRaDataPresent[0];
  while (poezd == '1' && stat == 0) {
    datchik = analogRead(A0);
    if (datchik < 40) {
      stat = 1;
    }
    tone (8, 600); // включаем на пьезодинамик 600 Гц
    delay(300);
    tone (8, 900);
    delay(300);
    noTone(8);
  }
}
