#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27,16,2);
#define Fire_Sensor 2
#define Vibration_sensor 3
#define Relay 5
#define Buzzer 6
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() 
{
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 pinMode(Fire_Sensor,INPUT);
 pinMode(Vibration_sensor,INPUT);
 pinMode(Relay,OUTPUT);
 pinMode(Buzzer,OUTPUT);
 digitalWrite(Relay ,HIGH);
 digitalWrite(Buzzer ,LOW);
 lcd.init();
 lcd.begin(16,2);
 lcd.backlight();
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("FOREST SECURITY");
 lcd.setCursor(0,1);
 lcd.print("TO SAVE TREES");
 delay(2000);
}

void loop() 
{
  // put your main code here, to run repeatedly:

 digitalWrite(trigPin, LOW);
 delayMicroseconds(2); // Sets the trigPin on HIGH state for 10 micro seconds
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);// Reads the echoPin, returns the sound wave travel time in microseconds
 duration = pulseIn(echoPin, HIGH);// Calculating the distance
 distance= duration*0.034/2;// Prints the distance on the Serial Monitor
 Serial.print("Distance: ");
 Serial.println(distance);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Distance:");
 lcd.setCursor(0,1);
 lcd.print(distance);
 delay(1000);
 
 int Fire_Sensor_state = digitalRead(Fire_Sensor);
 Serial.print("Fire_Sensor:");
 Serial.print(Fire_Sensor_state);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Fire_state:");
 lcd.setCursor(0,1);
 lcd.print(Fire_Sensor_state);
 delay(1000);

 int Vibration_sensor_state = digitalRead(Vibration_sensor);
 Serial.print("Vibration_sensor_state:");
 Serial.print(Vibration_sensor_state);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Vibration_state:");
 lcd.setCursor(0,1);
 lcd.print(Vibration_sensor_state);
 delay(1000);


 if(Fire_Sensor_state == 0)
 {
   digitalWrite(Relay ,LOW);
   digitalWrite(Buzzer ,HIGH);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("FIRE DETECTED");
   SendMessage();
   delay(1000);
 }
 else if(Vibration_sensor_state == 1)
 {
   digitalWrite(Buzzer ,HIGH);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("VIBRATION DETECTED");
   SendMessage1();
   delay(1000);
 }
 
 else
 {
   digitalWrite(Relay ,HIGH);
   digitalWrite(Buzzer ,LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("NORMAL CONDITION");
   delay(1000);
 }
}
void SendMessage()
{
  Serial.println("AT");
  delay(500);
  Serial.println("ATE0");
  delay(500);
  Serial.println("AT + CMGF = 1");
  delay(500);
  Serial.println("AT + CMGS = \"+919133758683\"\r");
  delay(500);
  Serial.println("FIRE DETECTED");
  delay(1000);
  Serial.write(26);
  Serial.println("Message sent..");
  delay(800);
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("MSG SENT");
  delay(1000);
}
void SendMessage1()
{
  Serial.println("AT");
  delay(500);
  Serial.println("ATE0");
  delay(500);
  Serial.println("AT + CMGF = 1");
  delay(500);
  Serial.println("AT + CMGS = \"+919133758683\"\r");
  delay(500);
  Serial.println("VIBRATION DETECTED");
  delay(1000);
  Serial.write(26);
  Serial.println("Message sent..");
  delay(800);
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("MSG SENT");
  delay(1000);
}
