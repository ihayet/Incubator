#include <LiquidCrystal.h>
#include <DHT.h>

#define BRIGHTNESS 11

#define DHTPIN A0
#define DHTTYPE DHT11

#define LED1 6
#define LED2 5

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

#define BUZZER 16

#define FAN1 18
#define FAN2 17
#define LIGHT 19

LiquidCrystal lcd(9, 10, 12, 13, 8, 7);

DHT dht(DHTPIN, DHTTYPE);

float temperature, humidity;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(BRIGHTNESS, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(FAN1, OUTPUT);
  pinMode(FAN2, OUTPUT);
  pinMode(LIGHT, OUTPUT);

  lcd.begin(16, 2);
  dht.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  lcd.setCursor(0, 0);
  lcd.print("Temp.: ");
  lcd.print(temperature);
  lcd.print(" *C");
  lcd.setCursor(0, 1);
  lcd.print("Hum.: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (digitalRead(BUTTON1) == HIGH)
  {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);

    digitalWrite(FAN1, LOW);
    digitalWrite(FAN2, LOW);
    digitalWrite(LIGHT, LOW);

    digitalWrite(BRIGHTNESS, HIGH);
    
    Serial.println("ON");
  }
  else if (digitalRead(BUTTON2) == HIGH)
  {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);

    digitalWrite(FAN1, HIGH);
    digitalWrite(FAN2, HIGH);
    digitalWrite(LIGHT, HIGH);

    digitalWrite(BRIGHTNESS, HIGH);
  }
  else if (digitalRead(BUTTON3) == HIGH)
  {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);

    digitalWrite(FAN1, LOW);
    digitalWrite(FAN2, LOW);
    digitalWrite(LIGHT, HIGH);

    digitalWrite(BRIGHTNESS, HIGH);
  }
}
