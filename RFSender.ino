/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

char rfSetting[6]  = "01111";

String command;
void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
}

void loop() {
  if (Serial.available() > 0) {
    // get incoming byte:
    command = Serial.readString();
    command.trim();
    if( command.length() == 2 && 
        command[0] > 64 && command[0] < 69 &&
       (command[1] == '0' | command[1] == '1')){
          char rfCommand[6] = "00000";
          rfCommand[command[0]-65] = '1';
          Serial.println(rfCommand);
          if(command[1] == '0') {
            mySwitch.switchOff(rfSetting, rfCommand);
          } else {
            mySwitch.switchOn(rfSetting, rfCommand);
          }
          delay(1000);
    } else {
      Serial.println("Invalid Input");
    }
  }
}
