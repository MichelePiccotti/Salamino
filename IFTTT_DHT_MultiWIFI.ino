#include <ESP8266IFTTT.h>
#include <ESP8266WiFi.h>
#include "DHTesp.h"

#ifdef ESP32
#pragma message(FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

#define cicli 6 //Minuti tra una richiesta IFTTT e la successiva (cicli di 10 minuti)

//------- Replace the following! ------
char ssid[] = "TP-LINK_2.4GHz_EXT";       // your network SSID (name)
char password[] = "piccotti123";  // your network key

char ssid1[] = "Mptx";       // your network SSID (name)
char password1[] = "a74JFK12PtX";  // your network key

char ssid2[] = "Mptx_EXT";       // your network SSID (name)
char password2[] = "a74JFK12PtX";  // your network key

char ssid3[] = "TP-LINK";       // your network SSID (name)
char password3[] = "12344321";  // your network key

String value3;
WiFiClientSecure client;
DHTesp dht;
int cycle = 0;
float TEM = 0;
float HUM = 0;
unsigned long times;
void setup() {

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  times = millis();
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    if ((millis() - times) > 30000) {
      Serial.print("\n");
      break;
    }
    value3 = ssid;
  }
  if (WiFi.status() != WL_CONNECTED) {
    times = millis();
    Serial.print(ssid1);
    WiFi.begin(ssid1, password1);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if ((millis() - times) > 30000) {
        Serial.print("\n");
        break;
      }
      value3 = ssid1;
    }
  }
  if (WiFi.status() != WL_CONNECTED) {
    times = millis();
    Serial.print(ssid2);
    WiFi.begin(ssid2, password2);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if ((millis() - times) > 30000) {
        Serial.print("\n");

        break;
      }
      value3 = ssid2;
    }
  }
  if (WiFi.status() != WL_CONNECTED) {
    times = millis();
    Serial.print(ssid3);
    WiFi.begin(ssid3, password3);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if ((millis() - times) > 30000) {
        Serial.print("\n");

        break;
      }
      value3 = ssid3;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(value3);
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  dht.setup(14, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  HUM += humidity;
  TEM += temperature;
  //Serial.println(HUM);
  //Serial.println(TEM);
  //Serial.println(value3);

  cycle++;
  if (cycle >= cicli) {
    String hum = String(HUM / cycle, 1);
    String tem = String(TEM / cycle, 1);
    //Serial.print("---");
    //Serial.println(hum);
    //Serial.println(tem);

    IFTTT.trigger("TempHum", "gfiBydohP6hLFYAYBBfChpCWFKTOGwxAVAruJUy0th", hum, tem, value3);
    cycle = 0;
    HUM = 0;
    TEM = 0;
  }
  delay(600000); // 10minuti
}
