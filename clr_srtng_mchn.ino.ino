#include <Wire.h> //I2C/TWI Library
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

int redPin = 13;
int greenPin = 12;
int bluePin = 11;
int red=0;
int green=0;
int blue=0;
int yellow=0;
int orange=0;
int total=0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //I2C pins declaration

Servo topServo;
Servo bottomServo;
int frequency = 0;
int color = 0;
void setup() {
  lcd.begin(16,2); //Defining 16 columns and 2 rows of lcd display
  iniDisplay();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(9);
  bottomServo.attach(10);
  Serial.begin(9600);
}
void loop() {
  topServo.write(14);
  delay(1500);
  topServo.write(44);
  delay(1000);
  
  color = readColor();  
  switch (color) {
    case 1:
    bottomServo.write(50);
    setColor(0,0,255);
    blue++;
    break;
    case 2:
    bottomServo.write(85);
    setColor(200,150,30);
    orange++;
    break;
    case 3:
    bottomServo.write(110);
    setColor(0,255,0);
    green++;
    break;
    case 4:
    bottomServo.write(135);
    setColor(255,255,0);
    yellow++;
    break;
    case 5:
    bottomServo.write(160);
    setColor(255,0,0);
    red++;
    break;
    
    case 0:
    setColor(0,0,0);
    break;
  }
if(color>0)
{
  total=red+green+blue+yellow+orange;
}
  
  color=0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("R=");
  lcd.print(red);
  lcd.setCursor(5,0);
  lcd.print("G=");
  lcd.print(green);
  lcd.setCursor(11,0);
  lcd.print("B=");
  lcd.print(blue);
  lcd.setCursor(0,1);
  lcd.print("O=");
  lcd.print(orange);
  lcd.setCursor(5,1);
  lcd.print("Y=");
  lcd.print(yellow);
  lcd.setCursor(11,1);
  lcd.print("T=");
  lcd.print(total);
  
  topServo.write(80);
  delay(1000);
}

int readColor() {
  int i=0;
  int R=0,G=0,B=0;
  // Setting red filtered photodiodes to be read
  while(i<1000)
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    R += frequency;
    i++;
  }
    i=0;
    R=abs(R/1000);
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(R);//printing RED color frequency
    Serial.print("  ");
    // Setting Green filtered photodiodes to be read
  while(i<1000)
  {
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    G += frequency;
    i++;
  }
    i=0;
    G=abs(G/1000);
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(G);//printing RED color frequency
    Serial.print("  ");
    // Setting Blue filtered photodiodes to be read
  while(i<1000)
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    B += frequency;
    i++;
  }
    B=abs(B/1000);
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(B);//printing RED color frequency
    Serial.println("  ");

  if((R>=14 & R<=18) & (G>=1 & G<=5) & (B>=14 & B<=18)){
    color = 1; // Blue
  }
  else if((R>=22 & R<=25) & (G>=0 & G<=5) & (B>=8 & B<=13)){
    color = 2; // Orange
  }
  else if((R>=16 & R<=20) & (G>=4 & G<=8) & (B>=9 & B<=13)){
    color = 3; // Green
  }
  else if((R>=24 & R<=26) & (G>=7 & G<=13) & (B>=9 & B<=18)){
    color = 4; // Yellow
  }
  else if((R>=17 & R<=22) & (G>=0 & G<=4) & (B>=9 & B<=12)){
    color = 5; // Red
  }
  return color;  
}

void iniDisplay()
{
  lcd.setCursor(5,0); 
  lcd.print(" Team:");
  lcd.setCursor(3,1);
  lcd.print("\"UNIVERSE7\"");
  delay(1500);
  lcd.setCursor(3,0);
  lcd.print("Led By:  ");
  lcd.setCursor(0,1);
  lcd.print("\"MISBAH KHALIL\"");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Team Members:  ");
  lcd.setCursor(0,1);
  lcd.print("\"BILAL-UD-DIN\"");
  delay(1200);
  lcd.setCursor(0,1);
  lcd.print("\"BILAL KHAWAJA\"");
  delay(1200);
  lcd.setCursor(0,1);
  lcd.print("\"NOUMAN EJAZ\"  ");
  delay(1200);
  lcd.clear();
  lcd.noBacklight();
  delay(500);
  lcd.backlight();
  lcd.print("COLOUR SORTING");
  lcd.setCursor(4,1);
  lcd.print("MACHINE");
  delay(2000);
}

void setColor(int red, int green, int blue)
{
 
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
