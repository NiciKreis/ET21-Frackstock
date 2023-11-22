#include <Arduino.h>
#include <SPI.h>
#include <NeoPixelConnect.h>
#include <BMI160Gen.h>
#include <cc1101.h>
#include <ccpacket.h>

// Lorenzo 9
// Antoine 4
// Jonas 8
// Michael 10


#include "RGB_LUT.h"
#define PRINT_MESSAGE
//#define USE_D_TAP
#define KAT 8

// NeoPixel
#define MAXIMUM_NUM_NEOPIXELS 8
NeoPixelConnect p(9, MAXIMUM_NUM_NEOPIXELS, pio0, 0);

// BMI160
const int bmi160_select_pin = 13;
const int bmi160_interrupt_pin = 14;
bool tap_interrupt = false;

// CC1101
#define CC1101_CS_PIN 17
#define CC1101_SCK_PIN 18
#define CC1101_MOSI_PIN 19
#define CC1101_MISO_PIN 16
#define CC1101_GDO0 20
#define CC1101Interrupt digitalPinToInterrupt(CC1101_GDO0)
CC1101 radio(CC1101_CS_PIN, CC1101_GDO0, CC1101_MISO_PIN);
byte syncWord[2] = {0x47, 0xB5};
bool packetWaiting = false;

// Interrupt functions
void messageReceived()
{
  packetWaiting = true;
}

uint8_t last_id, id,kat,r,g,b;
bool new_message = false;

void sendMessage(){
  CCPACKET packet;
  detachInterrupt(CC1101Interrupt);
  packet.length = 5;
  packet.data[0] = id;
  packet.data[1] = kat;
  packet.data[2] = r;
  packet.data[3] = g;
  packet.data[4] = b;
  radio.sendData(packet);
  attachInterrupt(CC1101Interrupt, messageReceived, FALLING);
}

bool doLights, doLightsLast = false;

void handleMessage(){
  CCPACKET packet;
  detachInterrupt(CC1101Interrupt);
  if (radio.receiveData(&packet) > 0){
    if (packet.crc_ok && packet.length > 0){
      if(!doLights){
        id = (uint8_t)packet.data[0];
        kat = (uint8_t)packet.data[1];
        r = (uint8_t)packet.data[2];
        g = (uint8_t)packet.data[3];
        b = (uint8_t)packet.data[4];
        #ifdef PRINT_MESSAGE
        Serial.print("KAT: ");
        Serial.println(kat);
        #endif
      }
    }
  }
  attachInterrupt(CC1101Interrupt, messageReceived, FALLING);
}

unsigned long lightStart = 0;
unsigned long lightStartPhase = 0;
unsigned int lightUp = 3000;
int deltaPhase = lightUp/300;
int phase = 0;

