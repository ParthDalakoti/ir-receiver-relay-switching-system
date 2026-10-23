#include <IRremote.hpp> 
 
#define IR_RECEIVE_PIN 2      // IR receiver ka signal pin 
#define RELAY_PIN      8      // Relay/LED connect is pin pe 
#define LED_PIN        LED_BUILTIN  // Built-in LED bhi toggle kar sakta hai testing ke liye 
 
bool relayState = false;  // shuru mein off (false) 
 
void setup() { 
  Serial.begin(115200); 
  Serial.println("IR Remote Relay/LED Control Started"); 
  Serial.println("OK button (206) press karo to toggle ON/OFF"); 
 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Receiver start + LED 
blink feedback 
 
  pinMode(RELAY_PIN, OUTPUT); 
  pinMode(LED_PIN, OUTPUT); 
   
  digitalWrite(RELAY_PIN, HIGH);   // Shuru mein relay OFF (agar active LOW hai) 
  digitalWrite(LED_PIN, LOW);      // Built-in LED off 
} 
 
void loop() { 
  if (IrReceiver.decode()) { 
     
    // Repeat code ignore (button hold karne pe aata hai) 
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) { 
       
      uint16_t command = IrReceiver.decodedIRData.command;  // Yeh decimal command hai 
       
      Serial.print("Received Command (decimal): "); 
      Serial.println(command); 
       
      if (command == 206) {  // Tera OK button ka code 
        relayState = !relayState;  // Toggle state (true/false) 
         
        if (relayState) { 
          digitalWrite(RELAY_PIN, LOW);   // Relay ON (active LOW ke liye) 
          digitalWrite(LED_PIN, HIGH); 
          Serial.println("OK Pressed -> LED/Relay ON"); 
        } else { 
          digitalWrite(RELAY_PIN, HIGH);  // Relay OFF 
          digitalWrite(LED_PIN, LOW); 
          Serial.println("OK Pressed -> LED/Relay OFF"); 

        } 
      } 
      // Agar aur buttons add karna hai to yahan else if laga dena 
    } 
     
    IrReceiver.resume();  // Agle signal ke liye ready 
  } 
} 
 
 
COMMAND OF REMOTE BUTTON  
 
OK - 206 
1-146 
2-147 
3-204 
4-142 
5-143 
0-135 
 
 
HOW TO FIND COMMAND OF ANY REMOTE USING IR RECEIVER AND ARDUINO 
CODE 
 
#include <IRremote.hpp> 
 
#define IR_RECEIVE_PIN 2   // Apna IR receiver pin yahan daal (2, 7, 11 kuch bhi) 
 
void setup() { 
  Serial.begin(115200); 
  Serial.println("IR Remote Button Decoder - Decimal Command Mode"); 
  Serial.println("Button daba, Command number (decimal) dikhega..."); 
   
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // LED blink karega jab 
signal aaye 
} 
 
void loop() { 
  if (IrReceiver.decode()) { 
     
    // Repeat ignore karo (hold karne pe aata hai) 
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) { 
       
      // Protocol bata do (NEC, Sony etc.) 
      Serial.print("Protocol: "); 
      switch (IrReceiver.decodedIRData.protocol) { 
        case NEC:     Serial.print("NEC"); break; 
        case SONY:    Serial.print("SONY"); break; 

        case RC5:     Serial.print("RC5"); break; 
        case RC6:     Serial.print("RC6"); break; 
        // aur bhi add kar sakta hai agar zarurat pade 
        default:      Serial.print("Unknown ("); Serial.print(IrReceiver.decodedIRData.protocol); 
Serial.print(")"); break; 
      } 
       
      // Address (remote ka group code) - decimal mein 
      Serial.print(" | Address: "); 
      Serial.print(IrReceiver.decodedIRData.address);   // Yeh decimal mein print hoga 
       
      // Command (button ka number) - decimal mein 
      Serial.print(" | Button Command (decimal): "); 
      Serial.print(IrReceiver.decodedIRData.command);   // Yeh tera main chahiye wala 
number hai! 
       
      // Extra info agar chahiye 
      Serial.print(" | Raw Data (hex): 0x"); 
      Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX); 
       
      Serial.println();  // Naya line 
    } 
     
    IrReceiver.resume();  // Agle signal ke liye ready 
  } 
}