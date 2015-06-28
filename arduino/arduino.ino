#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <ArduinoJson.h>

#define OUTPUT_PIN  6
#define LED_COUNT   70

bool DBG = false;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_COUNT, OUTPUT_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello world!");

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  StaticJsonBuffer<200> jsonBuffer;
  char *data = (char*) calloc(1, 200 * sizeof(char));
  int dataPos = 0;
  
  char cur;
  
  while (cur != '\n') {
    if (Serial.available() > 0) {
      cur = Serial.read();
      data[dataPos % 200] = cur;
      dataPos++;
    } else {}
  }

Serial.write(dataPos);

  if (dataPos == 0) {
    free(data);
    return;
  }

if (DBG) {
  Serial.write("Got: ");
  Serial.write(data);
  Serial.write("\n");  
}

JsonObject &root = jsonBuffer.parseObject(data);
  free(data);
  
  if (!root.success()) {
     Serial.write("Malformed json");
     return;
  }
  
  // Mode: 
  // 0 = Define the (R,G,B) value for a single LED
  // 1 = Single colour mode
  // 2 = Rainbow mode
  
  int mode = root["mode"];
  
  Serial.write((int)root["mode"]);
  if (mode == 0) {
     int pixel = root["pixel"];
     int red = root["r"];
     int green = root["g"];
     int blue = root["b"];
     pixels.setPixelColor(pixel, red, green, blue);
     pixels.show();
  } else if (mode == 1) {
    int red = root["r"];
    int green = root["g"];
    int blue = root["b"];
    for (int i=0; i<LED_COUNT; i++) {
      pixels.setPixelColor(i, red, green, blue); 
    }
    pixels.show();
  } else {
    Serial.write("Rainbow mode is left as an exercise to the reader to implement ¬_¬");
  }
}
