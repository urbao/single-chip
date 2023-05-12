#include <WiFi.h>

int port = 7777;  //Port number
WiFiServer server(port);

//Server connect to WiFi Network
const char *ssid = "iPhone";        //Enter your wifi SSID
const char *password = "00000000";  //Enter your wifi Password

int sw[2] = { 18, 19 };
bool right_sw = 0, left_sw = 0;

void setup() {
  Serial.begin(115200);

  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  //Connect to wifi

  // Wait for connection
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);

  pinMode(sw[0], INPUT);
  pinMode(sw[1], INPUT);
}

void loop() {
  /*do something*/
  WiFiClient client = server.available();

  //Serial.println(sendData.c_str());
  if (client) {
    if (client.connected()) {
      Serial.println("Client Connected");
    }

    while (client.connected()) {
      right_sw = (digitalRead(sw[0]) == HIGH) ? 1 : 0;
      left_sw = (digitalRead(sw[1]) == HIGH) ? 1 : 0;
      String command = "";
      /*do something*/
      if (right_sw == 0 && left_sw == 0) {
        command = "L0R0";
      } else if (right_sw == 1 && left_sw == 0) {
        command = "L0R1";
      } else if (right_sw == 0 && left_sw == 1) {
        command = "L1R0";
      } else if (right_sw == 1 && left_sw == 1) {
        command = "L1R1";
      }
      Serial.println(command);
      client.write(command.c_str());
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}