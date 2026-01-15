#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gateServo;

int entrySensor = 2;
int exitSensor  = 3;
int totalSlots = 5;
int availableSlots = 5;

void setup() {
  pinMode(entrySensor, INPUT);
  pinMode(exitSensor, INPUT);

  gateServo.attach(9);
  gateServo.write(0);  

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" Smart Parking ");
  delay(2000);
  lcd.clear();
}

void loop() {
  if(digitalRead(entrySensor) == LOW) {
    if(availableSlots > 0) {
      availableSlots--;
      openGate();
      delay(1500);
      closeGate();
    }
    else {
      lcd.setCursor(0,0);
      lcd.print(" Parking Full ");
      delay(2000);
    }
  }
  if(digitalRead(exitSensor) == LOW) {
    if(availableSlots < totalSlots) {
      availableSlots++;
      openGate();
      delay(1500);
      closeGate();
    }
  }


  lcd.setCursor(0,0);
  lcd.print("Slots Available");
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.print(availableSlots);
  delay(500);
}

void openGate() {
  gateServo.write(90);
}

void closeGate() {
  gateServo.write(0);
}
