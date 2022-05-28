#include <Servo.h>
#include <LiquidCrystal_I2C.h>
Servo servos[13];

LiquidCrystal_I2C lcd(0x27,16,2);
int plazas = 3;

void setup()
{
  pinMode(5,INPUT);
  pinMode(4,OUTPUT);
  servos[6].attach(6);
  pinMode(9,INPUT);
  pinMode(8,OUTPUT);
  servos[10].attach(10);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("+info en:");
  lcd.setCursor(0,1);
  lcd.print("bit.ly/3NzTFre");
  delay(3000);
  lcd.clear();
  delay(500);
  lcd.print("Joaquin");
  lcd.setCursor(0,1);
  lcd.print("Jose Enrique");
  delay(3000);
  lcd.clear();
}

void loop()
{
  if (Distance(4,5) < 5 && plazas > 0)
  {
    servos[6].write(90);
    delay(3000);
    servos[6].write(0);
    delay(500);
    plazas--;
  }
  if (Distance(8,9) < 5 && plazas != 3)
  {
    servos[10].write(90);
    delay(3000);
    servos[10].write(0);
    delay(500);
    plazas++;
  }

  
  if (plazas > 3)
  {
    lcd.clear();
    lcd.print("ERR");
    lcd.setCursor(0,1);
    lcd.print("NumPlazasErroneo");
    delay(1200);
  }
  else if (plazas <= 3)
  {
    lcd.clear();
    lcd.print("Mercadona | J&JE");
    lcd.setCursor(0,1);
    lcd.print("Plazas libres:");
    lcd.setCursor(15,1);
    lcd.print(plazas);
    delay(1200);
  }
}

long TP_init(int trigger_pin, int echo_pin)
{
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  long microseconds = pulseIn(echo_pin ,HIGH);
  return microseconds;
}
long Distance(int trigger_pin, int echo_pin)
{
  long microseconds = TP_init(trigger_pin, echo_pin);
  long distance;
  distance = microseconds/29/2;
  if (distance == 0){
    distance = 999;
  }
  return distance;
}
