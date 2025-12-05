  #include <LiquidCrystal.h>
// 完全沿用你的LCD引脚接法
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// === 完全保留你的引脚定义 ===
const int IR_L = 1;  // 左红外（模拟）
const int IR_R = A2;  // 右红外（模拟）

// LCD更新频率（300ms，数值变化更实时）
const unsigned long UPDATE_INTERVAL = 300;

void setup() {
  lcd.begin(16, 2);  // 16列2行LCD初始化
  lcd.print("IR Sensors: L/R");  // 标题说明
  delay(1000);
  lcd.clear();

  // 初始化传感器引脚（数字/模拟输入均用INPUT模式）
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT_PULLUP);
}

void loop() {
  // 按你的要求读取传感器：左/右模拟，中间数字
  int val_L = digitalRead(IR_L);    // 左：模拟值（0-1023）
  int val_R = digitalRead(IR_R);

  // 定期更新LCD（非阻塞，不卡顿）
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = millis();

    // 第一行：左传感器（模拟值）+ 中间传感器（数字值）
    lcd.setCursor(0, 0);
    lcd.print("L:");
    printPadded(val_L, 4); 

    // 第二行：右传感器（模拟值）
    lcd.setCursor(0, 1);
    lcd.print("R:");
    printPadded(val_R, 4);
    lcd.print("          "); 
  }
}

// 辅助函数：LCD数字占固定4位（不足补空格），避免数值位数变化导致残留
void printPadded(int num, int width) {
  if (num < 10) lcd.print("   ");    // 1位数字补3个空格
  else if (num < 100) lcd.print("  "); // 2位数字补2个空格
  else if (num < 1000) lcd.print(" ");  // 3位数字补1个空格
  lcd.print(num);
}
