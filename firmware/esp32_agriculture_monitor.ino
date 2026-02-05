#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Server URL (we will create this later)
const char* serverURL = "http://127.0.0.1:5000/data";

// Thresholds
#define SOIL_MOISTURE_THRESHOLD 40
#define TEMP_THRESHOLD 35

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void loop() {

  // -------- Sensor Simulation --------
  int soilMoisture = random(20, 80);   // %
  float temperature = random(20, 45);  // °C
  float humidity = random(40, 90);     // %

  String alert = "NORMAL";

  if (soilMoisture < SOIL_MOISTURE_THRESHOLD) {
    alert = "LOW_SOIL_MOISTURE";
  } else if (temperature > TEMP_THRESHOLD) {
    alert = "HIGH_TEMPERATURE";
  }

  // -------- JSON Data --------
  String jsonData = "{";
  jsonData += "\"temperature\":" + String(temperature) + ",";
  jsonData += "\"humidity\":" + String(humidity) + ",";
  jsonData += "\"soil_moisture\":" + String(soilMoisture) + ",";
  jsonData += "\"alert\":\"" + alert + "\"";
  jsonData += "}";

  Serial.println("Sending Data:");
  Serial.println(jsonData);

  // -------- HTTP POST --------
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  }

  delay(5000); // send data every 5 seconds
}
