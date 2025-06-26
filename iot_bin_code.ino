#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int buzzer = 7;
int rl = 5;     // Red LED
int gl = 6;     // Green LED
int ir = 2;     // IR Sensor

const int trigPin = 3;
const int echoPin = 4;

long duration;
int distanceCm;
char gchr;
unsigned char rcv;

// For averaging distance
int dist1 = 0, dista = 0;
int rtr1 = 0;

// Beep function
void beep() {
  digitalWrite(buzzer, LOW);
  delay(1500);
  digitalWrite(buzzer, HIGH);
  delay(200);
}

// Ultrasonic sensor function
unsigned int ultra_dist() {
  int ud = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  ud = distanceCm;
  return ud;
}

void okcheck() {
  unsigned char rcr;
  do {
    rcr = Serial.read();
  } while (rcr != 'K');
}

void setup() {
  Serial.begin(115200);
  serialEvent();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ir, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(rl, OUTPUT);
  pinMode(gl, OUTPUT);

  digitalWrite(buzzer, HIGH);
  digitalWrite(rl, LOW);
  digitalWrite(gl, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("   Welcome to ");
  lcd.setCursor(0, 1);
  lcd.print("  The Project ");
  delay(2000);
  lcd.clear();
  lcd.print("Wifi init");

  Serial.write("AT\r\n");
  delay(500);
  okcheck();
  Serial.write("ATE0\r\n");
  okcheck();
  Serial.write("AT+CWMODE=3\r\n");
  delay(500);
  Serial.write("AT+CIPMUX=1\r\n");
  delay(500);
  okcheck();
  Serial.write("AT+CIPSERVER=1,23\r\n");
  okcheck();

  lcd.clear();
  lcd.print("Waiting For");
  lcd.setCursor(0, 1);
  lcd.print("Connection");

  do {
    rcv = Serial.read();
  } while (rcv != 'C');

  lcd.clear();
  lcd.print("Connected");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("U:"); // Ultrasonic
  lcd.setCursor(0, 1);
  lcd.print("I:"); // IR Sensor
  serialEvent();
}

void loop() {
  dist1 = 0;
  for (rtr1 = 0; rtr1 < 5; rtr1++) {
    dista = ultra_dist();
    dist1 += dista;
    delay(10);
  }

  dist1 = dist1 / 5;
  lcd.setCursor(2, 0);
  convertl(dist1);

  if (dist1 < 10) {
    beep();
    digitalWrite(rl, HIGH);
    digitalWrite(gl, LOW);
    Serial.write("AT+CIPSEND=0,26\r\n");
    delay(2000);
    Serial.write(" Dustbin filled at zone 1 ");
    delay(3000);
  } else {
    digitalWrite(rl, LOW);
    digitalWrite(gl, HIGH);
  }

  if (digitalRead(ir) == LOW) {
    lcd.setCursor(2, 1);
    lcd.print("ON ");
    beep();
    digitalWrite(rl, HIGH);
    digitalWrite(gl, LOW);
    Serial.write("AT+CIPSEND=0,26\r\n");
    delay(2000);
    Serial.write(" Dustbin filled at zone 2 ");
    delay(3000);
  } else {
    lcd.setCursor(2, 1);
    lcd.print("OFF");
    digitalWrite(rl, LOW);
    digitalWrite(gl, HIGH);
  }
}

// Serial event function
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    gchr = inChar;
  }
}

// Function to convert and display value on LCD
void convertl(unsigned int value) {
  unsigned int a, b, c, d, e, f, g, h;

  a = value / 10000;
  b = value % 10000;
  c = b / 1000;
  d = b % 1000;
  e = d / 100;
  f = d % 100;
  g = f / 10;
  h = f % 10;

  a = a | 0x30;
  c = c | 0x30;
  e = e | 0x30;
  g = g | 0x30;
  h = h | 0x30;

  lcd.write(a);
  lcd.write(c);
  lcd.write(e);
  lcd.write(g);
  lcd.write(h);
}
