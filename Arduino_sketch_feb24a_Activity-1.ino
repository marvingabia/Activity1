#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Gustomo";
const char* password = "1234567890";

// Define multiple LED pins
const int ledPins[] = {2, 4, 5, 18, 19};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

WebServer server(80);  // Create a web server on port 80

int currentMode = 0; // Tracks the current mode

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 LED Control</title></head><body>";
  html += "<h1>ESP32 LED Control</h1>";
  html += "<button onclick=\"fetch('/nextMode').then(response => alert('Mode Changed!'))\">Change Mode</button>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleNextMode() {
  currentMode = (currentMode + 1) % 9; // Cycle through 9 modes (0-8)
  server.send(200, "text/plain", "Mode changed");
}

void setup() {
  Serial.begin(115200);

  // Initialize all LED pins
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Handle routes
  server.on("/", handleRoot);
  server.on("/nextMode", handleNextMode);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  switch (currentMode) {
    case 0:  // All LEDs OFF
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      break;

    case 1:  // All LEDs ON
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
      break;

    case 2:  // Blink Mode
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
      delay(500);
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      delay(500);
      break;

    case 3:  // Chase Mode (Left to Right)
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], HIGH);
        delay(200);
        digitalWrite(ledPins[i], LOW);
      }
      break;

    case 4:  // Reverse Chase Mode (Right to Left)
      for (int i = numLeds - 1; i >= 0; i--) {
        digitalWrite(ledPins[i], HIGH);
        delay(200);
        digitalWrite(ledPins[i], LOW);
      }
      break;

   
    case 6:  // Left to Right Wave Mode
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], HIGH);
        delay(200);
      }
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
        delay(200);
      }
      break;

    case 7:  // Right to Left Wave Mode
      for (int i = numLeds - 1; i >= 0; i--) {
        digitalWrite(ledPins[i], HIGH);
        delay(200);
      }
      for (int i = numLeds - 1; i >= 0; i--) {
        digitalWrite(ledPins[i], LOW);
        delay(200);
      }
      break;

    case 8:  // New: Alternating Light Mode**
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], (i % 2 == 0) ? HIGH : LOW);
      }
      delay(300);
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], (i % 2 == 0) ? LOW : HIGH);
      }
      delay(300);
      break;
  }
}









