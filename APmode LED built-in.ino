#include <ESP8266WiFi.h>

const char* ssid = "ESP8266-AP";
const char* password = "12345678";

WiFiServer server(80);
const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // LED mati

  WiFi.softAP(ssid, password);
  Serial.println("Access Point dibuat");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  while (!client.available()) delay(1);

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/ON") != -1) digitalWrite(ledPin, LOW);
  if (request.indexOf("/OFF") != -1) digitalWrite(ledPin, HIGH);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  // HTML ditulis per baris
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'>");
  client.println("<title>Kontrol LED</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Kontrol LED ESP8266</h1>");
  client.println("<p><a href=\"/ON\"><button>Nyalakan LED</button></a></p>");
  client.println("<p><a href=\"/OFF\"><button>Matikan LED</button></a></p>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Permintaan selesai");
}
