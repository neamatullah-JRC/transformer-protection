#include<LiquidCrystal.h>
const byte rs = A4, en = A3, d4 = A2, d5 = A1, d6 = A0, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int load = 4;
int ThermistorPin = A5;
#define echo 2
#define trigger 3
const int buttonPin = 5;

int buttonState;
long distance;
int level = 25;

int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;



void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  pinMode(load, OUTPUT);
  pinMode(echo, INPUT );
  pinMode(trigger, OUTPUT);

}


void loop() {
  digitalWrite(load,HIGH);
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2); 
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0) / 5.0 + 32.0;
Tf = 32.0;
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(Tf);
  lcd.print(" F     ");
 delay(500);
 // level = Ultrasonic_read();
   level = 40;
  
  lcd.setCursor(1, 1);
  lcd.print("oil:");
  lcd.print(level);
  lcd.print(" cm");

 delay(500);
  buttonState = digitalRead(buttonPin);

  if (Tf > 100)
  {
    digitalWrite(load,LOW);
    //SendMessagetemp();
    
  } else if (level < 20)
  {
    digitalWrite(load,LOW);
    //SendMessage0il();
  } else if (buttonState == HIGH)
  {
    digitalWrite(load,LOW );
    //SendMessageshort();
  }
}



long Ultrasonic_read() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echo, HIGH);
  return distance / 29 / 2;
}


void SendMessage0il() {
  lcd.clear();
  lcd.print("Massege sending...");
  Serial.begin(9600);
  Serial.print("\r");
  delay(1000);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+8801920639338\"\r");
  delay(1000);
  Serial.print("[WARNING] Oil level is low\r");
  delay(1000);
  Serial.write(0x1A);
  delay(1000);

}

void SendMessagetemp() {
  lcd.clear();
  lcd.print("Massege sending...");
  Serial.begin(9600);
  Serial.print("\r");
  delay(1000);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+8801920639338\"\r");
  delay(1000);
  Serial.print("[WARNING] Temperature has gone up from Normal State.\r");
  delay(1000);
  Serial.write(0x1A);
  delay(1000);
}

void SendMessageshort() {
  lcd.clear();
  lcd.print("Massege sending...");
  Serial.begin(9600);
  Serial.print("\r");
  delay(1000);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+8801920639338\"\r");
  delay(1000);
  Serial.print("[WARNING] short-circuit alert  \r");
  delay(1000);
  Serial.write(0x1A);
  delay(1000);
}

void makeCall() {
  Serial.begin(9600); //Baud rate of the GSM/GPRS Module
  Serial.print("Calling...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calling...");
  delay(1000);
  Serial.println("ATD+8801920639338;"); //Number to which you want to make call
  delay(10000);
  Serial.println("ATH");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ATH");
  delay(1000);
  Serial.print("finish");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("finish...");
  delay(1000);
}
