#include "activity_interface.pb.h"
#include "pb_common.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include <ESP8266WiFi.h>

const int trigPin = 2;
const int echoPin = 0;
const char* ssid = "onhub";
const char* password = "ekchotaghar";
const char* addr = "192.168.88.245";
const uint16_t port = 3570;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("trying to connect..."); 
    delay(500);
  }
  Serial.println("Connected to WiFi!");
  Serial.println(WiFi.localIP());
}

void loop() {                                         
  // clear trigger Pin
  digitalWrite(trigPin, LOW);
  delay(2);
  // set to high & wait.                                                                                                                                                                                                                
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // get voltage of echoPin.
  long duration = pulseIn(echoPin, HIGH);

  // we calculate distance with the formula: T * C / 2,
  //  where C is sonic speed of sound wave and T is time
  //  between emmission and reception.
  long distance = duration * 0.017;

  if (!client.connect(addr, port)) {
    Serial.println("connection failed");  
    Serial.println("wait 5 sec to reconnect...");
    delay(5000);
    return;
  }

  //thresh 27 
  if (distance <= 27) {
    Esp8266Alert_AlertThresholdCross alert Esp8266Alert_AlertThresholdCross_init_zero;
    alert.crossed_thresh = distance;
    sendEvent(alert);
    Serial.println("intruder");
    Serial.println(distance);
  }

  // each cycle is 1s
  delay(1000);
}

void sendEvent(Esp8266Alert_AlertThresholdCross e) {
  uint8_t buffer[128];
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  if (!pb_encode(&stream, Esp8266Alert_AlertThresholdCross_fields, &e)) {
    Serial.println("failed to encode proto");
    return;
  }
  client.write(buffer, stream.bytes_written);
}
