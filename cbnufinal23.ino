#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
}

void loop()
{
  lcd.setCursor(0,0); //첫번째 줄의 0번째 부터 출력
  lcd.print("Humidity: ");
  lcd.print("%");

  lcd.setCursor(0,1); //두번째 줄의 0번째 부터 력출
  lcd.print("Temp: ");
  lcd.println(" *C");

  delay(2000);
}
