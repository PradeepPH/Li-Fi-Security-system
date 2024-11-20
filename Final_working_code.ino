#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial mySerial(2,3);
#define Solenoid 12
#define ldr 8
int Buzzer = 4;
int GreenLed = 6;
int RedLed = 11;
int val;
int val2;
String duration;
int attemptCount=0;
int maxCount=5;
int lockout=3000;
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  mySerial.begin(9600);
  Serial.println("Initializing SIM800C...");
  delay(100);
  mySerial.println("AT");
  delay(100);
  pinMode(ldr, INPUT_PULLUP);
  pinMode(Solenoid, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(RedLed, OUTPUT);
  digitalWrite(RedLed, HIGH);
}

  void OpenDoor(){             //Lock opening function open for 3s
 
  digitalWrite(Solenoid,HIGH);
  tone(Buzzer, 500);
  digitalWrite(RedLed, LOW);
  digitalWrite(GreenLed, HIGH);
  
  delay(3000);
  digitalWrite(Solenoid,LOW);
  noTone(Buzzer);
  digitalWrite(RedLed, HIGH);
  digitalWrite(GreenLed, LOW);
}
void SendMessage(){
  mySerial.println("AT+CMGF+1");// Set SMS mode to text
  delay(1000);
  mySerial.println("AT+CMGS=\"+919481380043\""); // Replace with your recipient's number
  delay(1000);
  mySerial.println("Door opend"); // Message content
  delay(1000);
  mySerial.println((char)26); // End message with Ctrl+Z
  delay(1000); // Delay after sending message
}
void SendMessagetry(){
  mySerial.println("AT+CMGF+1");// Set SMS mode to text
  delay(1000);
  mySerial.println("AT+CMGS=\"+919481380043\""); // Replace with your recipient's number
  delay(1000);
  mySerial.println("Too many attempt"); // Message content
  delay(1000);
  mySerial.println((char)26); // End message with Ctrl+Z
  delay(1000); // Delay after sending message
}


void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(0);
  int val = digitalRead(ldr);
  while(val == 0)
  {
    int val2 = digitalRead(ldr);
    duration += val2;
 
    if(duration == "0001")
    {
      myservo.write(270);
      SendMessage();
      OpenDoor();
      delay(30000);
      myservo.write(0);
      
    }
  
    else if(val2 == 1)
    {
      duration = "";
     attemptCount++;
     if(attemptCount>=maxCount)
     {
        SendMessagetry();
        delay(30000);
        attemptCount=0;
     }
      break;
    }


    delay(200);
  }

}
