
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLPDkTDrGz"
#define BLYNK_DEVICE_NAME "Suhu"
#define BLYNK_AUTH_TOKEN "0a_xz61JEfJbwyHbk9G6Z7IBOWy1W478"

#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>



// You should get Auth Token in the Blynk App .
// Go to the Project Settings (nut icon).
char auth[] = "0a_xz61JEfJbwyHbk9G6Z7IBOWy1W478";
char ssid[] = "homeicon";
char pass[] = "ponen505";

#define DHTPIN D3           // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V2, h);
}

void setup()
{
  // Debug console 
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();

  Serial.print();
}
