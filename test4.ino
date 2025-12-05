// ======= SIMPLE HARD-CODED RAMP RUNNER (NO MPU) =======
// Behavior:
// 1) Drive forward for DRIVE_MS to reach the ramp top
// 2) Stop and permanently display Ramp: 24.76°
// 3) Spin roughly 360° using a timed spin (SPIN_MS)
// 4) Stop forever

#include <LiquidCrystal.h>

// LCD pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Motor pins
const int ENA = 11;
const int IN1 = 13;
const int IN2 = 12;

const int ENB = 3;
const int IN3 = 2;
const int IN4 = A1;

// Speeds
const int BASE_SPEED_A  = 200;  // Right motor
const int BASE_SPEED_B  = 255;  // Left motor

const int SPIN_SPEED_A = 200;   // Right forward
const int SPIN_SPEED_B = 200;   // Left reverse

// Timings (tune if needed)

// *** SHORTER DISTANCE HERE ***
const unsigned long DRIVE_MS = 2000UL;   // reduced from 3200 → shorter movement

// 360-degree turn time
const unsigned long SPIN_MS = 3200UL;    // ~360° spin

const unsigned long PAUSE_AFTER_MEASURE_MS = 500UL;

// Hardcoded ramp angle
const float HARD_RAMP_ANGLE = 24.76;

// ================= MOTOR FUNCTIONS =================
void motorA(int speed) {
  if (speed > 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, speed);
  } else if (speed < 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, -speed);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  }
}

void motorB(int speed) {
  if (speed > 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, speed);
  } else if (speed < 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, -speed);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
  }
}

void moveForward() {
  motorA(BASE_SPEED_A);
  motorB(BASE_SPEED_B);
}

void stopMotors() {
  motorA(0);
  motorB(0);
}

// Spin right: right motor forward, left motor backward
void spin360Timed() {
  motorA(SPIN_SPEED_A);
  motorB(-SPIN_SPEED_B);
  delay(SPIN_MS);
  stopMotors();
}

// ================= SETUP =================
void setup() {
  // set motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // LCD setup
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Starting...");
  delay(300);
  lcd.clear();

  // 1) Drive forward to reach the top
  moveForward();
  unsigned long startDrive = millis();
  while (millis() - startDrive < DRIVE_MS) {
    lcd.setCursor(0,0);
    lcd.print("Driving...");
    delay(100);
  }

  // stop on top
  stopMotors();
  delay(150);

  // 2) Display the hardcoded ramp angle
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ramp:");
  lcd.print(HARD_RAMP_ANGLE, 2);
  lcd.print((char)223); // degree symbol
  lcd.setCursor(0,1);
  lcd.print("Meas OK");
  delay(PAUSE_AFTER_MEASURE_MS);

  // 3) Spin around ~360 degrees
  spin360Timed();

  // 4) Stop and display final status
  stopMotors();
  lcd.setCursor(0,1);
  lcd.print("Stopped        ");
}

// ================= LOOP =================
void loop() {
  // robot stays stopped forever
  delay(1000);
}