void lightManager(){
  unsigned long now = millis();

  if(doLights && (!doLightsLast)){
    if(kat <= 2){
      p.neoPixelFill(r,g,b,true);
    }
    lightStart = now;
    phase = 0;
    lightStartPhase = now;
    doLightsLast = doLights;
  }else if((!doLights) && doLightsLast){
    p.neoPixelClear(true);
    doLightsLast = doLights;
  }
  doLightsLast = doLights;
  
  if(doLights){
    if(now > lightStart + lightUp){
      doLights = false;
    }
  }

  if(doLights){
    switch(kat){
      case 3: // RGB
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            p.neoPixelFill(LUT[phase][0],LUT[phase][1],LUT[phase][2],true);
          }
          lightStartPhase = now;
        }
        break;
      case 4: // Strobo
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            if(STROBO[phase]){
              p.neoPixelFill(r,g,b,true);
            } else {
              p.neoPixelClear(true);
            }
          }
          lightStartPhase = now;
        }
        break;
      case 5: // Strobo RGB kombi
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            if(STROBO[phase]){
            p.neoPixelFill(LUT[phase][0],LUT[phase][1],LUT[phase][2],true);
            } else {
              p.neoPixelClear(true);
            }
          }
          lightStartPhase = now;
        }
        break;
      case 6: // Sine 5HZ
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            p.neoPixelFill(
                (SINE_5HZ[phase]*r)/255,
                (SINE_5HZ[phase]*g)/255,
                (SINE_5HZ[phase]*b)/255,
                true);
          }
          lightStartPhase = now;
        }
        break;
      case 7: // Sine 5HZ RGB
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            p.neoPixelFill(
                (SINE_5HZ[phase]*LUT[phase][0])/255,
                (SINE_5HZ[phase]*LUT[phase][1])/255,
                (SINE_5HZ[phase]*LUT[phase][2])/255,
                true);
          }
          lightStartPhase = now;
        }
        break;

      case 8: // Sine 1HZ
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            p.neoPixelFill(
                (SINE_1HZ[phase]*r)/255,
                (SINE_1HZ[phase]*g)/255,
                (SINE_1HZ[phase]*b)/255,
                true);
          }
          lightStartPhase = now;
        }
        break;

      case 9: // Sine 1HZ
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            p.neoPixelFill(
                (SINE_1HZ[phase]*LUT[phase][0])/255,
                (SINE_1HZ[phase]*LUT[phase][1])/255,
                (SINE_1HZ[phase]*LUT[phase][2])/255,
                true);
          }
          lightStartPhase = now;
        }
        break;

      case 10: // HUE
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            p.neoPixelFill(
                HUE_R[phase],
                HUE_G[phase],
                HUE_B[phase],
                true);
          }
          lightStartPhase = now;
        }
        break;
      case 11: // HUE Circle
        if(now > lightStartPhase + deltaPhase){
          phase = phase + 1;
          if(phase < 300){
            int offset = 43;
            p.neoPixelSetValue(1,HUE_R[phase],HUE_G[phase],HUE_B[phase]);
            p.neoPixelSetValue(2,HUE_R[(phase+offset)%300],HUE_G[(phase+offset)%300],HUE_B[(phase+offset)%300]);
            p.neoPixelSetValue(3,HUE_R[(phase+offset*2)%300],HUE_G[(phase+offset*2)%300],HUE_B[(phase+offset*2)%300]);
            p.neoPixelSetValue(4,HUE_R[(phase+offset*3)%300],HUE_G[(phase+offset*3)%300],HUE_B[(phase+offset*3)%300]);
            p.neoPixelSetValue(5,HUE_R[(phase+offset*4)%300],HUE_G[(phase+offset*4)%300],HUE_B[(phase+offset*4)%300]);
            p.neoPixelSetValue(6,HUE_R[(phase+offset*5)%300],HUE_G[(phase+offset*5)%300],HUE_B[(phase+offset*5)%300]);
            p.neoPixelSetValue(7,HUE_R[(phase+offset*6)%300],HUE_G[(phase+offset*6)%300],HUE_B[(phase+offset*6)%300]);
            p.neoPixelShow();
          }
          lightStartPhase = now;
        }
        break;
    }
  }
}

void bmi160_intr()
{
  tap_interrupt = true;
} 

void setup() {
  Serial.begin(115200);

  p.neoPixelClear(true);
  
  BMI160.begin(BMI160GenClass::SPI_MODE, Wire, bmi160_select_pin, bmi160_interrupt_pin);
  BMI160.attachInterrupt(bmi160_intr);
  BMI160.setAccelerometerRange(BMI160_ACCEL_RANGE_16G);
  BMI160.setAccelerometerRate(800);

  #if !defined USE_D_TAP
  BMI160.setShockDetectionThreshold(14000);
  BMI160.setShockDetectionDuration(0);
  BMI160.setIntShockEnabled(true);
  #else
  BMI160.setTapQuietDuration(true);
  BMI160.setTapShockDuration(true);
  BMI160.setDoubleTapDetectionDuration(7);
  BMI160.setTapDetectionThreshold(14000);
  #endif
  
  SPI = arduino::MbedSPI(CC1101_MISO_PIN, CC1101_MOSI_PIN, CC1101_SCK_PIN);
  SPI.begin();
  radio.init();
  radio.setSyncWord(syncWord);
  radio.setCarrierFreq(CFREQ_868);
  radio.setChannel(0);
  radio.disableAddressCheck();
  radio.setTxPowerAmp(PA_LongDistance);
  attachInterrupt(CC1101Interrupt, messageReceived, FALLING);
  
}

void loop() {
  // handle recieved message
  if (packetWaiting){
    packetWaiting = false;
    handleMessage();
    if (last_id != id){
      last_id = id;
      // send to others
      sendMessage();
      // do lights
      doLights = true;
      Serial.println("Light up from message!");
    } else {
      Serial.println("Ignore Message!");
    }
  }

  // handle tap interrupt
  if (tap_interrupt){
    tap_interrupt = false;
    // calculate parameters
    if(!doLights){
      while(id == last_id){
        id = (uint8_t)rand();
      }
      last_id = id;
      kat = KAT;
      int i = rand()%13;
      r = RGB[i][0];
      g = RGB[i][1];
      b = RGB[i][2];
      // send to others
      sendMessage();
    }
    // do ligths
    doLights = true;
    Serial.println("Light up from DTap!");
  }

  lightManager();
}
