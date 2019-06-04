#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const char* server = "95.161.37.71";  // server's address
const char* resource = "/controler.php?id=1778";                    // http resource
const unsigned long BAUD_RATE = 9600;                 // serial connection speed
const unsigned long HTTP_TIMEOUT = 10000;  // max respone time from server
const size_t MAX_CONTENT_SIZE = 512;       // max size of the HTTP response
const int httpPort = 80;

const int rel4 = 2;
const int rel5 = 3;
const int rel6 = 5;
const int rel7 = 6;
const int rel8 = 7;
const int rel9 = 8;
const int rel10 = 9;
const int rel11 = 11;
const int rel12 = 12;
const int rel13 = 13;
const char* json = "{\"ControlerID\":\"1777\",\"pc1\":ok,\"pc2\":\"rest\"}";


const char* ssid = "gigaiii";
const char* pass = "19261926";
int i =0;
char incomingBytes[3];
bool skipResponseHeaders;
struct UserData {
  char pk6[32];
  char pk7[32];
  char pk8[32];
  char pk9[32];
};

//WiFiServer server(555);
IRsend irsend(3);

void setup() 
 {
  initSerial();
  delay(10);
  Serial.print("Connecting to "); //for debugging
  Serial.println(ssid); // for debugging
  IPAddress ip(192, 168, 0, 177);
  // WiFi.config(ip);
  WiFi.begin(ssid, pass);
  while (WiFi.status() !=WL_CONNECTED)
  {
     delay(500);
     Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());   
  irsend.begin();
  pinMode(4, OUTPUT);  }

void loop() 
{
WiFiClient client;
/*if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
*/

if (client.connect(server, 80)) {
  
      // Send the HTTP GET request to the server
      Serial.print("GET ");
      Serial.println(resource);
      client.print("GET ");
      client.print(resource);
      client.println(" HTTP/1.0");
      client.print("Host: ");
      client.println(server);
      client.println("Connection: close");
      client.println();
      bool sendRequest = true;
      
      // HTTP headers end with an empty line
      char endOfHeaders[] = "\r\n\r\n";
      client.setTimeout(HTTP_TIMEOUT);
      bool ok = client.find(endOfHeaders);
      if (!ok) {
        Serial.println("No response or invalid response!");
        skipResponseHeaders = false;
      }else skipResponseHeaders = true;
      Serial.println("Response OK!");
    
      if (sendRequest && skipResponseHeaders) {
          UserData userData;
          // Compute optimal size of the JSON buffer according to what we need to parse.
          // This is only required if you use StaticJsonBuffer.
          const size_t BUFFER_SIZE =
              JSON_OBJECT_SIZE(10) + MAX_CONTENT_SIZE;    // additional space for strings        
          // Allocate a temporary memory pool
          DynamicJsonBuffer jsonBuffer(BUFFER_SIZE);         
          JsonObject& root = jsonBuffer.parseObject(client); //JsonObject& root = jsonBuffer.parseObject(json);        
          if (!root.success()) {
            Serial.println("JSON parsing failed!");
            // return false;
          }
          
          String PCa = root["pc1"];
          String PCb = root["pc2"];
          String PCc = root["pc3"];
          String PCd = root["pc4"];
          String PCe = root["pc5"];
          String PCf = root["pc6"];
          String PCg = root["pc7"];
          String PCh = root["pc8"];
          String PCk = root["pc9"];
          String PCj = root["pc10"];
          Serial.println("working");
          
          if ( PCa == "on"){
              irsend.sendNEC(0xFB30CF, 32);
              Serial.println("cannel 0");
              delay(200);
             }
          if ( PCb == "on"){
              irsend.sendNEC(0xFB2AD5, 32);
              Serial.println("cannel 1");
              delay(200);
             }
          if ( PCc == "on"){
              irsend.sendNEC(0xFBA857, 32);
              Serial.println("cannel 2");
              delay(200);
             }
          if ( PCd == "on"){
              irsend.sendNEC(0xFB0AF5, 32);
              Serial.println("cannel 3");
              delay(200);
             } 
          if ( PCe == "on"){
             irsend.sendNEC(0xFB48B7, 32);
              Serial.println("cannel 4");
              delay(200);
             } 
          if ( PCf == "on"){
              irsend.sendNEC(0xFB8877, 32);
              Serial.println("cannel 5");
              delay(200);
             }
          if ( PCg == "on"){
              irsend.sendNEC(0xFB32CD, 32);
              Serial.println("cannel 6");
              delay(200);
             }
          if ( PCh == "on"){
              irsend.sendNEC(0xFB708F, 32);
              Serial.println("cannel 7");
              delay(200);
             }
          if ( PCk == "on"){
              digitalWrite(4,HIGH);
              Serial.println("light on");
              delay(200);
             }
           if ( PCk == "off"){
            digitalWrite(4,LOW);
            Serial.println("ligt low");
            delay(200);
           }
          if ( PCj == "on"){
              irsend.sendNEC(0xFB38C7, 32);
              Serial.println("on/of");
              delay(200);
             }
           }        
      }else Serial.println("connection failed");
   
   client.stop();
   delay(600); 
}
    
void initSerial() {
    Serial.begin(9600); 
   //while (!Serial) {
   //wait for serial port to initialize
   //}
   Serial.println("Serial ready");
}

void printUserData(const struct UserData* userData) {
 // Serial.print("pk1 = ");
 // Serial.println(userData->pk1);
 // Serial.print("pk2 = ");
 // Serial.println(userData->pk2);
 // Serial.println(userData->pk1);
  
}




    
    
