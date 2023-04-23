/*  in this project you'll learn how to use N number of LCD by defining one LCD object 
 *   
 *  to do this, i modified the"LiquidCrystal_I2C" module by: 
 *  
 *  modifiy the declariation of LiquidCrystal_I2C 
 *  
 *  from this : LiquidCrystal_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
 *  
 *  to this   : LiquidCrystal_I2C(uint8_t lcd_cols,uint8_t lcd_rows)
 *  
 *  as you can see i removed lcd address for declaration, but wiat.. i didn't remove it for ever 
 *  
 *  i put the Address parameter in new function declraration, and this it is:
 *  
 *  setAddress(uint8_t new_lcd_Addr),it set lcd address and initialize it.
 *  
 * the last thing is : i removed a delay() function in the class body 
 * 
 */
 
#include <Wire.h>
#include "src/LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(16,2);

byte count = 0; // number of conncted LCD
byte Address[8]; // 8 is the max number of LCD we can connect to I2c bus 

// keypad's pins
byte cols[3] = {8,9,10};
byte rows[4] = {4,5,6,7};

char key = 'n';
const char keys[4][3]= {
            {'1','2','3'},
            {'4','5','6'},
            {'7','8','9'},
            {'*','0','#'}
            };





void setup() {
  
  Serial.begin(9600);
  
//define keypad's pin as OUTPUT & INPUT
  for(byte i = 0; i < 3; i++){
    pinMode(cols[i], OUTPUT);
  }
  for(byte i = 0; i < 4; i++){
    pinMode(rows[i], INPUT);
  }
// initialize keypad pins 
  for(byte i = 0; i < 3; i++){
    digitalWrite(cols[i], LOW);
  }
  
/// scanning.. /// 
  Serial.println("I2C scanner, scaning..");
  Wire.begin();
  for(byte i = 8; i < 120; i++){
    Wire.beginTransmission(i);
    if(Wire.endTransmission() == 0){
      Serial.print("found address:");
      Serial.print(i, DEC);
      Serial.print("  (0x");Serial.print(i,HEX);Serial.println(")");
      count++;
      Address[count-1] = i;
//      delay(1); // may be needed
    }
  }   
   
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count);
  Serial.println (" device(s).");
  for(byte i = 0; i < count; i++){
  Serial.print("0x");Serial.println (Address[i],HEX);
  } 
  
//get conncted screen's info
  lcd.setAddress(Address[0]);
  lcd.setCursor(0,0);
  lcd.print("you have ");lcd.print(count);lcd.print("s lcd");
  delay(1000);
  lcd.clear();
  for(byte i = 0; i <= count -1 ;i++){
    lcd.setAddress(Address[i]);
    lcd.setCursor(0,0);
    lcd.print("screen number "); lcd.print(i+1);
    delay(500);
    lcd.clear();

    }
    
  lcd.setAddress(Address[0]);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("press key to  ");
  lcd.setCursor(0,1);
  lcd.print("select screen");
//  delay(1000);
  while(key == 'n') {key = get_key();}
  lcd.clear();
  
}

void loop() {
// use * key to reselect screen
  if(key == '*'){
    lcd.setAddress(Address[0]);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("press key to  ");
    lcd.setCursor(0,1);
    lcd.print("select screen");
    while(key == '*') {key = get_key();}
    lcd.clear();
  }
  if(int(key - '0') > count & (key != '*' & key != 'n') ){  // key '0' in ascii = 48 , key '1' = 49 ,  and so forth..
    lcd.setCursor(0,0);
    lcd.print("screen not found");
    delay(1000);
    lcd.print("press key agian");
    key = '*';
  }
  else{
    lcd.setAddress(Address[int(key - '0') - 1]);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("i'm selected.");
    lcd.setCursor(0,1);
    lcd.print("hi user");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("press * ");
    lcd.setCursor(0,1);
    lcd.print(" to reselect");
    while(key != '*') {key = get_key();}
    lcd.clear();
  }

}


// func to read keypad click
char get_key(){
  
  for(byte i = 0; i < 3; i++){
    digitalWrite(cols[i], HIGH);
    for(byte j = 0; j < 4; j++){
      if(digitalRead(rows[j])){ key = keys[j][i];}
    }
    digitalWrite(cols[i], LOW);
  }
  return(key);
  
}