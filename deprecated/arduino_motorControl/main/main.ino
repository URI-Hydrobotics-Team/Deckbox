#include <Servo.h>
const int MAX_MESSAGE_LENGTH = 12;
Servo test;


int pos = 0;
char buf[4];

void setup() {
  // put your setup code here, to run once:
      Serial.begin(9600);
       test.attach(9);
}




void loop() {
  //read serial
while (Serial.available() > 0){
   //Create a place to hold the incoming message
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;
   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();
   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
     message[message_pos] = '\0';
     //Print the message (or do other things)
     //Serial.println(message); 
     pos = atoi(message);

     //Reset for the next message
     message_pos = 0;
   }
 }







  
  if (pos > 0){
    Serial.print("working\n");
    test.write(pos);
    delay(15);
  }
  
  Serial.print(pos);
  Serial.println();
}
