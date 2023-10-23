#include <ESP8266WebServer.h>

int WEB_SERVER_PORT = 80;
ESP8266WebServer server(WEB_SERVER_PORT); 

void handle_root(){
  String page_code = "<form action=\"/LED\" method=\"POST\">";
  page_code += "<input type=\"text\" name=\"ssid\" placeholder=\"ssid\">";
  page_code += "<input type=\"passw\" name=\"passw\" placeholder=\"password\">";
  page_code += "<input type=\"submit\"></form>";
  server.send(200, "text/html", page_code);
}

void handle_connect(){ 
  if (server.hasArg("ssid") && server.hasArg("passw")) {
    String ssid = server.arg("ssid");
    String passw = server.arg("passw");
    Serial.println("Connecting to: " + passw);
    WiFi.begin(ssid.c_str(), passw.c_str());

    server.send(200, "text/html", "Connected");
    delay(1000);
    ESP.restart();
  } else {
    server.send(200, "text/html", "Login or password error.");
  }
  
}

void handle_led(){
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  server.sendHeader("Location", "/");
  server.send(303);
}

void handle_not_found(){
  server.send(404, "text/html", "404: check URL");

}

void handle_sensor(){
  int val = analogRead(A0);
  server.send(404, "text/html", String(val));
}

void server_init(){
  server.on("/", HTTP_GET, handle_root);
  server.on("/LED", HTTP_POST, handle_led);
  server.on("/CONNECT", HTTP_GET, handle_connect);
  server.on("/SENSOR", HTTP_GET, handle_sensor);
  server.onNotFound(handle_not_found); 
}

void server_begin(){
  Serial.print("Server started on port");
  Serial.println(WEB_SERVER_PORT);
}
