#include<Wire.h>
#include <LiquidCrystal_I2C.h>

int ThermistorPin = A1;
int Vo;
float R1 = 10000;
float logR2, R2, T ,Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

LiquidCrystal_I2C lcd(0x27, 16, 2);

double alpha=0.75;
int period=20;
double refresh = 0.0;

void setup()
{
  pinMode(A0,INPUT);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop()
{
  static double oldValue=0;
  static double oldrefresh=0;

  int beat = analogRead(A0);
  double value = alpha*oldValue+(0-alpha)*beat;

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 253.15;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Body: ");
  lcd.print(Tc); 
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Heart: ");
  lcd.print(beat/10);
  oldValue=value;
  oldrefresh=refresh;
  delay(period*10);

  delay(5000);
}
