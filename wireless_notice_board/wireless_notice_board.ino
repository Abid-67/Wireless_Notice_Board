#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoftwareSerial SIM900A(9,10);

int len, mark;
String dt;

void setup()
{
  lcd.begin(20,4);
  Serial.begin(9600);
  SIM900A.begin(9600);
  lcd.setCursor(3,0);
  lcd.print("Wireless Notice");
  lcd.setCursor(8,2);
  lcd.print("Board");
  delay(2000);
}

void loop()
{
  if (Serial.available()>0)
  {
    receiveMessage();
  } 
  if (SIM900A.available()>0)
  {
    Serial.write(SIM900A.read());
    dt = SIM900A.readString();
    lcd.clear();
    len = dt.length();
    mark = dt.indexOf('*');
    lcd.print(dt.substring(mark+1,len-2));
    Serial.println(dt.substring(mark+1,len-2));
  }
}

void receiveMessage()
{
  Serial.println("SIM900A received message");
  delay(1000);
  SIM900A.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
}
