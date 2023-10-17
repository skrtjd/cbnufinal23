#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MQ131.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//릴레이 모듈
int Relaypin11 = 3;                 // 1번 릴레이의 IN1 
int Relaypin12 = 4;                 // 1번 릴레이의 IN2 
int Relaypin21 = 5;                 // 2번 릴레이의 IN1
int Relaypin22 = 6;                 // 2번 릴레이의 IN2 

//오존 가스 센서
int OzoneAOpin = 8;                 // 오존 가스 센서의 AO
int OzoneDOpin = 17;                // 오존 가스 센서의 DO
//아날로그 핀은 A0~A5가 내부적으로 14~15로 정의되어 있음

//초음파 센서 모듈 트리거와 에코 핀 설정
int trigPin1 = 9;
int echoPin1 = 10;
int trigPin2 = 11;
int echoPin2 = 12;

// 조도센서 핀 설정
int CdSPin = 4;

void setup()
{
  Serial.begin(9600);                //시리얼 속도 설정

	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();

  pinMode(trigPin1, OUTPUT);               // trigPin1 출력
  pinMode(echoPin1, INPUT);                // echoPin1 입력
  pinMode(trigPin2, OUTPUT);               // trigPin2 출력
  pinMode(echoPin2, INPUT);                // echoPin2 입력

  pinMode(CdSPin, INPUT);                  // CdSPin 입력
}

void loop()
{
  long duration1, distance1;
  digitalWrite(trigPin1, HIGH);             // trigPin1에서 초음파 발생(echoPin1도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);       // echoPin1이 이 HIGH를 유지한 시간을 저장한다
  distance1 = ((float)(340*duration1)/1000) / 2;
  // 340은 초음파의 속도로 단위는 m/s
  // duration 값을 세컨드 단위로 변환시키기 위해 1000으로 나눈다.
  // 왕복거리이므로 2로 나눈다

  //Serial.print("Duration1:");
  //Serial.print(duration1);
  //Serial.print("\nDistance1:");
  //Serial.print(distance1);
  //Serial.println("mm\n");

  long duration2, distance2;
  digitalWrite(trigPin2, HIGH);             // trigPin2에서 초음파 발생(echoPin1도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);       // echoPin2이 이 HIGH를 유지한 시간을 저장한다
  distance2 = ((float)(340*duration2)/1000) / 2;    
  
  //Serial.print("Duration2:");
  //Serial.print(duration2);
  //Serial.print("\nDistance2:");
  //Serial.print(distance2);
  //Serial.println("mm\n");

  long disavg = (distance1 + distance2) / 2;       // distance1과 distance2의 평균값

  delay(1000);
  
  // LCD 컨트롤
  lcd.setCursor(0,0); //첫번째 줄의 0번째 부터 출력
  lcd.print("O3 density: ");
  lcd.print("%");
  lcd.print("");
  lcd.print("ppm");

  lcd.setCursor(0,1); //두번째 줄의 0번째 부터 출력
  lcd.print("Active : ");
  if(disavg < 0.5){
    lcd.print("O");
  }
  else{
    lcd.print("X");
  }
  lcd.println(" *C");

  delay(2000);
}
