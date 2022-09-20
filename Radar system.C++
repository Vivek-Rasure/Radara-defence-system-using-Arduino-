#include <Servo.h>
#include<LiquidCrystal.h>

Servo myservo;
Servo  las;
LiquidCrystal lcd(0, 1, 8, 9, 10, 11);
const int trigPin = 13;
const int echoPin = 12;
int laser = 6;
int d;
float duration;
float distance=0; 
float i;
float x=0, o, b;

void setup()
{ myservo.attach(3);
  las.attach(4);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(laser, OUTPUT);
  d = 30;
}

void loop()
{
  for (int i = 0; i <= 130; i += 5)
  { distance=0;
    myservo.write(i);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance <= d)
    { 
      lcd.setCursor(0,0);
      lcd.print("Distance:");
      lcd.print(distance);
      delay(10);
      lcd.setCursor(0, 1);
      lcd.print("Angle is ");
      lcd.print(i);
      lcd.print("deg");
      delay(2000);

      if (i < 65)
      {
        o = sin((3.14 * (i + 35)) / 180) * distance;
        b = sqrt((distance * distance) - (o * o));
        x = atan(o / (22.8 + b));
        x = x * 180 / 3.14;

      }
      else if (i > 65)
      {
        o = sin((3.14 * (180 - (i + 35))) / 180) * distance;


        b = sqrt((distance * distance) - (o * o));

        if (b < 22.8)
        {
          x = atan(o / (22.8 - b));

          x = x * 180 / 3.14;

        }
        else if (b > 22.8)
        {
          x = atan(o / (b - 22.8));
          x = x * 180 / 3.14;

          x = 180 - x;
        }
      }

      las.write(x);
      
       digitalWrite(laser, HIGH);

      delay(2500);
      digitalWrite(laser, LOW);
     
    }
    else
    {
      Serial.println("Not detected");
      delay(500);
      Serial.println("");
    }

  }
  for (i = 130; i >= 0; i -= 5)
  {
    myservo.write(i);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
   
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < d)
    { lcd.setCursor(0,0);
      lcd.print("Distance:");
      lcd.print(distance);
      delay(10);
      lcd.setCursor(0, 1);
      lcd.print("Angle is ");
      lcd.print(i);
      delay(2000);

      
      if (i > 65)
      {
        o = sin((3.14 * (180 - (i + 35))) / 180) * distance;


        b = sqrt((distance * distance) - (o * o));
         if (b > 22.8)
        {
          x = atan(o / (b - 22.8));
          x = x * 180 / 3.14;


          x = 180 - x;
        }
        else if (b < 22.8)
        {
          x = atan(o / (22.8 - b));

          x = x * 180 / 3.14;

        }
        
      }
     else if (i < 65)
      {
        o = sin((3.14 * (i + 35)) / 180) * distance;
        b = sqrt((distance * distance) - (o * o));
        x = atan(o / (22.8 + b));
        x = x * 180 / 3.14;

      }

      las.write(x);
      Serial.print("distance is");
      Serial.print(distance);
      Serial.println("cm");
      Serial.print("angle is ");
      Serial.println(i);
      Serial.println("");

      digitalWrite(laser, HIGH);
      delay(2500);
      digitalWrite(laser, LOW);
    }
    else
    {
      Serial.println("Not detected");
      delay(500);
      Serial.println("");
    }
   }
}
