#include<LiquidCrystal.h>
const byte rs = A4, en = A3, d4 = A2, d5 = A1, d6 = A0, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Buzzer = 3;
int rhL = 9;
int ThermistorPin = A5;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;



#define echo A2
#define trigger A3
long distance;
int level = 20;
int set = 20;

void setup()
{
  pinMode(Buzzer, OUTPUT);
  pinMode(echo, INPUT );
  pinMode(trigger, OUTPUT);

}


void loop(){
 Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0) / 5.0 + 32.0;

lcd.setCursor(0, 0);
  lcd.print("{T:");
  lcd.print(Tf);
  lcd.print(" F");
delay(500);


if (Tf >= 100) {
 lcd.clear(); 
  lcd.print("{T:");
  lcd.print(Tf);
  lcd.print(" F");
    delay(4000);
     SendMessage1();
  } else {
     delay(20);
  }

level = Ultrasonic_read();


}

long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echo, HIGH);
  return distance / 29 / 2;
}


void SendMessage() {
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW); 
  delay(10);
   lcd.clear();
   lcd.print("Massege sending1...");
  Serial.begin(9600);
  Serial.print("\r"); 
  delay(1000);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+8801797526666\"\r"); 
  delay(1000);
  Serial.print("Your Body Temperature/Heart Rate has changed from Your Normal State. Please Take Some Necessary Steps. \r"); 
  delay(1000);
  Serial.write(0x1A);
  delay(1000);
   //makeCall();
}

void SendMessage1() {
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW); 
  delay(10);   
   lcd.clear();
   lcd.print("Massege sending2...");
  Serial.begin(9600);
  Serial.print("\r");
  
  delay(1000);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+8801797526666\"\r");
  delay(1000);
  Serial.print("Your Body Temperature has gone up from Your Normal State. Please Take Some Necessary Steps.  \r"); 
  delay(1000);
  Serial.write(0x1A);
  delay(1000);
   //makeCall();
}

void SendMessage2() {
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW); 
  delay(10);
   
   lcd.clear();
   lcd.print("Massege sending3...");
  Serial.begin(9600); 
  Serial.print("\r");
  
  delay(1000);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+8801797526666\"\r");
  delay(1000);
  Serial.print("Your Heart Rate has gone Down from Your Normal State. Please Take Some Necessary Steps.  \r");
  delay(1000);
  Serial.write(0x1A);
  delay(1000);
   //makeCall();
}

void SendMessage3() {
  
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW); 
  delay(10);
   
   lcd.clear();
   lcd.print("Massege sending4...");
  Serial.begin(9600);
  Serial.print("\r");
  
  delay(1000);
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"+8801797526666\"\r");
  delay(1000);
  Serial.print("Your Heart Rate has gone up from Your Normal State. Please Take Some Necessary Steps.  \r");
  delay(1000);
  Serial.write(0x1A);
  delay(1000);
   //makeCall();
}

void makeCall() {
  Serial.begin(9600); //Baud rate of the GSM/GPRS Module
  Serial.print("Calling...");
  lcd.clear();
   lcd.setCursor(0, 0);
  lcd.print("Calling...");
  delay(1000);
  Serial.println("ATD+8801797526666;"); //Number to which you want to make call
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
