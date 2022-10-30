///* @file CustomKeypad.pde
//|| @version 1.0
//|| @author Alexander Brevig
//|| @contact alexanderbrevig@gmail.com
//||
//|| @description
//|| | Demonstrates changing the keypad size and key values.
//|| #
//*/
//#include "BigKeypad.h"
////#include <string>
//
//using namespace std;
//
////const byte ROWS = 4; //four rows
////const byte COLS = 4; //four columns
//const byte ROWS = 3; //four rows
//const byte COLS = 3; //four columns
////define the cymbols on the buttons of the keypads
////uint16_t hexaKeys[ROWS][COLS] = {
////  {'AA','BA','CA','DA'},
////  {'AB','BB','CB','DB'},   // There may be a warning mesage for each
////  {'AC','BC','CC','DC'},   // of the multi-char constants.  Ignore them.
////  {'AD','BD','CD','DD'}
////};
//uint16_t hexaKeys[ROWS][COLS] = {
//  {'AA','BA','CA'},
//  {'AB','BB','CB'},   // There may be a warning mesage for each
//  {'AC','BC','CC'}   // of the multi-char constants.  Ignore them.
//};
//// byte rowPins[ROWS] = {5,4,3,2}; //connect to the row pinouts of the keypad
//// byte colPins[COLS] = {9,8,7,6}; //connect to the column pinouts of the keypad
//byte rowPins[ROWS] = {6,4,2}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {7,5,3}; //connect to the column pinouts of the keypad
//
////initialize an instance of class NewKeypad
//BigKeypad customKeypad = BigKeypad( makeIntKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
//
//void setup(){
//  Serial.begin(9600);
//}
//  
//void loop(){
//  uint16_t customKey = customKeypad.getKey();
//  
//  if (customKey){
////    string str1 = char(customKey);
////    string str2 = char(customKey >> 8);
////    str = str1 + str2;
//    char output[3] = {char(customKey >> 8), char(customKey), '\0'};
////    Serial.write(char(customKey));
////    Serial.write(char(customKey >> 8));
//    Serial.write(output);
//  }
//}

/* @file CustomKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates changing the keypad size and key values.
  || #
*/
#include "BigKeypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
//uint16_t hexaKeys[ROWS][COLS] = {
//  {'1a', '2a', '3a', 'a3'},
//  {'4b', '5b', '6b', '3a'}, // There may be a warning mesage for each
//  {'7c', '8c', '9c', '3a'}, // of the multi-char constants.  Ignore them.
//  {'ef', 'cd', 'ab', '3a'}
//};
uint16_t hexaKeys[ROWS][COLS] = {
  {'AA','BA','CA'},
  {'AB','BB','CB'},   // There may be a warning mesage for each
  {'AC','BC','CC'}   // of the multi-char constants.  Ignore them.
};
//byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
byte rowPins[ROWS] = {6,4,2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7,5,3}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
BigKeypad customKeypad = BigKeypad( makeIntKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (customKeypad.getKeys()) {
    for (uint16_t i = 0; i < LIST_MAX; i++) {
      if (customKeypad.key[i].stateChanged) {
        if (customKeypad.key[i].kstate == PRESSED) {
          Serial.write(char(customKeypad.key[i].kchar >> 8));
          Serial.write(char(customKeypad.key[i].kchar));
//          Serial.write('\n'); //newline added for readability in serial monitor
        }
      }
    }
  }
}