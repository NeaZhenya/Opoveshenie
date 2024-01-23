#include <SPI.h>
#include <LoRa.h>

//определяем номера пинов, используемые трансивером
#define ss 10
#define rst 9
#define dio0 2

int counter = 0;

void setup() {
  //запускаем монитор порта
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");

  //настраиваем трансивер
  LoRa.setPins(ss, rst, dio0);

  //замените LoRa.begin(---E-) частотой, которую вы собираетесь использовать
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  // Измените слово синхронизации (0xF3)
  // Слово синхронизации нужно, чтобы не получать сообщения от других трансиверов
  // можно изменять в диапазоне 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  bool poezd = 0;
  int hall = analogRead(A0);
  Serial.println(hall);

  if (hall < 40)
  {
    poezd = 1;
    LoRa.beginPacket();
    LoRa.print(poezd);
    LoRa.print(" ");
    LoRa.print(counter);
    LoRa.endPacket();
    Serial.println();
  }else 
   {
    poezd =0;
    LoRa.beginPacket();
    LoRa.print(poezd);
    LoRa.print(" ");
    LoRa.print(counter);
    LoRa.endPacket();
   }
   counter++;
   if(counter>1000)
     counter = 0;
   delay(500);
}
