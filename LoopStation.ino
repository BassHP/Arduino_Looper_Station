//powered by b@ss - www.basshp.msxall.com

#include <SPI.h>
#include <TMRpcm.h>

//#define SD_ChipSelectPin 53  //se for usar o arduino mega SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  // Arduino Nano 328 /Uno

int count1 = 0;
int count2 = 0;
int count3 = 0;
int ledPin1 = 5;
int ledPin2 = 6;

TMRpcm audio;   // cria a saída de audio

void setup() {
  audio.speakerPin = 9; //5,6,11 or 46 no Mega, 9 no Uno, Nano, etc
  pinMode(9, OUTPUT);  //Pinos pares: 9,10 Mega: 5-2,6-7,11-12,46-45
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP); 
  Serial.begin(115200);
  
  if (!SD.begin(SD_ChipSelectPin)) {  
    return;
  } else {
    Serial.println("SD OK");
  }
  
  // Ativa o CS da SD 
  audio.CSPin = SD_ChipSelectPin;
}

void loop() {
  // Inicia gravação
  if (digitalRead(2) == LOW && count1 == 0) {
    //  audio.stopPlayback();
    count2 = 0;
    count1 = 1;
    audio.startRecording("loop.wav", 8000, A0);
    //delay(200);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin1, HIGH);
  }
  
  if (digitalRead(2) == HIGH && count1 == 1) {
    count1 = 0;
  }
  //Para gravção e inicia o playback do loop
  if (digitalRead(3) == LOW && count2 == 0) {
    audio.stopRecording("loop.wav");
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    audio.play("loop.wav");
    audio.loop(1);
    count2 = 1;
    delay(400);
  }
  //para playback
  if (digitalRead(3) == LOW && count2 == 1) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin1, LOW);
    audio.stopRecording("loop.wav");
    audio.stopPlayback();
    count2 = 2;
    delay(400);
  }
  
  if (digitalRead(3) == HIGH && count2 == 2) {
    count2 = 0;
  }
}

