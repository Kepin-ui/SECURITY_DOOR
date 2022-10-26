//   SECURITY DOOR PROTOTYPE V.1.0
//   BY KEVIN ARDIAN
//   BOARD NODEMCU8266 V1.0 LOLIN
//   GITHUB REPO https://github.com/Kepin-ui/SECURITY_DOOR

#include <SPI.h>
#include <MFRC522.h> 

#define SS_PIN        15      // D8 NodeMCU
#define RST_PIN       16      // D0 NodeMCU
#define RELAY         2       // D4 NODEMCU
#define ACCESS_DELAY  20000   
#define DENIED_DELAY  1000    
#define BUTTON        5       // D1 Nodemcu

byte uid[4];
String cardID;

MFRC522 rfid(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(RELAY, HIGH);
  Serial.println("PUT YOUR ID CARD TO THE READER");
  Serial.println();
}

void loop() {
  //VIA BUTTON SESSION
  int sensorVal=digitalRead(BUTTON);
   // Tombol Push Buton
        if(sensorVal == LOW){
        digitalWrite(RELAY,LOW);
        Serial.println("AKSES DITERIMA");
        Serial.println("VIA BUTTON");
        Serial.println(" ");
        delay(ACCESS_DELAY);
        digitalWrite(RELAY,HIGH);
        delay(1000);
    } else{digitalWrite(RELAY,HIGH);}
    
  //VIA RFID SESSION
  if ( ! rfid.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! rfid.PICC_ReadCardSerial())
  {
    return;
  }
  //SHOW UID
  Serial.print("UID TAG: ");
  String content= "";
  byte letter;
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("");
  content.toUpperCase();
  if (content.substring(1) == "83 DC F0 03")
  {
    // ACCESS GRANTED
    Serial.println("AKSES DITERIMA");
    Serial.println("ARDIAN");
    Serial.println("VIA RFID");
    Serial.println(" ");
    delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
  }
  else {
    // ACCESS DENIED
    Serial.println("AKSES DITOLAK");
    Serial.println(" ");
    delay(DENIED_DELAY);
  }
}
