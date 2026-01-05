#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,  16, 2);
// includes needed libraries and denotes address and LCD screen size for I2C communication
int second10s = 0;
int second1s = 0;
int minute1s = 0;
int minute10s = 0;
int hour1s = 0;
int hour10s = 0;
int ledtime = 0;
void setup() {
lcd.init();
lcd.backlight();
lcd.setCursor(0,1);
lcd.print("00:00:00");
lcd.setCursor(0,0);
lcd.print("Smartpen V1");
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(12, INPUT_PULLUP);
//sets arduino pins to needed type, initializes time values, and sets up the LCD screen
//the LCD screen is set up via I2C for simplicity, this project doesn't require manually wiring it
}

void loop() {
delay(983);
//this delay is the "clock"; normally it is 1000ms to denote one tick per second. it is 983 to account for the time it takes to execute the entire program per loop
//if it was at 1000, the clock would be ~25 minutes behind at the 24 hour mark (unacceptable) when it will only be ~1 minute behind at 983
if (digitalRead(12) == LOW) {
lcd.setCursor(7,1);
lcd.print(second1s);

lcd.setCursor(2,1);
lcd.print(":");
lcd.setCursor(5,1);
lcd.print(":");
lcd.setCursor(8,1);
lcd.print(" ");
//way to bypass number "spillage"  when the number becomes 2 digits

second1s++;
// each loop, the second variable increases by one. this is the basis for the other increments
if (second1s > 10) {
  second1s = second1s - 10;
  lcd.setCursor(8,1);
  lcd.print(" ");
  lcd.setCursor(7,1);
  lcd.print("0");
  second10s++;
  lcd.setCursor(6,1);
  lcd.print(second10s);

}
if (second10s > 5) {
  second10s = 0;
  lcd.setCursor(6,1);
  lcd.print("0");
  minute1s++;
  lcd.setCursor (4,1);
  lcd.print(minute1s);
}
if (minute1s > 9) {
  minute1s = minute1s - 10;
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(4,1);
  lcd.print("0");
  minute10s++;
  lcd.setCursor(3,1);
  lcd.print(minute10s);
}
if (minute10s > 5) {
  minute10s = 0;
  lcd.setCursor(3,1);
  lcd.print("0");
  hour1s++;
  ledtime++;
  lcd.setCursor(1,1);
  lcd.print(hour1s);
}
if (hour1s > 9) {
  hour1s = hour1s - 10;
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(1,1);
  lcd.print("0");
  hour10s++;
  lcd.setCursor(0,1);
  lcd.print(hour10s);
}
//all simple "if" statements to operate the "digital clock" on the LCD.

//i altered this code a little bit in my physical prototype as the red and yellow LED's (i presume) burned out, should use a resistor with more ohms next time.
//it could also be potentially poor soldering, i would have to look into it. either way, it's okay as the LEDs are only an augment to the timer
if (ledtime < 23) {
  digitalWrite(8, HIGH);

}
if (ledtime >= 23 && ledtime < 25) {
digitalWrite(8, LOW);
digitalWrite(10, HIGH);
}
if  (ledtime >= 25) {
  digitalWrite (10, LOW);
  digitalWrite (9, HIGH);
}
//code to the LED's to signal when you should take your next dose. 
}
else {
lcd.setCursor(0,1);
lcd.print("00:00:00        ");
second10s = 0;
second1s = 0;
minute1s = 0;
minute10s = 0;
hour1s = 0;
hour10s = 0;
ledtime = 0;
digitalWrite(8, LOW);
digitalWrite(9, LOW);
digitalWrite(10, LOW);
//code that resets the time, LEDs, and LCD whenever there is no pen inside
}
}
//old code here from when I was doing some hardware tinkering earlier, I kept it here incase you wanted to see how it orignally started as
//I just moved the entire loop code down here and marked it as a note, starting fresh with a blank loop for the final iteration

//delay(1000);
//lcd.setCursor(0,0);
//lcd.print("hi");
//if (digitalRead(12) == LOW) {
//  lcd.setCursor(0,1);
//  lcd.print(second);
//  second++;
//  if (second>60) {
//    second = second - 60;
//    lcd.setCursor(0,1);
//    lcd.print(second);
//    minute = minute + 1;
//    lcd.setCursor(4,1);
//    lcd.print(minute);
//  }
//}
//else{
//  lcd.setCursor(0,1);
//  lcd.print("                ");
//  second = 0;
//  minute = 0;
//  hour = 0;
//}
//}


//if (digitalRead(12) == LOW) {
//  digitalWrite(8, HIGH);
//  digitalWrite(9, HIGH);
//  digitalWrite(10, HIGH);
//  lcd.setCursor(0,1);
//lcd.print("secret!!!");
//}
//else {
//  digitalWrite(8, LOW);
//  digitalWrite(9, LOW);
//  digitalWrite(10, LOW);
//  lcd.setCursor(0,1);
//lcd.print("         ");
//}


