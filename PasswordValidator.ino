#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
const int rs=12, en=11,d4=5, d5=4,d6=3,d7=2,ct=9;
String password = "ABC123";
String enteredPassword = ""; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, 10, 9, 8};
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  analogWrite(ct,50);
  lcd_1.begin(16, 2); 
  lcd_1.setCursor(0, 0);
  lcd_1.print("Input Password: ");
  pinMode(6,OUTPUT); // LED
  pinMode(7,OUTPUT); // Buzzer
}

void loop()
{
  if (enteredPassword.length() < 6) {
    char customKey = customKeypad.getKey();
    if (customKey) {
      lcd_1.setCursor(enteredPassword.length(), 1); 
      lcd_1.print(customKey);
      enteredPassword += customKey;
    }
  }
  else {
    // Compare enteredPassword with predefined password
    if (enteredPassword.equals(password)) {
      lcd_1.clear();
      lcd_1.setCursor(0, 1);
      lcd_1.println("Access Granted");
      digitalWrite(6, HIGH);
      delay(1000);
      digitalWrite(6, LOW);
    } 
    else {
      lcd_1.clear();
      lcd_1.setCursor(0, 1);
      lcd_1.println("Access Denied");
      tone(7, 1000);
      delay(1000);
      noTone(7);
    }
    // Reset enteredPassword for the next entry
    enteredPassword = "";
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Input Password: ");
  }
}
