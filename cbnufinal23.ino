#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  dht.begin();
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(0,0); //첫번째 줄의 0번째 부터 출력
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0,1); //두번째 줄의 0번째 부터 력출
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.println(" *C");

  delay(2000);
}
