const char* host = "api.thingspeak.com";
String url = "/update?api_key=ONY67ZOFC5SCSKOD";   // Your Own Key here
const int httpPort = 80;
//change interval to 600
int interval = 600;
//get unsigned random number
unsigned long randomNum;
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "U+NetFC73";   // Your own ssid here
const char* password = "";  // Your own password here


String working() { 
	randomNum = rand() % 100; // get random number between 0 ~ 100
	return(String("field1=")+String(randomNum));
}

void delivering(String payload) { 
	WiFiClient client;
	Serial.print("connecting to ");
	Serial.println(host);
	if (!client.connect(host, httpPort)) {
		Serial.print("connection failed: ");
		Serial.println(payload);
		return;
	}
	String getheader = "GET "+ String(url) +"&"+ String(payload) +" HTTP/1.1";
	client.println(getheader);
	client.println("User-Agent: ESP8266 Seohwan Yoo");  
	client.println("Host: " + String(host));  
	client.println("Connection: close");  
	client.println();

	Serial.println(getheader);
	while (client.connected()) {
		String line = client.readStringUntil('\n');
		Serial.println(line);
	}
	Serial.println("Done cycle.");
}

void connect_ap() {
	Serial.println();
	Serial.print("connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.print("\n Got WiFi, IP address: ");
	Serial.println(WiFi.localIP());  
}

void setup() {
	Serial.begin(115200);
	connect_ap();
	randomSeed(42);
	Serial.println("ESPArduinoThingSpeak.cpp - 2017/3/23");
}

unsigned long mark = 0;
void loop() {
	if (millis() > mark ) {
		mark = millis() + interval;
		String payload = working();
		delivering(payload);
	}
}
