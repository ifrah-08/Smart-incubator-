#define BLYNK_TEMPLATE_ID "TMPL61gf8v_Te"
#define BLYNK_TEMPLATE_NAME "Incubator"
#define BLYNK_AUTH_TOKEN "NIddNoLvweZyfR1EwsC6YuBGTaFkm-Il"
#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DHTPIN 25
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define bulb 27
#define input1 32
#define input2 33
#define motor_enable 35

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "OPPO A95";
char pass[] = "j8a3iczu";

float Temperature;
float Humidity;

bool useManualTemperature = false;
unsigned long currentMillis = 0, previousMillis = 0, dayStartMillis = 0;
const unsigned long interval = 2000, oneDayMillis = 86400000;
int dayCounter = 1;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  pinMode(bulb, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  digitalWrite(bulb, LOW);
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  dayStartMillis = millis();
}

void loop() {
  Blynk.run();
  currentMillis = millis();
  // Increment the dayCounter if a day has passed
  if (currentMillis - dayStartMillis >= oneDayMillis) {
    dayCounter++;
    dayStartMillis += oneDayMillis;
  }
  if (!useManualTemperature) {
    if (dayCounter <= 18) {
      Temperature = 15.0;
      Humidity = 40.0;
    } else {
      Temperature = 45.0;
      Humidity = 70.0;
    }
  }
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature)) return;
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    if (dayCounter <= 18) {
      First_18_days(temperature, humidity);
    } else {
      Last_days(temperature, humidity);
    }
  }
}

BLYNK_WRITE(V2) {
  useManualTemperature = param.asInt();
  Serial.print("Use Manual Temperature: ");
  Serial.println(useManualTemperature ? "Enabled" : "Disabled");
}

BLYNK_WRITE(V3) {
  if (useManualTemperature) {
    Temperature = param.asFloat();  // Update global temperature with manual input
    Serial.print("Manual Temperature Set To: ");
    Serial.println(Temperature);
  }
}

BLYNK_WRITE(V4) {
  if (useManualTemperature) {
    Humidity = param.asFloat();  // Update global humidity with manual input
    Serial.print("Manual Humidity Set To: ");
    Serial.println(Humidity);
  }
}

void First_18_days(float temperature, float humidity) {
  control_ac_load(temperature);
  control_fan(humidity, temperature);
}

void Last_days(float temperature, float humidity) {
  control_ac_load(temperature);
  control_fan(humidity, temperature);
}

void control_ac_load(float temperature) {
  if (temperature > Temperature) {
    digitalWrite(bulb, LOW);
  } else {
    digitalWrite(bulb, HIGH);
  }
}

void control_fan(float humidity, float temperature) {
  if (humidity > Humidity || temperature > Temperature) {
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    analogWrite(motor_enable , 4000);
  } else {
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    analogWrite(motor_enable , 0);
  }
}
