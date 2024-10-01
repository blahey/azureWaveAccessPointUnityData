// Add to repository test!
//

#include <WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "AP_Network_SSID";    // Set the AP SSID
char password[] = "AP_Password";    // Set the AP password
char channel[] = "1";               // Set the AP channel
int status = WL_IDLE_STATUS;        // Indicator of Wifi status
int ssid_status = 0;                // Set SSID status, 1 hidden, 0 not hidden

WiFiUDP udp;
const char* udpAddress = "192.168.1.100";  // Default IP for the first connected device in AP mode
const int udpPort = 4211;

const int buttonPin = 21;
const int potPin = A0;

void setup() {
    Serial.begin(115200);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(potPin, INPUT);

    // Attempt to start AP
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to start AP with SSID: ");
        Serial.println(ssid);
        status = WiFi.apbegin(ssid, password, channel, ssid_status);
        delay(10000);
    }

    // AP MODE already started
    Serial.println("AP mode already started");
    Serial.println();
    printWifiData();
    printCurrentNet();
}

void loop() {
    int buttonState = digitalRead(buttonPin);
    int potValue = analogRead(potPin);

    char packetBuffer[50];
    sprintf(packetBuffer, "Button: %d, Pot: %d", buttonState, potValue);

    udp.beginPacket(udpAddress, udpPort);
    udp.write(packetBuffer);
    udp.endPacket();

    delay(40); // Send data every 40ms

    // Check the network connection once every 10 seconds
    // delay(10000);
    // printCurrentNet();
}

void printWifiData() {
    // Print your WiFi IP address
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // Print your subnet mask
    IPAddress subnet = WiFi.subnetMask();
    Serial.print("NetMask: ");
    Serial.println(subnet);

    // Print your gateway address
    IPAddress gateway = WiFi.gatewayIP();
    Serial.print("Gateway: ");
    Serial.println(gateway);
    Serial.println();
}

void printCurrentNet() {
    // Print the SSID of the AP
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // Print the MAC address of AP
    byte bssid[6];
    WiFi.BSSID(bssid);
    Serial.print("BSSID: ");
    Serial.print(bssid[0], HEX);
    Serial.print(":");
    Serial.print(bssid[1], HEX);
    Serial.print(":");
    Serial.print(bssid[2], HEX);
    Serial.print(":");
    Serial.print(bssid[3], HEX);
    Serial.print(":");
    Serial.print(bssid[4], HEX);
    Serial.print(":");
    Serial.println(bssid[5], HEX);

    // Print the encryption type
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type: ");
    Serial.println(encryption, HEX);
    Serial.println();
}
