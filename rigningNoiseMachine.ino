#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playWav2;     //xy=183,377
AudioPlaySdWav           playWav1;     //xy=190,302
AudioEffectFade          fade2;          //xy=368,359
AudioEffectFade          fade1;          //xy=375,281
AudioMixer4              mixer1;         //xy=595,314
AudioOutputI2S           i2s1;           //xy=820,273
AudioConnection          patchCord1(playWav2, 0, fade2, 0);
AudioConnection          patchCord2(playWav1, 0, fade1, 0);
AudioConnection          patchCord3(fade2, 0, mixer1, 1);
AudioConnection          patchCord4(fade1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=226,159
// GUItool: end automatically generated code


// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

int lastSwitch = 1;

void setup() {
  Serial.begin(9600);
//  while (!Serial);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(6);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  playWav1.play("rigning.wav");
  Serial.println("playing wav 1 first time");
  while (!playWav1.isPlaying()) {

  }
}


void loop() {

  if (playWav1.isPlaying() && (playWav1.lengthMillis() - playWav1.positionMillis() < 30000) && lastSwitch == 1) {
    //  if (playWav1.isPlaying() && (playWav1.positionMillis() > 2500) && lastSwitch == 1) {
    playWav2.play("rigning.wav");
    while (!playWav2.isPlaying()) {

    }
    //    AudioNoInterrupts();
    fade1.fadeOut(2000);
    fade2.fadeIn(2000);
    //    AudioInterrupts();
    lastSwitch = 0;
    Serial.println("swwitch");
  }

  if (playWav2.isPlaying() && (playWav2.lengthMillis() - playWav2.positionMillis() < 30000) && lastSwitch == 0) {
    //  if (playWav2.isPlaying() && (playWav2.positionMillis() > 2500) && lastSwitch == 0) {
    playWav1.play("rigning.wav");
    while (!playWav1.isPlaying()) {

    }
    //    AudioNoInterrupts();
    fade1.fadeIn(2000);
    fade2.fadeOut(2000);
    //    AudioInterrupts();
    lastSwitch = 1;
    Serial.println("swwitch");
  }
//  Serial.println(AudioMemoryUsageMax());
}
