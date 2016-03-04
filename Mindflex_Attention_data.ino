  /*
    Schematic
    Arduino: pin 6     Neopixel: In
             VCC                 +
             GND                 -
              
    Arduino: RX        Mindflex: TX 
             GND                 GND
  */
  
  #include <Brain.h>
  #include <Adafruit_NeoPixel.h>
  #include <avr/power.h>
  
  #define NUM_LED 1  //sets the maximum numbers of LEDs
  #define Threshold 3 // this sets the light to activate TENS
  #define PIN 6
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
  
  int attentionVal;
  //int signalVal;
  Brain brain(Serial);
  long interval = 500; // Changes based on attention value.
  
  
  void setup() {
    Serial.begin(9600); //begin serial communications
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
   
  }
    
   
  
  void loop() {
     if (brain.update()) {
           attentionVal = brain.readAttention();
           //signalVal = brain.readSignalQuality();
           
           //Serial.println(signalVal);
           Serial.println(attentionVal);
           // Attention runs from 0 to 100.
           interval = (100 - brain.readAttention()) * 10;
           
            if (attentionVal >= 1) {
                colorWipe(strip.Color(0, 0, 255), 50); // Solid Blue Light
                
            }
              else {
                  theaterChase(strip.Color(127,   0,   0), 50); // FLashing Red Light
           }
           delay(10);
      }
  }
    
    
    
    
    
  

  
  
  

  
    
  // Neopixel functions //  
  /////////////////////////////////////////////////////// 
  // FLashing Red Light 
  void theaterChase(uint32_t c, uint8_t wait) {
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
      for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, c);    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
      }
    }
  }

  // Solid Blue Light //
  void colorWipe(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
  }

   
    
