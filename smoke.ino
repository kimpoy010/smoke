#include <UIPEthernet.h>

int buzzer = 8;
int smokeA0 = A5;
int smokeA1 = A4;
int smokeA2 = A3;

int sensorThres1 = 650;
int sensorThres2 = 500;
int sensorThres3 = 500;


byte mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};    
EthernetClient client;
char server[] = "192.168.2.100";
int  interval = 5000; 
char uid[] = "1"; 
String readString = String(100); 

void setup() {
  
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(smokeA1, INPUT);
  pinMode(smokeA2, INPUT);

  
  Serial.begin(9600);
  Ethernet.begin(mac);
  
  Serial.print("IP Address        : ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  int analogSensor1 = analogRead(smokeA0);
  int analogSensor2 = analogRead(smokeA1);
  int analogSensor3 = analogRead(smokeA2);
  

  if (analogSensor1 > sensorThres1 || analogSensor2 > sensorThres2 || analogSensor3 > sensorThres3)
  {
          if(client.connect(server, 80)){
            Serial.println("-> Connected");
            // Make a HTTP request:
            client.print( "GET /apartment/insert.php?");
            client.print("uid=");
            client.print(uid);
            client.println( " HTTP/1.1");
            client.print( "Host: " );
            client.println(server);
            client.println( "Connection: close" );
            client.println();
            client.println();

           while (client.connected()) {
              if (client.available()) {
                char c = client.read();
                Serial.print(c);
              }
           }

            
            client.stop();
            delay(1000); 
            tone(buzzer, 1000);
            delay(10000); 
            noTone(buzzer);
            delay(1000);    
          }else{
            Serial.println("--> connection failed/n");
          }
  }
  else
  {
    noTone(buzzer);
  }
  delay(1000);
}


