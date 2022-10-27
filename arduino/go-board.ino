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
//#include <string>

using namespace std;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
uint16_t hexaKeys[ROWS][COLS] = {
  {'AA','BA','CA','DA'},
  {'AB','BB','CB','DB'},   // There may be a warning mesage for each
  {'AC','BC','CC','DC'},   // of the multi-char constants.  Ignore them.
  {'AD','BD','CD','DD'}
};
byte rowPins[ROWS] = {5,4,3,2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9,8,7,6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
BigKeypad customKeypad = BigKeypad( makeIntKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  uint16_t customKey = customKeypad.getKey();
  
  if (customKey){
//    string str1 = char(customKey);
//    string str2 = char(customKey >> 8);
//    str = str1 + str2;
    char output[3] = {char(customKey >> 8), char(customKey), '\0'};
//    Serial.write(char(customKey));
//    Serial.write(char(customKey >> 8));
    Serial.write(output);
  }
}